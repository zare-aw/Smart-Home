#include    "Includes.h"

uint32 CpuClk = OSC_CLK;
uint32 PerClk = OSC_CLK;

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

/*******************************************************************************
    Funkcija za inicijalizacija na PLL. Raboti so oscilator od 12MHz
    DISABLE za 12MHz (isklucen i diskonektiran PLL)
    ENABLE za 60MHz 
*******************************************************************************/
Status_t PLL_Init(uint8 a)
{
  switch(a) 
  {
  case DISABLE:
    PLLCON_bit.PLLE = 0;
    PLLCON_bit.PLLC = 0;
    PLLFEED = 0xAA;
    PLLFEED = 0x55;
    
    CpuClk = OSC_CLK;
    break;
  case ENABLE:
    PLLCFG_bit.MSEL = 4;
    PLLCFG_bit.PSEL = 1;
    PLLCON_bit.PLLE = 1;
    PLLFEED = 0xAA;
    PLLFEED = 0x55;
    
    while(!(PLLSTAT_bit.PLOCK));
    
    PLLCON_bit.PLLC = 1;
    PLLFEED = 0xAA;
    PLLFEED = 0x55;
    
    CpuClk = OSC_CLK * 5;
    break;
  default:
    CONTROL(0, INVALID_INIT_INPUT_PARAMETER);
  }
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
uint32 Read_CPU_CLK(void)
{
  return CpuClk;
}

/*******************************************************************************
    Funkcija za izbor na PCLK
    1 za PCLK = CCLK
    2 za PCLK = CCLK/2
    4 za PCLK = CCLK/4
*******************************************************************************/
void PCLK_Init(uint8 a)
{
  switch(a)
  {
  case 1:
    VPBDIV = 1;
    PerClk = CpuClk;
    break;
  case 2:
    VPBDIV = 2;
    PerClk = CpuClk / 2;
    break;
  case 4:
    VPBDIV = 0;
    PerClk = CpuClk / 4;
    break;
  default:
    break;
  }
}

/*******************************************************************************
* 
*******************************************************************************/
uint32 Read_PER_CLK(void)
{
  return PerClk;
}

/*******************************************************************************
*
*******************************************************************************/
void Print_Reset_Source(void)
{
  uint8 Rsir = RSIR;
  printc("\r # Reset reason: ");
  switch(Rsir)
  {
    case 0x01:
      printc("Power-On\n");
      break;
    case 0x02:
      printc("External Reset Pin\n");
      break;
    case 0x04:
      printc("Watchdog Timer\n");
      break;
    case 0x08:
      printc("Brown-Out Detect\n");
      break;
    default:
      printc("Unknown, RSIR = %X\n", Rsir);
      break;
  }
  
  RSIR = 0x0F;    // Reset reset source register
}
