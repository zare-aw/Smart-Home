/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2007
 *
 *    File name   : drv_hd44780_l.h
 *    Description : LCD low level I/O function inlcude file
 *
 *    History :
 *    1. Date        : June 13, 2005
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 30870 $
 **************************************************************************/
#include "includes.h"

#ifndef  __DRV_HD44780_L_H
#define  __DRV_HD44780_L_H

/* Delay macro */
#define HD44780_BUS_DLY()      for(volatile int dly = 10;dly;--dly)

void HD44780_IO_Init (void);
void HD44780SetRS(uint8 Data);
void HD44780SetE(uint8 Data);
void HD44780WrIO(uint8 Data);
#if HD4780_WR > 0
void HD44780SetRW(uint8 Data);
uint8 HD44780RdIO(void);
#endif

#endif // __DRV_HD44780_L_H
