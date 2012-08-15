#include "Global_Defines.h"
#include "Includes.h"

/*************************************************************************
* Function Name: HD44780_IO_Init
* @in: None
* @out: None
* Description: Init IO ports directions and level
*************************************************************************/
void HD44780_IO_Init(void)
{
  HD44780_RS_INIT();
  HD44780_RW_INIT();
  HD44780_E_INIT();
  HD44780_D7_INIT();
  HD44780_D6_INIT();
  HD44780_D5_INIT();
  HD44780_D4_INIT();
  HD44780_D3_INIT();
  HD44780_D2_INIT();
  HD44780_D1_INIT();
  HD44780_D0_INIT();
  
}

/*************************************************************************
* Function Name: HD44780_Set_RS
* @in: uint8 Data
* @out: None
* Description: Set RS signal
*************************************************************************/
void HD44780_Set_RS(uint8 Data)
{
  if(Data)
    HD44780_RS_SET();
  else
    HD44780_RS_CLR();
}

/*************************************************************************
* Function Name: HD44780_Set_E
* @in: uint8 Data
* @out: None
* Description: Set E signal
*************************************************************************/
void HD44780_Set_E(uint8 Data)
{
  if(Data)
    HD44780_E_SET();
  else
    HD44780_E_CLR();
}

/*************************************************************************
* Function Name: HD44780_Data_Out
* @in: None
* @out: None
* Description: Set HD44780 Data I/O to output
*************************************************************************/
void HD44780_Data_Out(void)
{
  HD44780_D7_OUT();
  HD44780_D6_OUT();
  HD44780_D5_OUT();
  HD44780_D4_OUT();
  HD44780_D3_OUT();
  HD44780_D2_OUT();
  HD44780_D1_OUT();
  HD44780_D0_OUT();
}

/*************************************************************************
* Function Name: HD44780_Data_In
* @in: None
* @out: None
* Description: Set HD44780 Data I/O to input
*************************************************************************/
void HD44780_Data_In(void)
{
  HD44780_D7_IN();
  HD44780_D6_IN();
  HD44780_D5_IN();
  HD44780_D4_IN();
  HD44780_D3_IN();
  HD44780_D2_IN();
  HD44780_D1_IN();
  HD44780_D0_IN();
}

/*************************************************************************
* Function Name: HD44780_Wr_IO
* @in: uint8 Data
* @out: None
* Description: Write to HD44780 I/O
*************************************************************************/
void HD44780_Write_IO(uint8 Data)
{
  HD44780_Data_Out();
#if HD44780_WR > 0
  HD44780_Set_RW(0);
#endif
  // Write Data
  // Clock E
  HD44780_Set_E(1);
  
#if HD44780_BUS_WIDTH != 8
  Data <<= 4;
#endif
  
  if(Data & 0x80)
    HD44780_D7_SET();
  else
    HD44780_D7_CLR();
  if(Data & 0x40)
    HD44780_D6_SET();
  else
    HD44780_D6_CLR();
  if(Data & 0x20)
    HD44780_D5_SET();
  else
    HD44780_D5_CLR();
  if(Data & 0x10)
    HD44780_D4_SET();
  else
    HD44780_D4_CLR();
  
#if HD44780_BUS_WIDTH == 8
  
  if(Data & 0x08)
    HD44780_D3_SET();
  else
    HD44780_D3_CLR();
  if(Data & 0x04)
    HD44780_D2_SET();
  else
    HD44780_D2_CLR();
  if(Data & 0x02)
    HD44780_D1_SET();
  else
    HD44780_D1_CLR();
  if(Data & 0x01)
    HD44780_D0_SET();
  else
    HD44780_D0_CLR();
  
#endif
  
  HD44780_BUS_DLY();
  HD44780_Set_E(0);
}

#if HD44780_WR > 0
/*************************************************************************
* Function Name: HD44780_Set_RW
* @in: uint8 Data
* @out: None
* Description: Set R/W signal
*************************************************************************/
void HD44780_Set_RW(uint8 Data)
{
  if(Data)
    HD44780_RW_SET();
  else
    HD44780_RW_CLR();
}

/*************************************************************************
* Function Name: HD44780_Rd_IO
* @in: None
* @out: uint8
* Description: Read from HD44780 I/O
*************************************************************************/
uint8 HD44780_Read_IO(void)
{
  uint8 Data = 0;
  
  HD44780_Data_In();
  HD44780_Set_RW(1);
  // Read Data
  HD44780_Set_E(1);
  HD44780_BUS_DLY();
  
  Data = (HD44780_D7_READ() << 3);
  Data |= (HD44780_D6_READ() << 2);
  Data |= (HD44780_D5_READ() << 1);
  Data |= (HD44780_D4_READ() << 0);
  
#if HD44780_BUS_WIDTH == 8
  Data <<= 4;
  Data |= (HD44780_D3_READ() << 3);
  Data |= (HD44780_D2_READ() << 2);
  Data |= (HD44780_D1_READ() << 1);
  Data |= (HD44780_D0_READ() << 0);
#endif
  
  HD44780_Set_E(0);
  
  return Data;
}
#endif
