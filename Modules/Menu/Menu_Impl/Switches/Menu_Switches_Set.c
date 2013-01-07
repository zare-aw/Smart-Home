#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "Menu_Switches.h"
#include "Out.h"
#include "SurfaceFlinger.h"

/**** Defines ****/

/**** Gloval Variables ****/
uint8 SetSwitchFlag = 0;
char SW_Set_Name[NO_OF_SWITCHES][SWITCHES_SET_STRING_LENGTH] = {0};

/**** Function definitions ****/
static Status_t Menu_Switch_Setting(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switches_Set_String(const Out_t *const Out_p, const uint32 SwitchesFlags)
{
  FuncIN(MENU_SWITCHES_SET_STRING);

  if(SwitchesFlags & SW_1_SET_STR)
  {
    /**** Set Switch 1 String ****/
    strcpy(SW_Set_Name[0], "Sw 1: ");
    strcat(SW_Set_Name[0], SW_Name[0]);
    if(Out_p -> S_1 == 1)
      strcat(SW_Set_Name[0], " = 1");
    else
      strcat(SW_Set_Name[0], " = 0");
  }
  
  if(SwitchesFlags & SW_2_SET_STR)
  {
    /**** Set Switch 2 String ****/
    strcpy(SW_Set_Name[1], "Sw 2: ");
    strcat(SW_Set_Name[1], SW_Name[1]);
    if(Out_p -> S_2 == 1)
      strcat(SW_Set_Name[1], " = 1");
    else
      strcat(SW_Set_Name[1], " = 0");
  }
  
  if(SwitchesFlags & SW_3_SET_STR)
  {
    /**** Set Switch 3 String ****/
    strcpy(SW_Set_Name[2], "Sw 3: ");
    strcat(SW_Set_Name[2], SW_Name[2]);
    if(Out_p -> S_3 == 1)
      strcat(SW_Set_Name[2], " = 1");
    else
      strcat(SW_Set_Name[2], " = 0");
  }
  
  if(SwitchesFlags & SW_4_SET_STR)
  {
    /**** Set Switch 4 String ****/
    strcpy(SW_Set_Name[3], "Sw 4: ");
    strcat(SW_Set_Name[3], SW_Name[3]);
    if(Out_p -> S_4 == 1)
      strcat(SW_Set_Name[3], " = 1");
    else
      strcat(SW_Set_Name[3], " = 0");
  }
  
  if(SwitchesFlags & SW_5_SET_STR)
  {
    /**** Set Switch 5 String ****/
    strcpy(SW_Set_Name[4], "Sw 5: ");
    strcat(SW_Set_Name[4], SW_Name[4]);
    if(Out_p -> S_5 == 1)
      strcat(SW_Set_Name[4], " = 1");
    else
      strcat(SW_Set_Name[4], " = 0");
  }
  
  if(SwitchesFlags & SW_6_SET_STR)
  {
    /**** Set Switch 6 String ****/
    strcpy(SW_Set_Name[5], "Sw 6: ");
    strcat(SW_Set_Name[5], SW_Name[5]);
    if(Out_p -> S_6 == 1)
      strcat(SW_Set_Name[5], " = 1");
    else
      strcat(SW_Set_Name[5], " = 0");
  }      
  
  EXIT_SUCCESS_FUNC(MENU_SWITCHES_SET_STRING);
}
FUNC_REGISTER(MENU_SWITCHES_SET_STRING, Menu_Switches_Set_String);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switches_Set(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCHES_SET);
  
  Out_t Out_s;
  
  Out_Get_State(OUT_PINS, &Out_s);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      Menu_Switches_Set_String(&Out_s,
                               SW_1_SET_STR |
                               SW_2_SET_STR |
                               SW_3_SET_STR |
                               SW_4_SET_STR |
                               SW_5_SET_STR |
                               SW_6_SET_STR);
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCHES_SET);
}
FUNC_REGISTER(MENU_SWITCHES_SET, Menu_Switches_Set);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_1_Set(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_1_SET);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetSwitchFlag = 1;
      Menu_Switch_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SetSwitchFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_1_SET);
}
FUNC_REGISTER(MENU_SWITCH_1_SET, Menu_Switch_1_Set);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_2_Set(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_2_SET);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetSwitchFlag = 2;
      Menu_Switch_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SetSwitchFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_2_SET);
}
FUNC_REGISTER(MENU_SWITCH_2_SET, Menu_Switch_2_Set);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_3_Set(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_3_SET);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetSwitchFlag = 3;
      Menu_Switch_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SetSwitchFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_3_SET);
}
FUNC_REGISTER(MENU_SWITCH_3_SET, Menu_Switch_3_Set);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_4_Set(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_4_SET);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetSwitchFlag = 4;
      Menu_Switch_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SetSwitchFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_4_SET);
}
FUNC_REGISTER(MENU_SWITCH_4_SET, Menu_Switch_4_Set);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_5_Set(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_5_SET);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetSwitchFlag = 5;
      Menu_Switch_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SetSwitchFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_5_SET);
}
FUNC_REGISTER(MENU_SWITCH_5_SET, Menu_Switch_5_Set);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_6_Set(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_6_SET);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetSwitchFlag = 6;
      Menu_Switch_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SetSwitchFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_6_SET);
}
FUNC_REGISTER(MENU_SWITCH_6_SET, Menu_Switch_6_Set);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_Set_Update_Display(const Out_t *Out_p, const uint32 Menu_SW_Ptr_Pos)
{
  FuncIN(MENU_SWITCH_SET_UPDATE_DISPLAY);
  
  char PointerString_1[3] = {0};
  char PointerString_2[3] = {0};
  
  switch(Menu_SW_Ptr_Pos)
  {
    case 0:
      strcpy(PointerString_1, "> ");
      strcpy(PointerString_2, "  ");
      break;
    case 1:
      strcpy(PointerString_1, "  ");
      strcpy(PointerString_2, "> ");
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  switch(SetSwitchFlag)
  {
    case 1:
      printd(1, "Set SW 1: %s", SW_Name[0]);
      if(Out_p -> S_1 == 0)
      {
        printd(2, "%s# OFF", PointerString_1);
        printd(3, "%s  ON", PointerString_2);
      }
      else
      {
        printd(2, "%s  OFF", PointerString_1);
        printd(3, "%s# ON", PointerString_2);
      }
      break;
    case 2:
      printd(1, "Set SW 2: %s", SW_Name[1]);
      if(Out_p -> S_2 == 0)
      {
        printd(2, "%s# OFF", PointerString_1);
        printd(3, "%s  ON", PointerString_2);
      }
      else
      {
        printd(2, "%s  OFF", PointerString_1);
        printd(3, "%s# ON", PointerString_2);
      }
      break;
    case 3:
      printd(1, "Set SW 3: %s", SW_Name[2]);
      if(Out_p -> S_3 == 0)
      {
        printd(2, "%s# OFF", PointerString_1);
        printd(3, "%s  ON", PointerString_2);
      }
      else
      {
        printd(2, "%s  OFF", PointerString_1);
        printd(3, "%s# ON", PointerString_2);
      }
      break;
    case 4:
      printd(1, "Set SW 4: %s", SW_Name[3]);
      if(Out_p -> S_4 == 0)
      {
        printd(2, "%s# OFF", PointerString_1);
        printd(3, "%s  ON", PointerString_2);
      }
      else
      {
        printd(2, "%s  OFF", PointerString_1);
        printd(3, "%s# ON", PointerString_2);
      }
      break;
    case 5:
      printd(1, "Set SW 5: %s", SW_Name[4]);
      if(Out_p -> S_5 == 0)
      {
        printd(2, "%s# OFF", PointerString_1);
        printd(3, "%s  ON", PointerString_2);
      }
      else
      {
        printd(2, "%s  OFF", PointerString_1);
        printd(3, "%s# ON", PointerString_2);
      }
      break;
    case 6:
      printd(1, "Set SW 6: %s", SW_Name[5]);
      if(Out_p -> S_6 == 0)
      {
        printd(2, "%s# OFF", PointerString_1);
        printd(3, "%s  ON", PointerString_2);
      }
      else
      {
        printd(2, "%s  OFF", PointerString_1);
        printd(3, "%s# ON", PointerString_2);
      }
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_SET_UPDATE_DISPLAY);
}
FUNC_REGISTER(MENU_SWITCH_SET_UPDATE_DISPLAY, Menu_Switch_Set_Update_Display);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_Setting(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_SETTING);
  
  Out_t Out_s;
  static uint32 Menu_SW_Ptr_Pos = 0;
  
  Out_Get_State(OUT_PINS, &Out_s);
  
  clrd();
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      switch(SetSwitchFlag)
      {
        case 1:
          Out_s.S_1 = Menu_SW_Ptr_Pos;
          Menu_Switches_Set_String(&Out_s, SW_1_SET_STR);
          break;
        case 2:
          Out_s.S_2 = Menu_SW_Ptr_Pos;
          Menu_Switches_Set_String(&Out_s, SW_2_SET_STR);
          break;
        case 3:
          Out_s.S_3 = Menu_SW_Ptr_Pos;
          Menu_Switches_Set_String(&Out_s, SW_3_SET_STR);
          break;
        case 4:
          Out_s.S_4 = Menu_SW_Ptr_Pos;
          Menu_Switches_Set_String(&Out_s, SW_4_SET_STR);
          break;
        case 5:
          Out_s.S_5 = Menu_SW_Ptr_Pos;
          Menu_Switches_Set_String(&Out_s, SW_5_SET_STR);
          break;
        case 6:
          Out_s.S_6 = Menu_SW_Ptr_Pos;
          Menu_Switches_Set_String(&Out_s, SW_6_SET_STR);
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      } // switch(SetSwitchFlag)
      
      Out_Set_State(&Out_s);
      
      Menu_Switch_Set_Update_Display(&Out_s, Menu_SW_Ptr_Pos);
      printd(4, "Switch Set!");
      break;
    case CANCEL_KEY_EVENT:
      Menu_SW_Ptr_Pos = 0;
      break;
    case UP_KEY_EVENT:
      Menu_SW_Ptr_Pos = 0;
      Menu_Switch_Set_Update_Display(&Out_s, Menu_SW_Ptr_Pos);
      break;
    case DOWN_KEY_EVENT:
      Menu_SW_Ptr_Pos = 1;
      Menu_Switch_Set_Update_Display(&Out_s, Menu_SW_Ptr_Pos);
      break;
    case FLAG_1_KEY_EVENT:
      Menu_Switch_Set_Update_Display(&Out_s, Menu_SW_Ptr_Pos);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  syncd();
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_SETTING);
}
FUNC_REGISTER(MENU_SWITCH_SETTING, Menu_Switch_Setting);


