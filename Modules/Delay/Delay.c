#include "Global_Defines.h"
#include "Func_Trace.h"
#include "Delay.h"
#include "Delay_Func.h"
#include "Includes.h"

unsigned int T0Flag = 0;
uint8 DlyStatus = FREE;
void *DlyCallback_p = NULL;

/*******************************************************************************
 *
 ******************************************************************************/
Status_t uDelay(uint32 Delay)
{
  FuncIN(UDELAY);
  
  Wait(Delay);
  
  EXIT_SUCCESS_FUNC(UDELAY);
}
FUNC_REGISTER(UDELAY, uDelay);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t mDelay(uint32 Delay)
{
  FuncIN(MDELAY);
  
  Wait(Delay * 1000);
  
  EXIT_SUCCESS_FUNC(MDELAY);
}
FUNC_REGISTER(MDELAY, mDelay);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t sDelay(uint32 Delay)
{
  FuncIN(SDELAY);
  
  Wait(Delay * 1000 * 1000);
  
  EXIT_SUCCESS_FUNC(SDELAY);
}
FUNC_REGISTER(SDELAY, sDelay);

/*******************************************************************************
 * Funkcija za docnenje
 * Kako prv argument se zadava vrednost
 * Kako vtor argument se zadava char i toa:
 *    m - milisekundi
 *    u - mikrosekundi
 *    s - sekundi
 * Mora da se inicijalizita Timer0
 ******************************************************************************/
Status_t Dly(unsigned int a, char c, void *Callback_p)
{
  FuncIN(DLY);
  
  unsigned int b;
  
  if(DlyStatus != FREE)
    EXIT_FUNC(DLY_BUSY_ERROR, DLY);
  
  DlyStatus = BUSY;
  
  if(PLLSTAT_bit.PLLE)
  {
    switch (VPBDIV)
    {
      case 0:
        b = ((PLLSTAT_bit.MSEL+1)*12000000)/4;  
        break;
      case 1:
        b = ((PLLSTAT_bit.MSEL+1)*12000000);
        break;
      case 2:
        b = ((PLLSTAT_bit.MSEL+1)*12000000)/2;
        break;
      default:
        Fatal_Abort(-TIMER_CLOCK_ERROR);
        break;
    }
  }
  else
  {
    switch (VPBDIV)
    {
      case 0:
        b = 12000000/4;  
        break;
      case 1:
        b = 12000000;
        break;
      case 2:
        b = 12000000/2;
        break;
      default:
        Fatal_Abort(-TIMER_CLOCK_ERROR);
        break;
    }
  }
  
  switch (c)
  {
    case 'm':
      b = b / 1000;
      break;
    case 'u':
      b = b / 1000000;
      break;
    case 's':
      b = b / 1000;
      a = a * 1000;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
      break;
  }
  
  T0MCR_bit.MR0STOP = 1;  // Zapri go TIMER0 na Match0
  Timer_0_Start(a, b);    // Start na TIMER0
  if(Callback_p == NULL)
  {
    T0Flag = 1;           // Ovoj flag treba za vo TIMER0ISR
    while(T0Flag);        // Cekaj dodeka ne se pojavi INT od TIMER0
    DlyStatus = FREE;
  }
  else 
    DlyCallback_p = Callback_p;
  
  EXIT_SUCCESS_FUNC(DLY);
}
FUNC_REGISTER(DLY, Dly);

/*******************************************************************************
 * 
 ******************************************************************************/
__arm void Dly_ISR(void)
{
  FuncIN(DLY_ISR);
  
  if(DlyCallback_p != NULL)
  {
    ((Status_t (*)(void))DlyCallback_p)();
    DlyCallback_p = NULL;
  }
  
  DlyStatus = FREE;
  T0Flag = 0;
  
  FuncOUT(DLY_ISR);
}
FUNC_REGISTER(DLY_ISR, Dly_ISR);

/*******************************************************************************
* 
*******************************************************************************/
void Dly_Stop(void)
{
  FuncIN(DLY_STOP);
  
  Timer_0_Stop();
  
  FuncOUT(DLY_STOP);
}
FUNC_REGISTER(DLY_STOP, Dly_Stop);
