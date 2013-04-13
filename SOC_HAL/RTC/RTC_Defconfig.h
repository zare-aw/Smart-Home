#ifndef _RTC_Defconfig_H
#define _RTC_Defconfig_H


#define RTC_COUNT_PER_SEC   32768
#define RTC_INC_CALLBACKS   10
#define NO_OF_SW_ALARMS     20

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

static RtcDateTime_t RTC_InitDateTime = {2012, 1, 1, 0, 0, 0};

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
	"March ",
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

#endif  // _RTC_Defconfig_H

