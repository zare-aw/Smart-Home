#ifndef _DS1820_h
#define _DS1820_h

#include "StatusHandling.h"

// Status Definitions
#define DS1820_NO_PRESENCE_ERROR            DS1820_OFFSET | 0x01
#define DS1820_SHORT_CIRCUIT_ERROR          DS1820_OFFSET | 0x02
#define DS1820_UNABLE_TO_READ_DATA_ERROR    DS1820_OFFSET | 0x03

// Function declarations
Status_t DS1820_Init(int Ch, char *SN);
Status_t DS1820_Start_Conversion(int Ch, uint8 *SerialNumber_p);
Status_t DS1820_Read_Temp(int *Temp, int Ch, uint8 *SerialNumber_p);
Status_t DS1820_Read_SN(uint8 *SerialNumber, int Ch);

#endif
