#include "Global_Defines.h"
#include "Includes.h"

uint32 DutyRatio;

/*******************************************************************************
 * Function Name: Pwm_Init
 * @in: uint8 Mode - Working Mode, SINGLE_EDGE_CONTROL or DOUBLE_EDGE_CONTROL
 * @in: uint32 Freq - PWM frequency
 * @in: uint8 OutEnable - Enabling PWM Outputs
 * @in: PwmOutD_t *PwmOutD - Pointer of PwmOutD_t structure for setting init Duty Cycle
 * @out: Status_t
 * Description: Set DutyCycle on Selected Output
*******************************************************************************/
Status_t Pwm_Init(uint8 Mode, uint32 Freq, uint8 OutEnable, PwmOutD_t *PwmOutD)
{
  Function_IN(PWM_INIT);
  // TODO: Add Implementation for double edge controlled PWM outputs
  
  PWMMR0 = Read_PER_CLK() / Freq;
  PWMPR = 0x00000000;       // Prescaler register
  PWMIR_bit.MR0INT = 1;     // Interrupt Reset on MR0
  PWMLER_bit.EM0L = 1;      // Latch 0 Enable
  
  PWMMCR_bit.MR0INT = 0;    // Disabled Interrupt on Match 0
  PWMMCR_bit.MR0RES = 1;    // Timer Reset after Match event
  PWMMCR_bit.MR0STOP = 0;   // Disabled Timer stop on Match 0
  
  DutyRatio = PWMMR0 / 1024;
  
  if(OutEnable & PWM_OUT_1_ON)
  {
    PWMPCR_bit.ENA1 = 1;    // Enable Output 1
    PWM_OUT_1_MUX();        // Mux Out1 to pad
    if(PwmOutD != NULL)
      PWMMR1 = DutyRatio * PwmOutD -> Out1D;
    
    PWMIR_bit.MR1INT = 1;     // Interrupt Reset on MR1
    PWMLER_bit.EM1L = 1;      // Latch 1 Enable
    
    PWMMCR_bit.MR1INT = 0;    // Disabled Interrupt on Match 1
    PWMMCR_bit.MR1RES = 0;    // Disabled Timer reset after Match event
    PWMMCR_bit.MR1STOP = 0;   // Disabled Timer stop on Match 1
    
    PWMPCR_bit.SEL1 = 0;      // Single Mode PWM Match 1

    PWM_DEBUG(printc("\r # PWM out 1 initialized with initial DutyCycle = %d\n", PwmOutD -> Out1D));
  }
  
  if(OutEnable & PWM_OUT_2_ON)
  {
    PWMPCR_bit.ENA2 = 1;    // Enable Output 2
    PWM_OUT_2_MUX();        // Mux Out2 to pad
    if(PwmOutD != NULL)
      PWMMR2 = DutyRatio * PwmOutD -> Out2D;
    
    PWMIR_bit.MR2INT = 1;     // Interrupt Reset on MR2
    PWMLER_bit.EM2L = 1;      // Latch 2 Enable
    
    PWMMCR_bit.MR2INT = 0;    // Disabled Interrupt on Match 2
    PWMMCR_bit.MR2RES = 0;    // Disabled Timer reset after Match event
    PWMMCR_bit.MR2STOP = 0;   // Disabled Timer stop on Match 2
    
    PWMPCR_bit.SEL2 = 0;      // Single Mode PWM Match 2

    PWM_DEBUG(printc("\r # PWM out 2 initialized with initial DutyCycle = %d\n", PwmOutD -> Out2D));
  }
  
  if(OutEnable & PWM_OUT_3_ON)
  {
    PWMPCR_bit.ENA3 = 1;    // Enable Output 3
    PWM_OUT_3_MUX();        // Mux Out3 to pad
    if(PwmOutD != NULL)
      PWMMR3 = DutyRatio * PwmOutD -> Out3D;
    
    PWMIR_bit.MR3INT = 1;     // Interrupt Reset on MR3
    PWMLER_bit.EM3L = 1;      // Latch 3 Enable
    
    PWMMCR_bit.MR3INT = 0;    // Disabled Interrupt on Match 3
    PWMMCR_bit.MR3RES = 0;    // Disabled Timer reset after Match event
    PWMMCR_bit.MR3STOP = 0;   // Disabled Timer stop on Match 3
    
    PWMPCR_bit.SEL3 = 0;      // Single Mode PWM Match 3

    PWM_DEBUG(printc("\r # PWM out 3 initialized with initial DutyCycle = %d\n", PwmOutD -> Out3D));
  }
  
  if(OutEnable & PWM_OUT_4_ON)
  {
    PWMPCR_bit.ENA4 = 1;    // Enable Output 4
    PWM_OUT_4_MUX();        // Mux Out4 to pad 
    if(PwmOutD != NULL)
      PWMMR4 = DutyRatio * PwmOutD -> Out4D;
    
    PWMIR_bit.MR4INT = 1;     // Interrupt Reset on MR4
    PWMLER_bit.EM4L = 1;      // Latch 4 Enable
    
    PWMMCR_bit.MR4INT = 0;    // Disabled Interrupt on Match 4
    PWMMCR_bit.MR4RES = 0;    // Disabled Timer reset after Match event
    PWMMCR_bit.MR4STOP = 0;   // Disabled Timer stop on Match 4
    
    PWMPCR_bit.SEL4 = 0;      // Single Mode PWM Match 4

    PWM_DEBUG(printc("\r # PWM out 4 initialized with initial DutyCycle = %d\n", PwmOutD -> Out4D));
  }
  
  if(OutEnable & PWM_OUT_5_ON)
  {
    PWMPCR_bit.ENA5 = 1;    // Enable Output 5
    PWM_OUT_5_MUX();        // Mux Out5 to pad
    if(PwmOutD != NULL)
      PWMMR5 = DutyRatio * PwmOutD -> Out5D;
    
    PWMIR_bit.MR5INT = 1;     // Interrupt Reset on MR5
    PWMLER_bit.EM5L = 1;      // Latch 5 Enable
    
    PWMMCR_bit.MR5INT = 0;    // Disabled Interrupt on Match 5
    PWMMCR_bit.MR5RES = 0;    // Disabled Timer reset after Match event
    PWMMCR_bit.MR5STOP = 0;   // Disabled Timer stop on Match 5
    
    PWMPCR_bit.SEL5 = 0;      // Single Mode PWM Match 5

    PWM_DEBUG(printc("\r # PWM out 5 initialized with initial DutyCycle = %d\n", PwmOutD -> Out5D));
  }
  
  if(OutEnable & PWM_OUT_6_ON)
  {
    PWMPCR_bit.ENA6 = 1;    // Enable Output 6
    PWM_OUT_6_MUX();        // Mux Out6 to pad
    if(PwmOutD != NULL)
      PWMMR6 = DutyRatio * PwmOutD -> Out6D;
    
    PWMIR_bit.MR6INT = 1;     // Interrupt Reset on MR6
    PWMLER_bit.EM6L = 1;      // Latch 6 Enable
    
    PWMMCR_bit.MR6INT = 0;    // Disabled Interrupt on Match 6
    PWMMCR_bit.MR6RES = 0;    // Disabled Timer reset after Match event
    PWMMCR_bit.MR6STOP = 0;   // Disabled Timer stop on Match 6
    
    PWMPCR_bit.SEL6 = 0;      // Single Mode PWM Match 6

    PWM_DEBUG(printc("\r # PWM out 6 initialized with initial DutyCycle = %d\n", PwmOutD -> Out6D));
  }
  
  PWMTCR_bit.CE = 1;          // Timer Counter Enabled
  PWMTCR_bit.PWMEN  = 1;      // PWM Enabled 
  
  RETURN_SUCCESS_FUNC(PWM_INIT);
}

