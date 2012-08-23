#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "RTC.h"
#include "StatusHandling.h"

Status_t Do_Set_Time(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_SET_TIME);
  
  Status_t Status;
  char ArgumentTokens[10] = {0};
  RtcTime_t Time;
  
  if(argc == 0)
    EXIT_FUNC(CMD_MISSING_ARGUMENT, DO_SET_TIME);
  
  if(strlen(argv[0]) > 8)  // Agument should be in format "HH:MM:SS"
    EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SET_TIME);
  
  strcpy(ArgumentTokens, argv[0]);  // strtok is changing the string. We need local copy!
  ArgumentTokens[8] = ':';  // For strtok termination
  
  Time.Hour = atoi(strtok(ArgumentTokens, ":"));  // Take first token before first ':' and convert to integer
  Time.Minute = atoi(strtok(NULL, ":"));  // Take second token before second ':' and convert to integer
  Time.Second = atoi(strtok(NULL, ":"));  // Take third token before third ':' and convert to integer
  
  Status = RTC_Set_Time(&Time);
  
  VERIFY(Status, Status);
  
  if(Status == RTC_INVALID_TIME_ERROR)
    printcmd("\r # Invalid Time!\n");
  else if(Status == SUCCESS)
    printcmd("\r # Time Set!\n");
  else
    printcmd("\r # Time Not Set! Unknown Error\n");
  
  EXIT_SUCCESS_FUNC(DO_SET_TIME);
}
FUNC_REGISTER(DO_SET_TIME, Do_Set_Time);

CMD_CREATE(
  set_time, 1, Do_Set_Time,
  "'set_time hh:mm:ss' - Set time in 24h format. Ex: 'set_time 14:02:55'\n",
  ""
);
