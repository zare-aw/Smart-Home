/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2005
 *
 *    File name   : drv_hd44780_l.c
 *    Description : I/O function
 *
 *    History :
 *    1. Date        : June 13, 2005
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 30870 $
**************************************************************************/
#include "drv_hd44780_cnfg.h"
#include "drv_hd44780_l.h"

#define HD44780_INPUT_SET_MASK        ~0x00FF0000
#define HD44780_OUTPUT_SET_MASK        0x03FF0000

/*************************************************************************
 * Function Name: HD44780_IO_Init
 * Parameters: none
 * Return: none
 * Description: Init IO ports directions and level
 *
 *************************************************************************/
void HD44780_IO_Init (void)
{
  IO1DIR  |= HD44780_OUTPUT_SET_MASK;
  // RS Output - Low
  HD44780SetRS(0);
  // E  Output - Low
  HD44780SetE(0);
#if HD4780_WR > 0
  // WR Output - Low
  HD44780SetRW(0);
#endif
}

/*************************************************************************
 * Function Name: HD44780SetRS
 * Parameters: Boolean Data
 * Return: none
 * Description: Set RS signal
 *
 *************************************************************************/
void HD44780SetRS (Boolean Data)
{
  if(Data)
  {
    IO1SET = 1<<24;
  }
  else
  {
    IO1CLR = 1<<24;
  }
}

/*************************************************************************
 * Function Name: HD44780SetE
 * Parameters: Boolean Data
 * Return: none
 * Description: Set E signal
 *
 *************************************************************************/
void HD44780SetE (Boolean Data)
{
  if(Data)
  {
    IO1SET = 1<<25;
  }
  else
  {
    IO1CLR = 1<<25;
  }
}

/*************************************************************************
 * Function Name: HD44780WrIO
 * Parameters: Int8U Data
 * Return: none
 * Description: Write to HD44780 I/O
 *
 *************************************************************************/
void HD44780WrIO (Int8U Data)
{
Int32U Tmp = (Int32U)Data << 16;
  // Set Direction
  IO1DIR  |= HD44780_OUTPUT_SET_MASK;
#if HD4780_WR > 0
  HD44780SetRW(0);
#endif
  // Write Data
  // Clock E
  HD44780SetE(1);

  IO1SET |=  Tmp & 0xFF0000;
  IO1CLR |= ~Tmp & 0xFF0000 ;
  HD44780_BUS_DLY();
  HD44780SetE(0);
}

#if HD4780_WR > 0
/*************************************************************************
 * Function Name: HD44780SetRW
 * Parameters: Boolean Data
 * Return: none
 * Description: Set R/W signal
 *
 *************************************************************************/
void HD44780SetRW (Boolean Data)
{
  if(Data)
  {
    IO0SET = 1<<22;
  }
  else
  {
    IO0CLR = 1<<22;
  }
}

/*************************************************************************
 * Function Name: HD44780RdIO
 * Parameters: none
 * Return: Int8U
 * Description: Read from HD44780 I/O
 *
 *************************************************************************/
Int8U HD44780RdIO (void)
{
Int8U Data;
  // Set Direction
  IO1DIR  &= HD44780_INPUT_SET_MASK;
  HD44780SetRW(1);
  // Read Data
  HD44780SetE(1);
  HD44780_BUS_DLY();
  Data = (IO1PIN >> 16) & 0xFF;
  HD44780SetE(0);
  // Clock E
  return Data;
}
#endif
