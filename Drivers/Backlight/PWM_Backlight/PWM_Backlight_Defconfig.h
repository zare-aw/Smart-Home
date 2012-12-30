#ifndef _PWM_Backlight_Defconfig_h
#define _PWM_Backlight_Defconfig_h

// Backlight Freq
#define BACKLIGHT_FREQ              128

#define BACKLIGHT_OUT               PWM_OUT_5_ON
#define BACKLIGHT_OUT_NUMBER        5
#define BACKLIGHT_START_INTENSITY   700
#define BACKLIGHT_CHANGE_JUMP_VALUE 20

#define CH_UP_KEY_ADDRESS       8
#define CH_UP_KEY_COMMAND       32

#define CH_DOWN_KEY_ADDRESS     8
#define CH_DOWN_KEY_COMMAND     33

#endif
