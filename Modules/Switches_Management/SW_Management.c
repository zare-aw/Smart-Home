#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"

#include "SW_Management.h"
#include "SW_Management_Debug.h"
#include "SW_Management_Func.h"

#include "Configs.h"
#include "Temperature.h"
#include "Alarm.h"

__packed SW_M_Event_t SW_M_Event[NO_OF_SWITCHES][NO_OF_EVENTS_PER_SWITCH] = {0};
void *CallbackON[]      = {(void *)Out_1_Set,
                           (void *)Out_2_Set,
                           (void *)Out_3_Set,
                           (void *)Out_4_Set,
                           (void *)Out_5_Set,
                           (void *)Out_6_Set};
void *CallbackOFF[]     = {(void *)Out_1_Clr,
                           (void *)Out_2_Clr,
                           (void *)Out_3_Clr,
                           (void *)Out_4_Clr,
                           (void *)Out_5_Clr,
                           (void *)Out_6_Clr};
void *CallbackToggle[]  = {(void *)Out_1_Toggle,
                           (void *)Out_2_Toggle,
                           (void *)Out_3_Toggle,
                           (void *)Out_4_Toggle,
                           (void *)Out_5_Toggle,
                           (void *)Out_6_Toggle};

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t SW_M_Get_Callback(uint32 NoOfSwitch, uint32 Type, void **Callback)
{
  FuncIN(SW_M_GET_CALLBACK);
  
  switch(Type)
  {
    case SW_CALLBACK_TYPE_ON:
      *Callback = CallbackON[NoOfSwitch - 1];
      break;
    case SW_CALLBACK_TYPE_OFF:
      *Callback = CallbackOFF[NoOfSwitch - 1];
      break;
    case SW_CALLBACK_TYPE_TOGGLE:
      *Callback = CallbackToggle[NoOfSwitch - 1];
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  EXIT_SUCCESS_FUNC(SW_M_GET_CALLBACK);
}
SW_M_FUNC_REGISTER(SW_M_GET_CALLBACK, SW_M_Get_Callback);
 
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t SW_M_Config_Temp_Event(uint32 NoOfSwitch, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_CONFIG_TEMP_EVENT);
  
  void *Callback;
  TempAlarm_t TempAlarm;
  
  if(((SW_M_Event_p -> Config & SW_EVENT_ON) == SW_EVENT_ON) &&
     ((SW_M_Event_p -> Config & SW_EVENT_TEMP_DEP) == SW_EVENT_TEMP_DEP))
  {
    /**** Config Temp_1 ****/
    if(SW_M_Event_p -> Temp_1.State == SW_TEMP_ALARM_ON)
    {
      if((SW_M_Event_p -> Config & SW_EVENT_RESPONSE_1_ON) == SW_EVENT_RESPONSE_1_ON)
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_ON, &Callback);
      else
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_OFF, &Callback);
      
      if(SW_M_Event_p -> Temp_1.AlarmID == SW_TEMP_NO_ALARM_ID)
      {
        Register_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor,
                            SW_M_Event_p -> Temp_1.Event,
                            SW_M_Event_p -> Temp_1.Temp,
                            Callback,
                            &(SW_M_Event_p -> Temp_1.AlarmID));
        
        Set_State_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor,
                             SW_M_Event_p -> Temp_1.AlarmID,
                             SW_M_Event_p -> Temp_1.State);
      }
      else
      {
        TempAlarm.Event = SW_M_Event_p -> Temp_1.Event;
        TempAlarm.State = SW_M_Event_p -> Temp_1.State;
        TempAlarm.SensorID = SW_M_Event_p -> Temp_1.Sensor;
        TempAlarm.AlarmID = SW_M_Event_p -> Temp_1.AlarmID;
        TempAlarm.Value = SW_M_Event_p -> Temp_1.Temp;
        TempAlarm.Callback = Callback;
        
        Set_Temp_Alarm(&TempAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Temp_1.AlarmID != SW_TEMP_NO_ALARM_ID)
      {
        Unregister_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor, SW_M_Event_p -> Temp_1.AlarmID);
        SW_M_Event_p -> Temp_1.AlarmID = SW_TEMP_NO_ALARM_ID;
      }
    }
    
    /**** Config Temp_2 ****/
    if(SW_M_Event_p -> Temp_2.State == SW_TEMP_ALARM_ON)
    {
      if((SW_M_Event_p -> Config & SW_EVENT_RESPONSE_2_ON) == SW_EVENT_RESPONSE_2_ON)
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_ON, &Callback);
      else
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_OFF, &Callback);
      
      if(SW_M_Event_p -> Temp_2.AlarmID == SW_TEMP_NO_ALARM_ID)
      {
        Register_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor,
                            SW_M_Event_p -> Temp_2.Event,
                            SW_M_Event_p -> Temp_2.Temp,
                            Callback,
                            &(SW_M_Event_p -> Temp_2.AlarmID));
        
        Set_State_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor,
                             SW_M_Event_p -> Temp_2.AlarmID,
                             SW_M_Event_p -> Temp_2.State);
      }
      else
      {
        TempAlarm.Event = SW_M_Event_p -> Temp_2.Event;
        TempAlarm.State = SW_M_Event_p -> Temp_2.State;
        TempAlarm.SensorID = SW_M_Event_p -> Temp_2.Sensor;
        TempAlarm.AlarmID = SW_M_Event_p -> Temp_2.AlarmID;
        TempAlarm.Value = SW_M_Event_p -> Temp_2.Temp;
        TempAlarm.Callback = Callback;
        
        Set_Temp_Alarm(&TempAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Temp_2.AlarmID != SW_TEMP_NO_ALARM_ID)
      {
        Unregister_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor, SW_M_Event_p -> Temp_2.AlarmID);
        SW_M_Event_p -> Temp_2.AlarmID = SW_TEMP_NO_ALARM_ID;
      }
    }
  }
  else
  {
    if(SW_M_Event_p -> Temp_1.AlarmID != SW_TEMP_NO_ALARM_ID)
    {
      Unregister_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor, SW_M_Event_p -> Temp_1.AlarmID);
      SW_M_Event_p -> Temp_1.AlarmID = SW_TEMP_NO_ALARM_ID;
    }
    
    if(SW_M_Event_p -> Temp_2.AlarmID != SW_TEMP_NO_ALARM_ID)
    {
      Unregister_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor, SW_M_Event_p -> Temp_2.AlarmID);
      SW_M_Event_p -> Temp_2.AlarmID = SW_TEMP_NO_ALARM_ID;
    }
  }
  
  EXIT_SUCCESS_FUNC(SW_M_CONFIG_TEMP_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_CONFIG_TEMP_EVENT, SW_M_Config_Temp_Event);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t SW_M_Config_Time_Event(uint32 NoOfSwitch, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_CONFIG_TIME_EVENT);

  TimeAlarm_t TimeAlarm;

  if(((SW_M_Event_p -> Config & SW_EVENT_ON) == SW_EVENT_ON) &&
     ((SW_M_Event_p -> Config & SW_EVENT_TIME_DEP) == SW_EVENT_TIME_DEP))
  {
    /**** Config Time_Start ****/
    if(SW_M_Event_p -> Time_Start.State == SW_TIME_ALARM_ON)
    {
      if((SW_M_Event_p -> Config & SW_EVENT_RESPONSE_1_ON) == SW_EVENT_RESPONSE_1_ON)
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_ON, &TimeAlarm.Callback);
      else
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_OFF, &TimeAlarm.Callback);
      
      if(SW_M_Event_p -> Time_Start.AlarmID == SW_TIME_NO_ALARM_ID)
      {
        TimeAlarm.State = SW_M_Event_p -> Time_Start.State;
        TimeAlarm.AlarmID = SW_TIME_NO_ALARM_ID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Start.Hour,
                                             SW_M_Event_p -> Time_Start.Minute,
                                             SW_M_Event_p -> Time_Start.Second};

        Register_Time_Alarm(&TimeAlarm);
      }
      else
      {
        TimeAlarm.State = SW_M_Event_p -> Time_Start.State;
        TimeAlarm.AlarmID = SW_M_Event_p -> Time_Start.AlarmID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Start.Hour,
                                             SW_M_Event_p -> Time_Start.Minute,
                                             SW_M_Event_p -> Time_Start.Second};

        Set_Time_Alarm(&TimeAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Time_Start.AlarmID != SW_TIME_NO_ALARM_ID)
      {
        Unregister_Time_Alarm(SW_M_Event_p -> Time_Start.AlarmID);
        SW_M_Event_p -> Time_Start.AlarmID = SW_TIME_NO_ALARM_ID;
      }
    }

    /**** Config Time_Stop ****/
    if(SW_M_Event_p -> Time_Stop.State == SW_TIME_ALARM_ON)
    {
      if((SW_M_Event_p -> Config & SW_EVENT_RESPONSE_2_ON) == SW_EVENT_RESPONSE_2_ON)
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_ON, &TimeAlarm.Callback);
      else
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_OFF, &TimeAlarm.Callback);
      
      if(SW_M_Event_p -> Time_Stop.AlarmID == SW_TIME_NO_ALARM_ID)
      {
        TimeAlarm.State = SW_M_Event_p -> Time_Stop.State;
        TimeAlarm.AlarmID = SW_TIME_NO_ALARM_ID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Stop.Hour,
                                             SW_M_Event_p -> Time_Stop.Minute,
                                             SW_M_Event_p -> Time_Stop.Second};

        Register_Time_Alarm(&TimeAlarm);
      }
      else
      {
        TimeAlarm.State = SW_M_Event_p -> Time_Stop.State;
        TimeAlarm.AlarmID = SW_M_Event_p -> Time_Stop.AlarmID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Stop.Hour,
                                             SW_M_Event_p -> Time_Stop.Minute,
                                             SW_M_Event_p -> Time_Stop.Second};

        Set_Time_Alarm(&TimeAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Time_Stop.AlarmID != SW_TIME_NO_ALARM_ID)
      {
        Unregister_Time_Alarm(SW_M_Event_p -> Time_Stop.AlarmID);
        SW_M_Event_p -> Time_Stop.AlarmID = SW_TIME_NO_ALARM_ID;
      }
    }
  }
  else
  {
    if(SW_M_Event_p -> Time_Start.AlarmID != SW_TIME_NO_ALARM_ID)
    {
      Unregister_Time_Alarm(SW_M_Event_p -> Time_Start.AlarmID);
      SW_M_Event_p -> Time_Start.AlarmID = SW_TIME_NO_ALARM_ID;
    }

    if(SW_M_Event_p -> Time_Stop.AlarmID != SW_TIME_NO_ALARM_ID)
    {
      Unregister_Time_Alarm(SW_M_Event_p -> Time_Stop.AlarmID);
      SW_M_Event_p -> Time_Stop.AlarmID = SW_TIME_NO_ALARM_ID;
    }
  }

  EXIT_SUCCESS_FUNC(SW_M_CONFIG_TIME_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_CONFIG_TIME_EVENT, SW_M_Config_Time_Event);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t SW_M_Config_Time_Temp_Event(uint32 NoOfSwitch, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_CONFIG_TIME_TEMP_EVENT);
  
  
  
  EXIT_SUCCESS_FUNC(SW_M_CONFIG_TIME_TEMP_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_CONFIG_TIME_TEMP_EVENT, SW_M_Config_Time_Temp_Event);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t SW_M_Set_Event(uint32 NoOfSwitch, uint32 NoOfEvent, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_SET_EVENT);
  
  SW_M_Config_Temp_Event(NoOfSwitch, SW_M_Event_p);
  
  SW_M_Config_Time_Event(NoOfSwitch, SW_M_Event_p);
  
  SW_M_Config_Time_Temp_Event(NoOfSwitch, SW_M_Event_p);
  
  SW_M_Event[NoOfSwitch - 1][NoOfEvent - 1] = *SW_M_Event_p;
  
  Config_SW_M_Write(SW_M_Event[0], NO_OF_SWITCHES, NO_OF_EVENTS_PER_SWITCH);
  
  EXIT_SUCCESS_FUNC(SW_M_SET_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_SET_EVENT, SW_M_Set_Event);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t SW_M_Get_Event(uint32 NoOfSwitch, uint32 NoOfEvent, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_GET_EVENT);
  
  *SW_M_Event_p = SW_M_Event[NoOfSwitch - 1][NoOfEvent - 1];
  
  EXIT_SUCCESS_FUNC(SW_M_GET_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_GET_EVENT, SW_M_Get_Event);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t SW_M_Init(void)
{
  FuncIN(SW_M_INIT);
  
  Config_SW_M_Init(NO_OF_SWITCHES, NO_OF_EVENTS_PER_SWITCH);
  
  Config_SW_M_Read(SW_M_Event[0], NO_OF_SWITCHES, NO_OF_EVENTS_PER_SWITCH);
  
  EXIT_SUCCESS_FUNC(SW_M_INIT);
}
SW_M_FUNC_REGISTER(SW_M_INIT, SW_M_Init);
