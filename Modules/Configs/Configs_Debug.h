#ifndef _Configs_Debug_h
#define _Configs_Debug_h

#include "Func_Trace.h"

/**** Debug switches (definitions) ****/
#define _CONFIG_FUNC_REGISTER     1

#define _CONFIG_INFO        1

#define _CONFIG_DEBUG       1
#define _CONFIG_DEBUG_L1    1
#define _CONFIG_DEBUG_L2    1
#define _CONFIG_DEBUG_L3    1

/**** Debug Macros ****/
#ifdef _CONFIG_FUNC_REGISTER
#define CONFIG_FUNC_REGISTER(Func, Name) FUNC_REGISTER(Func, Name)
#else
#define CONFIG_FUNC_REGISTER(Func, Name)
#endif


#ifdef _CONFIG_DEBUG
#define CONFIG_DEBUG(a) a
#else
#define CONFIG_DEBUG(a)
#endif

#ifdef _CONFIG_INFO
#define CONFIG_INFO(a) a
#else
#define CONFIG_INFO(a)
#endif

#ifdef _CONFIG_DEBUG_L1
#define CONFIG_DEBUG_L1(a) a
#else
#define CONFIG_DEBUG_L1(a)
#endif

#ifdef _CONFIG_DEBUG_L2
#define CONFIG_DEBUG_L2(a) a
#else
#define CONFIG_DEBUG_L2(a)
#endif

#ifdef _CONFIG_DEBUG_L3
#define CONFIG_DEBUG_L3(a) a
#else
#define CONFIG_DEBUG_L3(a)
#endif

#endif // _Configs_Debug_h