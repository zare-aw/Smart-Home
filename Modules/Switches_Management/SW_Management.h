#ifndef _SW_Management_h
#define _SW_Management_h

#include "Out.h"

/**** Configurations ****/
#define NO_OF_SWITCHES                NO_OF_OUTS
#define NO_OF_EVENTS_PER_SWITCH       4

/**** Defines ****/
/*******************************************************************************
 * SW_M_Event_s: Config: XXX XXX X X
 *                           ||| | |
 *                           ||| | -- ON - OFF
 *                           ||| ---- SINGLE - REPETITIVE
 *                           -------- Dependency
 ******************************************************************************/
#define SW_EVENT_OFF            0x00
#define SW_EVENT_ON             0x01
#define SW_EVENT_SINGLE         0x00
#define SW_EVENT_REPETITIVE     0x02
#define SW_EVENT_TIME_DEP       0x04
#define SW_EVENT_TEMP_DEP       0x08
#define SW_EVENT_TIME_TEMP_DEP  0x0C


/**** Structures ****/
typedef struct SW_M_Time_s
{
  uint8 Hour;   // Hour value
  uint8 Minute; // Minute value
  uint8 Second; // Second value
} SW_M_Time_t;

typedef struct SW_M_Date_s
{
  uint8 Month;  // Month value
  uint8 Day;    // Day value
  uint8 DoW;    // Day of week
  uint16 Year;  // Year value
} SW_M_Date_t;

typedef struct SW_M_Temp_s
{
  sint16 Temp;
  uint8 Sensor;
  uint8 Event;
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

#endif // _SW_Management_h