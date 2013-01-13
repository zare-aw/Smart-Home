#ifndef _FLASH_Management_Func_h
#define _FLASH_Management_Func_h

// FLASH_Management.c
#define FLASH_PREPARE_FOR_WRITE                   FLASH_MANAGEMENT_OFFSET | 0x01
#define FLASH_GET_SECTOR_NUMBER                   FLASH_MANAGEMENT_OFFSET | 0x02
#define FLASH_SECTORS_ERASE                       FLASH_MANAGEMENT_OFFSET | 0x03
#define FLASH_COPY_RAM_TO_FLASH                   FLASH_MANAGEMENT_OFFSET | 0x04

#endif // _FLASH_Management_Func_h