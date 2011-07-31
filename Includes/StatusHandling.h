#ifndef _StatusHandling_h
#define _StatusHandling_h

typedef unsigned int Status_t;
typedef unsigned long Function_t;

#define MAX_FUNCTION_IN_BECKUP_BUFFER  10

extern Function_t FunctionBuffer[MAX_FUNCTION_IN_BECKUP_BUFFER];
extern uint8 FunctionInBeckupBuffer;

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
    Function_OUT(FunctionBuffer[FunctionInBeckupBuffer - 1]); \
    return SUCCESS; \
  }while(0)


/*******************************************************************************
* Status defines
*******************************************************************************/
#define SUCCESS                             0
#define INFO                                1
#define GENERAL_ERROR                       2
#define FATAL_ERROR                         3
#define	UNKNOWN_ERROR		            4
#define COMMUNICATION_ERROR	            5
#define INVALID_INPUT_PARAMETER             6
#define INVALID_INIT_INPUT_PARAMETER        7
#define INVALID_INPUT_POINTER               8

#define	MEMORY_ERROR                        10
#define HEAP_ALLOCATION_ERROR               11

#define SET_SAMPLE_RATE_ERROR               21
#define SET_SAMPLE_NUMBER_ERROR             22

#define BUS_ERROR                           31
#define PCLKSEL_ERROR                       32

#define UART0_SEND_ERROR                    110
#define UART1_SEND_ERROR                    111

#define UART_0_RX_FIFO_ERROR                114
#define UART_1_RX_FIFO_ERROR                115

#define UART0_RECEIVE_ERROR                 118
#define UART1_RECEIVE_ERROR                 119

#define TIMER_CLOCK_ERROR                   130

#define DLY_BUSY_ERROR                      140
#define DLY_TIMER_UNAVAILABLE_ERROR         141

#define CONSOLE_COMMANDS_OVERFLOW           151
#define CONSOLE_COMMAND_ERROR               152
#define CONSOLE_COMMAND_EXECUTE_ERROR       153
#define CONSOLE_CHANNEL_INIT_ERROR          154

#define IR_GENERAL_ERROR                    200
#define IR_COMMAND_ERROR                    201
#define IR_CALLBACK_ERROR                   202
#define IR_READ_ERROR                       203
#define IR_COMMAND_SET_ERROR                204
#define IR_COMMAND_GET_ERROR                205
#define IR_COMMAND_INIT_ERROR               206

#define RTC_GENERAL_ERROR                   250
#define RTC_INIT_ERROR                      251
#define RTC_SET_ERROR                       252
#define RTC_INVALID_DATE_ERROR              253
#define RTC_INVALID_TIME_ERROR              254

#define DS1820_NO_PRESENCE_ERROR            300
#define DS1820_SHORT_CIRCUIT_ERROR          301
#define DS1820_UNABLE_TO_READ_DATA_ERROR    302

/*******************************************************************************
* Function code definition
*******************************************************************************/
#define INITIALIZATION                10
#define PLL_INIT                      12
#define MAM_INIT                      13

#define UART_0_INIT                   110
#define UART_1_INIT                   111

#define SET_INTERRUPT_STATE_UART_0    114
#define SET_INTERRUPT_STATE_UART_1    115

#define SET_TRIGGER_UART_0            118
#define SET_TRIGGER_UART_1            119

#define CONSOLE_COMMAND_EXECUTE       200
#define CONSOLE_SERVER_INIT           201
#define CONSOLE_PRINT_PULL            202
#define CONSOLE_ISR                   203

#define DLY                           400

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
#define CONSOLE_BECKLIGHT             1262
#define CONSOLE_SET_BECKLIGHT         1263
#define CONSOLE_LIGHT_SWITCH          1264
#define CONSOLE_SET_LIGHT_SWITCH      1265
#define CONSOLE_OUT_SWITCH            1266
#define CONSOLE_SET_OUT_SWITCH        1267
#define CONSOLE_SWITCH_SETTINGS       1268
#define CONSOLE_SET_SWITCH_SETTINGS   1269
#define CONSOLE_TEMP                  1270
#define CONSOLE_ALARM                 1271
#define CONSOLE_SET_ALARM             1272

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

// IR driver
#define IR_INIT                         10000
#define IR_COMMAND_INIT                 10001
#define IR_SET_COMMAND                  10002
#define IR_GET_COMMAND                  10003
#define IR_TIMER_ISR                    10004
#define IR_INPUT_ISR                    10005
#define IR_EXT_INTERRUPT_ISR            10006
#define IR_EXT_INTERRUPT_INIT           10007

// Out driver
#define OUT_INIT                        10100
#define OUT_SYNC                        10101

#define MENU_INIT                       10200
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

#define RTC_INIT                        10400
#define RTC_SET_DATE                    10401
#define RTC_SET_TIME                    10402
#define RTC_SET_DATE_TIME               10403
#define RTC_GET_DATE                    10404
#define RTC_GET_TIME                    10405
#define RTC_GET_DATE_TIME               10406
#define RTC_ENABLE_ALARM                10407
#define RTC_CLEAR_INT                   10408

#define FORMAT_DATE                     10430
#define FORMAT_TIME                     10431

#define DS1820_INIT                     10500
#define DS1820_START_CONVERSION         10501
#define DS1820_READ_TEMP                10502
#define DS1820_READ_SN                  10503
#define DS_RESET                        10520

void Function_IN(Function_t Function);
void Function_OUT(Function_t Function);
void This_Function_OUT(void);
uint8 Abort(Status_t Status);
void Print_Function_History(void);





#endif
