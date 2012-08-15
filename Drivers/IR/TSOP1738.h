#ifndef _TSOP1738_h
#define _TSOP1738_h

//#define _IR_DEBUG
#define _IR_INFO

#define MAX_IR_COMMANDS       150
#define RESERVED_IR_COMMANDS  50
#define IR_BURST_T            889
#define SINGLE_CALL           1
#define REPETITIVE_CALL       2
#define REPEAT_COMMAND        2
#define NEW_COMMAND           3

#define POWER_KEY       MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 1
#define UP_KEY          MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 2
#define DOWN_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 3
#define LEFT_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 4
#define RIGHT_KEY       MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 5
#define ENTER_KEY       MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 6
#define CANCEL_KEY      MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 7
#define MENU_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 8
#define EXIT_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 9
#define NUM1_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 10
#define NUM2_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 11
#define NUM3_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 12
#define NUM4_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 13
#define NUM5_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 14
#define NUM6_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 15
#define NUM7_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 16
#define NUM8_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 17
#define NUM9_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 18
#define NUM0_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 19
#define VOL_UP_KEY      MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 20
#define VOL_DOWN_KEY    MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 21
#define CH_UP_KEY       MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 22
#define CH_DOWN_KEY     MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 23
#define MUTE_KEY        MAX_IR_COMMANDS - RESERVED_IR_COMMANDS + 24

#ifdef _IR_DEBUG
#define IR_DEBUG(a) a
#else
#define IR_DEBUG(a)
#endif

#ifdef _IR_INFO
#define IR_INFO(a) a
#else
#define IR_INFO(a)
#endif

#define IR_PIN_INIT()     (PINSEL0_bit.P0_15 = 2, FIO0DIR_bit.P0_15 = 0)
#define IR_PIN_READ()     FIO0PIN_bit.P0_15
#define IR_INT_ENABLE()   (PINSEL0_bit.P0_15 = 2)
#define IR_INT_DISABLE()  (PINSEL0_bit.P0_15 = 0)

typedef struct ir_s
{
  uint8 Address;
  uint8 Command;
  uint8 CallMode;
  uint8 Target;
  Status_t (*Callback_p)(void * );
} ir_t;

__irq void Ext_Int_2_ISR(void);
Status_t IR_Init(void);
Status_t IR_Command_Init(uint16 NoOfCommand, ir_t *ir_p);
Status_t IR_Set_Command(uint16 NoOfCommand);
Status_t IR_Get_Command(uint16 NoOfCommand, ir_t * IR_Command);
__arm Status_t IR_Timer_ISR(void);
Status_t IR_Dummy_Handler(void *Ptr);

#endif
