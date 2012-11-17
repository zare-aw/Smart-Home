#include "Global_Defines.h"
#include "PWM_Backlight_Defconfig.h"
#include "Includes.h"
#include "Command.h"
#include "Timer.h"

void Pin_MUX_Init(void);

Status_t Initialization(void)
{
  FuncIN(INITIALIZATION);
  
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
  Delay_Timer_Init();
  Timer_1_Init();
  VICInit();
  (void)IR_Init();
  Menu_Callbacks_Init(NULL, NULL, NULL);
  RTC_Init(1);
  RTC_Enable();
  Menu_Init();
  PWM_Backlight_Init(BACKLIGHT_START_INTENSITY);
  
  Temp_Init();
  HD44780_PowerUpInit();
  
  Cmd_Init_Parameters_t Cmd_Init_Parameters;
  Cmd_Init_Parameters.putscmd = &puts;
  (void)Commands_Init(&Cmd_Init_Parameters);
  
  EXIT_SUCCESS_FUNC(INITIALIZATION);
}
FUNC_REGISTER(INITIALIZATION, Initialization);

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
  PCONP_bit.PCPWM0  = 1;
  PCONP_bit.PCI2C0  = 1;
  PCONP_bit.PCSPI0  = 1;
  PCONP_bit.PCRTC   = 1;
  PCONP_bit.PCSPI1  = 0;
  PCONP_bit.PCAD0   = 0;
  PCONP_bit.PCAD1   = 0;
  PCONP_bit.PCI2C1  = 0;
  PCONP_bit.PUSB    = 1;
}

/*******************************************************************************
* 
*******************************************************************************/
void Pin_MUX_Init(void)
{
  
}
