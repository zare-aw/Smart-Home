#include <stdlib.h>
#include <string.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Temperature.h"
#include "Temperature_Debug.h"
#include "Out.h"

//#define _CMD_TA_DEBUG   1

#ifdef _CMD_TA_DEBUG
#define CMD_TA_DEBUG(a) a
#else
#define CMD_TA_DEBUG(a)
#endif

TempAlarmResponse_t TempAlarmResponse[] =
{
  {
    .String = "out_1_ON",
    .Callback = (void *)Out_1_Set
  },
  {
    .String = "out_1_OFF",
    .Callback = (void *)Out_1_Clr
  },
  {
    .String = "out_2_ON",
    .Callback = (void *)Out_2_Set
  },
  {
    .String = "out_2_OFF",
    .Callback = (void *)Out_2_Clr
  },
  {
    .String = "out_3_ON",
    .Callback = (void *)Out_3_Set
  },
  {
    .String = "out_3_OFF",
    .Callback = (void *)Out_3_Clr
  },
  {
    .String = "out_4_ON",
    .Callback = (void *)Out_4_Set
  },
  {
    .String = "out_4_OFF",
    .Callback = (void *)Out_4_Clr
  },
  {
    .String = "out_5_ON",
    .Callback = (void *)Out_5_Set
  },
  {
    .String = "out_5_OFF",
    .Callback = (void *)Out_5_Clr
  },
  {
    .String = "out_6_ON",
    .Callback = (void *)Out_6_Set
  },
  {
    .String = "out_6_OFF",
    .Callback = (void *)Out_6_Clr
  },
  {
    .String = "sound_alarm",
    .Callback = (void *)Temp_Alarm_Dummy_Handler
  },
  {
    .String = "dummy",
    .Callback = (void *)Temp_Alarm_Dummy_Handler
  },
  {0} // Terminator
};
  

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Print_Temp_Alarms_Cmd(void)
{
  FuncIN(DO_PRINT_TEMP_ALARMS_CMD);
  
  TempAlarm_t TempAlarm_s;
  int NoOfAlarms = 0;
  
  for(uint8 i = 0; i < NO_OF_TEMP_SENSORS; i++)
    for(uint8 j = 0; j < NO_OF_ALARMS; j++)
      if(Read_Temp_Alarm(i, j, &TempAlarm_s) == SUCCESS)
      {
        NoOfAlarms++;
        printcmd("\r # TempSensor %d, AlarmID %d, State = ", i, j);
        switch(TempAlarm_s.State)
        {
          case ALARM_OFF:
            printcmd("OFF");
            break;
          case ALARM_ON:
            printcmd("ON");
            break;
          default:
            printcmd("UNKNOWN");
            break;
        }
        printcmd(", Event = ");
        switch(TempAlarm_s.Event)
        {
          case ABOVE:
            printcmd("ABOVE");
            break;
          case BELLOW:
            printcmd("BELLOW");
            break;
          case EQUAL:
            printcmd("EQUAL");
            break;
          case ABOVE_OR_EQUAL:
            printcmd("ABOVE_OR_EQUAL");
            break;
          case BELLOW_OR_EQUAL:
            printcmd("BELLOW_OR_EQUAL");
            break;
          case DIFFERENT:
            printcmd("DIFFERENT");
            break;
          default:
            printcmd("UNKNOWN");
            break;
        }
        printcmd(", Value = %d", TempAlarm_s.Value);
        TEMP_DEBUG(printcmd(", CallbackAddress = 0x%X", (uint32)TempAlarm_s.Callback));
        printcmd("\n");
      }
  
  if(NoOfAlarms == 0)
    printcmd("\r # No temperature alarms registered!\n");
  
  EXIT_SUCCESS_FUNC(DO_PRINT_TEMP_ALARMS_CMD);
}
FUNC_REGISTER(DO_PRINT_TEMP_ALARMS_CMD, Do_Print_Temp_Alarms_Cmd);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Try_Read_Sensor_ID_Cmd(char *argv, TempAlarm_t *TempAlarm_p)
{
  FuncIN(DO_TRY_READ_SENSOR_ID_CMD);
  
  ASSERT(argv != NULL, -INVALID_INPUT_POINTER);
  ASSERT(TempAlarm_p != NULL, -INVALID_INPUT_POINTER);
  
  char *CommandString = NULL;
  int SensorID;
  
  CommandString = strstr(argv, "sensor=");
  if(CommandString != NULL)
  {
    SensorID = atoi(CommandString + 7);
    
    if(Check_Sensor_Availability(SensorID))
      TempAlarm_p -> SensorID = SensorID;
    else
    {
      printcmd("\r # Sensor with ID = %d, not available!\n", SensorID);
      EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TRY_READ_SENSOR_ID_CMD);
    }
  }  
  else
    EXIT_FUNC(CMD_NOT_FOUND, DO_TRY_READ_SENSOR_ID_CMD);
  
  EXIT_SUCCESS_FUNC(DO_TRY_READ_SENSOR_ID_CMD);
}
FUNC_REGISTER(DO_TRY_READ_SENSOR_ID_CMD, Do_Try_Read_Sensor_ID_Cmd);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Try_Read_Response_Cmd(char *argv, TempAlarm_t *TempAlarm_p)
{
  FuncIN(DO_TRY_READ_RESPONSE_CMD);
  
  ASSERT(argv != NULL, -INVALID_INPUT_POINTER);
  ASSERT(TempAlarm_p != NULL, -INVALID_INPUT_POINTER);
  
  char *CommandString = NULL;
  int i;
  
  CommandString = strstr(argv, "response=");
  if(CommandString != NULL)
  {
    TempAlarm_p -> Callback = NULL;
    
    CMD_TA_DEBUG(printcmd("\r # (%s) 'response' found!\n", __func__));
    
    for(i = 0; TempAlarmResponse[i].String != NULL; i++)
    {   
      if(!strcmp(TempAlarmResponse[i].String, CommandString + 9))
      {
        TempAlarm_p -> Callback = TempAlarmResponse[i].Callback;
        CMD_TA_DEBUG(printcmd("\r # (%s) 'response' matched to '%s'\n",
                              __func__, TempAlarmResponse[i].String));
      }
    }
    
    if(TempAlarm_p -> Callback == NULL)
    {
      printcmd(" # Invalid 'response' parameter!\n");
      EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TRY_READ_RESPONSE_CMD);
    }
  } // if(CommandString != NULL)
  
  EXIT_SUCCESS_FUNC(DO_TRY_READ_RESPONSE_CMD);
}
FUNC_REGISTER(DO_TRY_READ_RESPONSE_CMD, Do_Try_Read_Response_Cmd);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Set_Temp_Alarm_Cmd(TempAlarm_t *TempAlarm_p)
{
  FuncIN(DO_SET_TEMP_ALARM_CMD);
  
  ASSERT(TempAlarm_p != NULL, -INVALID_INPUT_POINTER);
  
  CMD_TA_DEBUG(printcmd("\r # Do_Set_Temp_Alarm_Cmd() input parameters\n"));
  CMD_TA_DEBUG(printcmd("\r # SensorID = %u\n", TempAlarm_p -> SensorID));
  CMD_TA_DEBUG(printcmd("\r # AlarmID = %u\n", TempAlarm_p -> AlarmID));
  CMD_TA_DEBUG(printcmd("\r # Event = %u\n", TempAlarm_p -> Event));
  CMD_TA_DEBUG(printcmd("\r # State = %u\n", TempAlarm_p -> State));
  CMD_TA_DEBUG(printcmd("\r # Value = %d\n", TempAlarm_p -> Value));
  CMD_TA_DEBUG(printcmd("\r # Callback = 0x%X\n", TempAlarm_p -> Callback));
  
  if(TempAlarm_p -> AlarmID != NO_ALARM_ID)
  {
    VERIFY(Set_Temp_Alarm(TempAlarm_p), -TEMP_SET_ALARM_ERROR);
    printcmd(" # Temp Alarm set\n");
  }
  else
  {
    if((TempAlarm_p -> Event != NO_ALARM) &&
       (TempAlarm_p -> Value != -255) &&
       (TempAlarm_p -> Callback != NULL) &&
       (TempAlarm_p -> SensorID < NO_OF_TEMP_SENSORS))
    {
      VERIFY(Register_Temp_Alarm(TempAlarm_p -> SensorID, TempAlarm_p -> Event, TempAlarm_p -> Value,
                                  TempAlarm_p -> Callback, &(TempAlarm_p -> AlarmID)), -TEMP_ALARM_REGISTER_ERROR);
      printcmd("\r # Temp Alarm Registered\n");
    }
    else
    {
      printcmd("\r # Temp Alarm Not Register\n");
    }
    
    if((TempAlarm_p -> State != 0) && (TempAlarm_p -> SensorID < NO_OF_TEMP_SENSORS) && (TempAlarm_p -> AlarmID != NO_ALARM_ID))
    {
      VERIFY(Set_State_Temp_Alarm(TempAlarm_p -> SensorID, TempAlarm_p -> AlarmID, TempAlarm_p -> State), -TEMP_ALARM_SET_STATE_ERROR);
      printcmd("\r # Temp Alarm state set\n");
    }
    else
    {
      printcmd("\r # Temp Alarm state not set\n");
    }
  }
  
  EXIT_SUCCESS_FUNC(DO_SET_TEMP_ALARM_CMD);
}
FUNC_REGISTER(DO_SET_TEMP_ALARM_CMD, Do_Set_Temp_Alarm_Cmd);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Temp_Alarm(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_TEMP_ALARM);
  
  TempAlarm_t TempAlarm_s = {NULL};
  char *CommandString = NULL;
  
  TempAlarm_s.Value = -255;
  TempAlarm_s.AlarmID = NO_ALARM_ID;
  int i, SensorArgv = 0;
  Status_t Status = GENERAL_ERROR;
  
  if(argc > 0)
  {
    for(i = 0; i < argc; i++)
    {
      /********* Try for 'sensor=' ********/
      Status = Do_Try_Read_Sensor_ID_Cmd(argv[i], &TempAlarm_s);
      VERIFY(Status, Status);
      switch(Status)
      {
        case CMD_INVALID_ARGUMENT:
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TEMP_ALARM);
        case CMD_NOT_FOUND:
          break;
        case SUCCESS:
          SensorArgv = 1;
          break;
        default:
          break;
      } // switch(Status)
      
      /******** Try for 'temp=' ********/
      CommandString = strstr(argv[i], "temp=");
      if(CommandString != NULL)
        TempAlarm_s.Value = atoi(CommandString + 5);
      
      /******** Try for 'event=' ********/
      CommandString = strstr(argv[i], "event=");
      if(CommandString != NULL)
      {
        if(!strncmp("above", CommandString + 6, 5))
          TempAlarm_s.Event = ABOVE;
        else if(!strncmp("bellow", CommandString + 6, 6))
          TempAlarm_s.Event = BELLOW;
        else if(!strncmp("equal", CommandString + 6, 5))
          TempAlarm_s.Event = EQUAL;
        else if(!strncmp("above_or_equal", CommandString + 6, 14))
          TempAlarm_s.Event = ABOVE_OR_EQUAL;
        else if(!strncmp("bellow_or_equal", CommandString + 6, 15))
          TempAlarm_s.Event = BELLOW_OR_EQUAL;
        else if(!strncmp("different", CommandString + 6, 9))
          TempAlarm_s.Event = DIFFERENT;
        else
        {
          printcmd(" # Invalid 'event' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TEMP_ALARM);
        }
      } // if(CommandString != NULL)
      
      /******** Try for 'state=' ********/
      CommandString = strstr(argv[i], "state=");
      if(CommandString != NULL)
      {
        if(!strncmp("ON", CommandString + 6, 2))
          TempAlarm_s.State = ALARM_ON;
        else if(!strncmp("OFF", CommandString + 6, 3))
          TempAlarm_s.State = ALARM_OFF;
        else
        {
          printcmd(" # Invalid 'state' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TEMP_ALARM);
        }
      }
      
      /******** Try for 'alarmID=' ********/
      CommandString = strstr(argv[i], "alarmID=");
      if(CommandString != NULL)
        TempAlarm_s.AlarmID = atoi(CommandString + 8);
      
      /******** Try for 'response=' ********/
      Status = Do_Try_Read_Response_Cmd(argv[i], &TempAlarm_s);
      VERIFY(Status, Status);
      switch(Status)
      {
        case CMD_INVALID_ARGUMENT:
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TEMP_ALARM);
        case SUCCESS:
          break;
        default:
          break;
      } // switch(Status)
      
    } // for(i = 0; i < argc; i++)
    
    if(SensorArgv == 0)
    {
      printcmd("\r # Argument 'sensor' is missing!\n");
      EXIT_FUNC(CMD_MISSING_ARGUMENT, DO_TEMP_ALARM);
    }
    else
    {
      Do_Set_Temp_Alarm_Cmd(&TempAlarm_s);
    }
    
  } // if(argc > 0)
  else
  {
    Do_Print_Temp_Alarms_Cmd();
  }
  
  EXIT_SUCCESS_FUNC(DO_TEMP_ALARM);
}
FUNC_REGISTER(DO_TEMP_ALARM, Do_Temp_Alarm);

CMD_CREATE(
  temp_alarm, 6, Do_Temp_Alarm,
  "'temp_alarm' - Print registered temeperature alarms.\n"
  "'temp_alarm sensor=A temp=B event=C state=D alarmID=E response=F' - Set temperature alarm.\n",
  "sensor   A = Sensor ID.\n"
  "temp     B = Temperature in celsius\n"
  "event    C = above, bellow, equal, above_or_equal, bellow_or_equal, different\n"
  "state    D = ON, OFF\n"
  "alarmID  E = Alarm ID\n"
  "response F = out_1_ON, out_1_OFF, ... , out_6_ON, out_6_OFF, sound_alarm, dummy\n"
  "If you set 'alarmID' all other parameters is updated on that alarm. Other parameters is no necessary to set\n"
  "If you not set 'alarmID' you must set: sensor, temp, event, response, state.\n"
  "example 1: 'temp_alarm alarmID=2 temp=26 state=ON'\n"
  "example 2: 'temp_alarm sensor=int temp=26 state=ON event=equal response=out_1_OFF'\n"
);

