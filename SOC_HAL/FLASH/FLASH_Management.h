#ifndef _FLASH_Management_h
#define _FLASH_Management_h

/**** Exported Functions ****/
Status_t FLASH_Copy_RAM_To_FLASH(uint32 Dst_FLASH_Addr, uint32 Src_RAM_Addr, uint32 NoOfBytes);

#endif // _FLASH_Management_h