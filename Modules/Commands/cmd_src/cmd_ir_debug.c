#include <stdlib.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "TSOP1738.h"

Status_t Do_IR_Debug(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_IR_DEBUG);
  
  if(argc > 0)
  {
    switch(atoi(argv[0]))
    {
      case 0:
        IR_Received_Debug_Set_State(DISABLE);
        printcmd("\r # IR Received sequence debug Disabled!\n");
        break;
      case 1:
        printcmd("\r # IR Received sequence debug Enabled!\n");
        IR_Received_Debug_Set_State(ENABLE);
        break;
      default:
        EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_IR_DEBUG);
    } // switch(argv[0])
  }
  else
    EXIT_FUNC(CMD_MISSING_ARGUMENT, DO_IR_DEBUG);
  
  EXIT_SUCCESS_FUNC(DO_IR_DEBUG);
}
FUNC_REGISTER(DO_IR_DEBUG, Do_IR_Debug);

CMD_CREATE(
  ir_debug, 1, Do_IR_Debug,
  "'ir_debug' - Set received sequence debug printing. '1' - Enable, '0' - Disable\n",
  ""
);

