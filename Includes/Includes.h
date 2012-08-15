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
#include "DlyZare.h"
#include "SystemZare.h"
#include "TimerZare.h"
#include "rtc.h"
#include "UART0Zare.h"
#include "VICZare.h"
#include "InitializationZare.h"
#include "Console.h"
#include "i2c.h"
#include "menu.h"
#include "Temperature.h"
#include "ir.h"
#include "Commands.h"
#include "ConsoleCommands.h"
#include "Out.h"
#include "DS1820.h"
#include "SurfaceFlinger.h"
#include "drv_hd44780.h"
#include "drv_hd44780_cnfg.h"
#include "drv_hd44780_l.h"
#include "PWM.h"
#include "Backlight.h"

#endif