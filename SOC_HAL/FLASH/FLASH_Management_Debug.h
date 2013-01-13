#ifndef _FLASH_Management_Debug_h
#define _FLASH_Management_Debug_h

#include "Func_Trace.h"

/**** Debug switches (definitions) ****/
#define _FLASH_FUNC_REGISTER     1

#define _FLASH_INFO        1

//#define _FLASH_DEBUG       1
//#define _FLASH_DEBUG_L1    1
//#define _FLASH_DEBUG_L2    1
//#define _FLASH_DEBUG_L3    1

/**** Debug Macros ****/
#ifdef _FLASH_FUNC_REGISTER
#define FLASH_FUNC_REGISTER(Func, Name) FUNC_REGISTER(Func, Name)
#else
#define FLASH_FUNC_REGISTER(Func, Name)
#endif


#ifdef _FLASH_DEBUG
#define FLASH_DEBUG(a) a
#else
#define FLASH_DEBUG(a)
#endif

#ifdef _FLASH_INFO
#define FLASH_INFO(a) a
#else
#define FLASH_INFO(a)
#endif

#ifdef _FLASH_DEBUG_L1
#define FLASH_DEBUG_L1(a) a
#else
#define FLASH_DEBUG_L1(a)
#endif

#ifdef _FLASH_DEBUG_L2
#define FLASH_DEBUG_L2(a) a
#else
#define FLASH_DEBUG_L2(a)
#endif

#ifdef _FLASH_DEBUG_L3
#define FLASH_DEBUG_L3(a) a
#else
#define FLASH_DEBUG_L3(a)
#endif

#endif // _FLASH_Management_Debug_h