#ifndef _DS1820_Func_h
#define _DS1820_Func_h

// DS1820.c
#define DS1820_INIT                     DS1820_OFFSET | 0x01
#define DS1820_START_CONVERSION         DS1820_OFFSET | 0x02
#define DS1820_READ_TEMP                DS1820_OFFSET | 0x03
#define DS1820_READ_SN                  DS1820_OFFSET | 0x04
#define DS_RESET                        DS1820_OFFSET | 0x05

#endif
