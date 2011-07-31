#ifndef _RTC_H
#define _RTC_H

#include "Includes.h"

#define RTC_COUNT_PER_SEC     32768

#define RTC_YEARMIN         1901
#define RTC_YEARMAX         2099

// 1901.1.1 DOW = 2
#define RTC_BASEYEAR        1901
#define RTC_BASEMONTH       1
#define RTC_BASEDAY         1
#define RTC_BASEDOW         2

/* RTC Interrupt location register bit descriptions */
#define ILR_CIF_BIT         0
#define ILR_ALF_BIT         1

/* RTC Clock control register bit descriptions */
#define CCR_CLKEN_BIT       0
#define CCR_CTCRST_BIT      1

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

 /* RTC interrupt type */
#define RTCIncrementInt	    0x1
#define RTCAlarmInt	    0x2
#define RTCALLInt	    0x3

typedef struct {
	uint16 Year;  // Year value
	uint8 Month;  // Month value
	uint8 Day;    // Day value

	/* the below member is used in get-operation */
	uint8 DoW;    // Day of week
	uint16 DoY;    // Day of year
} RtcDate_t;

typedef struct {
	uint8 Hour;   // Hour value
	uint8 Minute; // Minute value
	uint8 Second; // Second value
} RtcTime_t;

typedef struct {
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

static RtcDateTime_t RTC_InitDateTime = {2011, 1, 1, 0, 0, 0};

static char *RTC_DOWTbl[] = {
	"Sunday ",
	"Monday ",
	"Tuesday ",
	"Wednesday ",
	"Thursday ",
	"Friday ",
	"Saturday "
};

static char *RTC_MonthTbl[] = {
	"",
	"January ",
	"February ",
	"Match ",
	"April ",
	"May ",
	"June ",
	"July ",
	"August ",
	"September ",
	"October ",
	"November ",
	"December "
};

static int RTC_MonthVal[]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


/* Declare functions */
void RTC_Enable(void);
void RTC_Disable(void);

Status_t RTC_Init(uint8 ClkSource);

Status_t RTC_Set_Date(RtcDate_t *Date_p);
Status_t RTC_Set_Time(RtcTime_t *Time_p);
Status_t RTC_Set_Date_Time(RtcDateTime_t *DateTime_p);

Status_t RTC_Get_Date(RtcDate_t *Date_p);
Status_t RTC_Get_Time(RtcTime_t *Time_p);
Status_t RTC_Get_Date_Time(RtcDateTime_t *DateTime_p);

void RTC_Enable_Inc_Int(uint8 IncIntType, void *Callback_p);
void RTC_Disable_Inc_Int(void);

Status_t RTC_Enable_Alarm(uint8 AlarmIntType, RtcDateTime_t *DateTime_p, void *Callback_p);
void RTC_Disable_Alarm_Int(void);

Status_t RTC_Clear_Int(uint32 IntType);
uint32 RTC_Check_Int_Type(void);

Status_t Format_Date(uint8 Type, RtcDate_t *Date_p, char *s);
Status_t Format_Time(uint8 Type, RtcTime_t *Time_p, char *s);

#endif  // _RTC_H