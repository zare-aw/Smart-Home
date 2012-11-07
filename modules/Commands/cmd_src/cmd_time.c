#include <string.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "RTC.h"
#include "StatusHandling.h"

Status_t Do_Time(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_TIME);
  
  char String[32] = {0};
  RtcTime_t Time;
  
  RTC_Get_Time(&Time);
  
  if(argc > 0)
  {
    if(strstr(argv[0], "-a") != NULL)
      ASSERT(SUCCESS == Format_Time(2, &Time, String), -RTC_GENERAL_ERROR);
    else
      EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TIME);
  }
  else
    ASSERT(SUCCESS == Format_Time(1, &Time, String), -RTC_GENERAL_ERROR);
  
  printcmd("\r # %s\n", String);
  
  EXIT_SUCCESS_FUNC(DO_TIME);
}
FUNC_REGISTER(DO_TIME, Do_Time);

CMD_CREATE(
  time, 1, Do_Time,
  "'time' - Print current time, '-a' as argument for 12h format\n",
  "'time' - Print current time in 24h format\n"
  "'time -a' - (with '-a' as argument) Print current time in 12h format\n"
);
