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

/*******************************************************************************
 * Functions definitions
*******************************************************************************/
void Fatal_Abort(Status_t Status);

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
* Status defines
*******************************************************************************/
#define SUCCESS                             0x0000
#define INFO                                0x0001
#define ERROR                               0x0002
#define GENERAL_ERROR                       0x0003
#define FATAL_ERROR                         0x0004
#define	UNKNOWN_ERROR		            0x0005
#define COMMUNICATION_ERROR	            0x0006
#define INVALID_INPUT_PARAMETER             0x0007
#define INVALID_INIT_INPUT_PARAMETER        0x0008
#define INVALID_INPUT_POINTER               0x0009

#define UNDEFINED_INSTRUCTIONS_EXCEPTION    0x0010
#define SOFTWARE_INTERRUPT_EXCEPTION        0x0011
#define PREFETCH_ABORT_EXCEPTION            0x0012
#define DATA_ABORT_EXCEPTION                0x0013

#define	MEMORY_ERROR                        0x0015
#define HEAP_ALLOCATION_ERROR               0x0016
#define REGISTER_ERROR                      0x0017

#define NOT_REGISTERED_ERROR                0x0020

#define BUS_ERROR                           0x0030
#define PCLKSEL_ERROR                       0x0031

#define TIMER_CLOCK_ERROR                   0x0040

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

#define TIME_SET_ALARM_ERROR                500
#define TIME_ALARM_REGISTER_ERROR           501
#define TIME_ALARM_SET_STATE_ERROR          502
#endif
