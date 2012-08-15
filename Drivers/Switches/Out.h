#ifndef _Out_h
#define _Out_h

#define _OUT_INFO

#ifdef _OUT_INFO
#define OUT_INFO(a) a
#else
#define OUT_INFO(a)
#endif

#define NO_OF_OUTS    6

// @in OutID in function Out_Get_State(uint8 OutID, Out_t *Out)
#define OUTS_TO_SET     1
#define OUT_PINS        2

/*******************************************************************************
* Struktura vo koja ke se cuvaat parametrite za izlezite.
*******************************************************************************/
typedef struct Out_s
{
  uint8 S_1;
  uint8 S_2;
  uint8 S_3;
  uint8 S_4;
  uint8 S_5;
  uint8 S_6;
  uint8 S_7;
  uint8 S_8;
  uint8 S_9;
  uint8 S_10;
  uint8 S_11;
  uint8 Change;
} Out_t;

/*******************************************************************************
* Definicija na Makroata za pinovite
*******************************************************************************/
#define OUT_1_INIT()   (PINSEL2 = 0, FIO1DIR_bit.P1_17 = 1, FIO1CLR_bit.P1_17 = 1)
#define OUT_2_INIT()   (PINSEL2 = 0, FIO1DIR_bit.P1_18 = 1, FIO1CLR_bit.P1_18 = 1)
#define OUT_3_INIT()   (PINSEL2 = 0, FIO1DIR_bit.P1_16 = 1, FIO1CLR_bit.P1_16 = 1)
#define OUT_4_INIT()   (PINSEL2 = 0, FIO1DIR_bit.P1_19 = 1, FIO1CLR_bit.P1_19 = 1)
#define OUT_5_INIT()   (PINSEL2 = 0, FIO1DIR_bit.P1_23 = 1, FIO1CLR_bit.P1_23 = 1)
#define OUT_6_INIT()   (PINSEL1_bit.P0_22 = 0, FIO0DIR_bit.P0_22 = 1, FIO0CLR_bit.P0_22 = 1)
#define OUT_7_INIT()
#define OUT_8_INIT()
#define OUT_9_INIT()
#define OUT_10_INIT()
#define OUT_11_INIT()

#define OUT_1_OUT()   (FIO1DIR_bit.P1_17 = 1)
#define OUT_2_OUT()   (FIO1DIR_bit.P1_18 = 1)
#define OUT_3_OUT()   (FIO1DIR_bit.P1_16 = 1)
#define OUT_4_OUT()   (FIO1DIR_bit.P1_19 = 1)
#define OUT_5_OUT()   (FIO1DIR_bit.P1_23 = 1)
#define OUT_6_OUT()   (FIO0DIR_bit.P0_22 = 1)
#define OUT_7_OUT()
#define OUT_8_OUT()
#define OUT_9_OUT()
#define OUT_10_OUT()
#define OUT_11_OUT()

#define OUT_1_IN()    (FIO1DIR_bit.P1_17 = 0)
#define OUT_2_IN()    (FIO1DIR_bit.P1_18 = 0)
#define OUT_3_IN()    (FIO1DIR_bit.P1_16 = 0)
#define OUT_4_IN()    (FIO1DIR_bit.P1_19 = 0)
#define OUT_5_IN()    (FIO1DIR_bit.P1_23 = 0)
#define OUT_6_IN()    (FIO0DIR_bit.P0_22 = 0)
#define OUT_7_IN()
#define OUT_8_IN()
#define OUT_9_IN()
#define OUT_10_IN()
#define OUT_11_IN()

#define OUT_1_SET()   (FIO1SET_bit.P1_17 = 1)
#define OUT_2_SET()   (FIO1SET_bit.P1_18 = 1)
#define OUT_3_SET()   (FIO1SET_bit.P1_16 = 1)
#define OUT_4_SET()   (FIO1SET_bit.P1_19 = 1)
#define OUT_5_SET()   (FIO1SET_bit.P1_23 = 1)
#define OUT_6_SET()   (FIO0SET_bit.P0_22 = 1)
#define OUT_7_SET()
#define OUT_8_SET()
#define OUT_9_SET()
#define OUT_10_SET()
#define OUT_11_SET()

#define OUT_1_CLR()   (FIO1CLR_bit.P1_17 = 1)
#define OUT_2_CLR()   (FIO1CLR_bit.P1_18 = 1)
#define OUT_3_CLR()   (FIO1CLR_bit.P1_16 = 1)
#define OUT_4_CLR()   (FIO1CLR_bit.P1_19 = 1)
#define OUT_5_CLR()   (FIO1CLR_bit.P1_23 = 1)
#define OUT_6_CLR()   (FIO0CLR_bit.P0_22 = 1)
#define OUT_7_CLR()
#define OUT_8_CLR()
#define OUT_9_CLR()
#define OUT_10_CLR()
#define OUT_11_CLR()

/*******************************************************************************
* Definicija na externi funkcii
*******************************************************************************/
Status_t Out_Init(void);
Status_t Out_Sync(void);
Status_t Out_Get_State(uint8 OutID, Out_t *Out);

Status_t Out_1_Set(void * Ptr);
Status_t Out_2_Set(void * Ptr);
Status_t Out_3_Set(void * Ptr);
Status_t Out_4_Set(void * Ptr);
Status_t Out_5_Set(void * Ptr);
Status_t Out_6_Set(void * Ptr);
Status_t Out_7_Set(void * Ptr);
Status_t Out_8_Set(void * Ptr);
Status_t Out_9_Set(void * Ptr);
Status_t Out_10_Set(void * Ptr);
Status_t Out_11_Set(void * Ptr);

Status_t Out_1_Clr(void * Ptr);
Status_t Out_2_Clr(void * Ptr);
Status_t Out_3_Clr(void * Ptr);
Status_t Out_4_Clr(void * Ptr);
Status_t Out_5_Clr(void * Ptr);
Status_t Out_6_Clr(void * Ptr);
Status_t Out_7_Clr(void * Ptr);
Status_t Out_8_Clr(void * Ptr);
Status_t Out_9_Clr(void * Ptr);
Status_t Out_10_Clr(void * Ptr);
Status_t Out_11_Clr(void * Ptr);

Status_t Out_1_Toggle(void * Ptr);
Status_t Out_2_Toggle(void * Ptr);
Status_t Out_3_Toggle(void * Ptr);
Status_t Out_4_Toggle(void * Ptr);
Status_t Out_5_Toggle(void * Ptr);
Status_t Out_6_Toggle(void * Ptr);
Status_t Out_7_Toggle(void * Ptr);
Status_t Out_8_Toggle(void * Ptr);
Status_t Out_9_Toggle(void * Ptr);
Status_t Out_10_Toggle(void * Ptr);
Status_t Out_11_Toggle(void * Ptr);


#endif