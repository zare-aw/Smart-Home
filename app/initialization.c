#include "Includes.h"

void Pin_MUX_Init(void);

Status_t Initialization(void)
{
  Function_IN(INITIALIZATION);
  
  printc("\n********************************\n");
  printc("\r*** Smart home system Rev 1.0 **\n");
  printc("\r********************************\n");
  
  (void)Out_Init();
  (void)Out_Sync();
  
  Pin_MUX_Init();
  
  Print_Reset_Source();
  
  Power_Init();
  (void)PLL_Init(ENABLE);
  PCLK_Init(2);
  (void)Console_Server_Init(CONSOLE_CHANELL, CONSOLE_SPEED, MODE_POOLING);
  (void)MAM_Init(ENABLE);
  GPIO_Init(FGPIO);
  Timer_0_Init();
  Timer_1_Init();
  VICInit();
  (void)IR_Init();
  Menu_Callbacks_Init(NULL, NULL, NULL);
  RTC_Init(1);
  RTC_Enable();
  Menu_Init();
  HD44780_PowerUpInit();
  
  __enable_interrupt();
  Temp_Init();
  __disable_interrupt();
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* Inicijalizacija na GPIO
* @In GPIO za obicni GPIO na P0 i P1
*     FGPIO za fast GPIO na P0 i P1
*******************************************************************************/
void GPIO_Init(uint8 a)
{
  switch(a)
  {
  case GPIO:
    SCS_bit.GPIO0M = 0;
    SCS_bit.GPIO1M = 0;
    break;
  case FGPIO:
    SCS_bit.GPIO0M = 1;
    SCS_bit.GPIO1M = 1;
    break;
  default:
    break;
  }
}

/*******************************************************************************
* Inicijalizacija na site moduli od uC, tuka se bira ON ili OFF na modulite
*******************************************************************************/
void Power_Init(void)
{
  PCONP_bit.PCTIM0  = 1;
  PCONP_bit.PCTIM1  = 1;
  PCONP_bit.PCURT0  = 1;
  PCONP_bit.PCURT1  = 1;
  PCONP_bit.PCPWM0  = 0;
  PCONP_bit.PCI2C0  = 1;
  PCONP_bit.PCSPI0  = 1;
  PCONP_bit.PCRTC   = 1;
  PCONP_bit.PCSPI1  = 0;
  PCONP_bit.PCAD0   = 0;
  PCONP_bit.PCAD1   = 0;
  PCONP_bit.PCI2C1  = 0;
  PCONP_bit.PUSB    = 0;
}

/*******************************************************************************
* 
*******************************************************************************/
void Pin_MUX_Init(void)
{
  LCD_BECKLIGHT_GPIO_INIT(); 
}