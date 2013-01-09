#ifndef _Alarm_Debug_h
#define _Alarm_Debug_h

#define _ALARM_INFO 1
#define _ALARM_DEBUG 0


#ifdef _ALARM_INFO
#define ALARM_INFO(a) a
#else
#define ALARM_INFO(a)
#endif

#ifdef _ALARM_DEBUG
#define ALARM_DEBUG(a) a
#else
#define ALARM_DEBUG(a)
#endif

#endif
