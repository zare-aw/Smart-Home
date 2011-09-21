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

uint8 FirstTemp[NO_OF_TEMP_SENSORS] = {1};

void Temp_Callback(void);

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
    CallbackID = RTC_Register_Inc_Int((void *)Temp_Callback, AlarmIntType_SEC);
  
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
    CallbackID = 255;
  }
  
  RETURN_SUCCESS();
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
    if(AlarmEvent[i] == 0)
    {
      AlarmEvent[SensorID][i] = Event;
      AlarmValue[SensorID][i] = TempValue;
      AlarmCallback[SensorID][i] = Callback_p;
      *AlarmID = i;
      break;
    }
  CONTROL(*AlarmID != NO_OF_ALARMS, TEMP_SLOTS_ERROR);
  
  RETURN_SUCCESS();
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
Status_t Temp_Init(void)
{
  Function_IN(TEMP_INIT);
  Status_t StatusReturn = GENERAL_ERROR;
  
  StatusReturn = DS1820_Init(1, NULL);
  if(StatusReturn == SUCCESS)
  {
    CONTROL(!Register_Temp_Sensor(1, NULL, &SensorID_1), TEMP_SENSOR_REGISTER_ERROR);
    printc("\rTemperature sensor on channel 1 registered on ID = %d\n", SensorID_1);
  }
  else
    printc("\rFailed to register Temperature sensor on channel 1\n");
  
  StatusReturn = DS1820_Init(2, NULL);
  if(StatusReturn == SUCCESS)
  {
    CONTROL(!Register_Temp_Sensor(2, NULL, &SensorID_2), TEMP_SENSOR_REGISTER_ERROR);
    printc("\rTemperature sensor on channel 2 registered on ID = %d\n", SensorID_2);
  }
  else
    printc("\rFailed to register Temperature sensor on channel 2\n");
  
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
      printc("\rTemperature sensor on channel 1 registered on ID = %d\n", SensorID_1);
    }
  }
  else
  {
    if(i < NO_OF_TEMP_SENSORS)
    {
      Unregister_Temp_Sensor(SensorID_1);
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
      printc("\rTemperature sensor on channel 2 registered on ID = %d\n", SensorID_2);
    }
  }
  else
  {
    if(i < NO_OF_TEMP_SENSORS)
    {
      Unregister_Temp_Sensor(SensorID_2);
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
            Temp[i] = SENSOR_REINIT;
        }
        else
        {
          if(DS1820_Read_Temp(&Temp[i], TempSensorCH[i], NULL) != SUCCESS)
            Temp[i] = SENSOR_REINIT;
        }
      }
      
      if(j < 8)
      {
        if(DS1820_Start_Conversion(TempSensorCH[i], TempSensorSN[i]) != SUCCESS)
          Temp[i] = SENSOR_REINIT;
      }
      else
      {
        if(DS1820_Start_Conversion(TempSensorCH[i], NULL) != SUCCESS)
          Temp[i] = SENSOR_REINIT;
      }
      
      FirstTemp[i] = 0;
      
      if(TempBeckup[i] != Temp[i])
      {
      
        // TODO: Implement support for Alarms
        
      }
      
      TempBeckup[i] = Temp[i];
    }
  }
  
  TempUpdate = 0;
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
void Temp_Callback(void)
{
  TempUpdate = 1;
}