/*******************************************************************************
 * Menu States
 ******************************************************************************/

uint8 SwitchesSetPath[] = {2, 1};
MENU_STATE_CREATE(
  // Name
  SwitchesSet,
  // Path
  SwitchesSetPath,
  // Max Level
  2,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switches_Set,
  // String
  "Switches Set"
);

uint8 Switch_1_SetPath[] = {2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Setting,
  // Path
  Switch_1_SetPath,
  // Max Level
  3,
  // Flags
  NULL,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_1_Set,
  // String
  SW_Set_Name[0]
);

uint8 Switch_2_SetPath[] = {2, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Setting,
  // Path
  Switch_2_SetPath,
  // Max Level
  3,
  // Flags
  NULL,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_2_Set,
  // String
  SW_Set_Name[1]
);

uint8 Switch_3_SetPath[] = {2, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Setting,
  // Path
  Switch_3_SetPath,
  // Max Level
  3,
  // Flags
  NULL,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_3_Set,
  // String
  SW_Set_Name[2]
);

uint8 Switch_4_SetPath[] = {2, 1, 3};
MENU_STATE_CREATE(
  // Name
  Switch_4_Setting,
  // Path
  Switch_4_SetPath,
  // Max Level
  3,
  // Flags
  NULL,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_4_Set,
  // String
  SW_Set_Name[3]
);

