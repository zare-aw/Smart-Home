#ifndef _TSOP1738_Debug_h
#define _TSOP1738_Debug_h

#define _TSOP_INFO
//#define _TSOP_DEBUG
//#define _TSOP_DEBUG_L1
//#define _TSOP_DEBUG_L2


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

#ifdef _TSOP_DEBUG_L1
#define TSOP_DEBUG_L1(a) a
#else
#define TSOP_DEBUG_L1(a)
#endif

#ifdef _TSOP_DEBUG_L2
#define TSOP_DEBUG_L2(a) a
#else
#define TSOP_DEBUG_L2(a)
#endif

#endif
