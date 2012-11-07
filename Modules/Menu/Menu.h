#ifndef _Menu_h
#define _Menu_h


#define NO_OF_LEVELS          100
#define INTERNAL_SENSOR       1
#define EXTERNAL_SENSOR       2
#define NO_SENSOR             -255

#define MAIN_VIEW_BUFFER_LINE 12
#define MAIN_VIEW_BUFFER_COL  25

// Events
#define POWER_KEY_EVENT       1
#define UP_KEY_EVENT          2
#define DOWN_KEY_EVENT        3
#define LEFT_KEY_EVENT        4
#define RIGHT_KEY_EVENT       5
#define ENTER_KEY_EVENT       6
#define CANCEL_KEY_EVENT      7
#define MENU_KEY_EVENT        8
#define EXIT_KEY_EVENT        9
#define NUM1_KEY_EVENT        10
#define NUM2_KEY_EVENT        11
#define NUM3_KEY_EVENT        12
#define NUM4_KEY_EVENT        13
#define NUM5_KEY_EVENT        14
#define NUM6_KEY_EVENT        15
#define NUM7_KEY_EVENT        16
#define NUM8_KEY_EVENT        17
#define NUM9_KEY_EVENT        18
#define NUM0_KEY_EVENT        19
#define VOL_UP_KEY_EVENT      20
#define VOL_DOWN_KEY_EVENT    21
#define CH_UP_KEY_EVENT       22
#define CH_DOWN_KEY_EVENT     23
#define MUTE_KEY_EVENT        24


// Functions
Status_t Menu_Init(void);
Status_t Menu(uint32 Event);
Status_t Register_Menu_Temp(const uint8 Source, const uint8 ID);
Status_t Unregister_Menu_Temp(const uint8 Source);
Status_t Menu_Sec_Int_Callback(void *Ptr);

// MenuCallbacks Functions
Status_t Menu_Callbacks_Init(uint8 DisplayType, uint16 Xres, uint16 Yres);
Status_t Power_Key_Callback(void *p);
Status_t Up_Key_Callback(void *p);
Status_t Down_Key_Callback(void *p);
Status_t Left_Key_Callback(void *p);
Status_t Right_Key_Callback(void *p);
Status_t Enter_Key_Callback(void *p);
Status_t Cancel_Key_Callback(void *p);
Status_t Menu_Key_Callback(void *p);
Status_t Exit_Key_Callback(void *p);
Status_t Num1_Key_Callback(void *p);
Status_t Num2_Key_Callback(void *p);
Status_t Num3_Key_Callback(void *p);
Status_t Num4_Key_Callback(void *p);
Status_t Num5_Key_Callback(void *p);
Status_t Num6_Key_Callback(void *p);
Status_t Num7_Key_Callback(void *p);
Status_t Num8_Key_Callback(void *p);
Status_t Num9_Key_Callback(void *p);
Status_t Num0_Key_Callback(void *p);
Status_t Vol_Up_Key_Callback(void *p);
Status_t Vol_Down_Key_Callback(void *p);
Status_t Ch_Up_Key_Callback(void *p);
Status_t Ch_Down_Key_Callback(void *p);
Status_t Mute_Key_Callback(void *p);

#endif
