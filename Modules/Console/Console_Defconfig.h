#ifndef _Console_Defconfig_h
#define _Console_Defconfig_h

#include "UART_LPC214X.h"

#define MAX_CONSOLE_COMMAND_LENGTH         128
#define CONSOLE_QUEUE_SIZE                 2048
#define MAX_CONSOLE_COMMAND_IN_QUEUE       3
#define VS_BUFFER_SIZE                     128
#define MAX_CONSOLE_COMMAND_HISTORY        3

#define CONSOLE_CHANELL     UART_0
#define CONSOLE_SPEED       115200
#define CONSOLE_MODE        MODE_POOLING

#ifndef MODE_INTERRUPT
#define MODE_INTERRUPT      1
#endif
#ifndef MODE_POOLING
#define MODE_POOLING        0
#endif

#endif
