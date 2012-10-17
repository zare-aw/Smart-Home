#ifndef _DS1820_Debug_h
#define _DS1820_Debug_h

#define _DS_INFO             1
#define _DS_DEBUG            1
//#define _DS_LOW_LEVEL_DEBUG  1

#ifdef _DS_INFO
#define DS_INFO(a) a
#else
#define DS_INFO(a)
#endif

#ifdef _DS_DEBUG
#define DS_DEBUG(a) a
#else
#define DS_DEBUG(a)
#endif

#ifdef _DS_LOW_LEVEL_DEBUG
#define DS_LL_DEBUG(a) a
#else
#define DS_LL_DEBUG(a)
#endif

#endif
