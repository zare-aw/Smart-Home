#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Command_Debug.h"

Status_t Do_Info(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FUNCTION_IN(DO_INFO);
  
  printcmd("\n # Smart Home system\n");
  printcmd(" # HW Version 1.0\n");
  printcmd(" # SW Version 1.0\n");
  printcmd(" # Compile Date = %s\n", __DATE__);
  printcmd(" # Compiler version = %d\n", __VER__);
  printcmd(" # Target ID = %d\n", __TID__); 
  
  FUNC_EXIT(CMD_SUCCESS, DO_INFO);
}

CMD_CREATE(
  info, 0, Do_Info,
  "info - print system info\n",
  NULL
);
