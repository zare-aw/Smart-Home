#include "Global_Defines.h"
#include "StatusHandling.h"
#include "DS1820.h"
#include "DS1820_HW.h"
#include "DS1820_Pins.h"
#include "DS1820_Func.h"
#include "Delay.h"
#include "Includes.h"

static Status_t DS_Reset(int Ch);

/*******************************************************************************
* 
*******************************************************************************/
Status_t DS1820_Init(int Ch, char *SN)
{
  FuncIN(DS1820_INIT);
  
  Status_t StatusReturn = GENERAL_ERROR;
  uint8 SerialNumber[8] = {0};
  
  DS_INIT(Ch);

  StatusReturn = DS1820_Read_SN(SerialNumber, Ch);
  if(StatusReturn != SUCCESS)
    EXIT_FUNC(StatusReturn, DS1820_INIT);
  
  if(SN != NULL)
    memcpy(SN, SerialNumber, 8);
  
  printc("\r # DS1820 Initialized, Chanell = %u, SerialNumber = ", Ch);
  for(int i = 7; i >= 0; i--)
  {
    if((SerialNumber[i] >> 4) == 0)
      printc("0");
    printc("%X", SerialNumber[i]);
  }
  printc("\n");
  
  EXIT_SUCCESS_FUNC(DS1820_INIT);
}
FUNC_REGISTER(DS1820_INIT, DS1820_Init);

/*******************************************************************************
* 
*******************************************************************************/
static Status_t DS_Reset(int Ch)
{
  FuncIN(DS_RESET);
  
  uint8 Result;
  
  DS_WRITE_LOW(Ch);
  DS_DIR_OUT(Ch);
  uDelay(480);
  DS_DIR_IN(Ch);            // Set Pin as input - wait for DS1820 to pull low
  uDelay(66);
  DS_READ(Ch, Result);
  
  if(Result != 0)
    EXIT_FUNC(DS1820_NO_PRESENCE_ERROR, DS_RESET);
  
  uDelay(480-66);
  DS_READ(Ch, Result);
  
  if(Result != 1)
    EXIT_FUNC(DS1820_SHORT_CIRCUIT_ERROR, DS_RESET);
  
  EXIT_SUCCESS_FUNC(DS_RESET);
}
FUNC_REGISTER(DS_RESET, DS_Reset);

