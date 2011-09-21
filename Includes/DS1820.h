#ifndef _DS1820_h
#define _DS1820_h

#define DS_INIT_1()       ( PINSEL2 &= ~(1 << 3), FIO1DIR_bit.P1_22 = 0 )
#define DS_READ_1(Value)  ( Value = FIO1PIN_bit.P1_22 )
#define DS_WRITE_LOW_1()  ( FIO1CLR_bit.P1_22 = 1 )
#define DS_WRITE_HIGH_1() ( FIO1SET_bit.P1_22 = 1 )
#define DS_DIR_IN_1()     ( FIO1DIR_bit.P1_22 = 0 )
#define DS_DIR_OUT_1()    ( FIO1DIR_bit.P1_22 = 1 )

#define DS_INIT_2()       ( PINSEL0_bit.P0_13 = 0, FIO0DIR_bit.P0_13 = 0 )
#define DS_READ_2(Value)  ( Value = FIO0PIN_bit.P0_13 )
#define DS_WRITE_LOW_2()  ( FIO0CLR_bit.P0_13 = 1 )
#define DS_WRITE_HIGH_2() ( FIO0SET_bit.P0_13 = 1 )
#define DS_DIR_IN_2()     ( FIO0DIR_bit.P0_13 = 0 )
#define DS_DIR_OUT_2()    ( FIO0DIR_bit.P0_13 = 1 )

#define DS_INIT(Ch) \
    do {\
      if (Ch == 1) \
        {\
          DS_INIT_1(); \
        }\
      else if (Ch == 2) \
        {\
          DS_INIT_2(); \
        }\
    }while (0)

#define DS_READ(Ch, Value) \
    do {\
      if (Ch == 1) \
        {\
          DS_READ_1(Value); \
        }\
      else if (Ch == 2) \
        {\
          DS_READ_2(Value); \
        }\
    }while (0)

#define DS_WRITE_LOW(Ch) \
    do {\
      if (Ch == 1) \
        {\
          DS_WRITE_LOW_1(); \
        }\
      else if (Ch == 2) \
        {\
          DS_WRITE_LOW_2(); \
        }\
    }while (0)

#define DS_WRITE_HIGH(Ch) \
    do {\
      if (Ch == 1) \
        {\
          DS_WRITE_HIGH_1(); \
        }\
      else if (Ch == 2) \
        {\
          DS_WRITE_HIGH_2(); \
        }\
    }while (0)

#define DS_DIR_IN(Ch) \
    do {\
      if (Ch == 1) \
        {\
          DS_DIR_IN_1(); \
        }\
      else if (Ch == 2) \
        {\
          DS_DIR_IN_2(); \
        }\
    }while (0)

#define DS_DIR_OUT(Ch) \
    do {\
      if (Ch == 1) \
        {\
          DS_DIR_OUT_1(); \
        }\
      else if (Ch == 2) \
        {\
          DS_DIR_OUT_2(); \
        }\
    }while (0)

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
Status_t DS1820_Init(int Ch, char *SN);
Status_t DS1820_Start_Conversion(int Ch, uint8 *SerialNumber_p);
Status_t DS1820_Read_Temp(int *Temp, int Ch, uint8 *SerialNumber_p);
Status_t DS1820_Read_SN(uint8 *SerialNumber, int Ch);

#endif