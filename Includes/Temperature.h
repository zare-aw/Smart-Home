#ifndef _Temperature_h
#define _Temperature_h

#define _TEMP_DEBUG           1
#define _TEMP_INFO            1

#define NO_OF_TEMP_SENSORS    4
#define NO_OF_CHANNELS        2
#define NO_OF_ALARMS          5

#define SENSOR_REMOVED        -255

// Register_Temp_Alarm(Event)
#define NO_ALARM              0
#define ABOVE                 1
#define BELLOW                2
#define EQUAL                 3
#define ABOVE_OR_EQUAL        4
#define BELLOW_OR_EQUAL       5
#define DIFFERENT             6

// Set_State_Temp_Alarm(State)
#define ALARM_OFF             0
#define ALARM_ON              1

#ifdef _TEMP_DEBUG
#define TEMP_DEBUG(a) a
#else
#define TEMP_DEBUG(a)
#endif

#ifdef _TEMP_INFO
#define TEMP_INFO(a) a
#else
#define TEMP_INFO(a)
#endif

// Functions
int ReadTemp(uint8 SensorID);
Status_t Register_Temp_Sensor(uint8 Ch, uint8 *SerialNumber, uint8 *SensorID);
Status_t Unregister_Temp_Sensor(uint8 SensorID);
Status_t Register_Temp_Alarm(uint8 SensorID, uint8 Event, int TempValue, void *Callback_p, uint8 *AlarmID);
Status_t Unregister_Temp_Alarm(uint8 SensorID, uint8 AlarmID);
Status_t Set_State_Temp_Alarm(uint8 SensorID, uint8 AlarmID, uint8 State);
Status_t Temp_Init(void);
Status_t Temp_Reinit(void);
Status_t Temp_Work(void);


#endif
