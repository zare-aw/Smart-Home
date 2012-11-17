#ifndef _Temperature_Debug_h
#define _Temperature_Debug_h

#define _TEMP_INFO
#define _TEMP_DEBUG


#ifdef _TEMP_INFO
#define TEMP_INFO(a) a
#else
#define TEMP_INFO(a)
#endif

#ifdef _TEMP_DEBUG
#define TEMP_DEBUG(a) a
#else
#define TEMP_DEBUG(a)
#endif

#endif
