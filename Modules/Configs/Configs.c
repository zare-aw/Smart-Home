#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"

#include "Configs.h"
#include "Configs_Debug.h"
#include "Configs_Func.h"

#include "FLASH_Management.h"
#include "SW_Management.h"

#define FLASH_WRITE_BUFFER_SIZE     1024

uint32 FLASH_Write_Buffer[FLASH_WRITE_BUFFER_SIZE / 4] = {0};

#pragma section=".sw_m_cfg"

/*******************************************************************************
 * Function for get start address of functions section
 ******************************************************************************/
static inline void *Get_SW_M_Config_Section_Begin(void)
{
  return __section_begin(".sw_m_cfg");
}

/*******************************************************************************
 * Function for write Switches management configuration
 ******************************************************************************/
Status_t Config_SW_M_Write(SW_M_Event_t __packed *SW_M_Event_p, uint32 NoOfSW, uint32 NoOfEventsPerSW)
{
  FuncIN(CONFIG_SW_M_WRITE);
  
  uint32 WriteSize = 0;
  uint32 FLASH_WriteSize = 0;
  
  WriteSize = sizeof(SW_M_Event_t) * NoOfSW * NoOfEventsPerSW;
  
  ASSERT(WriteSize <= FLASH_WRITE_BUFFER_SIZE, -INVALID_INPUT_PARAMETER);
  
  if(WriteSize <= 512)
    FLASH_WriteSize = 512;
  else if((WriteSize > 512) && (WriteSize <= 1024))
    FLASH_WriteSize = 1024;
  else if((WriteSize > 1024) && (WriteSize <= 4096))
    FLASH_WriteSize = 4096;
  else
    Fatal_Abort(-INVALID_INPUT_PARAMETER);
  
  memcpy((void *)FLASH_Write_Buffer, (void *)SW_M_Event_p, WriteSize);
  memset((void *)(((uint8 *)FLASH_Write_Buffer) + WriteSize), 0, FLASH_WriteSize - WriteSize);
  
  FLASH_Copy_RAM_To_FLASH((uint32)Get_SW_M_Config_Section_Begin(), (uint32)FLASH_Write_Buffer, FLASH_WriteSize);
  
  EXIT_SUCCESS_FUNC(CONFIG_SW_M_WRITE);
}
CONFIG_FUNC_REGISTER(CONFIG_SW_M_WRITE, Config_SW_M_Write);

/*******************************************************************************
 * Function for write Switches management configuration
 ******************************************************************************/
Status_t Config_SW_M_Read(SW_M_Event_t __packed *SW_M_Event_p, uint32 NoOfSW, uint32 NoOfEventsPerSW)
{
  FuncIN(CONFIG_SW_M_READ);
  
  uint32 ReadSize = 0;
  
  ReadSize = sizeof(SW_M_Event_t) * NoOfSW * NoOfEventsPerSW;
  
  memcpy((void *)SW_M_Event_p, Get_SW_M_Config_Section_Begin(), ReadSize);
  
  EXIT_SUCCESS_FUNC(CONFIG_SW_M_READ);
}
CONFIG_FUNC_REGISTER(CONFIG_SW_M_READ, Config_SW_M_Read);

/*******************************************************************************
 * Function for initialize Switches management configuration in FLASH
 ******************************************************************************/
Status_t Config_SW_M_Init(void)
{
  FuncIN(CONFIG_SW_M_INIT);
  
  Status_t Status;
  uint32 Sector;
  
  FLASH_Get_Sector_Number((uint32)Get_SW_M_Config_Section_Begin(), &Sector);
  
  Status = FLASH_Sectors_Blank_Check(Sector, Sector);
  
  if(Status == SUCCESS)
  {
    memset((void *)FLASH_Write_Buffer, 0, FLASH_WRITE_BUFFER_SIZE);
    FLASH_Copy_RAM_To_FLASH((uint32)Get_SW_M_Config_Section_Begin(), (uint32)FLASH_Write_Buffer, FLASH_WRITE_BUFFER_SIZE);
  }
  
  EXIT_SUCCESS_FUNC(CONFIG_SW_M_INIT);
}
CONFIG_FUNC_REGISTER(CONFIG_SW_M_INIT, Config_SW_M_Init);

