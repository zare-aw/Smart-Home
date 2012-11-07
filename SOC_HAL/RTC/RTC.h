#ifndef _RTC_H
#define _RTC_H

#include "StatusHandling.h"

/*******************************************************************************
 * RTC Status defines
 ******************************************************************************/
#define RTC_GENERAL_ERROR             RTC_OFFSET | 0x01
#define RTC_INIT_ERROR                RTC_OFFSET | 0x02
#define RTC_SET_ERROR                 RTC_OFFSET | 0x03
#define RTC_INVALID_DATE_ERROR        RTC_OFFSET | 0x04
#define RTC_INVALID_TIME_ERROR        RTC_OFFSET | 0x05
#define RTC_SW_ALARM_SLOTS_ERROR      RTC_OFFSET | 0x06
#define RTC_SW_ALARM_NOT_VALID        RTC_OFFSET | 0x07
#define RTC_INC_INT_SLOTS_ERROR       RTC_OFFSET | 0x08
#define RTC_INC_INT_NOT_VALID         RTC_OFFSET | 0x09

/*******************************************************************************
 * RTC Types
 ******************************************************************************/
/* RTC Increment Interrupt Type */
#define IncIntType_SEC	    0x1
#define IncIntType_MIN	    0x2
#define IncIntType_HOUR	    0x4
#define IncIntType_DAY	    0x8
#define IncIntType_MON	    0x40
#define IncIntType_YEAR	    0x80
#define IncIntType_DOW	    0x10
#define IncIntType_DOY	    0x20

/* RTC Alarm Interrupt Type */
#define AlarmIntType_SEC    0x1
#define AlarmIntType_MIN    0x2
#define AlarmIntType_HOUR   0x4
#define AlarmIntType_DAY    0x8
#define AlarmIntType_MON    0x40
#define AlarmIntType_YEAR   0x80
#define AlarmIntType_DOW    0x10
#define AlarmIntType_DOY    0x20

 /* Alarm Mode */
#define SINGLE_ALARM        0x1
#define REPETITIVE_ALARM    0x2

 /* Alarm State */
#define NO_ALARM_SET        0x0
#define RTC_ALARM_OFF       0x1
#define RTC_ALARM_ON        0x2

 /* Repetitive alarm masks */
#define MONDAY              0x01
#define TUESDAY             0x02
#define WEDNESDAY           0x04
#define THURSDAY            0x08
#define FRIDAY              0x10
#define SATURDAY            0x20
#define SUNDAY              0x40

/*******************************************************************************
 * Typedefs and Structures
 ******************************************************************************/
typedef struct
{
  uint16 Year;  // Year value
  uint8 Month;  // Month value
  uint8 Day;    // Day value

  /* the below member is used in get-operation */
  uint8 DoW;    // Day of week
  uint16 DoY;    // Day of year
} RtcDate_t;

typedef struct
{
  uint8 Hour;   // Hour value
  uint8 Minute; // Minute value
  uint8 Second; // Second value
} RtcTime_t;

typedef struct
{
  uint16 Year;  // Year value
  uint8 Month;  // Month value
  uint8 Day;    // Day value

  uint8 Hour;   // Hour value
  uint8 Minute; // Minute value
  uint8 Second; // Second value

  /* the below member is used in get-operation */
  uint8 DoW;    // Day of week
  uint16 DoY;    // Day of year
} RtcDateTime_t;

typedef struct
{
  uint16 Year;
  uint8 Month;
  uint8 Day;
  
  uint8 Hour;
  uint8 Minute;
  
  uint8 Mode;   // REPETITIVE_ALARM, SINGLE_ALARM. For repetitive is reading from DoW
  uint8 State;  // RTC_ALARM_OFF, RTC_ALARM_ON or NO_ALARM_SET.
  
  void *Callback;   // Return Status_t and get void pointer
  
  uint8 DoW;    // Day of week, one bit is one day starting from bit 0 - Monday
} RtcSwAlarm_t;
/**************************************************************
 * Functions Declarations
 *************************************************************/
void RTC_Enable(void);
void RTC_Disable(void);

Status_t RTC_Init(uint8 ClkSource);

Status_t RTC_Set_Date(RtcDate_t *Date_p);
Status_t RTC_Set_Time(RtcTime_t *Time_p);
Status_t RTC_Set_Date_Time(RtcDateTime_t *DateTime_p);

Status_t RTC_Get_Date(RtcDate_t *Date_p);
Status_t RTC_Get_Time(RtcTime_t *Time_p);
Status_t RTC_Get_Date_Time(RtcDateTime_t *DateTime_p);

Status_t RTC_Register_Inc_Int(void *Callback_p, uint32 Type, uint8 *Alarm_ID);
Status_t RTC_Unregister_Inc_Int(uint8 Alarm_ID);

Status_t RTC_Enable_Alarm(uint8 AlarmIntType, RtcDateTime_t *DateTime_p, void *Callback_p);
void RTC_Disable_Alarm_Int(void);

Status_t RTC_Clear_Int(uint32 IntType);
uint32 RTC_Check_Int_Type(void);

Status_t RTC_Register_SW_Alarm(RtcSwAlarm_t *AlarmData_p, uint8 *AlarmID);
Status_t RTC_Unregister_SW_Alarm(uint8 AlarmID);
Status_t RTC_Get_Registered_Sw_Alarms(RtcSwAlarm_t *AlarmData_p, uint8 *NoOfAlarms);

Status_t Format_Date(uint8 Type, RtcDate_t *Date_p, char *s);
Status_t Format_Time(uint8 Type, RtcTime_t *Time_p, char *s);

#endif  // _RTC_H

