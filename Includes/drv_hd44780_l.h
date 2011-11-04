#ifndef  __DRV_HD44780_L_H
#define  __DRV_HD44780_L_H

/* Delay macro */
#define HD44780_BUS_DLY()      for(volatile int dly = 10; dly; --dly)

#define HD44780_RS_INIT()   ( PINSEL2 &= ~(1 << 2),  FIO1CLR_bit.P1_21 = 1, FIO1DIR_bit.P1_21 = 1 )
#define HD44780_RW_INIT()   ( PINSEL1_bit.P0_20 = 0, FIO0CLR_bit.P0_20 = 1, FIO0DIR_bit.P0_20 = 1 )
#define HD44780_E_INIT()    ( PINSEL1_bit.P0_16 = 0, FIO0SET_bit.P0_16 = 1, FIO0DIR_bit.P0_16 = 1 )
#define HD44780_D7_INIT()   ( PINSEL2 &= ~(1 << 3),  FIO1CLR_bit.P1_20 = 1, FIO1DIR_bit.P1_20 = 1 )
#define HD44780_D6_INIT()   ( PINSEL1_bit.P0_18 = 0, FIO0CLR_bit.P0_18 = 1, FIO0DIR_bit.P0_18 = 1 )
#define HD44780_D5_INIT()   ( PINSEL1_bit.P0_17 = 0, FIO0CLR_bit.P0_17 = 1, FIO0DIR_bit.P0_17 = 1 )
#define HD44780_D4_INIT()   ( PINSEL1_bit.P0_19 = 0, FIO0CLR_bit.P0_19 = 1, FIO0DIR_bit.P0_19 = 1 )
#define HD44780_D3_INIT()
#define HD44780_D2_INIT()
#define HD44780_D1_INIT()
#define HD44780_D0_INIT()

#define HD44780_RS_OUT()    ( FIO1DIR_bit.P1_21 = 1 )
#define HD44780_RW_OUT()    ( FIO0DIR_bit.P0_20 = 1 )
#define HD44780_E_OUT()     ( FIO0DIR_bit.P0_16 = 1 )
#define HD44780_D7_OUT()    ( FIO1DIR_bit.P1_20 = 1 )
#define HD44780_D6_OUT()    ( FIO0DIR_bit.P0_18 = 1 )
#define HD44780_D5_OUT()    ( FIO0DIR_bit.P0_17 = 1 )
#define HD44780_D4_OUT()    ( FIO0DIR_bit.P0_19 = 1 )
#define HD44780_D3_OUT()
#define HD44780_D2_OUT()
#define HD44780_D1_OUT()
#define HD44780_D0_OUT()

#define HD44780_RS_IN()     ( FIO1DIR_bit.P1_21 = 0 )
#define HD44780_RW_IN()     ( FIO0DIR_bit.P0_20 = 0 )
#define HD44780_E_IN()      ( FIO0DIR_bit.P0_16 = 0 )
#define HD44780_D7_IN()     ( FIO1DIR_bit.P1_20 = 0 )
#define HD44780_D6_IN()     ( FIO0DIR_bit.P0_18 = 0 )
#define HD44780_D5_IN()     ( FIO0DIR_bit.P0_17 = 0 )
#define HD44780_D4_IN()     ( FIO0DIR_bit.P0_19 = 0 )
#define HD44780_D3_IN()
#define HD44780_D2_IN()
#define HD44780_D1_IN()
#define HD44780_D0_IN()

#define HD44780_RS_SET()    ( FIO1SET_bit.P1_21 = 1 )
#define HD44780_RW_SET()    ( FIO0SET_bit.P0_20 = 1 )
#define HD44780_E_SET()     ( FIO0SET_bit.P0_16 = 1 )
#define HD44780_D7_SET()    ( FIO1SET_bit.P1_20 = 1 )
#define HD44780_D6_SET()    ( FIO0SET_bit.P0_18 = 1 )
#define HD44780_D5_SET()    ( FIO0SET_bit.P0_17 = 1 )
#define HD44780_D4_SET()    ( FIO0SET_bit.P0_19 = 1 )
#define HD44780_D3_SET()
#define HD44780_D2_SET()
#define HD44780_D1_SET()
#define HD44780_D0_SET()

#define HD44780_RS_CLR()    ( FIO1CLR_bit.P1_21 = 1 )
#define HD44780_RW_CLR()    ( FIO0CLR_bit.P0_20 = 1 )
#define HD44780_E_CLR()     ( FIO0CLR_bit.P0_16 = 1 )
#define HD44780_D7_CLR()    ( FIO1CLR_bit.P1_20 = 1 )
#define HD44780_D6_CLR()    ( FIO0CLR_bit.P0_18 = 1 )
#define HD44780_D5_CLR()    ( FIO0CLR_bit.P0_17 = 1 )
#define HD44780_D4_CLR()    ( FIO0CLR_bit.P0_19 = 1 )
#define HD44780_D3_CLR()
#define HD44780_D2_CLR()
#define HD44780_D1_CLR()
#define HD44780_D0_CLR()


void HD44780_IO_Init(void);
void HD44780_Set_RS(uint8 Data);
void HD44780_Set_E(uint8 Data);
void HD44780_Data_Out(void);
void HD44780_Data_In(void);
void HD44780_Write_IO(uint8 Data);
#if HD4780_WR > 0
void HD44780_Set_RW(uint8 Data);
uint8 HD44780_Read_IO(void);
#endif

#endif // __DRV_HD44780_L_H
