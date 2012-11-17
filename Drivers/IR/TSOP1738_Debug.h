#ifndef _TSOP1738_Debug_h
#define _TSOP1738_Debug_h

#define _TSOP_INFO
//#define _TSOP_DEBUG


#ifdef _TSOP_INFO
#define TSOP_INFO(a) a
#else
#define TSOP_INFO(a)
#endif

#ifdef _TSOP_DEBUG
#define TSOP_DEBUG(a) a
#else
#define TSOP_DEBUG(a)
#endif

#endif
