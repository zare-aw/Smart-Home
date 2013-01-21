#ifndef _Menu_h
#define _Menu_h

#define NO_OF_DESKTOPS        3
#define NO_OF_LEVELS          20
#define MENU_NO_OF_LEVELS     7
#define INTERNAL_SENSOR       1
#define EXTERNAL_SENSOR       2
#define NO_SENSOR             -255

#define MAIN_VIEW_BUFFER_LINE 12
#define MAIN_VIEW_BUFFER_COL  25

#define MENU_POINTER_STRING         "> "
#define EMPTY_MENU_POINTER_STRING   "  "

#define MENU_STATE_NOT_FOUND                        MENU_OFFSET | 0x01
#define MENU_INVALID_EVENT                          MENU_OFFSET | 0x02
#define MENU_STATE_EXECUTION_FAILED                 MENU_OFFSET | 0x03

// Events
#define POWER_KEY_EVENT       0x00000001
#define UP_KEY_EVENT          0x00000002
#define DOWN_KEY_EVENT        0x00000004
#define LEFT_KEY_EVENT        0x00000008
#define RIGHT_KEY_EVENT       0x00000010
#define ENTER_KEY_EVENT       0x00000020
#define CANCEL_KEY_EVENT      0x00000040
#define MENU_KEY_EVENT        0x00000080
#define EXIT_KEY_EVENT        0x00000100
#define NUM1_KEY_EVENT        0x00000200
#define NUM2_KEY_EVENT        0x00000400
#define NUM3_KEY_EVENT        0x00000800
#define NUM4_KEY_EVENT        0x00001000
#define NUM5_KEY_EVENT        0x00002000
#define NUM6_KEY_EVENT        0x00004000
#define NUM7_KEY_EVENT        0x00008000
#define NUM8_KEY_EVENT        0x00010000
#define NUM9_KEY_EVENT        0x00020000
#define NUM0_KEY_EVENT        0x00040000
#define VOL_UP_KEY_EVENT      0x00080000
#define VOL_DOWN_KEY_EVENT    0x00100000
#define CH_UP_KEY_EVENT       0x00200000
#define CH_DOWN_KEY_EVENT     0x00400000
#define MUTE_KEY_EVENT        0x00800000
#define FLAG_1_KEY_EVENT      0x10000000

/**** Key Mask ****/
#define DEFAULT_KEY_MASK      0x000001E6

/**** Flags ****/
#define MENU_LAST_STATE           0x01
#define MENU_NO_DISPLAY_UPDATE    0x02

typedef struct Menu_State_s
{
  const uint8 *Path;      // Menu Path
  const uint16 MaxLevel;        // Maximum level
  const uint16 Flags;           // Menu state Flags
  const uint32 PossibleKeys;    // Possible keys for this state
  Status_t (*Callback)(struct Menu_State_s *Menu_State_p, const uint32 Key, void *);  // Implementation function
  const char *String;     // State string
} Menu_State_t;

// Macros
#pragma section=".menu"

#define MENU_STATE_CREATE(Name, Path, MaxLevel, Flags, Keys, Callback, String) \
  __root __packed const Menu_State_t Menu_##Name @ ".menu" = {Path, MaxLevel, Flags, Keys, Callback, String}

// Functions
Status_t Menu_Init(void);
Status_t Menu(uint32 Event);
Status_t Register_Menu_Temp(const uint8 Source, const uint8 ID);
Status_t Unregister_Menu_Temp(const uint8 Source);
Status_t Menu_Sec_Int_Callback(void *Ptr);

// Menu Callbacks
Status_t Menu_Callbacks_Init(uint8 DisplayType, uint16 Xres, uint16 Yres);

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

#endif
