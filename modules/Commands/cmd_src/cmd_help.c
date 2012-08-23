#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"

Status_t Do_Help(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_HELP);
  
  Status_t Status = GENERAL_ERROR; 
  
  ASSERT(argc <= Cmd_Tbl->MaxArgs, -INVALID_INPUT_PARAMETER);
  
  if(argc == 0)
  {
    Cmd_Tbl_t *Cmd_Tbl_p = Get_Cmd_Section_Begin();
    Cmd_Tbl_t *Cmd_Tbl_End_p = Get_Cmd_Section_End();
    
    printcmd("\n # Smart Home system console\n");
    printcmd(" # Supported commands:\n");
    
    while(Cmd_Tbl_p != Cmd_Tbl_End_p)
    {
      ASSERT(Cmd_Tbl_p->Name != NULL, -CMD_ILEGAL_COMMAND_PARAMETER);
      
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
    VERIFY(Status, Status);
    
    switch(Status)
    {
      case SUCCESS:
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
  
  EXIT_SUCCESS_FUNC(DO_HELP);
}
FUNC_REGISTER(DO_HELP, Do_Help);

CMD_CREATE(
  help, 1, Do_Help,
  "help - print help\n",
  "help 'command' - show usage and help information (for 'command').\n"
  "Without arguments, it prints a short usage message for all commands.\n\n"
  "To get detailed help information for specific commands you can type\n"
  "'help' with one command name as argument.\n"
);
