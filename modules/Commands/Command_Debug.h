#ifndef _Command_Debug_h
#define _Command_Debug_h

#define COMMAND_DEBUG

#ifdef COMMAND_DEBUG
#include "StatusHandling.h"
#else
typedef unsigned int Status_t;
#endif

#ifndef NULL
#define NULL  0
#endif

// Cmd Global error state defines
#define CMD_SUCCESS                             0x00
#define CMD_ERROR                               0x01
#define CMD_GENERAL_ERROR                       0x02
#define CMD_FATAL_ERROR                         0x03
#define	CMD_UNKNOWN_ERROR		        0x04
#define CMD_INVALID_INPUT_PARAMETER             0x05
#define CMD_INVALID_INIT_INPUT_PARAMETER        0x06
#define CMD_INVALID_INPUT_POINTER               0x07


#ifdef COMMAND_DEBUG
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