/*******************************************************************************
* 
*******************************************************************************/
static Status_t DS_Write_Bit(uint8 Data, int Ch)
{
  switch(Data)
  {
  case 0:
    DS_WRITE_LOW(Ch);
    DS_DIR_OUT(Ch);
    uDelay(40);
    DS_DIR_IN(Ch);
    uDelay(10);
    break;
  case 1:
    DS_WRITE_LOW(Ch);
    DS_DIR_OUT(Ch);
    uDelay(2);
    DS_DIR_IN(Ch);
    uDelay(48);
    break;
  default:
    Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  return SUCCESS;
}

/*******************************************************************************
* 
*******************************************************************************/
static int DS_Read_Bit(int Ch)
{
  int Result = 0;
  
  DS_WRITE_LOW(Ch);
  DS_DIR_OUT(Ch);
  uDelay(2);
  DS_DIR_IN(Ch);
  uDelay(3);
  DS_READ(Ch, Result);
  uDelay(70);
  
  return Result;
}

/*******************************************************************************
* 
*******************************************************************************/
static Status_t DS_Write_Byte(uint8 Data, int Ch)
{
  int i;
  Status_t StatusReturn = GENERAL_ERROR;
  
  for (i = 0; i < 8; i++)
  {
    StatusReturn = DS_Write_Bit(Data & 0x01, Ch);
    if(StatusReturn != SUCCESS)
      return StatusReturn;
    Data >>= 1;
  }
  return SUCCESS;
}

/*******************************************************************************
* 
*******************************************************************************/
static Status_t DS_Read_Byte(uint8 *Result, int Ch)
{
  int i, Bit;
  
  for (i = 0; i < 8; i++)
  {
    *Result >>= 1;      // Shift the result to get it ready for the next bit
    Bit = DS_Read_Bit(Ch);
    if(Bit)
      *Result |= 0x80;   // If result is one, then set MS bit
  }
  return SUCCESS;
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t DS1820_Start_Conversion(int Ch, uint8 *SerialNumber_p)
{
  FuncIN(DS1820_START_CONVERSION);
  
  Status_t StatusReturn = GENERAL_ERROR;
  int i;
  
  StatusReturn = DS_Reset(Ch);
  if(StatusReturn != SUCCESS)
    EXIT_FUNC(StatusReturn, DS1820_START_CONVERSION);
  
  if( SerialNumber_p == NULL)
  {
    StatusReturn = DS_Write_Byte(DS_SKIP_ROM_COMMAND, Ch);
    if(StatusReturn != SUCCESS)
      EXIT_FUNC(StatusReturn, DS1820_START_CONVERSION);
  }
  else
  {
    StatusReturn = DS_Write_Byte(DS_MATCH_ROM_COMMAND, Ch);
    if(StatusReturn != SUCCESS)
      EXIT_FUNC(StatusReturn, DS1820_START_CONVERSION);
    
    for(i = 0; i < 8; i++)
    {
      StatusReturn = DS_Write_Byte(SerialNumber_p[i], Ch);
      if(StatusReturn != SUCCESS)
        EXIT_FUNC(StatusReturn, DS1820_START_CONVERSION);
    }
  }
  
  StatusReturn = DS_Write_Byte(DS_CONVERT_TEMPERATURE_COMMAND, Ch);
  if(StatusReturn != SUCCESS)
    EXIT_FUNC(StatusReturn, DS1820_START_CONVERSION);
  
  EXIT_SUCCESS_FUNC(DS1820_START_CONVERSION);
}
FUNC_REGISTER(DS1820_START_CONVERSION, DS1820_Start_Conversion);

/*******************************************************************************
* 
*******************************************************************************/
Status_t DS1820_Read_Temp(int *Temp, int Ch, uint8 *SerialNumber_p)
{
  FuncIN(DS1820_READ_TEMP);
  
  Status_t StatusReturn = GENERAL_ERROR;
  uint8 Scratchpad[2] = {0};
  int i;
  
  StatusReturn = DS_Reset(Ch);
  if(StatusReturn != SUCCESS)
    EXIT_FUNC(StatusReturn, DS1820_READ_TEMP);
  
  if(SerialNumber_p == NULL)
  {
    StatusReturn = DS_Write_Byte(DS_SKIP_ROM_COMMAND, Ch);
    if(StatusReturn != SUCCESS)
      EXIT_FUNC(StatusReturn, DS1820_READ_TEMP);
  }
  else
  {
    StatusReturn = DS_Write_Byte(DS_MATCH_ROM_COMMAND, Ch);
    if(StatusReturn != SUCCESS)
      EXIT_FUNC(StatusReturn, DS1820_READ_TEMP);
    
    for(i = 0; i < 8; i++)
    {
      StatusReturn = DS_Write_Byte(SerialNumber_p[i], Ch);
      if(StatusReturn != SUCCESS)
        EXIT_FUNC(StatusReturn, DS1820_READ_TEMP);
    }
  }
      
  StatusReturn = DS_Write_Byte(DS_READ_SCRATCHPAD_COMMAND, Ch);
  if(StatusReturn != SUCCESS)
    EXIT_FUNC(StatusReturn, DS1820_READ_TEMP);
  
  if(DS_Read_Byte(&Scratchpad[0], Ch) != SUCCESS)
    EXIT_FUNC(DS1820_UNABLE_TO_READ_DATA_ERROR, DS1820_READ_TEMP);
  if(DS_Read_Byte(&Scratchpad[1], Ch) != SUCCESS)
    EXIT_FUNC(DS1820_UNABLE_TO_READ_DATA_ERROR, DS1820_READ_TEMP);
  
  if(Scratchpad[1])
    *Temp = ( -(((Scratchpad[0] ^ 0xFF) + 1) >> 1));   // Ako brojot e negativen napravi komplemet na 2
  else
    *Temp = (Scratchpad[0] >> 1);    // Ako ne vrati ja celobrojnata vredonst za temperaturata
  
  EXIT_SUCCESS_FUNC(DS1820_READ_TEMP);
}
FUNC_REGISTER(DS1820_READ_TEMP, DS1820_Read_Temp);

/*******************************************************************************
* 
*******************************************************************************/
Status_t DS1820_Read_SN(uint8 *SerialNumber, int Ch)
{
  FuncIN(DS1820_READ_SN);
  
  Status_t StatusReturn = GENERAL_ERROR;
  int i;
  
  ASSERT(SerialNumber != NULL, -INVALID_INPUT_PARAMETER);
  
  StatusReturn = DS_Reset(Ch);
  if(StatusReturn != SUCCESS)
    EXIT_FUNC(StatusReturn, DS1820_READ_SN);
  
  StatusReturn = DS_Write_Byte(DS_READ_ROM_COMMAND, Ch);
  if(StatusReturn != SUCCESS)
    EXIT_FUNC(StatusReturn, DS1820_READ_SN);
  
  for(i = 0; i < 8; i++)
    if(DS_Read_Byte(&(SerialNumber[i]), Ch) != SUCCESS)
      EXIT_FUNC(DS1820_UNABLE_TO_READ_DATA_ERROR, DS1820_READ_SN);
  
  EXIT_SUCCESS_FUNC(DS1820_READ_SN);
}
FUNC_REGISTER(DS1820_READ_SN, DS1820_Read_SN);

