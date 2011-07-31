#include "Includes.h"

// Ovaa struktura bi trebalo da se naoga vo RTC RAM. RAM so se napojuva od Baterija
Out_t Out = {0};

Status_t Out_Init(void)
{
  Function_IN(OUT_INIT);
  
  OUT_1_OUT();
  OUT_2_OUT();
  OUT_3_OUT();
  OUT_4_OUT();
  OUT_5_OUT();
  OUT_6_OUT();
  OUT_7_OUT();
  OUT_8_OUT();
  OUT_9_OUT();
  OUT_10_OUT();
  OUT_11_OUT();
  
  RETURN_SUCCESS();
}

Status_t Out_Sync(void)
{
  Function_IN(OUT_SYNC);
  if(Out.Change == 1)
  {
    Out.Change = 0;
    
    if(Out.S_1 == 0)
      OUT_1_CLR();
    else
      OUT_1_SET();
    
    if(Out.S_2 == 0)
      OUT_2_CLR();
    else
      OUT_2_SET();
    
    if(Out.S_3 == 0)
      OUT_3_CLR();
    else
      OUT_3_SET();
    
    if(Out.S_4 == 0)
      OUT_4_CLR();
    else
      OUT_4_SET();
    
    if(Out.S_5 == 0)
      OUT_5_CLR();
    else
      OUT_5_SET();
    
    if(Out.S_6 == 0)
      OUT_6_CLR();
    else
      OUT_6_SET();
    
    if(Out.S_7 == 0)
      OUT_7_CLR();
    else
      OUT_7_SET();
    
    if(Out.S_8 == 0)
      OUT_8_CLR();
    else
      OUT_8_SET();
    
    if(Out.S_9 == 0)
      OUT_9_CLR();
    else
      OUT_9_SET();
    
    if(Out.S_10 == 0)
      OUT_10_CLR();
    else
      OUT_10_SET();
    
    if(Out.S_11 == 0)
      OUT_11_CLR();
    else
      OUT_11_SET();
  } // if
  
  RETURN_SUCCESS();
}

Status_t Out_1_Set(void * Ptr)
{
  Out.S_1 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_2_Set(void * Ptr)
{
  Out.S_2 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_3_Set(void * Ptr)
{
  Out.S_3 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_4_Set(void * Ptr)
{
  Out.S_4 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_5_Set(void * Ptr)
{
  Out.S_5 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_6_Set(void * Ptr)
{
  Out.S_6 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_7_Set(void * Ptr)
{
  Out.S_7 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_8_Set(void * Ptr)
{
  Out.S_8 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_9_Set(void * Ptr)
{
  Out.S_9 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_10_Set(void * Ptr)
{
  Out.S_10 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_11_Set(void * Ptr)
{
  Out.S_11 = 1;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_1_Clr(void * Ptr)
{
  Out.S_1 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_2_Clr(void * Ptr)
{
  Out.S_2 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_3_Clr(void * Ptr)
{
  Out.S_3 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_4_Clr(void * Ptr)
{
  Out.S_4 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_5_Clr(void * Ptr)
{
  Out.S_5 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_6_Clr(void * Ptr)
{
  Out.S_6 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_7_Clr(void * Ptr)
{
  Out.S_7 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_8_Clr(void * Ptr)
{
  Out.S_8 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_9_Clr(void * Ptr)
{
  Out.S_9 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_10_Clr(void * Ptr)
{
  Out.S_10 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_11_Clr(void * Ptr)
{
  Out.S_11 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_1_Toggle(void * Ptr)
{
  if(Out.S_1 == 0)
    Out.S_1 = 1;
  else
    Out.S_1 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_2_Toggle(void * Ptr)
{
  if(Out.S_2 == 0)
    Out.S_2 = 1;
  else
    Out.S_2 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_3_Toggle(void * Ptr)
{
  if(Out.S_3 == 0)
    Out.S_3 = 1;
  else
    Out.S_3 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_4_Toggle(void * Ptr)
{
  if(Out.S_4 == 0)
    Out.S_4 = 1;
  else
    Out.S_4 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_5_Toggle(void * Ptr)
{
  if(Out.S_5 == 0)
    Out.S_5 = 1;
  else
    Out.S_5 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_6_Toggle(void * Ptr)
{
  if(Out.S_6 == 0)
    Out.S_6 = 1;
  else
    Out.S_6 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_7_Toggle(void * Ptr)
{
  if(Out.S_7 == 0)
    Out.S_7 = 1;
  else
    Out.S_7 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_8_Toggle(void * Ptr)
{
  if(Out.S_8 == 0)
    Out.S_8 = 1;
  else
    Out.S_8 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_9_Toggle(void * Ptr)
{
  if(Out.S_9 == 0)
    Out.S_9 = 1;
  else
    Out.S_9 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_10_Toggle(void * Ptr)
{
  if(Out.S_10 == 0)
    Out.S_10 = 1;
  else
    Out.S_10 = 0;
  Out.Change = 1;
  return SUCCESS;
}

Status_t Out_11_Toggle(void * Ptr)
{
  if(Out.S_11 == 0)
    Out.S_11 = 1;
  else
    Out.S_11 = 0;
  Out.Change = 1;
  return SUCCESS;
}

