#ifndef _StatusHandling_h
#define _StatusHandling_h

#include "Func_Trace.h"

typedef int Status_t;
typedef unsigned long Function_t;

#define MAX_FUNCTION_IN_BECKUP_BUFFER  10

#define FUNC_OUT_MASK     0x80000000

//#define _STATUS_DEBUG

#ifdef _STATUS_DEBUG
#define STATUS_DEBUG(a) a
#else
#define STATUS_DEBUG(a)
#endif

extern Function_t FunctionBuffer[MAX_FUNCTION_IN_BECKUP_BUFFER];
extern uint8 FunctionInBeckupBuffer;

/*******************************************************************************
 * Functions definitions
*******************************************************************************/
void Function_IN(Function_t Function);
void Function_OUT(Function_t Function);
void This_Function_OUT(void);
void Fatal_Abort(Status_t Status);
uint8 Abort(Status_t Status);
void Print_Function_History(void);

/*******************************************************************************
* Macro definitions
*******************************************************************************/
#define VERIFY(Status, Error) \
  do { \
    if (Status < SUCCESS) \
    { \
      Fatal_Abort(Error); \
    } \
  }while (0)

#define ASSERT(Condition, Status) \
  do { \
    if (!(Condition)) \
    {\
      Fatal_Abort(Status); \
    }\
  }while (0)



#define EXIT_FUNC(Status, Func) \
  do {\
    FuncOUT(Func); \
    return Status; \
  }while (0)

#define EXIT_SUCCESS_FUNC(Func)\
  do {\
    FuncOUT(Func); \
    return SUCCESS; \
  }while(0)


/*******************************************************************************
* Macro definitions
*******************************************************************************/
#if 1
#define CONTROL(Condition, Status) \
     do {\
       if (!(Condition)) \
         {\
           if(Abort(Status)) \
             {\
               This_Function_OUT(); \
               return Status;\
             }\
         }\
     }while (0)

#define CONTROL_ABORT(Condition, Status) \
     do {\
       if (!(Condition)) \
         {\
           if(Abort(Status)) \
             {\
               This_Function_OUT(); \
             }\
         }\
     }while (0)

#define CONTROL_EXIT(Condition, Status) \
     do {\
       if (!(Condition)) \
       {\
         This_Function_OUT(); \
         return Status;\
       }\
     }while (0)

#define CONTROL_EXIT_FUNC(Condition, Status, Func) \
     do {\
       if (!(Condition)) \
       {\
         Function_OUT(Func); \
         return Status; \
       }\
     }while (0)

#define EXIT(Condition, Status) \
     do {\
       if (!(Condition)) \
       {\
         return Status;\
       }\
     }while (0)

#define RETURN_SUCCESS()\
  do {\
    This_Function_OUT(); \
    return SUCCESS; \
  }while(0)

#define RETURN_SUCCESS_FUNC(Func)\
  do {\
    Function_OUT(Func); \
    return SUCCESS; \
  }while(0)
#endif

/*******************************************************************************
* Status defines
*******************************************************************************/
#define SUCCESS                             0
#define INFO                                1
#define ERROR                               2
#define GENERAL_ERROR                       3
#define FATAL_ERROR                         4
#define	UNKNOWN_ERROR		            5
#define COMMUNICATION_ERROR	            6
#define INVALID_INPUT_PARAMETER             7
#define INVALID_INIT_INPUT_PARAMETER        8
#define INVALID_INPUT_POINTER               9

#define UNDEFINED_INSTRUCTIONS_EXCEPTION    10
#define SOFTWARE_INTERRUPT_EXCEPTION        11
#define PREFETCH_ABORT_EXCEPTION            12
#define DATA_ABORT_EXCEPTION                13

#define	MEMORY_ERROR                        15
#define HEAP_ALLOCATION_ERROR               16
#define REGISTER_ERROR                      17

#define NOT_REGISTERED_ERROR                20

