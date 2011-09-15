#ifndef _Includes_h
#define _Includes_h

typedef unsigned char       uint8;
typedef signed char         sint8;
typedef unsigned short      uint16;
typedef signed short        sint16;
typedef unsigned int        uint32;
typedef signed int          sint32;
typedef unsigned long long  uint64;
typedef signed long long    sint64;

/*******************************************************************************
* Global Defines
*******************************************************************************/
#ifndef DISABLE
#define DISABLE   0
#endif

#ifndef ENABLE
#define ENABLE    1
#endif

#ifndef OFF
#define OFF       0
#endif

#ifndef ON
#define ON        1
#endif

#ifndef TRUE
#define TRUE      1
#endif

#ifndef FALSE
#define FALSE     0
#endif

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
#include "lcd.h"
#include "lcd_bukvi.h"
#include "Commands.h"
#include "ir.h"
#include "Out.h"
#include "DS1820.h"
#include "SurfaceFlinger.h"
#include "Temperature.h"

#endif