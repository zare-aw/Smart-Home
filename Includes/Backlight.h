#ifndef _Backlight_h
#define _Backlight_h

// Backlight Freq
#define BACKLIGHT_FREQ              128

#define BACKLIGHT_OUT               PWM_OUT_5_ON
#define BACKLIGHT_OUT_NUMBER        5
#define BACKLIGHT_START_INTENSITY   700

Status_t Backlight_Init(uint16 StartIntensity);
Status_t Set_Backlight_Intensity(uint16 Intensity);


#endif
