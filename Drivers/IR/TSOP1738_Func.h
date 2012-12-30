#ifndef _TSOP1738_Func_h
#define _TSOP1738_Func_h

// TSOP1738.c
#define IR_INIT                             TSOP1738_OFFSET | 0x01
#define IR_EXT_INTERRUPT_INIT               TSOP1738_OFFSET | 0x02
#define IR_COMMAND_INIT                     TSOP1738_OFFSET | 0x03
#define IR_SET_COMMAND                      TSOP1738_OFFSET | 0x04
#define IR_GET_COMMAND                      TSOP1738_OFFSET | 0x05
#define IR_TIMER_ISR                        TSOP1738_OFFSET | 0x06
#define IR_INPUT_ISR                        TSOP1738_OFFSET | 0x07
#define IR_EXT_INTERRUPT_ISR                TSOP1738_OFFSET | 0x08
#define IR_ADD_DELAYED_CALLBACK_IN_QUEUE    TSOP1738_OFFSET | 0x09
#define IR_GET_DELAYED_CALLBACK_FROM_QUEUE  TSOP1738_OFFSET | 0x0A
#define IR_DELAYED_WORK                     TSOP1738_OFFSET | 0x0B
#define IR_RECEIVED_DEBUG_SET_STATE         TSOP1738_OFFSET | 0x0C

#endif
