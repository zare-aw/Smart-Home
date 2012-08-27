#include "Global_Defines.h"
#include "Includes.h"

uint8 TempSensorSN[NO_OF_TEMP_SENSORS][8] = {0};
uint8 TempSensorCH[NO_OF_TEMP_SENSORS] = {0};
int Temp[NO_OF_TEMP_SENSORS] = {-250};
int TempBeckup[NO_OF_TEMP_SENSORS] = {-250};

uint8 AlarmEvent[NO_OF_TEMP_SENSORS][NO_OF_ALARMS] = {0};
uint8 AlarmState[NO_OF_TEMP_SENSORS][NO_OF_ALARMS] = {0};
int   AlarmValue[NO_OF_TEMP_SENSORS][NO_OF_ALARMS] = {-250};
void *AlarmCallback[NO_OF_TEMP_SENSORS][NO_OF_ALARMS] = {0};

uint8 SensorID_1 = 255;
uint8 SensorID_2 = 255;

uint8 CallbackID = 255;
uint8 TempUpdate = 0;
uint8 ReinitFlag = 0;

uint8 FirstTemp[NO_OF_TEMP_SENSORS] = {1};

Status_t Temp_Callback(void *Ptr);

/*******************************************************************************
* 
*******************************************************************************/
int ReadTemp(uint8 SensorID)
{
  return Temp[SensorID];
}