#define BUS_ERROR                           31
#define PCLKSEL_ERROR                       32

#define TIMER_CLOCK_ERROR                   130

#define IR_GENERAL_ERROR                    200
#define IR_COMMAND_ERROR                    201
#define IR_CALLBACK_ERROR                   202
#define IR_READ_ERROR                       203
#define IR_COMMAND_SET_ERROR                204
#define IR_COMMAND_GET_ERROR                205
#define IR_COMMAND_INIT_ERROR               206

#define MENU_ERROR                          350
#define MENU_DISPLAY_ERROR                  351

#define TEMP_SLOTS_ERROR                    400
#define TEMP_SENSOR_REGISTER_ERROR          401
#define TEMP_SENSOR_REINIT_ERROR            402
#define TEMP_SET_ALARM_ERROR                403
#define TEMP_ALARM_REGISTER_ERROR           404
#define TEMP_ALARM_SET_STATE_ERROR          405

/*******************************************************************************
* Function code definition
*******************************************************************************/
// ConsoleHelp
#define CONSOLE_HELP                  1250
#define CONSOLE_STATUS                1251
#define CONSOLE_LIST                  1252
#define CONSOLE_INFO                  1253
#define CONSOLE_TIME                  1254
#define CONSOLE_DATE                  1255
#define CONSOLE_SET_TIME              1256
#define CONSOLE_SET_DATE              1257
#define CONSOLE_CONFIG                1258
#define CONSOLE_SET_CONFIG            1259
#define CONSOLE_IR                    1260
#define CONSOLE_SET_IR                1261
#define CONSOLE_BACKLIGHT             1262
#define CONSOLE_SET_BACKLIGHT         1263
#define CONSOLE_LIGHT_SWITCH          1264
#define CONSOLE_SET_LIGHT_SWITCH      1265
#define CONSOLE_OUT_SWITCH            1266
#define CONSOLE_SET_OUT_SWITCH        1267
#define CONSOLE_SWITCH_SETTINGS       1268
#define CONSOLE_SET_SWITCH_SETTINGS   1269
#define CONSOLE_TEMP                  1270
#define CONSOLE_ALARM                 1271
#define CONSOLE_SET_ALARM             1272
#define CONSOLE_TEMP_ALARM            1273
#define CONSOLE_SET_TEMP_ALARM        1274

// Debug Commands help
#define CONSOLE_DUMP_DISPLAY          1500
#define CONSOLE_UPDATE_DISPLAY        1501

// Console Commands
#define GET_TIME_COMMAND                2001
#define SET_TIME_COMMAND                2002
#define GET_DATE_COMMAND                2003
#define SET_DATE_COMMAND                2004
#define GET_CONFIGURATION_COMMAND       2005
#define SET_CONFIGURATIONS_COMMAND      2006
#define GET_IR_COMMANDS_COMMAND         2007
#define SET_IR_COMMANDS_COMMAND         2008
#define GET_BACK_LIGHT_LEVEL_COMMAND    2009
#define SET_BACK_LIGHT_LEVEL_COMMAND    2010
#define GET_LIGHT_SWITCH_LEVEL_COMMAND  2011
#define SET_LIGHT_SWITCH_LEVEL_COMMAND  2012
#define GET_OUT_SWITCH_COMMAND          2013
#define SET_OUT_SWITCH_COMMAND          2014
#define GET_TEMP_COMMAND                2015
#define GET_SWITCH_SETINGS_COMMAND      2016
#define SET_SWITCH_SETINGS_COMMAND      2017
#define GET_ALARM_COMMAND               2030
#define SET_ALARM_COMMAND               2031
#define GET_TEMP_ALARM_COMMAND          2032
#define SET_TEMP_ALARM_COMMAND          2033

// Debug Commands
#define DISPLAY_DUMP_COMMAND            2500
#define DISPLAY_UPDATE_COMMAND          2501

#endif
