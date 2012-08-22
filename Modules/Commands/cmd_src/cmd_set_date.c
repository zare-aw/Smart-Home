#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Command_Debug.h"
#include "RTC.h"
#include "StatusHandling.h"

Status_t Do_Set_Date(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FUNCTION_IN(DO_SET_DATE);
  
  char ArgumentTokens[12] = {0};
  RtcDate_t Date;
  
  if(argc == 0)
    FUNC_EXIT(CMD_MISSING_ARGUMENT, DO_SET_DATE);
  
  if(strlen(argv[0]) > 10)  // Agument should be in format "DD:MM:YYYY"
    FUNC_EXIT(CMD_INVALID_ARGUMENT, DO_SET_DATE);
  
  strcpy(ArgumentTokens, argv[0]);  // strtok is changing the string. We need local copy!
  ArgumentTokens[10] = '.';  // For strtok termination
  
  Date.Day = atoi(strtok(ArgumentTokens, "."));  // Take first token before first '.' and convert to integer
  Date.Month = atoi(strtok(NULL, "."));  // Take second token before second '.' and convert to integer
  Date.Year = atoi(strtok(NULL, "."));  // Take third token before third '.' and convert to integer
  
  if(RTC_Set_Date(&Date) == RTC_INVALID_DATE_ERROR)
    printcmd("\r # Invalid Date!\n");
  else
    printcmd("\r # Date Set\n");
  
  FUNC_EXIT(SUCCESS, DO_SET_DATE);
}

CMD_CREATE(
  set_date, 1, Do_Set_Date,
  "'set_date dd.mm.yyyy' - Set date. Ex: 'set_date 14.02.2012'\n",
  ""
);
