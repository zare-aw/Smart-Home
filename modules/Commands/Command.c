#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Command_Defconfig.h"
#include "StatusHandling.h"

Status_t printcmd(const char *format, ...);
static Status_t Parse_Line(char *Line, uint32 *argc, uint32 MaxArguments, char *argv[]);

/*******************************************************************************
* Function pointers defines
*******************************************************************************/
Status_t (*putscmd)(const char *) = NULL;

/*******************************************************************************
* Function for get start address of command section
*******************************************************************************/
inline Cmd_Tbl_t *Get_Cmd_Section_Begin(void)
{
  return __section_begin(".cmd");
}

/*******************************************************************************
* Function for get end address of command section
*******************************************************************************/
inline Cmd_Tbl_t *Get_Cmd_Section_End(void)
{
  return __section_end(".cmd");
}

/*******************************************************************************
* Function for get size on command section
*******************************************************************************/
uint32 Get_Cmd_Section_Size(void)
{
  return __section_size(".cmd");
}

/*******************************************************************************
* Function for find command table entry for a command
* @in *Cmd - Char pointer with command string
* @out **Cmd_Tbl_p - Double pointer for returning Cmd_Tbl structire of the CMD
* @out Status_t - Status
*******************************************************************************/
Status_t Find_Cmd(const char *Cmd, Cmd_Tbl_t **Cmd_Tbl_p)
{
  FuncIN(FIND_CMD);
  
  Cmd_Tbl_t *Cmd_Section_Begin = Get_Cmd_Section_Begin();
  Cmd_Tbl_t *Cmd_Section_End = Get_Cmd_Section_End();
  Cmd_Tbl_t *Cmd_Tbl;
  Cmd_Tbl_t *Cmd_Tbl_Temp;
  int Len;
  int N_Found = 0;
  
  ASSERT((Cmd != NULL) && (Cmd_Tbl_p != NULL), -INVALID_INPUT_POINTER);
  
  Len = strlen(Cmd);
  
  for(Cmd_Tbl = Cmd_Section_Begin; Cmd_Tbl != Cmd_Section_End; Cmd_Tbl++)
  {
    if(strncmp(Cmd, Cmd_Tbl -> Name, Len) == 0)
    {
      if (Len == strlen(Cmd_Tbl -> Name))
      {
        *Cmd_Tbl_p = Cmd_Tbl;   // Full match
        EXIT_SUCCESS_FUNC(FIND_CMD);
      }
      
      Cmd_Tbl_Temp = Cmd_Tbl;
      N_Found++;
    }
  } // for
  
  if(N_Found == 1)
  {
    *Cmd_Tbl_p = Cmd_Tbl_Temp;
    EXIT_FUNC(CMD_POSSIBLE_CMD, FIND_CMD);
  }
  
  EXIT_FUNC(CMD_NOT_FOUND, FIND_CMD);
}
FUNC_REGISTER(FIND_CMD, Find_Cmd);

/*******************************************************************************
* Function for run command
* @in *Cmd - Pointer to command string together with all arguments
* @out Status_t - Status of execution of the requested command
*******************************************************************************/
Status_t Run_Command(const char *Cmd)
{
  FuncIN(RUN_COMMAND);
  
  Status_t Status = GENERAL_ERROR;
  Status_t FindCmd_Status = GENERAL_ERROR;
  char *CmdStr;
  Cmd_Tbl_t *Cmd_Tbl_p;
  char CmdBuffer[CMD_BUFFER_SIZE] = {0};
  uint32 argc = 0;
  char *argv[CFG_MAX_ARGUMENTS];
  
  strcpy(CmdBuffer, Cmd);
  
  ASSERT((Cmd != NULL), -INVALID_INPUT_POINTER);

  // Extract first word from line. That will be the command word.
  CmdStr = strtok(CmdBuffer, " ");
  
  if(CmdStr != 0)
  {
    FindCmd_Status = Find_Cmd(CmdStr, &Cmd_Tbl_p);
    VERIFY(FindCmd_Status, FindCmd_Status);
  }
  else
    EXIT_FUNC(CMD_EMPTY_COMMAND, RUN_COMMAND);

  switch(FindCmd_Status)
  {
    case SUCCESS:
      strcpy(CmdBuffer, Cmd);
      Status = Parse_Line(CmdBuffer, &argc, Cmd_Tbl_p->MaxArgs, argv);
      
      VERIFY(Status, Status);
      
      if(Status > SUCCESS)
      {
        printcmd("Too many arguments!\n");
        printcmd("Usage:\n%s\n", Cmd_Tbl_p->Usage);
        break;
      }
      
      // Run Command
      Status = (Cmd_Tbl_p->Cmd)(Cmd_Tbl_p, NULL, argc, argv);
      if(Status != SUCCESS)
      {
        switch(Status)
        {
          case CMD_INVALID_ARGUMENT:
            printcmd("Invalid argument!\n");
            printcmd("Usage:\n%s\n", Cmd_Tbl_p->Usage);
            break;
          case CMD_MISSING_ARGUMENT:
            printcmd("Missing argument!\n");
            printcmd("Usage:\n%s\n", Cmd_Tbl_p->Usage);
            break;
          default:
            printcmd("Unknown error!\n");
            printcmd("Usage:\n%s\n", Cmd_Tbl_p->Usage);
            break;
        }
        
        EXIT_FUNC(CMD_NOT_EXECUTED, RUN_COMMAND);
      }
      break;
    case CMD_POSSIBLE_CMD:
      printcmd("Did you mean: %s\n", Cmd_Tbl_p->Name);
      break;
    case CMD_NOT_FOUND:
      printcmd("Command '%s' not found! Try 'help'", CmdStr);
      break;
    default:
      break;
  } // sitch(FindCmd_Status)

  EXIT_SUCCESS_FUNC(RUN_COMMAND);
}
FUNC_REGISTER(RUN_COMMAND, Run_Command);

