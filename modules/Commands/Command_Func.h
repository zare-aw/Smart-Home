#ifndef _Command_Func_h
#define _Command_Func_h

#include "Func_Trace.h"
#include "StatusHandling.h"

#define FIND_CMD        COMMANDS_OFFSET | 0x01
#define RUN_COMMAND     COMMANDS_OFFSET | 0x02
#define PRINTCMD        COMMANDS_OFFSET | 0x03
#define PARSE_LINE      COMMANDS_OFFSET | 0x04
#define COMMANDS_INIT   COMMANDS_OFFSET | 0x05

// cmd_help.c
#define HELP_OFFSET                                         0x0100
#define DO_HELP         COMMANDS_OFFSET | HELP_OFFSET |     0x0001

// cmd_info.c
#define INFO_OFFSET                                         0x0200
#define DO_INFO         COMMANDS_OFFSET | INFO_OFFSET |     0x0001

// cmd_time.c
#define TIME_OFFSET                                         0x0300
#define DO_TIME         COMMANDS_OFFSET | TIME_OFFSET |     0x0001

// cmd_set_time.c
#define SET_TIME_OFFSET                                     0x0400
#define DO_SET_TIME     COMMANDS_OFFSET | SET_TIME_OFFSET | 0x0001

// cmd_date.c
#define DATE_OFFSET                                         0x0500
#define DO_DATE         COMMANDS_OFFSET | DATE_OFFSET |     0x0001

// cmd_set_date.c
#define SET_DATE_OFFSET                                     0x0600
#define DO_SET_DATE     COMMANDS_OFFSET | SET_DATE_OFFSET | 0x0001

// cmd_ir.c
#define IR_OFFSET                                           0x0700
#define DO_IR           COMMANDS_OFFSET | IR_OFFSET |       0x0001

// cmd_bl.c
#define BL_OFFSET                                           0x0800
#define DO_BL           COMMANDS_OFFSET | BL_OFFSET |       0x0001

// cmd_temp.c
#define TEMP_OFFSET                                         0x0900
#define DO_TEMP         COMMANDS_OFFSET | TEMP_OFFSET |     0x0001

// cmd_dd.c
#define DD_OFFSET                                           0x0A00
#define DO_DD           COMMANDS_OFFSET | DD_OFFSET |       0x0001

// cmd_du.c
#define DU_OFFSET                                           0x0B00
#define DO_DU           COMMANDS_OFFSET | DU_OFFSET |       0x0001

// cmd_set_ir.c
#define SET_IR_OFFSET                                       0x0C00
#define DO_SET_IR       COMMANDS_OFFSET | SET_IR_OFFSET |   0x0001

// cmd_switch.c
#define SW_OFFSET                                           0x0D00
#define DO_SW           COMMANDS_OFFSET | SW_OFFSET |       0x0001

#endif
