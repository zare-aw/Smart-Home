#include <intrinsics.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"

#include "FLASH_Management.h"
#include "FLASH_Management_Debug.h"
#include "FLASH_Management_Func.h"

#include "Console.h"
#include "Delay.h"
#include "CLK_Reset.h"

#define IAP_LOCATION      0x7ffffff1

#define FLASH_IAP_RETRY   5

/**** FLASH Commands ****/
#define FLASH_PREPARE_SECTOR_FOR_WRITE      50
#define FLASH_COPY_RAM_BUFFER_TO_FLASH      51
#define FLASH_ERASE_SECTORS                 52

/**** FLASH Status codes ****/
#define FLASH_STATUS_CMD_SUCCESS                              0
#define FLASH_STATUS_INVALID_COMMAND                          1
#define FLASH_STATUS_SRC_ADDR_ERROR                           2
#define FLASH_STATUS_DST_ADDR_ERROR                           3
#define FLASH_STATUS_SRC_ADDR_NOT_MAPPED                      4
#define FLASH_STATUS_DST_ADDR_NOT_MAPPED                      5
#define FLASH_STATUS_COUNT_ERROR                              6
#define FLASH_STATUS_INVALID_SECTOR                           7
#define FLASH_STATUS_SECTOR_NOT_BLANK                         8
#define FLASH_STATUS_SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION  9
#define FLASH_STATUS_COMPARE_ERROR                            10
#define FLASH_STATUS_BUSY                                     11

