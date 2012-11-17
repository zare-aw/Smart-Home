#ifndef _Out_h
#define _Out_h

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
* Definicija na externi funkcii
*******************************************************************************/
Status_t Out_Init(void);
Status_t Out_Sync(void);
Status_t Out_Get_State(uint8 OutID, Out_t *Out);
Status_t Out_Set_State(Out_t *Out_p);

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