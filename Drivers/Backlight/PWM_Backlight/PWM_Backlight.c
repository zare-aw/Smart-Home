#include "Global_Defines.h"
#include "Includes.h"

/*******************************************************************************
 * Function Name: Backlight_Init
 * @in: uint16 StartIntensity - Backlight Intensity upon initialization
 * @out: Status_t
 * Description: Set default backlight
*******************************************************************************/
Status_t Backlight_Init(uint16 StartIntensity)
{
  Function_IN(BACKLIGHT_INIT);

  PwmOutD_t BacklightStartIntensity = {0};

  BacklightStartIntensity.Out5D = StartIntensity;

  Pwm_Init(SINGLE_EDGE_CONTROL, BACKLIGHT_FREQ, BACKLIGHT_OUT, &BacklightStartIntensity);

  BACKLIGHT_DEBUG(printc("\r # Backlight Initialized with Initial Intensity = %d\n", StartIntensity));

  RETURN_SUCCESS_FUNC(BACKLIGHT_INIT);
}


/*******************************************************************************
 * Function Name: Backlight_Intensity
 * @in: uint16 SetIntensity - Set the desired Intensity
 * @out: Status_t
 * Description: Set Intensity
*******************************************************************************/
Status_t Set_Backlight_Intensity(uint16 Intensity)
{
  Function_IN(SET_BACKLIGHT_INTENSITY);

  Pwm_Set_Duty_Cycle(BACKLIGHT_OUT_NUMBER, Intensity);

  BACKLIGHT_DEBUG(printc("\r # Backlight: Set new Intensity = %d\n", Intensity));

  RETURN_SUCCESS_FUNC(SET_BACKLIGHT_INTENSITY);
}
