#ifndef _Command_Debug_h
#define _Command_Debug_h

#define COMMAND_DEBUG

#ifdef COMMAND_DEBUG
#ifdef _StatusHandling_h
#include "StatusHandling.h"
#define FUNCTION_IN(Function) Function_In(Function)
#define CMD_RETURN_SUCCESS(Function) RETURN_SUCCESS_FUNC(Function)
#endif
#else
#define FUNCTION_IN(Function) 0
#define CMD_RETURN_SUCCESS(Function) return 0;
#endif

#endif