#ifndef _Command_Func_h
#define _Command_Func_h

#include "StatusHandling.h"

#define FIND_CMD        COMMANDS_OFFSET | 0x01
#define RUN_COMMAND     COMMANDS_OFFSET | 0x02
#define PRINTCMD        COMMANDS_OFFSET | 0x03
#define PARSE_LINE      COMMANDS_OFFSET | 0x04
#define COMMANDS_INIT   COMMANDS_OFFSET | 0x05

// cmd_help.c
#define HELP_OFFSET     0x0100
#define DO_HELP         COMMANDS_OFFSET | HELP_OFFSET | 0x01

// cmd_info.c
#define INFO_OFFSET     0x0200
#define DO_INFO         COMMANDS_OFFSET | INFO_OFFSET | 0x01

// cmd_time.c
#define TIME_OFFSET     0x0300
#define DO_TIME         COMMANDS_OFFSET | TIME_OFFSET | 0x01

// cmd_set-time.c
#define SET_TIME_OFFSET 0x0400
#define DO_SET_TIME     COMMANDS_OFFSET | SET_TIME_OFFSET | 0x01

#endif
