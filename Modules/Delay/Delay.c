#include "Global_Defines.h"
#include    "Includes.h"


unsigned int T0Flag = 0;
uint8 DlyStatus = FREE;
void *DlyCallback_p = NULL;

/*******************************************************************************
    Funkcija za docnenje
    Kako prv argument se zadava vrednost
    Kako vtor argument se zadava char i toa:
      m - milisekundi
      u - mikrosekundi
      s - sekundi
    Mora da se inicijalizita Timer0
*******************************************************************************/
Status_t Dly(unsigned int a, char c, void *Callback_p)
{
  Function_IN(DLY);
  unsigned int b;
  
  CONTROL_EXIT(DlyStatus == FREE, DLY_BUSY_ERROR);
  
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
      CONTROL(0, TIMER_CLOCK_ERROR);
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
      break;
    }
  }
  switch (c)
  {
  case 'm':
    b=b/1000;
    break;
  case 'u':
    b=b/1000000;
    break;
  case 's':
    b=b/1000;
    a=a*1000;
    break;
  default:
    CONTROL(0, INVALID_INPUT_PARAMETER);
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
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
__arm void Dly_ISR(void)
{
  if(DlyCallback_p != NULL)
    ((Status_t (*)(void))DlyCallback_p)();
  DlyCallback_p = NULL;
  
  DlyStatus = FREE;
  T0Flag = 0;
}

/*******************************************************************************
* 
*******************************************************************************/
void DlyStop(void)
{
  Timer_0_Stop();
}