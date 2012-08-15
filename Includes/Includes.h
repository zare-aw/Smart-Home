#ifndef _Includes_h
#define _Includes_h

/*******************************************************************************
* So definicija na konstantata se definira koj cip ke se koristi
*******************************************************************************/

#include <NXP/iolpc2148.h>

/*******************************************************************************
* Includes
*******************************************************************************/

#include <intrinsics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "StatusHandling.h"
#include "Delay.h"
#include "MAM.h"
#include "CLK_Reset.h"
#include "Timer.h"
#include "RTC.h"
#include "UART_LPC214X.h"
#include "VIC.h"
#include "Initialization.h"
#include "Console.h"
#include "I2C.h"
#include "Menu.h"
#include "Temperature.h"
#include "TSOP1738.h"
#include "Commands.h"
#include "ConsoleCommands.h"
#include "Out.h"
#include "DS1820.h"
#include "SurfaceFlinger.h"
#include "HD44780.h"
#include "HD44780_cnfg.h"
#include "HD44780_l.h"
#include "PWM.h"
#include "PWM_Backlight.h"

#endif
