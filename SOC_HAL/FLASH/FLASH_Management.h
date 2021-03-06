#ifndef _FLASH_Management_h
#define _FLASH_Management_h

/**** Status Codes ****/
#define FLASH_SECTOR_NOT_BLANK            FLASH_MANAGEMENT_OFFSET | 0x01

/**** Exported Functions ****/
Status_t FLASH_Get_Sector_Number(uint32 Address, uint32 *Sector);
Status_t FLASH_Copy_RAM_To_FLASH(uint32 Dst_FLASH_Addr, uint32 Src_RAM_Addr, uint32 NoOfBytes);
Status_t FLASH_Sectors_Blank_Check(uint32 StartSectorNumber, uint32 EndSectorNumber);

#endif // _FLASH_Management_h