/*******************************************************************************
 * Function Name: Pwm_Set_Duty_Cycle
 * @in: uint8 Out - PWM output select
 * @in: uint16 DutyCycle - PWM DutyCycle
 * @out: Status_t
 * Description: Set DutyCycle on Selected Output
*******************************************************************************/
Status_t Pwm_Set_Duty_Cycle(uint8 Out, uint16 DutyCycle)
{
  Function_IN(PWM_SET_DUTY_CYCLE);
  
  CONTROL(DutyCycle <= 1024, INVALID_INPUT_PARAMETER);
  
  switch(Out)
  {
    case 1:
      PWMLER_bit.EM1L = 0;
      PWMMR1 = DutyRatio * DutyCycle;
      PWMLER_bit.EM1L = 1;
      PWM_DEBUG(printc("\r # PWM out 1 set DutyCycle = %d\n", DutyCycle));
      break;
    case 2:
      PWMLER_bit.EM2L = 0;
      PWMMR2 = DutyRatio * DutyCycle;
      PWMLER_bit.EM2L = 1;
      PWM_DEBUG(printc("\r # PWM out 2 set DutyCycle = %d\n", DutyCycle));
      break;
    case 3:
      PWMLER_bit.EM3L = 0;
      PWMMR3 = DutyRatio * DutyCycle;
      PWMLER_bit.EM3L = 1;
      PWM_DEBUG(printc("\r # PWM out 3 set DutyCycle = %d\n", DutyCycle));
      break;
    case 4:
      PWMLER_bit.EM4L = 0;
      PWMMR4 = DutyRatio * DutyCycle;
      PWMLER_bit.EM4L = 1;
      PWM_DEBUG(printc("\r # PWM out 4 set DutyCycle = %d\n", DutyCycle));
      break;
    case 5:
      PWMLER_bit.EM5L = 0;
      PWMMR5 = DutyRatio * DutyCycle;
      PWMLER_bit.EM5L = 1;
      PWM_DEBUG(printc("\r # PWM out 5 set DutyCycle = %d\n", DutyCycle));
      break;
    case 6:
      PWMLER_bit.EM6L = 0;
      PWMMR6 = DutyRatio * DutyCycle;
      PWMLER_bit.EM6L = 1;
      PWM_DEBUG(printc("\r # PWM out 6 set DutyCycle = %d\n", DutyCycle));
      break;
    default:
      CONTROL(0, INVALID_INPUT_PARAMETER);
  }
  
  RETURN_SUCCESS_FUNC(PWM_SET_DUTY_CYCLE);
}