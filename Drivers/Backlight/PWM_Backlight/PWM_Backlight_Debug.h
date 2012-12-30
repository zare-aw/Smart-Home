#ifndef _PWM_Backlight_Debug_h
#define _PWM_Backlight_Debug_h

#define _BL_DEBUG
//#define _BL_DEBUG_L1

#ifdef _BL_DEBUG
#define BL_DEBUG(a) a
#else
#define BL_DEBUG(a)
#endif

#ifdef _BL_DEBUG_L1
#define BL_DEBUG_L1(a) a
#else
#define BL_DEBUG_L1(a)
#endif

#endif
