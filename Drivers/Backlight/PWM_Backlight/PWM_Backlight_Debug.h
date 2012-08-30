#ifndef _PWM_Backlight_Debug_h
#define _PWM_Backlight_Debug_h

#define _BACKLIGHT_DEBUG

#ifdef _BACKLIGHT_DEBUG
#define BACKLIGHT_DEBUG(a) a
#else
#define BACKLIGHT_DEBUG(a)
#endif

#endif
