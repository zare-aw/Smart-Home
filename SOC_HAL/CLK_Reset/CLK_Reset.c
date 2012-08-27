#include "Global_Defines.h"
#include "CLK_Reset_Func.h"
#include "CLK_Reset_Defconfig.h"
#include "Includes.h"

uint32 CpuClk = OSC_CLK;
uint32 PerClk = OSC_CLK;

/*******************************************************************************
    Funkcija za inicijalizacija na PLL. Raboti so oscilator od 12MHz
    DISABLE za 12MHz (isklucen i diskonektiran PLL)
    ENABLE za 60MHz 
*******************************************************************************/
Status_t PLL_Init(uint8 a)
{
  FuncIN(PLL_INIT);
  
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
    Fatal_Abort(-INVALID_INIT_INPUT_PARAMETER);
  }
  
  EXIT_SUCCESS_FUNC(PLL_INIT);
}
FUNC_REGISTER(PLL_INIT, PLL_Init);

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
Status_t PCLK_Init(uint8 a)
{
  FuncIN(PCLK_INIT);
  
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
      Fatal_Abort(-INVALID_INIT_INPUT_PARAMETER);
      break;
  }
  
  EXIT_SUCCESS_FUNC(PCLK_INIT);
}
FUNC_REGISTER(PCLK_INIT, PCLK_Init);

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
  FuncIN(PRINT_RESET_SOURCE);
  
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
  
  FuncOUT(PRINT_RESET_SOURCE);
}
FUNC_REGISTER(PRINT_RESET_SOURCE, Print_Reset_Source);

