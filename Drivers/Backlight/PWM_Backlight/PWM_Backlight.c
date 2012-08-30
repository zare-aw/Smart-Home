#include "Global_Defines.h"
#include "PWM_Backlight_Defconfig.h"
#include "PWM_Backlight_Debug.h"
#include "PWM_Backlight_Func.h"
#include "Includes.h"

/*******************************************************************************
 * Function Name: PWM_Backlight_Init
 * @in: uint16 StartIntensity - Backlight Intensity upon initialization
 * @out: Status_t
 * Description: Set default backlight
*******************************************************************************/
Status_t PWM_Backlight_Init(uint16 StartIntensity)
{
  FuncIN(PWM_BACKLIGHT_INIT);

  PwmOutD_t BacklightStartIntensity = {0};

  BacklightStartIntensity.Out5D = StartIntensity;

  Pwm_Init(SINGLE_EDGE_CONTROL, BACKLIGHT_FREQ, BACKLIGHT_OUT, &BacklightStartIntensity);

  BACKLIGHT_DEBUG(printc("\r # Backlight Initialized with Initial Intensity = %d\n", StartIntensity));

  EXIT_SUCCESS_FUNC(PWM_BACKLIGHT_INIT);
}
FUNC_REGISTER(PWM_BACKLIGHT_INIT, Backlight_Init);

/*******************************************************************************
 * Function Name: Set_PWM_Backlight_Intensity
 * @in: uint16 SetIntensity - Set the desired Intensity
 * @out: Status_t
 * Description: Set Intensity
*******************************************************************************/
Status_t Set_PWM_Backlight_Intensity(uint16 Intensity)
{
  FuncIN(SET_PWM_BACKLIGHT_INTENSITY);

  Pwm_Set_Duty_Cycle(BACKLIGHT_OUT_NUMBER, Intensity);

  BACKLIGHT_DEBUG(printc("\r # Backlight: Set new Intensity = %d\n", Intensity));

  EXIT_SUCCESS_FUNC(SET_PWM_BACKLIGHT_INTENSITY);
}
FUNC_REGISTER(SET_PWM_BACKLIGHT_INTENSITY, Set_Backlight_Intensity);

