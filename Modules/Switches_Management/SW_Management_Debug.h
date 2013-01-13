#ifndef _SW_Management_Debug_h
#define _SW_Management_Debug_h

#include "Func_Trace.h"

/**** Debug switches (definitions) ****/
#define _SW_M_FUNC_REGISTER     1

#define _SW_M_INFO        1

#define _SW_M_DEBUG       1
#define _SW_M_DEBUG_L1    1
#define _SW_M_DEBUG_L2    1
#define _SW_M_DEBUG_L3    1

/**** Debug Macros ****/
#ifdef _SW_M_FUNC_REGISTER
#define SW_M_FUNC_REGISTER(Func, Name) FUNC_REGISTER(Func, Name)
#else
#define SW_M_FUNC_REGISTER(Func, Name)
#endif


#ifdef _SW_M_DEBUG
#define SW_M_DEBUG(a) a
#else
#define SW_M_DEBUG(a)
#endif

#ifdef _SW_M_INFO
#define SW_M_INFO(a) a
#else
#define SW_M_INFO(a)
#endif

#ifdef _SW_M_DEBUG_L1
#define SW_M_DEBUG_L1(a) a
#else
#define SW_M_DEBUG_L1(a)
#endif

#ifdef _SW_M_DEBUG_L2
#define SW_M_DEBUG_L2(a) a
#else
#define SW_M_DEBUG_L2(a)
#endif

#ifdef _SW_M_DEBUG_L3
#define SW_M_DEBUG_L3(a) a
#else
#define SW_M_DEBUG_L3(a)
#endif


#endif // _SW_Management_Debug_h