#ifndef _DS1820_h
#define _DS1820_h

#define DS_INIT(Ch)       ( PINSEL2 &= ~(1 << 3), FIO1DIR_bit.P1_22 = 0 )
#define DS_READ(Ch)       ( FIO1PIN_bit.P1_22 )
#define DS_WRITE_LOW(Ch)  ( FIO1CLR_bit.P1_22 = 1 )
#define DS_WRITE_HIGH(Ch) ( FIO1SET_bit.P1_22 = 1 )
#define DS_DIR_IN(Ch)     ( FIO1DIR_bit.P1_22 = 0 )
#define DS_DIR_OUT(Ch)    ( FIO1DIR_bit.P1_22 = 1 )

#define OW_CONF_DELAYOFFSET2 0


// Commands
#define DS_SKIP_ROM_COMMAND               0xCC
#define DS_READ_ROM_COMMAND               0x33
#define DS_MATCH_ROM_COMMAND              0x55
#define DS_SEARCH_ROM_COMMAND             0xF0
#define DS_ALARM_SEARCH_COMMAND           0xEC
#define DS_CONVERT_TEMPERATURE_COMMAND    0x44
#define DS_READ_SCRATCHPAD_COMMAND        0xBE
#define DS_WRITE_SCRATCHPAD_COMMAND       0x4E
#define DS_COPY_SCRATCHPAD_COMMAND        0x48
#define DS_RECALL_EEPROM_COMMAND          0xB8
#define DS_READ_POWER_SUPPLY_COMMAND      0xB4

// Function declarations
Status_t DS1820_Init(int Ch);
Status_t DS1820_Start_Conversion(int Ch);
Status_t DS1820_Read_Temp(int *Temp, int Ch);
Status_t DS1820_Read_SN(uint8 *SerialNumber, int Ch);

#endif