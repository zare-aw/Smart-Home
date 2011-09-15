#include "Includes.h"

uint8 TempSensorSN[NO_OF_TEMP_SENSORS][8] = {0};
uint8 TempSensorCH[NO_OF_TEMP_SENSORS] = {0};
int Temp[NO_OF_TEMP_SENSORS] = {-250};

uint8 AlarmEvent[NO_OF_TEMP_SENSORS][NO_OF_ALARMS] = {0};
int   AlarmValue[NO_OF_TEMP_SENSORS][NO_OF_ALARMS] = {-250};
void *AlarmCallback[NO_OF_TEMP_SENSORS][NO_OF_ALARMS] = {0};

/*******************************************************************************
* 
*******************************************************************************/
int ReadTemp(uint8 SensorID)
{
  return Temp[SensorID];
}

/*******************************************************************************
* @in: Ch - Number of channel where is connected sensor. Starting from 1.
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
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Unregister_Temp_Sensor(uint8 SensorID)
{
  Function_IN(UNREGISTER_TEMP_SENSOR);
  CONTROL(TempSensorCH[SensorID] != 0, NOT_REGISTERED_ERROR);
  
  TempSensorCH[SensorID] = 0;
  memset(TempSensorSN[SensorID], 0, 8);
  Temp[SensorID] = -250;
  
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
  AlarmValue[SensorID][AlarmID] = -250;
  AlarmCallback[SensorID][AlarmID] = NULL;
      
  RETURN_SUCCESS();
}
