#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "Out.h"
#include "SurfaceFlinger.h"

#define NO_OF_SWITCHES                NO_OF_OUTS
#define SWITCHES_STRING_LENGTH        8
#define SWITCHES_SET_STRING_LENGTH    X_SIZE + 1

uint8 SetSwitchFlag = 0;

char SW_Name[NO_OF_SWITCHES][SWITCHES_STRING_LENGTH] = {"SW_1", "SW_2",
                                                        "SW_3", "SW_4",
                                                        "SW_5", "SW_6"};

char SW_Set_Name[NO_OF_SWITCHES][SWITCHES_SET_STRING_LENGTH] = {0};

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Switches_State_Display(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(SWITCHES_STATE_DISPLAY);
  
  Out_t Out_s;
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      Out_Get_State(OUT_PINS, &Out_s);
      
      clrd();
      printd(1, "%s:%d%*c%s:%d", SW_Name[0], Out_s.S_1, (8 - strlen(SW_Name[0])), ' ', SW_Name[1], Out_s.S_2);
      printd(2, "%s:%d%*c%s:%d", SW_Name[2], Out_s.S_3, (8 - strlen(SW_Name[2])), ' ', SW_Name[3], Out_s.S_4);
      printd(3, "%s:%d%*c%s:%d", SW_Name[4], Out_s.S_5, (8 - strlen(SW_Name[4])), ' ', SW_Name[5], Out_s.S_6);
      syncd();
      break;
    case CANCEL_KEY_EVENT:
      clrd();
      break;
    case UP_KEY_EVENT:
      break;
    case DOWN_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(SWITCHES_STATE_DISPLAY);
}
FUNC_REGISTER(SWITCHES_STATE_DISPLAY, Switches_State_Display);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switches_Set(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCHES_SET);
  
  Out_t Out_s;
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      Out_Get_State(OUT_PINS, &Out_s);
      
      /**** Set Switch 1 String ****/
      strcpy(SW_Set_Name[0], "Sw 1: ");
      strcat(SW_Set_Name[0], SW_Name[0]);
      if(Out_s.S_1 == 1)
        strcat(SW_Set_Name[0], " = 1");
      else
        strcat(SW_Set_Name[0], " = 0");
      
      /**** Set Switch 2 String ****/
      strcpy(SW_Set_Name[1], "Sw 2: ");
      strcat(SW_Set_Name[1], SW_Name[1]);
      if(Out_s.S_2 == 1)
        strcat(SW_Set_Name[1], " = 1");
      else
        strcat(SW_Set_Name[1], " = 0");
      
      /**** Set Switch 3 String ****/
      strcpy(SW_Set_Name[2], "Sw 3: ");
      strcat(SW_Set_Name[2], SW_Name[2]);
      if(Out_s.S_3 == 1)
        strcat(SW_Set_Name[2], " = 1");
      else
        strcat(SW_Set_Name[2], " = 0");
      
      /**** Set Switch 4 String ****/
      strcpy(SW_Set_Name[3], "Sw 4: ");
      strcat(SW_Set_Name[3], SW_Name[3]);
      if(Out_s.S_4 == 1)
        strcat(SW_Set_Name[3], " = 1");
      else
        strcat(SW_Set_Name[3], " = 0");
      
      /**** Set Switch 5 String ****/
      strcpy(SW_Set_Name[4], "Sw 5: ");
      strcat(SW_Set_Name[4], SW_Name[4]);
      if(Out_s.S_5 == 1)
        strcat(SW_Set_Name[4], " = 1");
      else
        strcat(SW_Set_Name[4], " = 0");
      
      /**** Set Switch 6 String ****/
      strcpy(SW_Set_Name[5], "Sw 6: ");
      strcat(SW_Set_Name[5], SW_Name[5]);
      if(Out_s.S_6 == 1)
        strcat(SW_Set_Name[5], " = 1");
      else
        strcat(SW_Set_Name[5], " = 0");
      
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


uint8 SwitchesPath[] = {2};
MENU_STATE_CREATE(
  // Name
  Switches,
  // Path
  SwitchesPath,
  // Max Level
  1,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  NULL,
  // String
  "Switches"
);

uint8 SwitchesStatePath[] = {2, 0};
MENU_STATE_CREATE(
  // Name
  SwitchesState,
  // Path
  SwitchesStatePath,
  // Max Level
  2,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Switches_State_Display,
  // String
  "Switches State"
);

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

uint8 SwitchesStateDisplayPath[] = {2, 0, 0};
MENU_STATE_CREATE(
  // Name
  SwitchesStateDisplay,
  // Path
  SwitchesStateDisplayPath,
  // Max Level
  3,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Switches_State_Display,
  // String
  ""
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
