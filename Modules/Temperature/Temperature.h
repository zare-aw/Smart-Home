#ifndef _Temperature_h
#define _Temperature_h

#define NO_OF_TEMP_SENSORS    4
#define NO_OF_CHANNELS        2
#define NO_OF_ALARMS          5

#define TEMP_EMPTY_SLOT       -250
#define SENSOR_REMOVED        -255

#define NO_ALARM_ID           0xFF

// Register_Temp_Alarm(Event)
#define NO_ALARM              0
#define ABOVE                 1
#define BELLOW                2
#define EQUAL                 3
#define ABOVE_OR_EQUAL        4
#define BELLOW_OR_EQUAL       5
#define DIFFERENT             6

// Set_State_Temp_Alarm(State)
#define ALARM_OFF             1
#define ALARM_ON              2

typedef struct TempAlarm_s
{
  uint8 Event;
  uint8 State;
  uint8 SensorID;
  uint8 AlarmID;
  int Value;
  void *Callback;
} TempAlarm_t;

typedef struct TempAlarmResponse_s
{
  char *String;
  void *Callback;
} TempAlarmResponse_t;

// Functions
int ReadTemp(uint8 SensorID);
Status_t Register_Temp_Sensor(uint8 Ch, uint8 *SerialNumber, uint8 *SensorID);
Status_t Unregister_Temp_Sensor(uint8 SensorID);
int Check_Sensor_Availability(uint8 SensorID);
Status_t Register_Temp_Alarm(uint8 SensorID, uint8 Event, int TempValue, void *Callback_p, uint8 *AlarmID);
Status_t Set_Temp_Alarm(TempAlarm_t *TempAlarm_p);
Status_t Unregister_Temp_Alarm(uint8 SensorID, uint8 AlarmID);
Status_t Set_State_Temp_Alarm(uint8 SensorID, uint8 AlarmID, uint8 State);
Status_t Read_Temp_Alarm(uint8 SensorID, uint8 AlarmID, TempAlarm_t *TempAlarm_p);
Status_t Read_Temp_Alarm_Wrap(uint8 SensorID, uint8 AlarmID, TempAlarm_t *TempAlarm_p);
Status_t Temp_Init(void);
Status_t Temp_Reinit(void);
Status_t Temp_Work(void);
Status_t Temp_Alarm_Dummy_Handler(void *Ptr);


#endif
