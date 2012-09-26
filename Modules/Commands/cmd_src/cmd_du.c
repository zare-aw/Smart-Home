#include <stdlib.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "SurfaceFlinger.h"

Status_t Do_Du(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_DU);
  
  int Status = 0;
  
  if(argc > 0)
  {
    Status = atoi(argv[0]);
    switch(Status)
	{
	  case 1:
	    Console_Display_Update_Set(ENABLE);
	    break;
      case 0:
	    Console_Display_Update_Set(DISABLE);
	    break;
	  default:
	    EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_DU);
	}
  }
  else
    EXIT_FUNC(CMD_MISSING_ARGUMENT, DO_DU);
  
  EXIT_SUCCESS_FUNC(DO_DU);
}
FUNC_REGISTER(DO_DU, Do_Du);

CMD_CREATE(
  du, 1, Do_Du,
  "'du n' - Enable display update. 'n' = '0' for disable and '1' for enable\n",
  "'du n' - Enable display update in console. Display surface buffer will be printed in console each time when is updated\n"
  "'du n' - (with 'n' as argument) to enable or disable display update in console. 'n = 0' for disable and 'n = 1' for enable\n"
);

