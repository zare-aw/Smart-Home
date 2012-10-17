#ifndef _DS1820_HW_h
#define _DS1820_HW_h

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

#endif
