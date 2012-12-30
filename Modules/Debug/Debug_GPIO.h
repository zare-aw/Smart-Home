#ifndef _Debug_GPIO_h
#define _Debug_GPIO_h

#include <NXP/iolpc2148.h>

/*******************************************************************************
* Macros
*******************************************************************************/
#define DBG_PIN_1_INIT()  (PINSEL1_bit.P0_28 = 0, FIO0DIR_bit.P0_28 = 1, FIO0CLR_bit.P0_28 = 1)

#define DBG_PIN_1_OUT()   (FIO0DIR_bit.P0_28 = 1)

#define DBG_PIN_1_IN()    (FIO0DIR_bit.P0_28 = 0)

#define DBG_PIN_1_GET()   (FIO0PIN_bit.P0_28)

#define DBG_PIN_1_SET()   (FIO0SET_bit.P0_28 = 1)

#define DBG_PIN_1_CLR()   (FIO0CLR_bit.P0_28 = 1)

/*******************************************************************************
* Functions
*******************************************************************************/
void Debug_GPIO_Init(void);

#endif // _Debug_GPIO_h
