#ifndef _RTC_Func_H
#define _RTC_Func_H

#include "Func_Trace.h"

// RTC.c
#define RTC_INIT                        RTC_OFFSET | 0x01
#define RTC_SET_DATE                    RTC_OFFSET | 0x02
#define RTC_SET_TIME                    RTC_OFFSET | 0x03
#define RTC_SET_DATE_TIME               RTC_OFFSET | 0x04
#define RTC_GET_DATE                    RTC_OFFSET | 0x05
#define RTC_GET_TIME                    RTC_OFFSET | 0x06
#define RTC_GET_DATE_TIME               RTC_OFFSET | 0x07
#define RTC_ENABLE_INC_INT              RTC_OFFSET | 0x08
#define RTC_DISABLE_INC_INT             RTC_OFFSET | 0x09
#define RTC_REGISTER_INC_INT            RTC_OFFSET | 0x0A
#define RTC_UNREGISTER_INC_INT          RTC_OFFSET | 0x0B
#define RTC_ENABLE_ALARM                RTC_OFFSET | 0x0C
#define RTC_CLEAR_INT                   RTC_OFFSET | 0x0D
#define RTC_REGISTER_SW_ALARM           RTC_OFFSET | 0x0E
#define RTC_UNREGISTER_SW_ALARM         RTC_OFFSET | 0x0F
#define RTC_GET_REGISTERED_SW_ALARM     RTC_OFFSET | 0x10
#define RTC_SW_ALARM_CALLBACK           RTC_OFFSET | 0x11
#define RTC_ISR                         RTC_OFFSET | 0x12

#define FORMAT_DATE                     RTC_OFFSET | 0x20
#define FORMAT_TIME                     RTC_OFFSET | 0x21

#endif  // _RTC_Func_H

