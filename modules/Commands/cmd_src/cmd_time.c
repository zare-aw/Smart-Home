#include "Command.h"
#include "Command_Func.h"
#include "Command_Debug.h"
#include "rtc.h"
#include "StatusHandling.h"

Status_t Do_Time(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FUNCTION_IN(DO_TIME);
  char String[32] = {0};
  RtcTime_t Time;
  
  RTC_Get_Time(&Time);
  
  if(argc > 0)
  {
    if(strstr(argv[0], "-a") != NULL)
      CONTROL(!Format_Time(2, &Time, String), RTC_GENERAL_ERROR);
    else
      FUNC_EXIT(CMD_INVALID_ARGUMENT, DO_TIME);
  }
  else
    CONTROL(!Format_Time(1, &Time, String), RTC_GENERAL_ERROR);
  
  printcmd("\r # %s\n", String);
  
  FUNC_EXIT(CMD_SUCCESS, DO_TIME);
}

CMD_CREATE(
  time, 1, Do_Time,
  "'time' - Print current time, '-a' as argument for 12h format\n",
  "'time' - Print current time in 24h format\n"
  "'time -a' - (with '-a' as argument) Print current time in 12h format\n"
);
