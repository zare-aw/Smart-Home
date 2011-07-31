#include "Includes.h"

static Status_t DS_Reset(int Ch);

/*******************************************************************************
* 
*******************************************************************************/
Status_t DS1820_Init(int Ch)
{
  Function_IN(DS1820_INIT);
  Status_t StatusReturn = GENERAL_ERROR;
  uint8 SerialNumber[8] = {0};
  
  DS_INIT(Ch);

  StatusReturn = DS1820_Read_SN(SerialNumber, Ch);
  CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_INIT);
  
  printc("\r # DS1820 Initialized, Chanell = %u, SerialNumber = ", Ch);
  for(int i = 7; i >= 0; i--)
  {
    if((SerialNumber[i] >> 4) == 0)
      printc("0");
    printc("%X", SerialNumber[i]);
  }
  printc("\n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
static Status_t DS_Reset(int Ch)
{
  Function_IN(DS_RESET);
  
  DS_WRITE_LOW(Ch);
  DS_DIR_OUT(Ch);
  CONTROL_EXIT_FUNC(Dly(480, 'u', NULL) == SUCCESS, DLY_TIMER_UNAVAILABLE_ERROR, DS_RESET);
  DS_DIR_IN(Ch);            // Set Pin as input - wait for DS1820 to pull low
  CONTROL_EXIT_FUNC(Dly(66, 'u', NULL) == SUCCESS, DLY_TIMER_UNAVAILABLE_ERROR, DS_RESET);
  CONTROL_EXIT_FUNC(DS_READ(Ch) == 0, DS1820_NO_PRESENCE_ERROR, DS_RESET);
  CONTROL_EXIT_FUNC(Dly(480-66, 'u', NULL) == SUCCESS, DLY_TIMER_UNAVAILABLE_ERROR, DS_RESET);
  CONTROL_EXIT_FUNC(DS_READ(Ch) == 1, DS1820_SHORT_CIRCUIT_ERROR, DS_RESET);
  
  RETURN_SUCCESS();
}

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
    EXIT(Dly(50, 'u', NULL) == SUCCESS, DLY_TIMER_UNAVAILABLE_ERROR);
    DS_DIR_IN(Ch);
    EXIT(Dly(10, 'u', NULL) == SUCCESS, DLY_TIMER_UNAVAILABLE_ERROR);
    break;
  case 1:
    DS_WRITE_LOW(Ch);
    DS_DIR_OUT(Ch);
    EXIT(Dly(2, 'u', NULL) == SUCCESS, DLY_TIMER_UNAVAILABLE_ERROR);
    DS_DIR_IN(Ch);
    EXIT(Dly(58, 'u', NULL) == SUCCESS, DLY_TIMER_UNAVAILABLE_ERROR);
    break;
  default:
    EXIT(0, INVALID_INPUT_PARAMETER);
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
  if(Dly(4, 'u', NULL) != SUCCESS)
    goto ErrorExit;
  DS_DIR_IN(Ch);
  if(Dly(4, 'u', NULL) != SUCCESS)
    goto ErrorExit;
  Result = DS_READ(Ch);
  if(Dly(65, 'u', NULL) != SUCCESS)
    goto ErrorExit;
  
  return Result;
ErrorExit:
  return -1;
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
    EXIT(StatusReturn == SUCCESS, StatusReturn);
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
    EXIT(Bit != (-1), DLY_TIMER_UNAVAILABLE_ERROR);
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
  Function_IN(DS1820_START_CONVERSION);
  Status_t StatusReturn = GENERAL_ERROR;
  int i;
  
  StatusReturn = DS_Reset(Ch);
  CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_START_CONVERSION);
  
  if( SerialNumber_p == NULL)
  {
    StatusReturn = DS_Write_Byte(DS_SKIP_ROM_COMMAND, Ch);
    CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_START_CONVERSION);
  }
  else
  {
    StatusReturn = DS_Write_Byte(DS_MATCH_ROM_COMMAND, Ch);
    CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_START_CONVERSION);
    for(i = 0; i < 8; i++)
    {
      StatusReturn = DS_Write_Byte(SerialNumber_p[i], Ch);
      CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_START_CONVERSION);
    }
  }
  
  StatusReturn = DS_Write_Byte(DS_CONVERT_TEMPERATURE_COMMAND, Ch);
  CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_START_CONVERSION);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t DS1820_Read_Temp(int *Temp, int Ch, uint8 *SerialNumber_p)
{
  Function_IN(DS1820_READ_TEMP);
  Status_t StatusReturn = GENERAL_ERROR;
  uint8 Scratchpad[2] = {0};
  int i;
  
  StatusReturn = DS_Reset(Ch);
  CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_READ_TEMP);
  
  if( SerialNumber_p == NULL)
  {
    StatusReturn = DS_Write_Byte(DS_SKIP_ROM_COMMAND, Ch);
    CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_READ_TEMP);
  }
  else
  {
    StatusReturn = DS_Write_Byte(DS_MATCH_ROM_COMMAND, Ch);
    CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_READ_TEMP);
    for(i = 0; i < 8; i++)
    {
      StatusReturn = DS_Write_Byte(SerialNumber_p[i], Ch);
      CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_READ_TEMP);
    }
  }
      
  StatusReturn = DS_Write_Byte(DS_READ_SCRATCHPAD_COMMAND, Ch);
  CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_READ_TEMP);
  
  CONTROL_EXIT_FUNC(DS_Read_Byte(&Scratchpad[0], Ch) == SUCCESS, DS1820_UNABLE_TO_READ_DATA_ERROR, DS1820_READ_TEMP);
  CONTROL_EXIT_FUNC(DS_Read_Byte(&Scratchpad[1], Ch) == SUCCESS, DS1820_UNABLE_TO_READ_DATA_ERROR, DS1820_READ_TEMP);
  
  if(Scratchpad[1])
    *Temp = ( -(((Scratchpad[0] ^ 0xFF) + 1) >> 1));   // Ako brojot e negativen napravi komplemet na 2
  else
    *Temp = (Scratchpad[0] >> 1);    // Ako ne vrati ja celobrojnata vredonst za temperaturata
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t DS1820_Read_SN(uint8 *SerialNumber, int Ch)
{
  Function_IN(DS1820_READ_SN);
  Status_t StatusReturn = GENERAL_ERROR;
  int i;
  
  CONTROL(SerialNumber != NULL, INVALID_INPUT_PARAMETER);
  
  StatusReturn = DS_Reset(Ch);
  CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_READ_SN);
  
  StatusReturn = DS_Write_Byte(DS_READ_ROM_COMMAND, Ch);
  CONTROL_EXIT_FUNC(StatusReturn == SUCCESS, StatusReturn, DS1820_READ_SN);
  
  for(i = 0; i < 8; i++)
    CONTROL_EXIT_FUNC(DS_Read_Byte(&(SerialNumber[i]), Ch) == SUCCESS, DS1820_UNABLE_TO_READ_DATA_ERROR, DS1820_READ_SN);
  
  RETURN_SUCCESS();
}