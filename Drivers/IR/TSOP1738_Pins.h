#ifndef _TSOP1738_Pins_h
#define _TSOP1738_Pins_h

#include <NXP/iolpc2148.h>

/*******************************************************************************
* Definicija na Makroata za pinovite
*******************************************************************************/
#define TSOP_PIN_INIT()     (PINSEL0_bit.P0_15 = 2, FIO0DIR_bit.P0_15 = 0)
#define TSOP_PIN_READ()     FIO0PIN_bit.P0_15
#define TSOP_INT_ENABLE()   (PINSEL0_bit.P0_15 = 2)
#define TSOP_INT_DISABLE()  (PINSEL0_bit.P0_15 = 0)

#endif  // _Out_Pins_h