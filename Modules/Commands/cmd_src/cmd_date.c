#include <string.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "RTC.h"
#include "StatusHandling.h"

Status_t Do_Date(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_DATE);
  
  RtcDate_t Date;
  char String[32] = {0};
  
  RTC_Get_Date(&Date);
  
  if(argc > 0)
  {
    if(strstr(argv[0], "-l") != NULL)
      ASSERT(SUCCESS == Format_Date(2, &Date, String), -RTC_GENERAL_ERROR);
    else
      EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_DATE);
  }
  else
    ASSERT(SUCCESS == Format_Date(1, &Date, String), -RTC_GENERAL_ERROR);
  
  printcmd("\r # %s\n", String);
  
  EXIT_SUCCESS_FUNC(DO_DATE);
}
FUNC_REGISTER(DO_DATE, Do_Date);

CMD_CREATE(
  date, 1, Do_Date,
  "'date' - Print current date, '-l' as argument for extended format\n",
  "'date -l' - (with '-l' as argument) Print current date in extended format\n"
);
