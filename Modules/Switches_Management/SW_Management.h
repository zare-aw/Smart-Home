#ifndef _SW_Management_h
#define _SW_Management_h

#include "Out.h"
#include "Temperature.h"
#include "Alarm.h"

/**** Configurations ****/
#define NO_OF_SWITCHES                NO_OF_OUTS
#define NO_OF_EVENTS_PER_SWITCH       4

/**** Defines ****/
/*******************************************************************************
 * SW_M_Event_s: Config: X X X XXX X X
 *                         | | ||| | |
 *                         | | ||| | -- ON - OFF
 *                         | | ||| ---- SINGLE - REPETITIVE
 *                         | | -------- Dependency
 *                         | ---------- Response 1 on TimeStart/Temp_1 (ON or OFF)
 *                         ------------ Response 2 on TimeStop/Temp_2 (ON or OFF)
 ******************************************************************************/
#define SW_EVENT_OFF            0x00
#define SW_EVENT_ON             0x01
#define SW_EVENT_SINGLE         0x00
#define SW_EVENT_REPETITIVE     0x02
#define SW_EVENT_TIME_DEP       0x04
#define SW_EVENT_TEMP_DEP       0x08
#define SW_EVENT_TIME_TEMP_DEP  0x10
#define SW_EVENT_RESPONSE_1_OFF 0x00
#define SW_EVENT_RESPONSE_1_ON  0x20
#define SW_EVENT_RESPONSE_2_OFF 0x00
#define SW_EVENT_RESPONSE_2_ON  0x40

/*******************************************************************************
 * SW_M_Temp_s: Event:
 ******************************************************************************/
#define SW_TEMP_ALARM_NO_ALARM              NO_ALARM
#define SW_TEMP_ALARM_ABOVE                 ABOVE
#define SW_TEMP_ALARM_BELLOW                BELLOW
#define SW_TEMP_ALARM_EQUAL                 EQUAL
#define SW_TEMP_ALARM_ABOVE_OR_EQUAL        ABOVE_OR_EQUAL
#define SW_TEMP_ALARM_BELLOW_OR_EQUAL       BELLOW_OR_EQUAL
#define SW_TEMP_ALARM_DIFFERENT             DIFFERENT

/*******************************************************************************
 * SW_M_Temp_s: State:
 ******************************************************************************/
#define SW_TEMP_ALARM_OFF     ALARM_OFF
#define SW_TEMP_ALARM_ON      ALARM_ON

/*******************************************************************************
 * SW_M_Time_s: State:
 ******************************************************************************/
#define SW_TIME_ALARM_OFF     ALARM_OFF
#define SW_TIME_ALARM_ON      ALARM_ON

/*******************************************************************************
 * SW_M_Temp_s: AlarmID:
 ******************************************************************************/
#define SW_TEMP_NO_ALARM_ID       NO_ALARM_ID

/*******************************************************************************
 * SW_M_Time_s: AlarmID:
 ******************************************************************************/
#define SW_TIME_NO_ALARM_ID       NO_TIME_ALARM_ID

/*******************************************************************************
 * SW_M_Get_Callback: Type:
 ******************************************************************************/
#define SW_CALLBACK_TYPE_ON       1
#define SW_CALLBACK_TYPE_OFF      2
#define SW_CALLBACK_TYPE_TOGGLE   3


/**** Structures ****/
typedef struct SW_M_Time_s
{
  uint8 Hour;     // Hour value
  uint8 Minute;   // Minute value
  uint8 Second;   // Second value
  uint8 State;    // State, ON or OFF
  uint8 AlarmID;  // Alarm ID number
} SW_M_Time_t;

typedef struct SW_M_Date_s
{
  uint8 Repeat;  //Repeat days
  uint8 Month;  // Month value
  uint8 Day;    // Day value
  uint8 DoW;    // Day of week
  uint16 Year;  // Year value
} SW_M_Date_t;

typedef struct SW_M_Temp_s
{
  sint16 Temp;    // Temperature Value
  uint8 Sensor;   // Sensor ID number
  uint8 Event;    // Temperature Event
  uint8 State;    // State, ON or OFF
  uint8 AlarmID;  // Alarm ID number
} SW_M_Temp_t;

typedef struct SW_M_Event_s
{
  uint8 Config;
  SW_M_Date_t Date;
  SW_M_Time_t Time_Start;
  SW_M_Time_t Time_Stop;
  SW_M_Temp_t Temp_1;
  SW_M_Temp_t Temp_2;
} SW_M_Event_t;

/**** Exported Functions ****/
Status_t SW_M_Set_Event(uint32 NoOfSwitch, uint32 NoOfEvent, SW_M_Event_t *SW_M_Event_p);
Status_t SW_M_Get_Event(uint32 NoOfSwitch, uint32 NoOfEvent, SW_M_Event_t *SW_M_Event_p);
Status_t SW_M_Init(void);
Status_t SW_M_Init_Event_Reg(void);

#endif // _SW_Management_h