/*******************************************************************************
* Function for printing back to standard output which calling commands
* @in format - String for printing together with all formating characters
* @in ... - Aditional parameters
* @out Status_t - Status
*      SUCCESS                      - Successfully printed input string.
*      CMD_INVALID_FUNCTION_POINTER - Function pointer for return printing
*                                     function is NULL. This function pointer
*                                     should be initialized before use.
*                                     That is done in 'Commands_Init' function.
*      Status                       - Other status returned from other function.
*******************************************************************************/
Status_t printcmd(const char *format, ...)
{
  FuncIN(PRINTCMD);
  
  Status_t Status = GENERAL_ERROR;
  char VsBuffer[CMD_BUFFER_SIZE] = {0};
  va_list args;
  
  va_start(args, format);
  vsprintf(VsBuffer, format, args);
  
  ASSERT(putscmd != NULL, -CMD_INVALID_FUNCTION_POINTER);
  
  Status = putscmd(VsBuffer);
  
  VERIFY(Status, Status);

  va_end(args);

  EXIT_SUCCESS_FUNC(PRINTCMD);
}
FUNC_REGISTER(PRINTCMD, printcmd);

/*******************************************************************************
* Function for parsing arguments on one line
* @in *Line - Char pointer to the string. Function is modify this string!!!
* @out *argc - Pointer to uint32 where this function is writing back
*              number of arguments
* @in MaxArguments - Maximum number of arguments for current command
* @out *argv[] - list of char pointers to the arguments
* @out Status_t - Status
*      SUCCESS                       - line is parsed successfully
*      CMD_TOO_MANY_ARGUMENTS        - Too many input arguments in input line
*      CMD_ILEGAL_COMMAND_PARAMETERS - The command itself is with
*                                      wrong arguments.
*******************************************************************************/
static Status_t Parse_Line(char *Line, uint32 *argc, uint32 MaxArguments, char *argv[])
{
  FuncIN(PARSE_LINE);
  
  // Eliminate command word
  strtok(Line, " ");
  
  // Count and copy the arguments
  for(*argc = 0; (*argc < (MaxArguments + 1)) && (*argc < CFG_MAX_ARGUMENTS); (*argc)++)
  {
    argv[*argc] = strtok(NULL, " ");
    if(argv[*argc] == NULL)
      break;
    else
      if(*argc == MaxArguments)
        EXIT_FUNC(CMD_TOO_MANY_ARGUMENTS, PARSE_LINE);
  }
  
  ASSERT(*argc < CFG_MAX_ARGUMENTS, -CMD_ILEGAL_COMMAND_PARAMETER);
  
  if(*argc > MaxArguments)
    EXIT_FUNC(CMD_TOO_MANY_ARGUMENTS, PARSE_LINE);
  
  EXIT_SUCCESS_FUNC(PARSE_LINE);
}
FUNC_REGISTER(PARSE_LINE, Parse_Line);

/*******************************************************************************
* Function for parsing arguments on one line
* @in *Cmd_Init_Parameters_p - Structure pointer with needed function pointers
* @out Status_t - Status
*      SUCCESS - Commands server successfully initialized!
*******************************************************************************/
Status_t Commands_Init(Cmd_Init_Parameters_t *Cmd_Init_Parameters_p)
{
  FuncIN(COMMANDS_INIT);
  
  putscmd = Cmd_Init_Parameters_p->putscmd;
  
  EXIT_SUCCESS_FUNC(COMMANDS_INIT);
}
FUNC_REGISTER(COMMANDS_INIT, Commands_Init);
