#ifndef _Command_Debug_h
#define _Command_Debug_h

#define __COMMAND_DEBUG

#ifdef __COMMAND_DEBUG
#include "StatusHandling.h"
#else
typedef int Status_t;
#endif

#ifndef NULL
#define NULL  0
#endif

#ifdef __COMMAND_DEBUG
#define FUNCTION_IN(Function) Function_IN(Function)
#define FUNCTION_OUT(Function) Function_OUT(Function)
#define RET_SUCCESS(Function) RETURN_SUCCESS_FUNC(Function)
#else
#define FUNCTION_IN(Function)
#define FUNCTION_OUT(Function)
#define RET_SUCCESS(Function) return CMD_SUCCESS;
#endif

#define FATAL_ABORT(Status, Function) \
  do {\
    if(Abort(Status)) \
    {\
      FUNCTION_OUT(Function); \
      return Status;\
    }\
  }while (0)

#define FUNC_EXIT(Status, Function) \
  do {\
    FUNCTION_OUT(Function); \
    return Status;\
  }while (0)


#endif