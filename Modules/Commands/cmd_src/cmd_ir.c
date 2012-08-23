#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "TSOP1738.h"

Status_t Do_Ir(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_IR);
  
  ir_t IR_Command = {0};
  uint16 i;
  
  printcmd("\r # Maximum supported general IR commands: %u\n", MAX_IR_COMMANDS - RESERVED_IR_COMMANDS);
  printcmd("\r # IR Commands:\n");
  
  for(i = 0; i < MAX_IR_COMMANDS; i++)
  {
    VERIFY(IR_Get_Command(i, &IR_Command), -IR_COMMAND_GET_ERROR);
    if((IR_Command.Address != NULL) || (IR_Command.Command != NULL) || (IR_Command.CallMode != NULL) || (IR_Command.Target != NULL))
      printcmd("\r # IR_Command_Number = %u\tAddress = %u\tCommand = %u\tCallMode = %u\tTarget = %u\n", i, IR_Command.Address, IR_Command.Command, IR_Command.CallMode, IR_Command.Target);
  }
  
  printcmd("\r # Other IR Commands are empty \n");
  
  EXIT_SUCCESS_FUNC(DO_IR);
}
FUNC_REGISTER(DO_IR, Do_Ir);

CMD_CREATE(
  ir, 0, Do_Ir,
  "'ir' - Print saved IR commands\n",
  ""
);
