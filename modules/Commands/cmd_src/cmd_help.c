#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Command_Debug.h"

Status_t Do_Help(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FUNCTION_IN(DO_HELP);
  Status_t Status = CMD_GENERAL_ERROR; 
  
  if(argc > Cmd_Tbl->MaxArgs)
    FATAL_ABORT(-CMD_INVALID_INPUT_PARAMETER, DO_HELP);
  
  if(argc == 0)
  {
    Cmd_Tbl_t *Cmd_Tbl_p = Get_Cmd_Section_Begin();
    Cmd_Tbl_t *Cmd_Tbl_End_p = Get_Cmd_Section_End();
    
    printcmd("\n # Smart Home system console\n");
    printcmd(" # Supported commands:\n");
    
    while(Cmd_Tbl_p != Cmd_Tbl_End_p)
    {
      if(Cmd_Tbl_p->Name == NULL)
        FATAL_ABORT(-CMD_ILEGAL_COMMAND_PARAMETER, DO_HELP);
      
      if(Cmd_Tbl_p->Usage == NULL)
        printcmd(" - %s, Usage: No usage details\n", Cmd_Tbl_p->Name);
      else
        printcmd(" - %s, Usage: %s\n", Cmd_Tbl_p->Name, Cmd_Tbl_p->Usage);
      
      Cmd_Tbl_p++;
    }
    
    printcmd("\n");
  } // if(argc == 0)
  else
  {
    Cmd_Tbl_t *Cmd_Tbl_p;
    Status = Find_Cmd(argv[0], &Cmd_Tbl_p);
    if(Status < CMD_SUCCESS)
      FATAL_ABORT(Status, DO_HELP);
    
    switch(Status)
    {
      case CMD_SUCCESS:
#ifdef CFG_HELP
        printcmd("%s\nUsage:\n%s\nHelp:\n%s\n\n", Cmd_Tbl_p->Name, Cmd_Tbl_p->Usage, Cmd_Tbl_p->Help);
#else
        printcmd("%s\nUsage:\n%s\n\n", Cmd_Tbl_p->Name, Cmd_Tbl_p->Usage);
#endif
        break;
      case CMD_POSSIBLE_CMD:
        printcmd("Did you mean: help %s\n", Cmd_Tbl_p->Name);
        break;
      case CMD_NOT_FOUND:
        printcmd("Command '%s' not found! Try 'help'", argv[0]);
        break;
      default:
        break;
    } // sitch(Status) 
  } // else
  
  FUNC_EXIT(CMD_SUCCESS, DO_HELP);
}

CMD_CREATE(
  help, 1, Do_Help,
  "help - print help\n",
  "help 'command' - show usage and help information (for 'command').\n"
  "Without arguments, it prints a short usage message for all commands.\n\n"
  "To get detailed help information for specific commands you can type\n"
  "'help' with one command name as argument.\n"
);
