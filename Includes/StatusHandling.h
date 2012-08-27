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
    return Status;\
  }while (0)

#define EXIT_SUCCESS_FUNC(Func)\
  do {\
    FuncOUT(Func); \
    return SUCCESS; \
  }while(0)


/*******************************************************************************
* Macro definitions
*******************************************************************************/
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

#define DLY_BUSY_ERROR                      140
#define DLY_TIMER_UNAVAILABLE_ERROR         141

#define IR_GENERAL_ERROR                    200
#define IR_COMMAND_ERROR                    201
#define IR_CALLBACK_ERROR                   202
#define IR_READ_ERROR                       203
#define IR_COMMAND_SET_ERROR                204
#define IR_COMMAND_GET_ERROR                205
#define IR_COMMAND_INIT_ERROR               206

#define DS1820_NO_PRESENCE_ERROR            300
#define DS1820_SHORT_CIRCUIT_ERROR          301
#define DS1820_UNABLE_TO_READ_DATA_ERROR    302

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
// System
#define INITIALIZATION                10

// Delay
#define DLY                           400

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

// IR Driver
#define IR_INIT                         10000
#define IR_COMMAND_INIT                 10001
#define IR_SET_COMMAND                  10002
#define IR_GET_COMMAND                  10003
#define IR_TIMER_ISR                    10004
#define IR_INPUT_ISR                    10005
#define IR_EXT_INTERRUPT_ISR            10006
#define IR_EXT_INTERRUPT_INIT           10007

// Out Driver
#define OUT_INIT                        10100
#define OUT_SYNC                        10101
#define OUT_GET_STATE                   10102

// Menu Callbacks
#define MENU_CALLBACKS_INIT             10200
#define POWER_KEY_CALLBACK              10201
#define UP_KEY_CALLBACK                 10202
#define DOWN_KEY_CALLBACK               10203
#define LEFT_KEY_CALLBACK               10204
#define RIGHT_KEY_CALLBACK              10205
#define ENTER_KEY_CALLBACK              10206
#define CANCEL_KEY_CALLBACK             10207
#define MENU_KEY_CALLBACK               10208
#define EXIT_KEY_CALLBACK               10209
#define NUM1_KEY_CALLBACK               10211
#define NUM2_KEY_CALLBACK               10212
#define NUM3_KEY_CALLBACK               10213
#define NUM4_KEY_CALLBACK               10214
#define NUM5_KEY_CALLBACK               10215
#define NUM6_KEY_CALLBACK               10216
#define NUM7_KEY_CALLBACK               10217
#define NUM8_KEY_CALLBACK               10218
#define NUM9_KEY_CALLBACK               10219
#define NUM0_KEY_CALLBACK               10220
#define VOL_UP_KEY_CALLBACK             10221
#define VOL_DOWN_KEY_CALLBACK           10222
#define CH_UP_KEY_CALLBACK              10223
#define CH_DOWN_KEY_CALLBACK            10224
#define MUTE_KEY_CALLBACK               10225

// DS1820 Driver
#define DS1820_INIT                     10500
#define DS1820_START_CONVERSION         10501
#define DS1820_READ_TEMP                10502
#define DS1820_READ_SN                  10503
#define DS_RESET                        10520

// Menu
#define MENU_INIT                       10600
#define MENU                            10601
#define DISPLAY_MENU_UPDATE             10602
#define DISPLAY_DATE_TIME_UPDATE        10603
#define DISPLAY_TEMP_UPDATE             10604
#define REGISTER_MENU_TEMP              10605
#define UNREGISTER_MENU_TEMP            10606
#define MENU_SEC_INT_CALLBACK           10607
#define UPDATE_DISPLAY_PANEL            10608
#define UPDATE_SURFACE_BUFFER           10609
#define PRINTD                          10610

// Temperature
#define REGISTER_TEMP_SENSOR            10700
#define UNREGISTER_TEMP_SENSOR          10701
#define REGISTER_TEMP_ALARM             10702
#define SET_TEMP_ALARM                  10703
#define UNREGISTER_TEMP_ALARM           10704
#define SET_STATE_TEMP_ALARM            10705
#define READ_TEMP_ALARM                 10706
#define TEMP_INIT                       10707
#define TEMP_REINIT                     10708
#define TEMP_WORK                       10709

// Backlight
#define BACKLIGHT_INIT                  10900
#define SET_BACKLIGHT_INTENSITY         10901

#endif
