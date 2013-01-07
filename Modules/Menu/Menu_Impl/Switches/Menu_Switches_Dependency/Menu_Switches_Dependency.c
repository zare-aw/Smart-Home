#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "Menu_Switches.h"

/**** Gloval Variables ****/
uint8 SwitchDependencyFlag = 0;

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_SW_Dep_Set_Name(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SW_DEP_SET_NAME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      Menu_Switches_Set_Display_String(SW_1_SET_STR |
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
  
  EXIT_SUCCESS_FUNC(MENU_SW_DEP_SET_NAME);
}
FUNC_REGISTER(MENU_SW_DEP_SET_NAME, Menu_SW_Dep_Set_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_SW_1_Dependency_Set_Flag(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_1_DEPENDENCY_SET_FLAG);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchDependencyFlag = 1;
      break;
    case CANCEL_KEY_EVENT:
      SwitchDependencyFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_1_DEPENDENCY_SET_FLAG);
}
FUNC_REGISTER(MENU_SWITCH_1_DEPENDENCY_SET_FLAG, Menu_SW_1_Dependency_Set_Flag);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_SW_2_Dependency_Set_Flag(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_2_DEPENDENCY_SET_FLAG);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchDependencyFlag = 2;
      break;
    case CANCEL_KEY_EVENT:
      SwitchDependencyFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_2_DEPENDENCY_SET_FLAG);
}
FUNC_REGISTER(MENU_SWITCH_2_DEPENDENCY_SET_FLAG, Menu_SW_2_Dependency_Set_Flag);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_SW_3_Dependency_Set_Flag(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_3_DEPENDENCY_SET_FLAG);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchDependencyFlag = 3;
      break;
    case CANCEL_KEY_EVENT:
      SwitchDependencyFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_3_DEPENDENCY_SET_FLAG);
}
FUNC_REGISTER(MENU_SWITCH_3_DEPENDENCY_SET_FLAG, Menu_SW_3_Dependency_Set_Flag);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_SW_4_Dependency_Set_Flag(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_4_DEPENDENCY_SET_FLAG);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchDependencyFlag = 4;
      break;
    case CANCEL_KEY_EVENT:
      SwitchDependencyFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_4_DEPENDENCY_SET_FLAG);
}
FUNC_REGISTER(MENU_SWITCH_4_DEPENDENCY_SET_FLAG, Menu_SW_4_Dependency_Set_Flag);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_SW_5_Dependency_Set_Flag(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_5_DEPENDENCY_SET_FLAG);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchDependencyFlag = 5;
      break;
    case CANCEL_KEY_EVENT:
      SwitchDependencyFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_5_DEPENDENCY_SET_FLAG);
}
FUNC_REGISTER(MENU_SWITCH_5_DEPENDENCY_SET_FLAG, Menu_SW_5_Dependency_Set_Flag);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_SW_6_Dependency_Set_Flag(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_6_DEPENDENCY_SET_FLAG);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchDependencyFlag = 6;
      break;
    case CANCEL_KEY_EVENT:
      SwitchDependencyFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_6_DEPENDENCY_SET_FLAG);
}
FUNC_REGISTER(MENU_SWITCH_6_DEPENDENCY_SET_FLAG, Menu_SW_6_Dependency_Set_Flag);


/*******************************************************************************
 * Menu States
 ******************************************************************************/

uint8 SwitchesDependencyPath[] = {2, 3};
MENU_STATE_CREATE(
  // Name
  SwitchesDependency,
  // Path
  SwitchesDependencyPath,
  // Max Level
  2,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_SW_Dep_Set_Name,
  // String
  "Sw Dependency"
);

uint8 Switch_1_DependencyPath[] = {2, 3, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Dependency,
  // Path
  Switch_1_DependencyPath,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_SW_1_Dependency_Set_Flag,
  // String
  SW_Display_Name[0]
);

uint8 Switch_2_DependencyPath[] = {2, 3, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Dependency,
  // Path
  Switch_2_DependencyPath,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_SW_2_Dependency_Set_Flag,
  // String
  SW_Display_Name[1]
);

uint8 Switch_3_DependencyPath[] = {2, 3, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Dependency,
  // Path
  Switch_3_DependencyPath,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_SW_3_Dependency_Set_Flag,
  // String
  SW_Display_Name[2]
);

uint8 Switch_4_DependencyPath[] = {2, 3, 3};
MENU_STATE_CREATE(
  // Name
  Switch_4_Dependency,
  // Path
  Switch_4_DependencyPath,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_SW_4_Dependency_Set_Flag,
  // String
  SW_Display_Name[3]
);

uint8 Switch_5_DependencyPath[] = {2, 3, 4};
MENU_STATE_CREATE(
  // Name
  Switch_5_Dependency,
  // Path
  Switch_5_DependencyPath,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_SW_5_Dependency_Set_Flag,
  // String
  SW_Display_Name[4]
);

uint8 Switch_6_DependencyPath[] = {2, 3, 5};
MENU_STATE_CREATE(
  // Name
  Switch_6_Dependency,
  // Path
  Switch_6_DependencyPath,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_SW_6_Dependency_Set_Flag,
  // String
  SW_Display_Name[5]
);

