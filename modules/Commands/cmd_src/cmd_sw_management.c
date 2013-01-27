#include <string.h>
#include <stdlib.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "RTC.h"
#include "StatusHandling.h"
#include "Alarm.h"
#include "SW_Management.h"

#define _CMD_SW_MNG_DEBUG   0

#ifdef _CMD_SW_MNG_DEBUG
#define CMD_SW_MNG_DEBUG(a) a
#else
#define CMD_SW_MNG_DEBUG(a)
#endif

#define TIME_START  1
#define TIME_STOP   2
#define TEMP1       3
#define TEMP2       4

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Try_Read_Sensor_Cmd(char *argv, uint8 *Sensor_p)
{
  FuncIN(DO_TRY_READ_SENSOR_CMD);
  
  ASSERT(argv != NULL, -INVALID_INPUT_POINTER);
  ASSERT(Sensor_p != NULL, -INVALID_INPUT_POINTER);
  
  char *CommandString = NULL;
  int SensorID;
  
  CommandString = strstr(argv, "sensor=");
  if(CommandString != NULL)
  {
    SensorID = atoi(CommandString + 7);
    
    if(Check_Sensor_Availability(SensorID))
      *Sensor_p = SensorID;
    else
    {
      printcmd("\r # Sensor with ID = %d, not available!\n", SensorID);
      EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TRY_READ_SENSOR_CMD);
    }
  }  
  else
    EXIT_FUNC(CMD_NOT_FOUND, DO_TRY_READ_SENSOR_CMD);
  
  EXIT_SUCCESS_FUNC(DO_TRY_READ_SENSOR_CMD);
}
FUNC_REGISTER(DO_TRY_READ_SENSOR_CMD, Do_Try_Read_Sensor_Cmd);
/*******************************************************************************
* 
*******************************************************************************/
Status_t SW_M_Status(uint32 NoOfSwitch, uint32 NoOfEvent)
{
  FuncIN(SW_M_STATUS);
  uint32 i = 1;
  uint32 j = 1;
  uint8 flag = FALSE;
  uint32 max_events = 0;
  uint32 max_sw = 0;
  SW_M_Event_t SW_M_Event_s = {0};
  
  if (0 == NoOfSwitch) {
    max_events = NO_OF_EVENTS_PER_SWITCH;
    max_sw = NO_OF_SWITCHES;
    i = 1;
    j = 1;
  } else if(0 == NoOfEvent) {
    max_events = NO_OF_EVENTS_PER_SWITCH;
    max_sw = NoOfSwitch;
    i = NoOfSwitch;
    j = 1;
  } else {
    max_events = NoOfEvent;
    max_sw = NoOfSwitch;
    i = NoOfSwitch;
    j = NoOfEvent;
  }
  for(; i <= max_sw; i++)
  {
      for(; j <= max_events; j++)
      {
        SW_M_Get_Event(i, j, &SW_M_Event_s);
        if (0 == SW_M_Event_s.Config)
          continue;
        flag = TRUE;
        printcmd("\r # Switch number: %d Event number: %d\n", i, j);
        
        printcmd("\r # Config = 0x%X\n",              SW_M_Event_s.Config);
        printcmd("\r # Repeat Days= 0x%X\n",          SW_M_Event_s.Date.Repeat);
        printcmd("\r # Event Date = %02u.%02u.%02u\n",SW_M_Event_s.Date.Day,
                                                      SW_M_Event_s.Date.Month,
                                                      SW_M_Event_s.Date.Year);
        
        printcmd("\r # Time Start = %02u:%02u:%02u\n",SW_M_Event_s.Time_Start.Hour,
                                                      SW_M_Event_s.Time_Start.Minute,
                                                      SW_M_Event_s.Time_Start.Second);
        printcmd("\r # Time Start AlarmID = %d\n",    SW_M_Event_s.Time_Start.AlarmID);
        printcmd("\r # Time Start State = %d\n",      SW_M_Event_s.Time_Start.State);
  
        printcmd("\r # Time Stop = %02u:%02u:%02u\n", SW_M_Event_s.Time_Stop.Hour,
                                                      SW_M_Event_s.Time_Stop.Minute,
                                                      SW_M_Event_s.Time_Stop.Second);
        printcmd("\r # Time Stop AlarmID = %d\n",     SW_M_Event_s.Time_Stop.AlarmID);
        printcmd("\r # Time Stop State = %d\n",       SW_M_Event_s.Time_Stop.State);
        
        printcmd("\r # Temperature Value 1= %d\n",     SW_M_Event_s.Temp_1.Temp);
        printcmd("\r # Temp Sensor ID 1= %d\n",        SW_M_Event_s.Temp_1.Sensor);
        printcmd("\r # Temp Event 1= %d\n",            SW_M_Event_s.Temp_1.Event);
        printcmd("\r # Temp State 1= %d\n",            SW_M_Event_s.Temp_1.State);
        printcmd("\r # Temp AlarmID 1= %d\n",          SW_M_Event_s.Temp_1.AlarmID);
  
        printcmd("\r # Temperature Value 2= %d\n",     SW_M_Event_s.Temp_2.Temp);
        printcmd("\r # Temp Sensor ID 2= %d\n",        SW_M_Event_s.Temp_2.Sensor);
        printcmd("\r # Temp Event 2= %d\n",            SW_M_Event_s.Temp_2.Event);
        printcmd("\r # Temp State 2= %d\n",            SW_M_Event_s.Temp_2.State);
        printcmd("\r # Temp AlarmID 2= %d\n",          SW_M_Event_s.Temp_2.AlarmID);
      }
  }

  if (FALSE == flag)
  {
    printcmd("\r # Not Registered Event!\n");
  }
  EXIT_SUCCESS_FUNC(SW_M_STATUS);
}
FUNC_REGISTER(SW_M_STATUS, SW_M_Status);
/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_SW_Management(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_SW_MANAGEMENT);
  int i;
  Status_t Status = GENERAL_ERROR;
  SW_M_Event_t SW_M_Event_s = {0};

  char ArgumentTokens[12] = {0};
  uint8 Set_type = 0;
  uint8 Event = 0;
  uint8 Sensor;   // Sensor ID number
  sint16 Temp = 0;
  uint32 NoOfSwitch = 0;
  uint32 NoOfEvent = 0;

  char *CommandString = NULL;

  if(argc > 0)
  {
    for(i = 0; i < argc; i++)
    {
      /******** Try for 'config=' ********/
      CommandString = strstr(argv[i], "config=");
      if(CommandString != NULL)
        SW_M_Event_s.Config = strtol(CommandString + 7, NULL, 2);
      
      /******** Try for 'date=' ********/
      CommandString = strstr(argv[i], "date=");
      if(CommandString != NULL){
        if(strlen(CommandString + 5) > 10)  // Agument should be in format "DD.MM.YYYY"
        {
          printcmd(" # Invalid 'date' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SW_MANAGEMENT);
        }
        strcpy(ArgumentTokens, CommandString + 5);  // strtok is changing the string. We need local copy!
        ArgumentTokens[10] = '.';  // For strtok termination

        SW_M_Event_s.Date.Day = atoi(strtok(ArgumentTokens, "."));  // Take first token before first '.' and convert to integer
        SW_M_Event_s.Date.Month = atoi(strtok(NULL, "."));  // Take second token before second '.' and convert to integer
        SW_M_Event_s.Date.Year = atoi(strtok(NULL, "."));  // Take third token before third '.' and convert to integer
      }

      /******** Try for 'no_of_switch=' ********/
      CommandString = strstr(argv[i], "switch_no=");
      if(CommandString != NULL)
        NoOfSwitch = strtol(CommandString + 10, NULL, 2);
      
      /******** Try for 'no_of_event=' ********/
      CommandString = strstr(argv[i], "event_no=");
      if(CommandString != NULL)
        NoOfEvent = strtol(CommandString + 9, NULL, 2);
      
      /******** Try for 'repeat=' ********/
      CommandString = strstr(argv[i], "repeat=");
      if(CommandString != NULL)
        SW_M_Event_s.Date.Repeat = strtol(CommandString + 7, NULL, 2);
      
      /******** Try for 'set_type=' ********/
      CommandString = strstr(argv[i], "set_type=");
      if(CommandString != NULL)
      {
        if(!strncmp("Time_Start", CommandString + 9, 10))
          Set_type = TIME_START;
        else if(!strncmp("Time_Stop", CommandString + 9, 9))
          Set_type = TIME_STOP;
        else if(!strncmp("Temp1", CommandString + 9, 5))
          Set_type = TEMP1;
        else if(!strncmp("Temp2", CommandString + 9, 5))
          Set_type = TEMP2;
        else
        {
          printcmd(" # Invalid 'set_type' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SW_MANAGEMENT);
        }
      }
        
      /******** Try for 'time=' ********/
      CommandString = strstr(argv[i], "time=");
      if(CommandString != NULL){
        if(strlen(CommandString + 5) > 8)  // Agument should be in format "HH:MM:SS"
        {
          printcmd(" # Invalid 'time' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SW_MANAGEMENT);
        }
        strcpy(ArgumentTokens, CommandString + 5);  // strtok is changing the string. We need local copy!
        ArgumentTokens[8] = ':';  // For strtok termination
        if(Set_type == TIME_START) {
          SW_M_Event_s.Time_Start.Hour = atoi(strtok(ArgumentTokens, ":"));  // Take first token before first ':' and convert to integer
          SW_M_Event_s.Time_Start.Minute = atoi(strtok(NULL, ":"));  // Take second token before second ':' and convert to integer
          SW_M_Event_s.Time_Start.Second = atoi(strtok(NULL, ":"));  // Take third token before third ':' and convert to integer
        } else if(Set_type == TIME_STOP) {
          SW_M_Event_s.Time_Stop.Hour = atoi(strtok(ArgumentTokens, ":"));  // Take first token before first ':' and convert to integer
          SW_M_Event_s.Time_Stop.Minute = atoi(strtok(NULL, ":"));  // Take second token before second ':' and convert to integer
          SW_M_Event_s.Time_Stop.Second = atoi(strtok(NULL, ":"));  // Take third token before third ':' and convert to integer
        } else {
          printcmd(" # Not set 'set_type' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SW_MANAGEMENT);     
        }
      }

      /******** Try for 'temp=' ********/
      CommandString = strstr(argv[i], "temp=");
      if(CommandString != NULL)
        Temp = atoi(CommandString + 5);
        if(Set_type == TEMP1) {
          SW_M_Event_s.Temp_1.Temp = Temp;
        } else if(Set_type == TEMP2) {
          SW_M_Event_s.Temp_2.Temp = Temp;
        }

      /********* Try for 'sensor=' ********/
      Status = Do_Try_Read_Sensor_Cmd(argv[i], &Sensor);
      VERIFY(Status, Status);
      switch(Status)
      {
        case CMD_INVALID_ARGUMENT:
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TEMP_ALARM);
        case CMD_NOT_FOUND:
          break;
        case SUCCESS:
        if(Set_type == TEMP1) {
          SW_M_Event_s.Temp_1.Sensor = Sensor;
        } else if(Set_type == TEMP2) {
          SW_M_Event_s.Temp_2.Sensor = Sensor;
        }
          break;
        default:
          break;
      } // switch(Status)
      
      /******** Try for 'state=' ********/
      CommandString = strstr(argv[i], "state=");
      if(CommandString != NULL)
      {
        if(!strncmp("ON", CommandString + 6, 2)) {
          if(Set_type == TIME_START) {
            SW_M_Event_s.Time_Start.State = SW_TEMP_ALARM_ON;
          } else if(Set_type == TIME_STOP) {
            SW_M_Event_s.Time_Stop.State = SW_TEMP_ALARM_ON;
          } else if(Set_type == TEMP1) {
            SW_M_Event_s.Temp_1.State = SW_TEMP_ALARM_ON;
          } else if(Set_type == TEMP2) {
            SW_M_Event_s.Temp_1.State = SW_TEMP_ALARM_ON;
          }
        } else if(!strncmp("OFF", CommandString + 6, 3)) {
          if(Set_type == TIME_START) {
            SW_M_Event_s.Time_Start.State = SW_TEMP_ALARM_OFF;
          } else if(Set_type == TIME_STOP) {
            SW_M_Event_s.Time_Stop.State = SW_TEMP_ALARM_OFF;
          } else if(Set_type == TEMP1) {
            SW_M_Event_s.Temp_1.State = SW_TEMP_ALARM_OFF;
          } else if(Set_type == TEMP2) {
            SW_M_Event_s.Temp_1.State = SW_TEMP_ALARM_OFF;
          }
        } else {
          printcmd(" # Invalid 'state' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SW_MANAGEMENT);
        }
      }

      /******** Try for 'event=' ********/
      CommandString = strstr(argv[i], "event=");
      if(CommandString != NULL)
      {
        if(!strncmp("above", CommandString + 6, 5))
          Event = SW_TEMP_ALARM_ABOVE;
        else if(!strncmp("bellow", CommandString + 6, 6))
          Event = SW_TEMP_ALARM_BELLOW;
        else if(!strncmp("equal", CommandString + 6, 5))
          Event = SW_TEMP_ALARM_EQUAL;
        else if(!strncmp("above_or_equal", CommandString + 6, 14))
          Event = SW_TEMP_ALARM_ABOVE_OR_EQUAL;
        else if(!strncmp("bellow_or_equal", CommandString + 6, 15))
          Event = SW_TEMP_ALARM_BELLOW_OR_EQUAL;
        else if(!strncmp("different", CommandString + 6, 9))
          Event = SW_TEMP_ALARM_DIFFERENT;
        else
        {
          printcmd(" # Invalid 'event' parameter!\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SW_MANAGEMENT);
        }
        
        if(Set_type == TEMP1) {
          SW_M_Event_s.Temp_1.Event = Event;
        } else if(Set_type == TEMP2) {
          SW_M_Event_s.Temp_2.Event = Event;
        }
      } // if(CommandString != NULL)
      
      switch(Status)
      {
        case CMD_INVALID_ARGUMENT:
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SW_MANAGEMENT);
        case SUCCESS:
          break;
        default:
          break;
      } // switch(Status)
       
    } // for(i = 0; i < argc; i++)

    if (0 == memcmp( &((SW_M_Event_t){0}), &SW_M_Event_s, sizeof(SW_M_Event_t))) {
        SW_M_Status(NoOfSwitch, NoOfEvent);
    } else {
      SW_M_Event_s.Temp_1.AlarmID = SW_TEMP_NO_ALARM_ID;
      SW_M_Event_s.Temp_2.AlarmID = SW_TEMP_NO_ALARM_ID;
      SW_M_Set_Event(NoOfSwitch, NoOfEvent, &SW_M_Event_s);
    }
  } else
  {
    SW_M_Status(NoOfSwitch, NoOfEvent); 
  }
  
  EXIT_SUCCESS_FUNC(DO_SW_MANAGEMENT);
}
FUNC_REGISTER(DO_SW_MANAGEMENT, Do_SW_Management);

CMD_CREATE(
  sw_mng, 17, Do_SW_Management,
  "'sw_mng' - Print SW events.\n"
  "'sw_mng - switch_no=A event_no=B config=C date=D repeat=E set_type=F time=B response=D state=E'  - Set event.\n",
  "switch_no    A = Number of switch.\n"
  "event_no     B = Number of event.\n"
  "config       C = Config parameter for event.\n"    
  "date         D = Date when to perform the response.\n"
  "repeat       F = Days in week when to perform the response ex. 100 == WEDNESDAY\n"
  "set_type     E = Type of alarm to which followed parameter will be set.\n"
  "set corresponding value for the type: Time_Start, Time_Stop, Temp1, Temp2"
  "time         E = Time when to perform the response.\n"
  "temp         F = bordering temperature value in celsius.\n"
  "sensor       G = Sensor ID.\n"
  "event        H = above, bellow, equal, above_or_equal, bellow_or_equal, different\n"
  "response     J = out_1_ON, out_1_OFF, ... , out_6_ON, out_6_OFF\n"
  "state        K = ON, OFF (enable or disable the alarm)\n"
  "example 1: 'sw_mng switch_no=1 event_no=1 config=00100101 set_type=Time_Start date=27.01.2013 time=12:00:00 response=out_1_OFF state=ON'\n"
  "example 2: 'sw_mng switch_no=1 event_no=1 config=00101001 set_type=Temp1 date=27.01.2013 temp=25 sensor=1 response=out_1_OFF state=ON'\n"    
  "example 3: 'sw_mng switch_no=1 event_no=1'\n"
  "example 4: 'sw_mng switch_no=1'\n"
);
