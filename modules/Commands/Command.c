#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "Command.h"
#include "Command_Func.h"
#include "Command_Defconfig.h"

Status_t printcmd(const char *format, ...);
static Status_t Parse_Line(char *Line, uint32 *argc, uint32 MaxArguments, char *argv[]);

/*******************************************************************************
* Function pointers defines
*******************************************************************************/
Status_t (*putscmd)(const char *) = NULL;

/*******************************************************************************
* Function for get start address of command section
*******************************************************************************/
static inline Cmd_Tbl_t *Get_Cmd_Section_Begin(void)
{
  return __section_begin(".cmd");
}

/*******************************************************************************
* Function for get end address of command section
*******************************************************************************/
static inline Cmd_Tbl_t *Get_Cmd_Section_End(void)
{
  return __section_end(".cmd");
}

/*******************************************************************************
* Function for get size on command section
*******************************************************************************/
static inline uint32 Get_Cmd_Section_Size(void)
{
  return __section_size(".cmd");
}

/*******************************************************************************
* Function for find command table entry for a command
*******************************************************************************/
static Status_t Find_Cmd(const char *Cmd, Cmd_Tbl_t **Cmd_Tbl_p)
{
  FUNCTION_IN(FIND_CMD);
  Cmd_Tbl_t *Cmd_Section_Begin = Get_Cmd_Section_Begin();
  Cmd_Tbl_t *Cmd_Section_End = Get_Cmd_Section_End();
  Cmd_Tbl_t *Cmd_Tbl;
  Cmd_Tbl_t *Cmd_Tbl_Temp;
  int Len;
  int N_Found = 0;
  
  if((Cmd == NULL) || (Cmd_Tbl_p == NULL))
    FATAL_ABORT(-CMD_INVALID_INPUT_POINTER, FIND_CMD);
  
  Len = strlen(Cmd);
  
  for(Cmd_Tbl = Cmd_Section_Begin; Cmd_Tbl != Cmd_Section_End; Cmd_Tbl++)
  {
    if(strncmp(Cmd, Cmd_Tbl -> Name, Len) == 0)
    {
      if (Len == strlen(Cmd_Tbl -> Name))
      {
        *Cmd_Tbl_p = Cmd_Tbl;   // Full match
        FUNC_EXIT(CMD_SUCCESS, FIND_CMD);
      }
      
      Cmd_Tbl_Temp = Cmd_Tbl;
      N_Found++;
    }
  } // for
  
  if(N_Found == 1)
  {
    *Cmd_Tbl_p = Cmd_Tbl_Temp;
    FUNC_EXIT(CMD_POSSIBLE_CMD, FIND_CMD);
  }
  
  FUNC_EXIT(CMD_NOT_FOUND, FIND_CMD);
}

/*******************************************************************************
* Function for run command
*******************************************************************************/
Status_t Run_Command(const char *Cmd)
{
  FUNCTION_IN(RUN_COMMAND);
  Status_t Status;
  char *CmdStr;
  Cmd_Tbl_t *Cmd_Tbl;
  char CmdBuffer[CMD_BUFFER_SIZE] = {0};
  uint32 argc = 0;
  char *argv[CFG_MAX_ARGUMENTS];
  
  strcpy(CmdBuffer, Cmd);
  
  if((Cmd == NULL))
    FATAL_ABORT(-CMD_INVALID_INPUT_POINTER, RUN_COMMAND);

  // Extract first word from line. That will be the command word.
  CmdStr = strtok(CmdBuffer, " ");
  
  if(CmdStr != 0)
  {
    Status = Find_Cmd(CmdStr, &Cmd_Tbl);
    if(Status < CMD_SUCCESS)
      FATAL_ABORT(Status, RUN_COMMAND);
  }
  else
    FUNC_EXIT(CMD_EMPTY_COMMAND, RUN_COMMAND);

  switch(Status)
  {
    case CMD_SUCCESS:
      
      Status = Parse_Line(CmdBuffer, &argc, Cmd_Tbl->MaxArgs, argv);
      if(Status < 0)
        FATAL_ABORT(Status, RUN_COMMAND);
      else if(Status == CMD_TOO_MANY_ARGUMENTS)
      {
        printcmd("Usage:\n%s\n", Cmd_Tbl->Usage);
        break;
      }
      
      // Run Command
      Status = (Cmd_Tbl->Cmd)(Cmd_Tbl, NULL, argc, argv);
      if(Status != CMD_SUCCESS)
        FUNC_EXIT(CMD_NOT_EXECUTED, RUN_COMMAND);
      break;
    case CMD_POSSIBLE_CMD:
      printcmd("Did you mean: %s\n", Cmd_Tbl->Name);
      break;
    case CMD_NOT_FOUND:
      printcmd("Command '%s' not found! Try 'help'", CmdStr);
      break;
    default:
      break;
  }

  FUNC_EXIT(CMD_SUCCESS, RUN_COMMAND);
}

/*******************************************************************************
* Function for printing back to standard output which calling commands
*******************************************************************************/
Status_t printcmd(const char *format, ...)
{
  FUNCTION_IN(PRINTCMD);
  Status_t Status = CMD_GENERAL_ERROR;
  char VsBuffer[CMD_BUFFER_SIZE] = {0};
  va_list args;
  
  va_start(args, format);
  vsprintf(VsBuffer, format, args);
  
  if(putscmd != NULL)
    Status = putscmd(VsBuffer);
  else
    FATAL_ABORT(CMD_INVALID_FUNCTION_POINTER, PRINTCMD);
  
  if(Status < CMD_SUCCESS)
    FATAL_ABORT(Status, PRINTCMD);

  va_end(args);

  FUNC_EXIT(CMD_SUCCESS, PRINTCMD);
}

/*******************************************************************************
* Function for parsing arguments on one line
*******************************************************************************/
static Status_t Parse_Line(char *Line, uint32 *argc, uint32 MaxArguments, char *argv[])
{
  FUNCTION_IN(PARSE_LINE);
  
  // Eliminate command word
  strtok(Line, " ");
  
  // Count and copy the arguments
  for(*argc = 0; (argv[*argc] != NULL) && (*argc < MaxArguments) && (*argc < CFG_MAX_ARGUMENTS); (*argc)++)
    argv[*argc] = strtok(NULL, " ");
  
  if(*argc == CFG_MAX_ARGUMENTS)
    FATAL_ABORT(CMD_ILEGAL_COMMAND_PARAMETER, PARSE_LINE);
  
  if(*argc == MaxArguments)
    FUNC_EXIT(CMD_TOO_MANY_ARGUMENTS, PARSE_LINE);
  
  FUNC_EXIT(CMD_SUCCESS, PARSE_LINE);
}
