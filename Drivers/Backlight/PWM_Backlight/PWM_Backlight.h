#ifndef _PWM_Backlight_h
#define _PWM_Backlight_h

/**** Defines ****/
#define BL_DECREASE   0
#define BL_INCREASE   1

Status_t PWM_Backlight_Init(uint16 StartIntensity);
Status_t Set_PWM_Backlight_Intensity(uint16 Intensity);
Status_t Get_PWM_Backlight_Intensity(uint16 *Intensity);

#endif
