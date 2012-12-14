#ifndef _Alarm_Debug_h
#define _Alarm_Debug_h

#define _TIME_INFO 1
#define _TIME_DEBUG 1


#ifdef _TIME_INFO
#define TIME_INFO(a) a
#else
#define TIME_INFO(a)
#endif

#ifdef _TIME_DEBUG
#define TIME_DEBUG(a) a
#else
#define TIME_DEBUG(a)
#endif

#endif
