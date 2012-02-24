#ifndef _Command_Debug_h
#define _Command_Debug_h

#define COMMAND_DEBUG

typedef unsigned int Status_t;

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
#ifdef _StatusHandling_h
#include "StatusHandling.h"
#define FUNCTION_IN(Function) Function_In(Function)
#define CMD_RETURN_SUCCESS(Function) RETURN_SUCCESS_FUNC(Function)
#endif
#else
#define FUNCTION_IN(Function) 0
#define CMD_RETURN_SUCCESS(Function) return CMD_SUCCESS;
#endif

#endif