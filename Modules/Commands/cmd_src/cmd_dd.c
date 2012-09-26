#include <stdlib.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "SurfaceFlinger.h"

Status_t Do_Dd(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_DD);
  
  Console_Display_Dump();
  
  EXIT_SUCCESS_FUNC(DO_DD);
}
FUNC_REGISTER(DO_DD, Do_Dd);

CMD_CREATE(
  dd, 0, Do_Dd,
  "'dd' - Dump display buffer in console\n",
  "Dump display buffer from surface flinger which shoud be displayed on display\n"
  "This command is used only for debuging!\n"
);

