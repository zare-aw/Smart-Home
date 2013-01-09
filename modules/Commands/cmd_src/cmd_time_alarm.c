#include <string.h>
#include <stdlib.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "RTC.h"
#include "StatusHandling.h"
#include "Alarm.h"

#define _CMD_TIMEA_DEBUG   0

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
Status_t Do_Set_Time_Alarm_Cmd(TimeAlarm_t *TimeAlarm_p)
{
  FuncIN(DO_SET_TIME_ALARM_CMD);
  
  ASSERT(TimeAlarm_p != NULL, -INVALID_INPUT_POINTER);
  
  CMD_TIMEA_DEBUG(printcmd("\r # (%s) input parameters\n",__func__));
  CMD_TIMEA_DEBUG(printcmd("\r # date = %02u.%02u.%02u\n",  TimeAlarm_p -> DateTime.Day,
                                                            TimeAlarm_p -> DateTime.Month,
                                                            TimeAlarm_p -> DateTime.Year));
  CMD_TIMEA_DEBUG(printcmd("\r # time = %02u:%02u:%02u\n",  TimeAlarm_p -> DateTime.Hour,
                                                            TimeAlarm_p -> DateTime.Minute,
                                                            TimeAlarm_p -> DateTime.Second));
  CMD_TIMEA_DEBUG(printcmd("\r # AlarmID = %u\n", TimeAlarm_p -> AlarmID));
  CMD_TIMEA_DEBUG(printcmd("\r # State = %u\n", TimeAlarm_p -> State));
  CMD_TIMEA_DEBUG(printcmd("\r # Callback = 0x%X\n", TimeAlarm_p -> Callback));
  
  if(TimeAlarm_p -> AlarmID != NO_ALARM_ID)
  {
    VERIFY(Set_Time_Alarm(TimeAlarm_p), -TIME_SET_ALARM_ERROR);
    printcmd(" # Time Alarm set\n");
  }
  else
  {
    if((TimeAlarm_p -> Callback != NULL) &&
       (TimeAlarm_p -> DateTime.Hour != 0 ||
       TimeAlarm_p -> DateTime.Minute != 0 ||
       TimeAlarm_p -> DateTime.Second != 0))
    {
      VERIFY(Register_Time_Alarm(TimeAlarm_p), -TIME_ALARM_REGISTER_ERROR);
      printcmd("\r # Time Alarm Registered\n");
    }
    else
    {
      printcmd("\r # Time Alarm Not Register\n");
    }
  }
  EXIT_SUCCESS_FUNC(DO_SET_TIME_ALARM_CMD);
}
FUNC_REGISTER(DO_SET_TIME_ALARM_CMD, Do_Set_Time_Alarm_Cmd);
/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Time_Alarm(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_TIME_ALARM);
  int i;
  Status_t Status = GENERAL_ERROR;
  TimeAlarm_t TimeAlarm_s = {0};
  char ArgumentTokens[12] = {0};
  char *CommandString = NULL;
  uint8 Remove = FALSE;

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

      /******** Try for 'state=' ********/
      CommandString = strstr(argv[i], "state=");
      if(CommandString != NULL)
      {
        if(!strncmp("ON", CommandString + 6, 2))
          TimeAlarm_s.State = ALARM_ON;
        else if(!strncmp("OFF", CommandString + 6, 3))
          TimeAlarm_s.State = ALARM_OFF;
        else
        {
          printcmd(" # Invalid 'state' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TIME_ALARM);
        }
      }

      /******** Try for 'alarmID=' ********/
      CommandString = strstr(argv[i], "alarmID=");
      if(CommandString != NULL)
        TimeAlarm_s.AlarmID = atoi(CommandString + 8);

      /******** Try for '-rm' ********/
      CommandString = strstr(argv[i], "-rm");
      if(CommandString != NULL)
        Remove = TRUE;

      /******** Try for 'repeat=' ********/
      CommandString = strstr(argv[i], "repeat=");
      if(CommandString != NULL)
        TimeAlarm_s.Repeat = strtol(CommandString + 7, NULL, 2);

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
       
    } // for(i = 0; i < argc; i++)
    if(Remove == FALSE)
      Do_Set_Time_Alarm_Cmd(&TimeAlarm_s);
    else
      Remove_Time_Alarm(TimeAlarm_s.AlarmID);
    
  } else
  {
    Time_Alarm_Status(NULL);
  }
  
  EXIT_SUCCESS_FUNC(DO_TIME_ALARM);
}
FUNC_REGISTER(DO_TIME_ALARM, Do_Time_Alarm);

CMD_CREATE(
  time_alarm, 6, Do_Time_Alarm,
  "'time_alarm' - Print registered time alarms.\n"
  "'time_alarm - date=A time=B alarmID=C response=D state=E repeat=F -rm'  - Set time alarm.\n",
  "date     A = Date when to perform the response.\n"
  "time     B = Time when to perform the response.\n"
  "alarmID  E = Alarm ID\n"
  "response F = out_1_ON, out_1_OFF, ... , out_6_ON, out_6_OFF, sound_alarm, dummy\n"
  "state    D = ON, OFF (enable or disable the alarm)\n"
  "repeat   F = Days in week when to perform the response ex. 100 == WEDNESDAY\n"
  "-rm      remove alarm with alarmID=C\n"
  "If you set 'alarmID' all other parameters is updated on that alarm. Other parameters is no necessary to set\n"
  "If you not set 'alarmID' you must set: date, time, response, state.\n"
  "example 1: 'time_alarm date=01.01.2013 time=12:00:00 response=out_1_OFF state=ON'\n"
  "example 2: 'time_alarm alarmID=2 time=12:00:00 repeat=1010100 state=ON'\n"
  "example 3: 'time_alarm alarmID=2 -rm'\n"
);
