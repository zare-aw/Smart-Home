#ifndef _menu_h
#define _menu_h

#define _MENU_DEBUG

#ifdef _MENU_DEBUG
#define MENU_DEBUG(a) a
#else
#define MENU_DEBUG(a)
#endif

Status_t Menu_Init(uint8 DisplayType, uint16 Xres, uint16 Yres);
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