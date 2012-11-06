#ifndef _Func_Trace_h
#define _Func_Trace_h

/*******************************************************************************
* Macros
*******************************************************************************/

/*******************************************************************************
* Offsets
*******************************************************************************/
// Modules
#define FUNC_TRACE_OFFSET       0x01000000
#define CONSOLE_OFFSET          0x04000000
#define COMMANDS_OFFSET         0x05000000
#define DELAY_OFFSET            0x06000000
#define DISPLAY_OFFSET          0x07000000

// SOC_HAL
#define CLK_RESET_OFFSET        0x21000000
#define MAM_OFFSET              0x22000000
#define VIC_OFFSET              0x23000000
#define TIMERS_OFFSET           0x24000000
#define RTC_OFFSET              0x25000000
#define PWM_OFFSET              0x26000000
#define UART_OFFSET             0x27000000
#define I2C_OFFSET              0x28000000

// Drivers
#define PWM_BACKLIGHT_OFFSET    0x41000000
#define DS1820_OFFSET           0x42000000

/*******************************************************************************
* Func_Trace status
*******************************************************************************/
#define FUNC_NOT_FOUND      FUNC_TRACE_OFFSET | 0x01

/*******************************************************************************
* Typedefs
*******************************************************************************/
typedef unsigned long Func_t;

typedef struct Func_Tbl_s
{
  Func_t Func;        // Function flag
  char *Name;         // Function name
} Func_Tbl_t;

#pragma section=".func"

#define FUNC_REGISTER(Func, Name) \
__root __packed Func_Tbl_t Func_##Name @ ".func" = {Func, #Name}

/*******************************************************************************
* Functions
*******************************************************************************/
void FuncIN(Func_t Function);
void FuncOUT(Func_t Function);
void Print_Func_History(void);

#endif