uint8 Switch_5_SetPath[] = {2, 1, 4};
MENU_STATE_CREATE(
  // Name
  Switch_5_Setting,
  // Path
  Switch_5_SetPath,
  // Max Level
  3,
  // Flags
  NULL,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_5_Set,
  // String
  SW_Set_Name[4]
);

uint8 Switch_6_SetPath[] = {2, 1, 5};
MENU_STATE_CREATE(
  // Name
  Switch_6_Setting,
  // Path
  Switch_6_SetPath,
  // Max Level
  3,
  // Flags
  NULL,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_6_Set,
  // String
  SW_Set_Name[5]
);

uint8 Switch_1_SetLastPath[] = {2, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_SetLast,
  // Path
  Switch_1_SetLastPath,
  // Max Level
  4,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Switch_Setting,
  // String
  ""
);

uint8 Switch_2_SetLastPath[] = {2, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_SetLast,
  // Path
  Switch_2_SetLastPath,
  // Max Level
  4,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Switch_Setting,
  // String
  ""
);

uint8 Switch_3_SetLastPath[] = {2, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_SetLast,
  // Path
  Switch_3_SetLastPath,
  // Max Level
  4,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Switch_Setting,
  // String
  ""
);

uint8 Switch_4_SetLastPath[] = {2, 1, 3, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_SetLast,
  // Path
  Switch_4_SetLastPath,
  // Max Level
  4,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Switch_Setting,
  // String
  ""
);

uint8 Switch_5_SetLastPath[] = {2, 1, 4, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_SetLast,
  // Path
  Switch_5_SetLastPath,
  // Max Level
  4,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Switch_Setting,
  // String
  ""
);

uint8 Switch_6_SetLastPath[] = {2, 1, 5, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_SetLast,
  // Path
  Switch_6_SetLastPath,
  // Max Level
  4,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Switch_Setting,
  // String
  ""
);