typedef void (*IAP)(uint32 [], uint32[]);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t FLASH_Prepare_For_Write(uint32 StartSectorNumber, uint32 EndSectorNumber)
{
  FuncIN(FLASH_PREPARE_FOR_WRITE);
  
  uint32 Command[] = {FLASH_PREPARE_SECTOR_FOR_WRITE,
                      StartSectorNumber,
                      EndSectorNumber};
  uint32 Result[2] = {0xFF};
  
  IAP IAP_Entry = (IAP)IAP_LOCATION;
  
  for(uint32 i = 0; i < FLASH_IAP_RETRY; i++)
  {
    __disable_interrupt();
    IAP_Entry(Command, Result);
    __enable_interrupt();
    
    switch(Result[0])
    {
      case FLASH_STATUS_CMD_SUCCESS:
        FLASH_DEBUG_L2(printc("(%s) FLASH Successfully prepared!\n", __func__));
        EXIT_SUCCESS_FUNC(FLASH_PREPARE_FOR_WRITE);
      case FLASH_STATUS_BUSY:
        FLASH_DEBUG_L3(printc("(%s) FLASH Busy! Retrying ...\n", __func__));
        uDelay(100);
        break;
      case FLASH_STATUS_INVALID_SECTOR:
        Fatal_Abort(-INVALID_INPUT_PARAMETER);
      default:
        EXIT_FUNC(UNKNOWN_ERROR, FLASH_PREPARE_FOR_WRITE);
    } // switch(Result[0])
  } // for(uint32 i = 0; i < IAP_RETRY; i++)
  
  EXIT_FUNC(UNKNOWN_ERROR, FLASH_PREPARE_FOR_WRITE);
}
FLASH_FUNC_REGISTER(FLASH_PREPARE_FOR_WRITE, FLASH_Prepare_For_Write);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t FLASH_Get_Sector_Number(uint32 Address, uint32 *Sector)
{
  FuncIN(FLASH_GET_SECTOR_NUMBER);
  
  ASSERT(Sector != NULL, -INVALID_INPUT_POINTER);
  
  if(Address < 0x1000)
    *Sector = 0;
  else if((Address >= 0x1000) && (Address < 0x2000))
    *Sector = 1;
  else if((Address >= 0x2000) && (Address < 0x3000))
    *Sector = 2;
  else if((Address >= 0x3000) && (Address < 0x4000))
    *Sector = 3;
  else if((Address >= 0x4000) && (Address < 0x5000))
    *Sector = 4;
  else if((Address >= 0x5000) && (Address < 0x6000))
    *Sector = 5;
  else if((Address >= 0x6000) && (Address < 0x7000))
    *Sector = 6;
  else if((Address >= 0x7000) && (Address < 0x8000))
    *Sector = 7;
  else if((Address >= 0x8000) && (Address < 0x10000))
    *Sector = 8;
  else if((Address >= 0x10000) && (Address < 0x18000))
    *Sector = 9;
  else if((Address >= 0x18000) && (Address < 0x20000))
    *Sector = 10;
  else if((Address >= 0x20000) && (Address < 0x28000))
    *Sector = 11;
  else if((Address >= 0x28000) && (Address < 0x30000))
    *Sector = 12;
  else if((Address >= 0x30000) && (Address < 0x38000))
    *Sector = 13;
  else if((Address >= 0x38000) && (Address < 0x40000))
    *Sector = 14;
  else if((Address >= 0x40000) && (Address < 0x48000))
    *Sector = 15;
  else if((Address >= 0x48000) && (Address < 0x50000))
    *Sector = 16;
  else if((Address >= 0x50000) && (Address < 0x58000))
    *Sector = 17;
  else if((Address >= 0x58000) && (Address < 0x60000))
    *Sector = 18;
  else if((Address >= 0x60000) && (Address < 0x68000))
    *Sector = 19;
  else if((Address >= 0x68000) && (Address < 0x70000))
    *Sector = 20;
  else if((Address >= 0x70000) && (Address < 0x78000))
    *Sector = 21;
  else if((Address >= 0x78000) && (Address < 0x79000))
    *Sector = 22;
  else if((Address >= 0x79000) && (Address < 0x7A000))
    *Sector = 23;
  else if((Address >= 0x7A000) && (Address < 0x7B000))
    *Sector = 24;
  else if((Address >= 0x7B000) && (Address < 0x7C000))
    *Sector = 25;
  else if((Address >= 0x7C000) && (Address < 0x7D000))
    *Sector = 26;
  else
  {
    FLASH_DEBUG_L3(printc("(%s) Address Invalid!\n", __func__));
    Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  EXIT_SUCCESS_FUNC(FLASH_GET_SECTOR_NUMBER);
}
FLASH_FUNC_REGISTER(FLASH_GET_SECTOR_NUMBER, FLASH_Get_Sector_Number);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t FLASH_Sectors_Erase(uint32 StartSectorNumber, uint32 EndSectorNumber)
{
  FuncIN(FLASH_SECTORS_ERASE);
  
  uint32 Command[] = {FLASH_ERASE_SECTORS,
                      StartSectorNumber,
                      EndSectorNumber,
                      Read_CPU_CLK() / 1000};
  uint32 Result[2] = {0xFF};
  
  IAP IAP_Entry = (IAP)IAP_LOCATION;
  
  FLASH_Prepare_For_Write(StartSectorNumber, EndSectorNumber);
  
  for(uint32 i = 0; i < FLASH_IAP_RETRY; i++)
  {
    __disable_interrupt();
    IAP_Entry(Command, Result);
    __enable_interrupt();
    
    switch(Result[0])
    {
      case FLASH_STATUS_CMD_SUCCESS:
        FLASH_DEBUG_L1(printc("(%s) FLASH Successfully Erased!\n", __func__));
        EXIT_SUCCESS_FUNC(FLASH_SECTORS_ERASE);
      case FLASH_STATUS_BUSY:
        FLASH_DEBUG_L2(printc("(%s) FLASH Busy! Retrying ...\n", __func__));
        uDelay(100);
        break;
      case FLASH_STATUS_SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION:
        FLASH_DEBUG_L2(printc("(%s) Sector not prepared for write operation!\n", __func__));
        FLASH_DEBUG_L2(printc("(%s) Preparing for Erase, StartSector = %u, EndSector = %u\n",
                              __func__, StartSectorNumber, EndSectorNumber));
        FLASH_Prepare_For_Write(StartSectorNumber, EndSectorNumber);
        break;
      case FLASH_STATUS_INVALID_SECTOR:
        Fatal_Abort(-INVALID_INPUT_PARAMETER);
      default:
        EXIT_FUNC(UNKNOWN_ERROR, FLASH_SECTORS_ERASE);
    } // switch(Result[0])
  } // for(uint32 i = 0; i < IAP_RETRY; i++)
  
  EXIT_FUNC(UNKNOWN_ERROR, FLASH_SECTORS_ERASE);
}
FLASH_FUNC_REGISTER(FLASH_SECTORS_ERASE, FLASH_Sectors_Erase);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t FLASH_Copy_RAM_To_FLASH(uint32 Dst_FLASH_Addr, uint32 Src_RAM_Addr, uint32 NoOfBytes)
{
  FuncIN(FLASH_COPY_RAM_TO_FLASH);
  
  uint32 Command[] = {FLASH_COPY_RAM_BUFFER_TO_FLASH,
                      Dst_FLASH_Addr,
                      Src_RAM_Addr,
                      NoOfBytes,
                      Read_CPU_CLK() / 1000};
  uint32 Result[2] = {0xFF};
  uint32 StartSector;
  uint32 EndSector;
  
  FLASH_Get_Sector_Number(Dst_FLASH_Addr, &StartSector);
  FLASH_Get_Sector_Number(Dst_FLASH_Addr + NoOfBytes, &EndSector);
  
  FLASH_Sectors_Erase(StartSector, EndSector);
  
  FLASH_Prepare_For_Write(StartSector, EndSector);
  
  IAP IAP_Entry = (IAP)IAP_LOCATION;
  
  for(uint32 i = 0; i < FLASH_IAP_RETRY; i++)
  {
    __disable_interrupt();
    IAP_Entry(Command, Result);
    __enable_interrupt();
    
    switch(Result[0])
    {
      case FLASH_STATUS_CMD_SUCCESS:
        FLASH_DEBUG(printc("(%s) RAM To FLASH Copy Successful!\n", __func__));
        EXIT_SUCCESS_FUNC(FLASH_COPY_RAM_TO_FLASH);
      case FLASH_STATUS_BUSY:
        FLASH_DEBUG_L1(printc("(%s) FLASH Busy! Retrying ...\n", __func__));
        uDelay(100);
        break;
      case FLASH_STATUS_SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION:
        FLASH_Get_Sector_Number(Dst_FLASH_Addr, &StartSector);
        FLASH_Get_Sector_Number(Dst_FLASH_Addr + NoOfBytes, &EndSector);
        
        FLASH_DEBUG_L1(printc("(%s) Sector not prepared for write operation!\n", __func__));
        FLASH_DEBUG_L1(printc("(%s) Preparing for write, DstAddr = %08#X, NoOfBytes = %u\n",
                              __func__, Dst_FLASH_Addr, NoOfBytes));
        FLASH_Prepare_For_Write(StartSector, EndSector);
        break;
      case FLASH_STATUS_SRC_ADDR_ERROR:
      case FLASH_STATUS_DST_ADDR_ERROR:
      case FLASH_STATUS_SRC_ADDR_NOT_MAPPED:
      case FLASH_STATUS_DST_ADDR_NOT_MAPPED:
      case FLASH_STATUS_COUNT_ERROR:
        Fatal_Abort(-INVALID_INPUT_PARAMETER);
      default:
        EXIT_FUNC(UNKNOWN_ERROR, FLASH_COPY_RAM_TO_FLASH);
    } // switch(Result[0])
  } // for(uint32 i = 0; i < IAP_RETRY; i++)
  
  EXIT_FUNC(UNKNOWN_ERROR, FLASH_COPY_RAM_TO_FLASH);
}
FLASH_FUNC_REGISTER(FLASH_COPY_RAM_TO_FLASH, FLASH_Copy_RAM_To_FLASH);