/*******************************************************************************
* @in: Ch - Number of channel on witch is connected sensor. Starting from 1.
* @in: SerialNumber - Serial number of sensor.
* @out: SensorID - ID of the sensor.
*******************************************************************************/
Status_t Register_Temp_Sensor(uint8 Ch, uint8 *SerialNumber, uint8 *SensorID)
{
  Function_IN(REGISTER_TEMP_SENSOR);
  CONTROL(Ch <= NO_OF_CHANNELS, INVALID_INPUT_PARAMETER);
  *SensorID = NO_OF_TEMP_SENSORS;
  
  for(int i = 0; i < NO_OF_TEMP_SENSORS; i++)
    if(TempSensorCH[i] == 0)
    {
      TempSensorCH[i] = Ch;
      if(SerialNumber != NULL)
        memcpy(TempSensorSN[i], SerialNumber, 8);
      *SensorID = i;
      break;
    }
  CONTROL(*SensorID != NO_OF_TEMP_SENSORS, TEMP_SLOTS_ERROR);
  
  FirstTemp[*SensorID] = 1;
  
  if(CallbackID == 255)
  {
    RTC_Register_Inc_Int((void *)Temp_Callback, IncIntType_SEC, &CallbackID);
    TEMP_DEBUG(printc("\r # Temp callback registered on RTC icrement interrupt with ID = %d\n", CallbackID));
  }
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Unregister_Temp_Sensor(uint8 SensorID)
{
  Function_IN(UNREGISTER_TEMP_SENSOR);
  CONTROL(TempSensorCH[SensorID] != 0, NOT_REGISTERED_ERROR);
  int i;
  
  TempSensorCH[SensorID] = 0;
  memset(TempSensorSN[SensorID], 0, 8);
  Temp[SensorID] = -250;
  
  for(i = 0; i < NO_OF_TEMP_SENSORS; i++)
    if(TempSensorCH[i] != 0)
      break;
  
  if((i == NO_OF_TEMP_SENSORS) && CallbackID != 255)
  {
    RTC_Unregister_Inc_Int(CallbackID);
    TEMP_DEBUG(printc("\r # Temp callback unregistered on RTC icrement interrupt with ID = %d\n", CallbackID));
    CallbackID = 255;
  }
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
int Check_Sensor_Availability(uint8 SensorID)
{
  return TempSensorCH[SensorID];
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Register_Temp_Alarm(uint8 SensorID, uint8 Event, int TempValue, void *Callback_p, uint8 *AlarmID)
{
  Function_IN(REGISTER_TEMP_ALARM);
  CONTROL(SensorID < NO_OF_TEMP_SENSORS, INVALID_INPUT_PARAMETER);
  CONTROL(TempSensorCH[SensorID] != 0, NOT_REGISTERED_ERROR);
  CONTROL(Callback_p != NULL, INVALID_INPUT_POINTER);
  CONTROL((TempValue > -55) && (TempValue < 125), INVALID_INPUT_PARAMETER);
  CONTROL(AlarmID != NULL, INVALID_INPUT_POINTER);
  *AlarmID = NO_OF_ALARMS;
  
  for(int i = 0; i < NO_OF_ALARMS; i++)
    if(AlarmEvent[SensorID][i] == NO_ALARM)
    {
      AlarmEvent[SensorID][i] = Event;
      AlarmValue[SensorID][i] = TempValue;
      AlarmCallback[SensorID][i] = Callback_p;
      *AlarmID = i;
      break;
    }
  CONTROL(*AlarmID < NO_OF_ALARMS, TEMP_SLOTS_ERROR);
  
  TEMP_DEBUG(printc("\r # Temp Alarm registered with parameters:\n"));
  TEMP_DEBUG(printc("\r # Sensor ID = %d\n", SensorID));
  TEMP_DEBUG(printc("\r # Event = %d\n", Event));
  TEMP_DEBUG(printc("\r # Temperature = %d\n", TempValue));
  TEMP_DEBUG(printc("\r # Alarm ID = %d\n", *AlarmID));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_Temp_Alarm(TempAlarm_t *TempAlarm_p)
{
  Function_IN(SET_TEMP_ALARM);
  CONTROL(TempAlarm_p -> SensorID < NO_OF_TEMP_SENSORS, INVALID_INPUT_PARAMETER);
  CONTROL(TempAlarm_p -> AlarmID < NO_OF_ALARMS, INVALID_INPUT_PARAMETER);
  
  if(AlarmEvent[TempAlarm_p -> SensorID][TempAlarm_p -> AlarmID] != NO_ALARM)
  {
    TEMP_DEBUG(printc("\r # Temp Alarm set with parameters:\n"));
    TEMP_DEBUG(printc("\r # Sensor ID = %d\n", TempAlarm_p -> SensorID));
    TEMP_DEBUG(printc("\r # Alarm ID = %d\n", TempAlarm_p -> AlarmID));
    
    if(TempAlarm_p -> Event != 0)
    {
      AlarmEvent[TempAlarm_p -> SensorID][TempAlarm_p -> AlarmID] = TempAlarm_p -> Event;
      TEMP_DEBUG(printc("\r # Event = %d\n", TempAlarm_p -> Event));
    }
    if(TempAlarm_p -> Value != -255)
    {
      AlarmValue[TempAlarm_p -> SensorID][TempAlarm_p -> AlarmID] = TempAlarm_p -> Value;
      TEMP_DEBUG(printc("\r # Temperature = %d\n", TempAlarm_p -> Value));
    }
    if(TempAlarm_p -> Callback != NULL)
    {
      AlarmCallback[TempAlarm_p -> SensorID][TempAlarm_p -> AlarmID] = TempAlarm_p -> Callback;
    }
    if(TempAlarm_p -> State != 0)
    {
      AlarmState[TempAlarm_p -> SensorID][TempAlarm_p -> AlarmID] = TempAlarm_p -> State;
      TEMP_DEBUG(printc("\r # State = %d\n", TempAlarm_p -> State));
    }
  }
  
  RETURN_SUCCESS_FUNC(SET_TEMP_ALARM);
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Unregister_Temp_Alarm(uint8 SensorID, uint8 AlarmID)
{
  Function_IN(UNREGISTER_TEMP_ALARM);
  CONTROL(TempSensorCH[SensorID] != 0, NOT_REGISTERED_ERROR);
  CONTROL(AlarmEvent[SensorID][AlarmID] != 0, NOT_REGISTERED_ERROR);
  
  AlarmEvent[SensorID][AlarmID] = 0;
  AlarmState[SensorID][AlarmID] = ALARM_OFF;
  AlarmValue[SensorID][AlarmID] = -250;
  AlarmCallback[SensorID][AlarmID] = NULL;
  
  TEMP_DEBUG(printc("\r # Temp Alarm unregistered wih parameters:\n"));
  TEMP_DEBUG(printc("\r # Sensor ID = %d\n", SensorID));
  TEMP_DEBUG(printc("\r # Alarm ID = %d\n", AlarmID));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_State_Temp_Alarm(uint8 SensorID, uint8 AlarmID, uint8 State)
{
  Function_IN(SET_STATE_TEMP_ALARM);
  CONTROL(TempSensorCH[SensorID] != 0, NOT_REGISTERED_ERROR);
  CONTROL(AlarmEvent[SensorID][AlarmID] != 0, NOT_REGISTERED_ERROR);
  
  AlarmState[SensorID][AlarmID] = State;
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Read_Temp_Alarm(uint8 SensorID, uint8 AlarmID, TempAlarm_t *TempAlarm_p)
{
  Function_IN(READ_TEMP_ALARM);
  EXIT(TempSensorCH[SensorID] != 0, NOT_REGISTERED_ERROR);
  EXIT(AlarmEvent[SensorID][AlarmID] != 0, NOT_REGISTERED_ERROR);
  
  TempAlarm_p -> Event = AlarmEvent[SensorID][AlarmID];
  TempAlarm_p -> State = AlarmState[SensorID][AlarmID];
  TempAlarm_p -> Value = AlarmValue[SensorID][AlarmID];
  TempAlarm_p -> Callback = AlarmCallback[SensorID][AlarmID];
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Read_Temp_Alarm_Wrap(uint8 SensorID, uint8 AlarmID, TempAlarm_t *TempAlarm_p)
{
  switch(SensorID)
  {
    case 1:
      return Read_Temp_Alarm(SensorID_1, AlarmID, TempAlarm_p);
    case 2:
      return Read_Temp_Alarm(SensorID_2, AlarmID, TempAlarm_p);
    default:
      return INVALID_INPUT_PARAMETER;
  }
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Temp_Init(void)
{
  Function_IN(TEMP_INIT);
  Status_t StatusReturn = GENERAL_ERROR;
  
  for(int i = 0; i < NO_OF_TEMP_SENSORS; i++)
    Temp[i] = -250;
  
  for(int i = 0; i < NO_OF_TEMP_SENSORS; i++)
    for(int j = 0; j < NO_OF_ALARMS; j++)
      AlarmEvent[i][j] = NO_ALARM;
  
  StatusReturn = DS1820_Init(1, NULL);
  if(StatusReturn == SUCCESS)
  {
    CONTROL(!Register_Temp_Sensor(1, NULL, &SensorID_1), TEMP_SENSOR_REGISTER_ERROR);
    CONTROL(!Register_Menu_Temp(INTERNAL_SENSOR, SensorID_1), TEMP_SENSOR_REGISTER_ERROR);
    printc("\r # Temperature sensor on channel 1 registered on ID = %d\n", SensorID_1);
  }
  else
    printc("\r # Failed to register Temperature sensor on channel 1\n");
  
  StatusReturn = DS1820_Init(2, NULL);
  if(StatusReturn == SUCCESS)
  {
    CONTROL(!Register_Temp_Sensor(2, NULL, &SensorID_2), TEMP_SENSOR_REGISTER_ERROR);
    CONTROL(!Register_Menu_Temp(EXTERNAL_SENSOR, SensorID_2), TEMP_SENSOR_REGISTER_ERROR);
    printc("\r # Temperature sensor on channel 2 registered on ID = %d\n", SensorID_2);
  }
  else
    printc("\r # Failed to register Temperature sensor on channel 2\n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Temp_Reinit(void)
{
  Function_IN(TEMP_REINIT);
  Status_t StatusReturn = GENERAL_ERROR;
  int i;
  
  for(i = 0; i < NO_OF_TEMP_SENSORS; i++)
    if(TempSensorCH[i] == 1)
      break;
  
  StatusReturn = DS1820_Init(1, NULL);
  if(StatusReturn == SUCCESS)
  {
    if(i == NO_OF_TEMP_SENSORS)
    {
      CONTROL(!Register_Temp_Sensor(1, NULL, &SensorID_1), TEMP_SENSOR_REGISTER_ERROR);
      CONTROL(!Register_Menu_Temp(INTERNAL_SENSOR, SensorID_1), TEMP_SENSOR_REGISTER_ERROR);
      printc("\rTemperature sensor on channel 1 registered on ID = %d\n", SensorID_1);
    }
  }
  else
  {
    if(i < NO_OF_TEMP_SENSORS)
    {
      Unregister_Temp_Sensor(SensorID_1);
      CONTROL(!Unregister_Menu_Temp(INTERNAL_SENSOR), TEMP_SENSOR_REGISTER_ERROR);
      printc("\rFailed to register Temperature sensor on channel 1. Sensor removed!\n");
    }
  }
  
  for(i = 0; i < NO_OF_TEMP_SENSORS; i++)
    if(TempSensorCH[i] == 2)
      break; 
  
  StatusReturn = DS1820_Init(2, NULL);
  if(StatusReturn == SUCCESS)
  {
    if(i == NO_OF_TEMP_SENSORS)
    {
      CONTROL(!Register_Temp_Sensor(2, NULL, &SensorID_2), TEMP_SENSOR_REGISTER_ERROR);
      CONTROL(!Register_Menu_Temp(EXTERNAL_SENSOR, SensorID_2), TEMP_SENSOR_REGISTER_ERROR);
      printc("\rTemperature sensor on channel 2 registered on ID = %d\n", SensorID_2);
    }
  }
  else
  {
    if(i < NO_OF_TEMP_SENSORS)
    {
      Unregister_Temp_Sensor(SensorID_2);
      CONTROL(!Unregister_Menu_Temp(EXTERNAL_SENSOR), TEMP_SENSOR_REGISTER_ERROR);
      printc("\rFailed to register Temperature sensor on channel 2. Sensor removed!\n");
    }
  }
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Temp_Work(void)
{
  Function_IN(TEMP_WORK);
  int j;
  
  if(ReinitFlag == 1)
  {
    CONTROL(!Temp_Reinit(), TEMP_SENSOR_REINIT_ERROR);
    ReinitFlag = 0;
    RETURN_SUCCESS();
  }
  
  if(TempUpdate == 0)
    RETURN_SUCCESS();
  
  for(int i = 0; i < NO_OF_TEMP_SENSORS; i++)
  {
    if(TempSensorCH[i] != 0)
    {
      for(j = 0; j < 8; j++)
          if(TempSensorSN[i][j] != 0)
            break;
      
      if(FirstTemp[i] == 0)
      {
        if(j < 8)
        {
          if(DS1820_Read_Temp(&Temp[i], TempSensorCH[i], TempSensorSN[i]) != SUCCESS)
            Temp[i] = SENSOR_REMOVED;
        }
        else
        {
          if(DS1820_Read_Temp(&Temp[i], TempSensorCH[i], NULL) != SUCCESS)
            Temp[i] = SENSOR_REMOVED;
        }
      }
      
      if(j < 8)
      {
        if(DS1820_Start_Conversion(TempSensorCH[i], TempSensorSN[i]) != SUCCESS)
          Temp[i] = SENSOR_REMOVED;
      }
      else
      {
        if(DS1820_Start_Conversion(TempSensorCH[i], NULL) != SUCCESS)
          Temp[i] = SENSOR_REMOVED;
      }
      
      FirstTemp[i] = 0;
      
      if(TempBeckup[i] != Temp[i])
      {
        for(int j = 0; j < NO_OF_ALARMS; j++)
          if((AlarmEvent[i][j] != NO_ALARM) && (AlarmState[i][j] == ALARM_ON))
          {
            switch(AlarmEvent[i][j])
            {
              case ABOVE:
                if((TempBeckup[i] <= AlarmValue[i][j]) && (Temp[i] > AlarmValue[i][j]))
                {
                  ((Status_t(*)(void*))(AlarmCallback[i][j]))(NULL);
                  TEMP_INFO(printc(" # Temperature Alarm, SensorID = %d, AlarmID = %d\n", i, j));
                  TEMP_DEBUG(printc(" # Temperature = %d, AlarmEvent = ABOVE, TempValue = %d\n", Temp[i], AlarmValue[i][j]));
                }
                break;
              case BELLOW:
                if((TempBeckup[i] >= AlarmValue[i][j]) && (Temp[i] < AlarmValue[i][j]))
                {
                  ((Status_t(*)(void*))(AlarmCallback[i][j]))(NULL);
                  TEMP_INFO(printc(" # Temperature Alarm, SensorID = %d, AlarmID = %d\n", i, j));
                  TEMP_DEBUG(printc(" # Temperature = %d, AlarmEvent = BELLOW, TempValue = %d\n", Temp[i], AlarmValue[i][j]));
                }
                break;
              case EQUAL:
                if((TempBeckup[i] != AlarmValue[i][j]) && (Temp[i] == AlarmValue[i][j]))
                {
                  ((Status_t(*)(void*))(AlarmCallback[i][j]))(NULL);
                  TEMP_INFO(printc(" # Temperature Alarm, SensorID = %d, AlarmID = %d\n", i, j));
                  TEMP_DEBUG(printc(" # Temperature = %d, AlarmEvent = EQUAL, TempValue = %d\n", Temp[i], AlarmValue[i][j]));
                }
                break;
              case ABOVE_OR_EQUAL:
                if((TempBeckup[i] < AlarmValue[i][j]) && (Temp[i] >= AlarmValue[i][j]))
                {
                  ((Status_t(*)(void*))(AlarmCallback[i][j]))(NULL);
                  TEMP_INFO(printc(" # Temperature Alarm, SensorID = %d, AlarmID = %d\n", i, j));
                  TEMP_DEBUG(printc(" # Temperature = %d, AlarmEvent = ABOVE_OR_EQUAL, TempValue = %d\n", Temp[i], AlarmValue[i][j]));
                }
                break;
              case BELLOW_OR_EQUAL:
                if((TempBeckup[i] > AlarmValue[i][j]) && (Temp[i] <= AlarmValue[i][j]))
                {
                  ((Status_t(*)(void*))(AlarmCallback[i][j]))(NULL);
                  TEMP_INFO(printc(" # Temperature Alarm, SensorID = %d, AlarmID = %d\n", i, j));
                  TEMP_DEBUG(printc(" # Temperature = %d, AlarmEvent = BELLOW_OR_EQUAL, TempValue = %d\n", Temp[i], AlarmValue[i][j]));
                }
                break;
              case DIFFERENT:
                if((TempBeckup[i] == AlarmValue[i][j]) && (Temp[i] != AlarmValue[i][j]))
                {
                  ((Status_t(*)(void*))(AlarmCallback[i][j]))(NULL);
                  TEMP_INFO(printc(" # Temperature Alarm, SensorID = %d, AlarmID = %d\n", i, j));
                  TEMP_DEBUG(printc(" # Temperature = %d, AlarmEvent = DIFFERENT, TempValue = %d\n", Temp[i], AlarmValue[i][j]));
                }
                break;
              default:
                break;
            }
          }
      }
      
      if(Temp[i] == SENSOR_REMOVED)
        ReinitFlag = 1;
      
      TempBeckup[i] = Temp[i];
    }
  }
  
  TempUpdate = 0;
  RETURN_SUCCESS_FUNC(TEMP_WORK);
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Temp_Callback(void *Ptr)
{
  TempUpdate = 1;
  
  return SUCCESS;
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Temp_Alarm_Dummy_Handler(void *Ptr)
{
  TEMP_INFO(printc(" # Temperature alarm dummy handler executed!\n"));
  
  return SUCCESS;
}
