#ifndef _DS1820_Pins_h
#define _DS1820_Pins_h

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

#endif
