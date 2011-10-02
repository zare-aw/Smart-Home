#ifndef _Out_h
#define _Out_h

#define _OUT_INFO

#ifdef _OUT_INFO
#define OUT_INFO(a) a
#else
#define OUT_INFO(a)
#endif

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
#define OUT_1_OUT()// (PINSEL0_bit.P0_0 = 0, IO0DIR_bit.P0_0 = 1)
#define OUT_2_OUT()
#define OUT_3_OUT()
#define OUT_4_OUT()
#define OUT_5_OUT()
#define OUT_6_OUT()
#define OUT_7_OUT()
#define OUT_8_OUT()
#define OUT_9_OUT()
#define OUT_10_OUT()
#define OUT_11_OUT()

#define OUT_1_IN()
#define OUT_2_IN()
#define OUT_3_IN()
#define OUT_4_IN()
#define OUT_5_IN()
#define OUT_6_IN()
#define OUT_7_IN()
#define OUT_8_IN()
#define OUT_9_IN()
#define OUT_10_IN()
#define OUT_11_IN()

#define OUT_1_SET()// (IO0SET_bit.P0_10 = 1)
#define OUT_2_SET()
#define OUT_3_SET()
#define OUT_4_SET()
#define OUT_5_SET()
#define OUT_6_SET()
#define OUT_7_SET()
#define OUT_8_SET()
#define OUT_9_SET()
#define OUT_10_SET()
#define OUT_11_SET()

#define OUT_1_CLR()
#define OUT_2_CLR()
#define OUT_3_CLR()
#define OUT_4_CLR()
#define OUT_5_CLR()
#define OUT_6_CLR()
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