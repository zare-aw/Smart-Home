#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Command.h"
#include "Command_Func.h"
#include "Menu.h"

Status_t Do_X(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_X);
  
  
  if(argc > 0)
  {
    switch(*argv[0])
    {
      case '2':   // Down
        Down_Key_Callback(NULL);
        break;
      case '8':   // Up
        Up_Key_Callback(NULL);
        break;
      case '4':   // Left
        Left_Key_Callback(NULL);
        break;
      case '6':   // Right
        Right_Key_Callback(NULL);
        break;
      case '-':   // Cancel
        Cancel_Key_Callback(NULL);
        break;
      case '+':   // Enter
        Enter_Key_Callback(NULL);
        break;
      default:
        EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_X);
    }
  }
  else
    EXIT_FUNC(CMD_MISSING_ARGUMENT, DO_X);
  
  EXIT_SUCCESS_FUNC(DO_X);
}
FUNC_REGISTER(DO_X, Do_X);

CMD_CREATE(
  x, 1, Do_X,
  "'x A' - Call buttons callbacks for Menu development.\n",
  "A = 2 - Down\n"
  "    8 - Up\n"
  "    4 - Left\n"
  "    6 - Right\n"
  "    - - Cancel\n"
  "    + - Enter\n"
);

