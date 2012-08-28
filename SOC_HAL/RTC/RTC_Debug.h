#ifndef _RTC_Debug_H
#define _RTC_Debug_H


#define _RTC_DEBUG            1
#define _RTC_LOW_LEVEL_DEBUG  1

#ifdef _RTC_DEBUG
#define RTC_DEBUG(a) a
#else
#define RTC_DEBUG(a)
#endif

#ifdef _RTC_LOW_LEVEL_DEBUG
#define RTC_LL_DEBUG(a) a
#else
#define RTC_LL_DEBUG(a)
#endif

#endif  // _RTC_Debug_H

