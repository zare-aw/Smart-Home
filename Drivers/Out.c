#include "Includes.h"

// Ovaa struktura bi trebalo da se naoga vo RTC RAM. RAM so se napojuva od Baterija
Out_t Out = {0};

Status_t Out_Init(void)
{
  Function_IN(OUT_INIT);
  
  OUT_1_INIT();
  OUT_2_INIT();
  OUT_3_INIT();
  OUT_4_INIT();
  OUT_5_INIT();
  OUT_6_INIT();
  OUT_7_INIT();
  OUT_8_INIT();
  OUT_9_INIT();
  OUT_10_INIT();
  OUT_11_INIT();
  
  RETURN_SUCCESS();
}

Status_t Out_Sync(void)
{
  Function_IN(OUT_SYNC);
  if(Out.Change == 1)
  {
    Out.Change = 0;
    
    if(Out.S_1 == 0)
    {
      OUT_1_CLR();
      OUT_INFO(printc("\r # Out 1 Clear\n"));
    }
    else
    {
      OUT_1_SET();
      OUT_INFO(printc("\r # Out 1 Set\n"));
    }
    
    if(Out.S_2 == 0)
    {
      OUT_2_CLR();
      OUT_INFO(printc("\r # Out 2 Clear\n"));
    }
    else
    {
      OUT_2_SET();
      OUT_INFO(printc("\r # Out 2 Set\n"));
    }
    
    if(Out.S_3 == 0)
    {
      OUT_3_CLR();
      OUT_INFO(printc("\r # Out 3 Clear\n"));
    }
    else
    {
      OUT_3_SET();
      OUT_INFO(printc("\r # Out 3 Set\n"));
    }
    
    if(Out.S_4 == 0)
    {
      OUT_4_CLR();
      OUT_INFO(printc("\r # Out 4 Clear\n"));
    }
    else
    {
      OUT_4_SET();
      OUT_INFO(printc("\r # Out 4 Set\n"));
    }
    
    if(Out.S_5 == 0)
    {
      OUT_5_CLR();
      OUT_INFO(printc("\r # Out 5 Clear\n"));
    }
    else
    {
      OUT_5_SET();
      OUT_INFO(printc("\r # Out 5 Set\n"));
    }
    
    if(Out.S_6 == 0)
    {
      OUT_6_CLR();
      OUT_INFO(printc("\r # Out 6 Clear\n"));
    }
    else
    {
      OUT_6_SET();
      OUT_INFO(printc("\r # Out 6 Set\n"));
    }
    
    if(Out.S_7 == 0)
    {
      OUT_7_CLR();
      OUT_INFO(printc("\r # Out 7 Clear\n"));
    }
    else
    {
      OUT_7_SET();
      OUT_INFO(printc("\r # Out 7 Set\n"));
    }
    
    if(Out.S_8 == 0)
    {
      OUT_8_CLR();
      OUT_INFO(printc("\r # Out 8 Clear\n"));
    }
    else
    {
      OUT_8_SET();
      OUT_INFO(printc("\r # Out 8 Set\n"));
    }
    
    if(Out.S_9 == 0)
    {
      OUT_9_CLR();
      OUT_INFO(printc("\r # Out 9 Clear\n"));
    }
    else
    {
      OUT_9_SET();
      OUT_INFO(printc("\r # Out 9 Set\n"));
    }
    
    if(Out.S_10 == 0)
    {
      OUT_10_CLR();
      OUT_INFO(printc("\r # Out 10 Clear\n"));
    }
    else
    {
      OUT_10_SET();
      OUT_INFO(printc("\r # Out 10 Set\n"));
    }
    
    if(Out.S_11 == 0)
    {
      OUT_11_CLR();
      OUT_INFO(printc("\r # Out 11 Clear\n"));
    }
    else
    {
      OUT_11_SET();
      OUT_INFO(printc("\r # Out 11 Set\n"));
    }
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

