#include <string.h>
#include <stdlib.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "RTC.h"
#include "StatusHandling.h"
#include "Alarm.h"

#define _CMD_TIMEA_DEBUG   1

#ifdef _CMD_TIMEA_DEBUG
#define CMD_TIMEA_DEBUG(a) a
#else
#define CMD_TIMEA_DEBUG(a)
#endif


/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Try_Read_Time_Response_Cmd(char *argv, TimeAlarm_t *TimeAlarm_p)
{
  FuncIN(DO_TRY_READ_TIME_RESPONSE_CMD);
  
  ASSERT(argv != NULL, -INVALID_INPUT_POINTER);
  ASSERT(TimeAlarm_p != NULL, -INVALID_INPUT_POINTER);
  
  char *CommandString = NULL;
  int i;
  
  CommandString = strstr(argv, "response=");
  if(CommandString != NULL)
  {
    TimeAlarm_p -> Callback = NULL;
    
    CMD_TIMEA_DEBUG(printcmd("\r # (%s) 'response' found!\n", __func__));
    
    for(i = 0; AlarmResponse[i].String != NULL; i++)
    {
      if(!strcmp(AlarmResponse[i].String, CommandString + 9))
      {
        TimeAlarm_p -> Callback = AlarmResponse[i].Callback;
        CMD_TIMEA_DEBUG(printcmd("\r # (%s) 'response' matched to '%s'\n",
                              __func__, AlarmResponse[i].String));
      }
    }
    
    if(TimeAlarm_p -> Callback == NULL)
    {
      printcmd(" # Invalid 'response' parameter!\n");
      EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TRY_READ_TIME_RESPONSE_CMD);
    }
  } // if(CommandString != NULL)
  
  EXIT_SUCCESS_FUNC(DO_TRY_READ_TIME_RESPONSE_CMD);
}
FUNC_REGISTER(DO_TRY_READ_TIME_RESPONSE_CMD, Do_Try_Read_Time_Response_Cmd);
/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Reg_Time_Alarm_Cmd(TimeAlarm_t *TimeAlarm_p)
{
  FuncIN(DO_REG_TIME_ALARM_CMD);
  
  ASSERT(TimeAlarm_p != NULL, -INVALID_INPUT_POINTER);
  
  CMD_TIMEA_DEBUG(printcmd("\r # (%s) input parameters\n",__func__));
  CMD_TIMEA_DEBUG(printcmd("\r # date = %02u.%02u.%02u\n", TimeAlarm_p -> DateTime.Day,
                                                  TimeAlarm_p -> DateTime.Month,
                                                  TimeAlarm_p -> DateTime.Year));
  CMD_TIMEA_DEBUG(printcmd("\r # time = %02u:%02u:%02u\n", TimeAlarm_p -> DateTime.Hour,
                                                  TimeAlarm_p -> DateTime.Minute,
                                                  TimeAlarm_p -> DateTime.Second));
  CMD_TIMEA_DEBUG(printcmd("\r # Callback = 0x%X\n", TimeAlarm_p -> Callback));
  
  if(TimeAlarm_p -> Callback != NULL)
  {
    VERIFY(Register_Time_Alarm(TimeAlarm_p), -TIME_ALARM_REGISTER_ERROR);
    printcmd("\r # Time Alarm Registered\n");
  }
  else
  {
    printcmd("\r # Time Alarm Not Register\n");
  }

  EXIT_SUCCESS_FUNC(DO_REG_TIME_ALARM_CMD);
}
FUNC_REGISTER(DO_REG_TIME_ALARM_CMD, Do_Reg_Time_Alarm_Cmd);
/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Time_Alarm(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_TIME_ALARM);
  int i;
  Status_t Status = GENERAL_ERROR;
  TimeAlarm_t TimeAlarm_s = {0, 0};
  char ArgumentTokens[12] = {0};
  char *CommandString = NULL;
  
  if(argc > 0)
  {
    for(i = 0; i < argc; i++)
    {
      /******** Try for 'date=' ********/
      CommandString = strstr(argv[i], "date=");
      if(CommandString != NULL){
        if(strlen(CommandString + 5) > 10)  // Agument should be in format "DD.MM.YYYY"
        {
          printcmd(" # Invalid 'date' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TIME_ALARM);
        }
        strcpy(ArgumentTokens, CommandString + 5);  // strtok is changing the string. We need local copy!
        ArgumentTokens[10] = '.';  // For strtok termination
  
        TimeAlarm_s.DateTime.Day = atoi(strtok(ArgumentTokens, "."));  // Take first token before first '.' and convert to integer
        TimeAlarm_s.DateTime.Month = atoi(strtok(NULL, "."));  // Take second token before second '.' and convert to integer
        TimeAlarm_s.DateTime.Year = atoi(strtok(NULL, "."));  // Take third token before third '.' and convert to integer
      }
      
      /******** Try for 'time=' ********/
      CommandString = strstr(argv[i], "time=");
      if(CommandString != NULL){
        if(strlen(CommandString + 5) > 8)  // Agument should be in format "HH:MM:SS"
        {
          printcmd(" # Invalid 'time' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TIME_ALARM);
        }
        strcpy(ArgumentTokens, CommandString + 5);  // strtok is changing the string. We need local copy!
        ArgumentTokens[8] = ':';  // For strtok termination
        
        TimeAlarm_s.DateTime.Hour = atoi(strtok(ArgumentTokens, ":"));  // Take first token before first ':' and convert to integer
        TimeAlarm_s.DateTime.Minute = atoi(strtok(NULL, ":"));  // Take second token before second ':' and convert to integer
        TimeAlarm_s.DateTime.Second = atoi(strtok(NULL, ":"));  // Take third token before third ':' and convert to integer
      }
      
      /******** Try for 'response=' ********/
      Status = Do_Try_Read_Time_Response_Cmd(argv[i], &TimeAlarm_s);
      VERIFY(Status, Status);
      switch(Status)
      {
        case CMD_INVALID_ARGUMENT:
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TIME_ALARM);
        case SUCCESS:
          break;
        default:
          break;
      } // switch(Status)
       
    }
    Do_Reg_Time_Alarm_Cmd(&TimeAlarm_s); 
    
  } else if (argc == 0)
  {
    Time_Alarm_Status(NULL);
  }
  
  EXIT_SUCCESS_FUNC(DO_TIME_ALARM);
}
FUNC_REGISTER(DO_TIME_ALARM, Do_Time_Alarm);

CMD_CREATE(
  time_alarm, 3, Do_Time_Alarm,
  "'time_alarm' - Print registered time alarms.\n"
  "'time_alarm - date=A time=B response=C'  - Set time alarm.\n",
  "example 1: 'time_alarm date=01.01.2012 time=12:00:00 response=out_1_OFF'\n"
);
