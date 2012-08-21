#ifndef _Console_Func_h
#define _Console_Func_h

#include "Func_Trace.h"
#include "StatusHandling.h"

/**** Function definitions ****/
Status_t Get_Console_Func_String(Func_t Function, char *FuncString);

/**** Function Flag definitions ****/
// Console.c
#define ADD_STRING_IN_CONSOLE_QUEUE         CONSOLE_OFFSET | 0x01
#define CONSOLE_PRINT_PULL                  CONSOLE_OFFSET | 0x02
#define CONSOLE_ISR                         CONSOLE_OFFSET | 0x03
#define CONSOLE_SERVER_INIT                 CONSOLE_OFFSET | 0x04
#define ADD_CONSOLE_COMMAND_IN_QUEUE        CONSOLE_OFFSET | 0x05
#define ADD_CONSOLE_COMMAND_IN_HISTORY      CONSOLE_OFFSET | 0x06
#define GET_CONSOLE_COMMAND_FROM_HISTORY    CONSOLE_OFFSET | 0x07
#define REMOVE_CONSOLE_COMMAND_FROM_QUEUE   CONSOLE_OFFSET | 0x08
#define CONSOLE_COMMAND_EXECUTE             CONSOLE_OFFSET | 0x09

#endif
