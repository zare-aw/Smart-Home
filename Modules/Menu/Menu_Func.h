#ifndef _Menu_Func_h
#define _Menu_Func_h

// Menu.c
#define MENU_INIT                   MENU_OFFSET | 0x01
#define MENU                        MENU_OFFSET | 0x02
#define DISPLAY_MENU_UPDATE         MENU_OFFSET | 0x03
#define DISPLAY_DATE_TIME_UPDATE    MENU_OFFSET | 0x04
#define DISPLAY_TEMP_UPDATE         MENU_OFFSET | 0x05
#define REGISTER_MENU_TEMP          MENU_OFFSET | 0x06
#define UNREGISTER_MENU_TEMP        MENU_OFFSET | 0x07
#define MENU_SEC_INT_CALLBACK       MENU_OFFSET | 0x08
#define FIND_MENU_STATE             MENU_OFFSET | 0x09

// MenuCallbacks.c
#define MENU_CALLBACKS_OFFSET                                             0x0100
#define POWER_KEY_CALLBACK          MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0001
#define UP_KEY_CALLBACK             MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0002
#define DOWN_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0003
#define LEFT_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0004
#define RIGHT_KEY_CALLBACK          MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0005
#define ENTER_KEY_CALLBACK          MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0006
#define CANCEL_KEY_CALLBACK         MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0007
#define MENU_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0008
#define EXIT_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0009
#define NUM1_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x000A
#define NUM2_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x000B
#define NUM3_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x000C
#define NUM4_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x000D
#define NUM5_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x000E
#define NUM6_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x000F
#define NUM7_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0010
#define NUM8_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0011
#define NUM9_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0012
#define NUM0_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0013
#define VOL_UP_KEY_CALLBACK         MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0014
#define VOL_DOWN_KEY_CALLBACK       MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0015
#define CH_UP_KEY_CALLBACK          MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0016
#define CH_DOWN_KEY_CALLBACK        MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0017
#define MUTE_KEY_CALLBACK           MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0018
#define MENU_CALLBACKS_INIT         MENU_CALLBACKS_OFFSET | MENU_OFFSET | 0x0019

// Menu_Time.c
#define MENU_TIME_OFFSET                                                  0x0200
#define MENU_SET_TIME                    MENU_TIME_OFFSET | MENU_OFFSET | 0x0001
#define MENU_UPDATE_DISP_PTR_POS         MENU_TIME_OFFSET | MENU_OFFSET | 0x0002
#define MENU_INCREMENT_PTR_POS_NUMBER    MENU_TIME_OFFSET | MENU_OFFSET | 0x0003
#define MENU_DECREMENT_PTR_POS_NUMBER    MENU_TIME_OFFSET | MENU_OFFSET | 0x0004

#endif
