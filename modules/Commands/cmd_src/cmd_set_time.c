#include "Command.h"
#include "Command_Func.h"
#include "Command_Debug.h"
#include "rtc.h"
#include "StatusHandling.h"

Status_t Do_Set_Time(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FUNCTION_IN(DO_SET_TIME);
  char ArgumentTokens[10] = {0};
  RtcTime_t Time;
  
  if(argc == 0)
    FUNC_EXIT(CMD_MISSING_ARGUMENT, DO_SET_TIME);
  
  if(strlen(argv[0]) > 8)  // Agument should be in format "HH:MM:SS"
    FUNC_EXIT(CMD_INVALID_ARGUMENT, DO_SET_TIME);
  
  strcpy(ArgumentTokens, argv[0]);  // strtok is changing the string. We need local copy!
  ArgumentTokens[8] = ':';  // For strtok termination
  
  Time.Hour = atoi(strtok(ArgumentTokens, ":"));  // Take first token before first ':' and convert to integer
  Time.Minute = atoi(strtok(NULL, ":"));  // Take second token before second ':' and convert to integer
  Time.Second = atoi(strtok(NULL, ":"));  // Take third token before third ':' and convert to integer
  
  if(RTC_Set_Time(&Time) == RTC_INVALID_TIME_ERROR)
    printcmd("\r # Invalid Time!\n");
  else
    printcmd("\r # Time Set!\n");
 
  FUNC_EXIT(CMD_SUCCESS, DO_SET_TIME);
}

CMD_CREATE(
  set_time, 1, Do_Set_Time,
  "'set-time hh:mm:ss' - Set time in 24h format. Ex: 'set-time 14:02:55'\n",
  NULL
);
