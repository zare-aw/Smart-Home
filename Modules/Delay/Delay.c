#include <intrinsics.h>
#include <stdlib.h>
#include "Global_Defines.h"
#include "Func_Trace.h"
#include "Timer.h"

#include "Delay.h"
#include "Delay_Func.h"

#define DELAY_WORK_BUFFER_SIZE    10

typedef struct DelayWork_s
{
  uint32 Delay;
  uint32 AbsDelay;
  void (*Callback)(void *);
} DelayWork_t;

DelayWork_t DelayWork[DELAY_WORK_BUFFER_SIZE] = {0};

void Delay_ISR(void *Ptr);

/*******************************************************************************
 *
 ******************************************************************************/
void uDelay(uint32 Delay)
{
  FuncIN(UDELAY);
  
  __istate_t s = __get_interrupt_state();
  __disable_interrupt();
  
  Wait(Delay);
  
  __set_interrupt_state(s);
  
  FuncOUT(UDELAY);
}
FUNC_REGISTER(UDELAY, uDelay);

/*******************************************************************************
 *
 ******************************************************************************/
void mDelay(uint32 Delay)
{
  FuncIN(MDELAY);
  
  Wait(Delay * 1000);
  
  FuncOUT(MDELAY);
}
FUNC_REGISTER(MDELAY, mDelay);

/*******************************************************************************
 *
 ******************************************************************************/
static int Compare_DelayWork(const void *A, const void *B)
{
  uint32 AbsDelay_A = ((DelayWork_t *)A) -> AbsDelay;
  uint32 AbsDelay_B = ((DelayWork_t *)B) -> AbsDelay;
  uint32 *Callback_A = (uint32*)(((DelayWork_t *)A) -> Callback);
  uint32 *Callback_B = (uint32*)(((DelayWork_t *)B) -> Callback);
  
  if((Callback_A == NULL) || (Callback_B == NULL))
  {
    if((Callback_A == NULL) && (Callback_B == NULL))
      return 0;
    else
    {
      if(Callback_A == NULL)
        return 1;
      else
        return -1;
    }
  }
  
  if(AbsDelay_A < DELAY_TIMER_GET_COUNTER())
    AbsDelay_A += DELAY_TIMER_RESET_VALUE;
  
  if(AbsDelay_B < DELAY_TIMER_GET_COUNTER())
    AbsDelay_B += DELAY_TIMER_RESET_VALUE;
  
  return AbsDelay_A - AbsDelay_B;
}

/*******************************************************************************
 * Function for register delayed work function
 * @uint32 Delay: Delay value micro seconds
 * @void (*)(void *) Callback: Work function callback. This function is
 *                             called in interrupt context.
 *                             This function must have '__arm' flag!
 ******************************************************************************/
Status_t Delay_Work(const uint32 Delay, void (*Callback)(void *))
{
  FuncIN(DELAY_WORK);
  
  Status_t Status;
  int i;
  uint32 AbsDelay;
  
  ASSERT(Callback != NULL, -INVALID_INPUT_POINTER);
  
  __disable_interrupt();
  
  AbsDelay = DELAY_TIMER_GET_COUNTER() + Delay;
  if(AbsDelay > DELAY_TIMER_RESET_VALUE)
    AbsDelay -= DELAY_TIMER_RESET_VALUE;
  
  for(i = 0; i < DELAY_WORK_BUFFER_SIZE; i++)
  {
    if(DelayWork[i].Callback == NULL)
    {
      DelayWork[i].Delay = Delay;
      DelayWork[i].AbsDelay = AbsDelay;
      DelayWork[i].Callback = Callback;
      break;
    }
  }
  
  if(i == DELAY_WORK_BUFFER_SIZE)
  {
    __enable_interrupt();
    EXIT_FUNC(DELAY_QUEUE_FULL , DELAY_WORK);
  }
  
  qsort(DelayWork, DELAY_WORK_BUFFER_SIZE, sizeof(DelayWork_t), Compare_DelayWork);
  
  Status = Delay_Timer_Set_Match_0(DelayWork[0].AbsDelay, Delay_ISR);
  
  __enable_interrupt();
  
  VERIFY(Status, Status);
  
  EXIT_SUCCESS_FUNC(DELAY_WORK);
}
FUNC_REGISTER(DELAY_WORK, Delay_Work);

/*******************************************************************************
 *
 ******************************************************************************/
__arm void Delay_ISR(void *Ptr)
{
  FuncIN(DELAY_ISR);
  
  int i;
  
  if(DelayWork[1].Callback != NULL)
    Delay_Timer_Set_Match_0(DelayWork[1].AbsDelay, Delay_ISR);
  
  ASSERT(DelayWork[0].Callback != NULL, -NOT_REGISTERED_ERROR);
  DelayWork[0].Callback(NULL);
  
  for(i = 0; i < (DELAY_WORK_BUFFER_SIZE - 1); i++)
  {
    DelayWork[i] = DelayWork[i + 1];
    if(DelayWork[i].Callback == NULL)
      break;
  }
  
  FuncOUT(DELAY_ISR);
}
FUNC_REGISTER(DELAY_ISR, Delay_ISR);

