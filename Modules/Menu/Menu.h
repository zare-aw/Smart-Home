#ifndef _Menu_h
#define _Menu_h


#define NO_OF_LEVELS          100
#define INTERNAL_SENSOR       1
#define EXTERNAL_SENSOR       2
#define NO_SENSOR             -255

#define MAIN_VIEW_BUFFER_LINE 12
#define MAIN_VIEW_BUFFER_COL  25

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

typedef struct Menu_State_s
{
  uint8 Level;      // Menu level
  uint8 State;      // Menu state
  uint8 Parent;     // Menu parent state
  uint8 Flags;      // Menu state Flags
  uint32 PossibleKeys;    // Possible keys for this state
  Status_t (*Callback)(uint32 Key, void *);  // Implementation function
  char *String;     // State string
} Menu_State_t;

// Macros
#pragma section=".menu"

#define MENU_STATE_CREATE(Level, State, Parent, Flags, Keys, Callback, String) \
__root __packed Menu_State_t Menu_##Callback @ ".menu" = {Level, State, Parent, Flags, Keys, Callback, String}

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

#endif
