#include "Global_Defines.h"
#include "Includes.h"

/*******************************************************************************
    Funkcija za inicijalizacija na MAM. Kako vlezen argument se dava:
    DISABLE za da go isklucis MAM 
    ENABLE za da go vklucis MAM celosno
    ako Osc = 12 MHz
    Definirana za LPC2387
*******************************************************************************/
Status_t MAM_Init(unsigned int a)
{
  Function_IN(MAM_INIT);
  unsigned int m;
  switch (a)
  {
  case ENABLE:
    m = PLLSTAT_bit.MSEL + 1;
    if(m < 2)                   // Nagodi go MAM Timing za CCLK < 20MHz
    {
      MAMCR = 0;
      MAMTIM = 1;
      MAMCR = 2;
    }
    if(m > 1)
    {
      if(m < 4)                 // Nagodi go MAM Timing za (20MHz < CCLK < 40MHz)
      {
        MAMCR = 0;
        MAMTIM = 2;
        MAMCR = 2;
      }
      else                      // Nagodi go MAM Timing za CCLK > 40MHz
      {
        MAMCR = 0;
        MAMTIM = 3;
        MAMCR = 2;
      }
    }
    break;
  case DISABLE:
      MAMCR = 0;
    break;
  default:
      CONTROL(0, INVALID_INIT_INPUT_PARAMETER);
  }
  RETURN_SUCCESS();
}
