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
  
  
  EXIT_SUCCESS_FUNC(DLY);
}
FUNC_REGISTER(DLY, Dly);
