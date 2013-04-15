#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "Menu_Switches.h"
#include "SW_Management.h"
#include "Menu_SW_Time_Dep.h"
#include "Menu_SW_Temp_Dep.h"
#include "Menu_SW_Time_Temp_Dep.h"

#pragma section=".menu"

/**** Defines ****/
#define EV_1_SET_STR    1
#define EV_2_SET_STR    2
#define EV_3_SET_STR    4
#define EV_4_SET_STR    8

/**** Gloval Variables ****/
uint8 SwitchDependencyFlag = 0;
uint8 SwitchEventDependencyFlag = 0;

SW_M_Event_t SW_M_Event_g;

char SW_Event_DisplayName[NO_OF_EVENTS_PER_SWITCH][SWITCHES_SET_STRING_LENGTH] = {0};
char SW_Event_State_DisplayName[SWITCHES_SET_STRING_LENGTH] = {0};
char SW_Event_SaveName[SWITCHES_SET_STRING_LENGTH] = {0};
char SW_Event_TimeDependencyName[SWITCHES_SET_STRING_LENGTH] = {0};
char SW_Event_TempDependencyName[SWITCHES_SET_STRING_LENGTH] = {0};
char SW_Event_TimeTempDependencyName[SWITCHES_SET_STRING_LENGTH] = {0};

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
static Status_t Menu_SW_Set_Event_Display_String(const uint32 EventsFlags)
{
  FuncIN(MENU_SW_SET_EVENT_DISPLAY_STRING);
  
  SW_M_Event_t SW_M_Event;
  
  /**** Set Event 1 String ****/
  if(EventsFlags & EV_1_SET_STR)
  {
    SW_M_Get_Event(SwitchDependencyFlag, 1, &SW_M_Event);
    
    strcpy(SW_Event_DisplayName[0], "Event 1: ");
    
    if((SW_M_Event.Config & SW_EVENT_ON) == SW_EVENT_ON)
      strcat(SW_Event_DisplayName[0], "ON");
    else
      strcat(SW_Event_DisplayName[0], "OFF");
  }
  
  /**** Set Event 2 String ****/
  if(EventsFlags & EV_2_SET_STR)
  {
    SW_M_Get_Event(SwitchDependencyFlag, 2, &SW_M_Event);
    
    strcpy(SW_Event_DisplayName[1], "Event 2: ");
    
    if((SW_M_Event.Config & SW_EVENT_ON) == SW_EVENT_ON)
      strcat(SW_Event_DisplayName[1], "ON");
    else
      strcat(SW_Event_DisplayName[1], "OFF");
  }
  
  /**** Set Event 3 String ****/
  if(EventsFlags & EV_3_SET_STR)
  {
    SW_M_Get_Event(SwitchDependencyFlag, 3, &SW_M_Event);
    
    strcpy(SW_Event_DisplayName[2], "Event 3: ");
    
    if((SW_M_Event.Config & SW_EVENT_ON) == SW_EVENT_ON)
      strcat(SW_Event_DisplayName[2], "ON");
    else
      strcat(SW_Event_DisplayName[2], "OFF");
  }
  
  /**** Set Event 4 String ****/
  if(EventsFlags & EV_4_SET_STR)
  {
    SW_M_Get_Event(SwitchDependencyFlag, 4, &SW_M_Event);
    
    strcpy(SW_Event_DisplayName[3], "Event 4: ");
    
    if((SW_M_Event.Config & SW_EVENT_ON) == SW_EVENT_ON)
      strcat(SW_Event_DisplayName[3], "ON");
    else
      strcat(SW_Event_DisplayName[3], "OFF");
  }
  
  EXIT_SUCCESS_FUNC(MENU_SW_SET_EVENT_DISPLAY_STRING);
}
FUNC_REGISTER(MENU_SW_SET_EVENT_DISPLAY_STRING, Menu_SW_Set_Event_Display_String);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Set_Event_State_Display_String(void)
{
  FuncIN(MENU_SET_EVENT_STATE_DISPLAY_STRING);
  
  if((SW_M_Event_g.Config & SW_EVENT_ON) == SW_EVENT_ON)
    strcpy(SW_Event_State_DisplayName, "State: ON");
  else
    strcpy(SW_Event_State_DisplayName, "State: OFF");
  
  EXIT_SUCCESS_FUNC(MENU_SET_EVENT_STATE_DISPLAY_STRING);
}
FUNC_REGISTER(MENU_SET_EVENT_STATE_DISPLAY_STRING, Menu_SW_Set_Event_State_Display_String);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Set_Event_Save_Display_String(uint32 SaveFlag)
{
  FuncIN(MENU_SET_EVENT_SAVE_DISPLAY_STRING);
  
  switch(SaveFlag)
  {
    case 0:
      strcpy(SW_Event_SaveName, "Save");
      break;
    case 1:
      strcpy(SW_Event_SaveName, "Save: Saved!");
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } 
  
  EXIT_SUCCESS_FUNC(MENU_SET_EVENT_SAVE_DISPLAY_STRING);
}
FUNC_REGISTER(MENU_SET_EVENT_SAVE_DISPLAY_STRING, Menu_SW_Set_Event_Save_Display_String);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Set_Dependency_Display_Strings(void)
{
  FuncIN(MENU_SET_DEPENDENCY_DISPLAY_STRINGS);
  
  if((SW_M_Event_g.Config & SW_EVENT_TIME_TEMP_DEP) == SW_EVENT_TIME_DEP)
  {
    strcpy(SW_Event_TimeDependencyName, "# Time Dep");
    strcpy(SW_Event_TempDependencyName, "  Temp Dep");
    strcpy(SW_Event_TimeTempDependencyName, "  Time & Temp Dep");
  }
  else if((SW_M_Event_g.Config & SW_EVENT_TIME_TEMP_DEP) == SW_EVENT_TEMP_DEP)
  {
    strcpy(SW_Event_TimeDependencyName, "  Time Dep");
    strcpy(SW_Event_TempDependencyName, "# Temp Dep");
    strcpy(SW_Event_TimeTempDependencyName, "  Time & Temp Dep");
  }
  else if((SW_M_Event_g.Config & SW_EVENT_TIME_TEMP_DEP) == SW_EVENT_TIME_TEMP_DEP)
  {
    strcpy(SW_Event_TimeDependencyName, "  Time Dep");
    strcpy(SW_Event_TempDependencyName, "  Temp Dep");
    strcpy(SW_Event_TimeTempDependencyName, "# Time & Temp Dep");
  }
  else
  {
    strcpy(SW_Event_TimeDependencyName, "  Time Dep");
    strcpy(SW_Event_TempDependencyName, "  Temp Dep");
    strcpy(SW_Event_TimeTempDependencyName, "  Time & Temp Dep");
  }
  
  EXIT_SUCCESS_FUNC(MENU_SET_DEPENDENCY_DISPLAY_STRINGS);
}
FUNC_REGISTER(MENU_SET_DEPENDENCY_DISPLAY_STRINGS, Menu_Set_Dependency_Display_Strings);

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
      Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                       EV_2_SET_STR |
                                       EV_3_SET_STR |
                                       EV_4_SET_STR);
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
      Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                       EV_2_SET_STR |
                                       EV_3_SET_STR |
                                       EV_4_SET_STR);
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
      Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                       EV_2_SET_STR |
                                       EV_3_SET_STR |
                                       EV_4_SET_STR);
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
      Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                       EV_2_SET_STR |
                                       EV_3_SET_STR |
                                       EV_4_SET_STR);
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
      Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                       EV_2_SET_STR |
                                       EV_3_SET_STR |
                                       EV_4_SET_STR);
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
      Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                       EV_2_SET_STR |
                                       EV_3_SET_STR |
                                       EV_4_SET_STR);
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
 *
 ******************************************************************************/
static Status_t Menu_Event_1_Dependency_Set_Flag(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_EVENT_1_DEPENDENCY_SET_FLAG);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchEventDependencyFlag = 1;
      SW_M_Get_Event(SwitchDependencyFlag, SwitchEventDependencyFlag, &SW_M_Event_g);
      Menu_Set_Event_State_Display_String();
      Menu_Set_Event_Save_Display_String(0);
      break;
    case CANCEL_KEY_EVENT:
      Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                       EV_2_SET_STR |
                                       EV_3_SET_STR |
                                       EV_4_SET_STR);
      SwitchEventDependencyFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_EVENT_1_DEPENDENCY_SET_FLAG);
}
FUNC_REGISTER(MENU_EVENT_1_DEPENDENCY_SET_FLAG, Menu_Event_1_Dependency_Set_Flag);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Event_2_Dependency_Set_Flag(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_EVENT_2_DEPENDENCY_SET_FLAG);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchEventDependencyFlag = 2;
      SW_M_Get_Event(SwitchDependencyFlag, SwitchEventDependencyFlag, &SW_M_Event_g);
      Menu_Set_Event_State_Display_String();
      Menu_Set_Event_Save_Display_String(0);
      break;
    case CANCEL_KEY_EVENT:
      Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                       EV_2_SET_STR |
                                       EV_3_SET_STR |
                                       EV_4_SET_STR);
      SwitchEventDependencyFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_EVENT_2_DEPENDENCY_SET_FLAG);
}
FUNC_REGISTER(MENU_EVENT_2_DEPENDENCY_SET_FLAG, Menu_Event_2_Dependency_Set_Flag);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Event_3_Dependency_Set_Flag(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_EVENT_3_DEPENDENCY_SET_FLAG);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchEventDependencyFlag = 3;
      SW_M_Get_Event(SwitchDependencyFlag, SwitchEventDependencyFlag, &SW_M_Event_g);
      Menu_Set_Event_State_Display_String();
      Menu_Set_Event_Save_Display_String(0);
      break;
    case CANCEL_KEY_EVENT:
      Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                       EV_2_SET_STR |
                                       EV_3_SET_STR |
                                       EV_4_SET_STR);
      SwitchEventDependencyFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_EVENT_3_DEPENDENCY_SET_FLAG);
}
FUNC_REGISTER(MENU_EVENT_3_DEPENDENCY_SET_FLAG, Menu_Event_3_Dependency_Set_Flag);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Event_4_Dependency_Set_Flag(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_EVENT_4_DEPENDENCY_SET_FLAG);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchEventDependencyFlag = 4;
      SW_M_Get_Event(SwitchDependencyFlag, SwitchEventDependencyFlag, &SW_M_Event_g);
      Menu_Set_Event_State_Display_String();
      Menu_Set_Event_Save_Display_String(0);
      break;
    case CANCEL_KEY_EVENT:
      Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                       EV_2_SET_STR |
                                       EV_3_SET_STR |
                                       EV_4_SET_STR);
      SwitchEventDependencyFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_EVENT_4_DEPENDENCY_SET_FLAG);
}
FUNC_REGISTER(MENU_EVENT_4_DEPENDENCY_SET_FLAG, Menu_Event_4_Dependency_Set_Flag);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Event_State_Update_Display(const uint32 Menu_SW_Ptr_Pos)
{
  FuncIN(MENU_EVENT_STATE_UPDATE_DISPLAY);
  
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
  
  printd(1, "Set Sw%u: Ev%u", SwitchDependencyFlag, SwitchEventDependencyFlag);
  
  if((SW_M_Event_g.Config & SW_EVENT_ON) == SW_EVENT_ON)
  {
    printd(2, "%s  OFF", PointerString_1);
    printd(3, "%s# ON", PointerString_2);
  }
  else
  {
    printd(2, "%s# OFF", PointerString_1);
    printd(3, "%s  ON", PointerString_2);
  }
  
  EXIT_SUCCESS_FUNC(MENU_EVENT_STATE_UPDATE_DISPLAY);
}
FUNC_REGISTER(MENU_EVENT_STATE_UPDATE_DISPLAY, Menu_Event_State_Update_Display);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Event_Set_State(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_EVENT_SET_STATE);
  
  static uint32 FirstEnter = 1;
  static uint32 Menu_SW_Event_Ptr_Pos = 0;
  
  clrd();
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      if(FirstEnter == 1)
      {
        FirstEnter = 0;
        Menu_Event_State_Update_Display(Menu_SW_Event_Ptr_Pos);
        syncd();
        
        EXIT_SUCCESS_FUNC(MENU_EVENT_SET_STATE);
      }
      
      if(Menu_SW_Event_Ptr_Pos == 1)
        SW_M_Event_g.Config |= SW_EVENT_ON;
      else
        SW_M_Event_g.Config &= ~SW_EVENT_ON;
      
      Menu_Set_Event_State_Display_String();
      Menu_Set_Event_Save_Display_String(0);
      
      Menu_Event_State_Update_Display(Menu_SW_Event_Ptr_Pos);
      
      printd(4, "Event State Set!");
      break;
    case CANCEL_KEY_EVENT:
      FirstEnter = 1;
      Menu_SW_Event_Ptr_Pos = 0;
      break;
    case UP_KEY_EVENT:
      Menu_SW_Event_Ptr_Pos = 0;
      Menu_Event_State_Update_Display(Menu_SW_Event_Ptr_Pos);
      break;
    case DOWN_KEY_EVENT:
      Menu_SW_Event_Ptr_Pos = 1;
      Menu_Event_State_Update_Display(Menu_SW_Event_Ptr_Pos);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  syncd();
  
  EXIT_SUCCESS_FUNC(MENU_EVENT_SET_STATE);
}
FUNC_REGISTER(MENU_EVENT_SET_STATE, Menu_Event_Set_State);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Event_Set_Dependency(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_EVENT_SET_DEPENDENCY);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      Menu_Set_Event_Save_Display_String(0);
      Menu_Set_Dependency_Display_Strings();
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_EVENT_SET_DEPENDENCY);
}
FUNC_REGISTER(MENU_EVENT_SET_DEPENDENCY, Menu_Event_Set_Dependency);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Event_Save(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_EVENT_SAVE);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SW_M_Set_Event(SwitchDependencyFlag, SwitchEventDependencyFlag, &SW_M_Event_g);
      Menu_Set_Event_Save_Display_String(1);
      
      switch(SwitchEventDependencyFlag)
      {
        case 1:
          Menu_SW_Set_Event_Display_String(EV_1_SET_STR);
          break;
        case 2:
          Menu_SW_Set_Event_Display_String(EV_2_SET_STR);
          break;
        case 3:
          Menu_SW_Set_Event_Display_String(EV_3_SET_STR);
          break;
        case 4:
          Menu_SW_Set_Event_Display_String(EV_4_SET_STR);
          break;
        default:
          Menu_SW_Set_Event_Display_String(EV_1_SET_STR |
                                           EV_2_SET_STR |
                                           EV_3_SET_STR |
                                           EV_4_SET_STR);
          break;
      }
      
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_EVENT_SAVE);
}
FUNC_REGISTER(MENU_EVENT_SAVE, Menu_Event_Save);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Set_Time_Dependency(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SET_TIME_DEPENDENCY);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SW_M_Event_g.Config &= ~SW_EVENT_TEMP_DEP;
      SW_M_Event_g.Config |= SW_EVENT_TIME_DEP;
      
      Menu_Set_Dependency_Display_Strings();
      Menu_Time_Dep_Set_Time_Name();
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SET_TIME_DEPENDENCY);
}
FUNC_REGISTER(MENU_SET_TIME_DEPENDENCY, Menu_Set_Time_Dependency);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Set_Temp_Dependency(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SET_TEMP_DEPENDENCY);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SW_M_Event_g.Config &= ~SW_EVENT_TIME_DEP;
      SW_M_Event_g.Config |= SW_EVENT_TEMP_DEP;
      
      Menu_Set_Dependency_Display_Strings();
      Menu_Temp_Dep_Set_Temp_Name();
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SET_TEMP_DEPENDENCY);
}
FUNC_REGISTER(MENU_SET_TEMP_DEPENDENCY, Menu_Set_Temp_Dependency);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Set_Time_Temp_Dependency(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SET_TIME_TEMP_DEPENDENCY);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SW_M_Event_g.Config |= SW_EVENT_TIME_TEMP_DEP;
      
      Menu_Set_Dependency_Display_Strings();
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SET_TIME_TEMP_DEPENDENCY);
}
FUNC_REGISTER(MENU_SET_TIME_TEMP_DEPENDENCY, Menu_Set_Time_Temp_Dependency);


/*******************************************************************************
 * Menu States
 ******************************************************************************/


/*******************************************************************************
 * Level 2
 ******************************************************************************/

const uint8 SwitchesDependencyPath[] = {2, 3};
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


/*******************************************************************************
 * Level 3
 ******************************************************************************/

const uint8 Switch_1_DependencyPath[] = {2, 3, 0};
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

const uint8 Switch_2_DependencyPath[] = {2, 3, 1};
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

const uint8 Switch_3_DependencyPath[] = {2, 3, 2};
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

const uint8 Switch_4_DependencyPath[] = {2, 3, 3};
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

const uint8 Switch_5_DependencyPath[] = {2, 3, 4};
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

const uint8 Switch_6_DependencyPath[] = {2, 3, 5};
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


/*******************************************************************************
 * Level 4
 ******************************************************************************/

/**** Switch 1 ****/
const uint8 Switch_1_Event_1_DependencyPath[] = {2, 3, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Dependency,
  // Path
  Switch_1_Event_1_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_1_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[0]
);

const uint8 Switch_1_Event_2_DependencyPath[] = {2, 3, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Dependency,
  // Path
  Switch_1_Event_2_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_2_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[1]
);

const uint8 Switch_1_Event_3_DependencyPath[] = {2, 3, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Dependency,
  // Path
  Switch_1_Event_3_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_3_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[2]
);

const uint8 Switch_1_Event_4_DependencyPath[] = {2, 3, 0, 3};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Dependency,
  // Path
  Switch_1_Event_4_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_4_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[3]
);


/**** Switch 2 ****/
const uint8 Switch_2_Event_1_DependencyPath[] = {2, 3, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Dependency,
  // Path
  Switch_2_Event_1_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_1_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[0]
);

const uint8 Switch_2_Event_2_DependencyPath[] = {2, 3, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Dependency,
  // Path
  Switch_2_Event_2_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_2_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[1]
);

const uint8 Switch_2_Event_3_DependencyPath[] = {2, 3, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Dependency,
  // Path
  Switch_2_Event_3_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_3_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[2]
);

const uint8 Switch_2_Event_4_DependencyPath[] = {2, 3, 1, 3};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Dependency,
  // Path
  Switch_2_Event_4_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_4_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[3]
);


/**** Switch 3 ****/
const uint8 Switch_3_Event_1_DependencyPath[] = {2, 3, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Dependency,
  // Path
  Switch_3_Event_1_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_1_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[0]
);

const uint8 Switch_3_Event_2_DependencyPath[] = {2, 3, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Dependency,
  // Path
  Switch_3_Event_2_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_2_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[1]
);

const uint8 Switch_3_Event_3_DependencyPath[] = {2, 3, 2, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Dependency,
  // Path
  Switch_3_Event_3_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_3_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[2]
);

const uint8 Switch_3_Event_4_DependencyPath[] = {2, 3, 2, 3};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Dependency,
  // Path
  Switch_3_Event_4_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_4_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[3]
);


/**** Switch 4 ****/
const uint8 Switch_4_Event_1_DependencyPath[] = {2, 3, 3, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Dependency,
  // Path
  Switch_4_Event_1_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_1_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[0]
);

const uint8 Switch_4_Event_2_DependencyPath[] = {2, 3, 3, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Dependency,
  // Path
  Switch_4_Event_2_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_2_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[1]
);

const uint8 Switch_4_Event_3_DependencyPath[] = {2, 3, 3, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Dependency,
  // Path
  Switch_4_Event_3_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_3_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[2]
);

const uint8 Switch_4_Event_4_DependencyPath[] = {2, 3, 3, 3};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Dependency,
  // Path
  Switch_4_Event_4_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_4_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[3]
);


/**** Switch 5 ****/
const uint8 Switch_5_Event_1_DependencyPath[] = {2, 3, 4, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Dependency,
  // Path
  Switch_5_Event_1_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_1_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[0]
);

const uint8 Switch_5_Event_2_DependencyPath[] = {2, 3, 4, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Dependency,
  // Path
  Switch_5_Event_2_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_2_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[1]
);

const uint8 Switch_5_Event_3_DependencyPath[] = {2, 3, 4, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Dependency,
  // Path
  Switch_5_Event_3_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_3_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[2]
);

const uint8 Switch_5_Event_4_DependencyPath[] = {2, 3, 4, 3};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Dependency,
  // Path
  Switch_5_Event_4_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_4_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[3]
);


/**** Switch 6 ****/
const uint8 Switch_6_Event_1_DependencyPath[] = {2, 3, 5, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Dependency,
  // Path
  Switch_6_Event_1_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_1_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[0]
);

const uint8 Switch_6_Event_2_DependencyPath[] = {2, 3, 5, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Dependency,
  // Path
  Switch_6_Event_2_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_2_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[1]
);

const uint8 Switch_6_Event_3_DependencyPath[] = {2, 3, 5, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Dependency,
  // Path
  Switch_6_Event_3_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_3_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[2]
);

const uint8 Switch_6_Event_4_DependencyPath[] = {2, 3, 5, 3};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Dependency,
  // Path
  Switch_6_Event_4_DependencyPath,
  // Max Level
  4,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_4_Dependency_Set_Flag,
  // String
  SW_Event_DisplayName[3]
);


/*******************************************************************************
 * Level 5
 ******************************************************************************/

/**** Switch 1 State **********************************************************/
const uint8 Switch_1_Event_1_StatePath[] = {2, 3, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_State,
  // Path
  Switch_1_Event_1_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_1_Event_2_StatePath[] = {2, 3, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_State,
  // Path
  Switch_1_Event_2_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_1_Event_3_StatePath[] = {2, 3, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_State,
  // Path
  Switch_1_Event_3_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_1_Event_4_StatePath[] = {2, 3, 0, 3, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_State,
  // Path
  Switch_1_Event_4_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);


/**** Switch 2 State **********************************************************/
const uint8 Switch_2_Event_1_StatePath[] = {2, 3, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_State,
  // Path
  Switch_2_Event_1_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_2_Event_2_StatePath[] = {2, 3, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_State,
  // Path
  Switch_2_Event_2_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_2_Event_3_StatePath[] = {2, 3, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_State,
  // Path
  Switch_2_Event_3_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_2_Event_4_StatePath[] = {2, 3, 1, 3, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_State,
  // Path
  Switch_2_Event_4_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);


/**** Switch 3 State **********************************************************/
const uint8 Switch_3_Event_1_StatePath[] = {2, 3, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_State,
  // Path
  Switch_3_Event_1_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_3_Event_2_StatePath[] = {2, 3, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_State,
  // Path
  Switch_3_Event_2_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_3_Event_3_StatePath[] = {2, 3, 2, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_State,
  // Path
  Switch_3_Event_3_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_3_Event_4_StatePath[] = {2, 3, 2, 3, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_State,
  // Path
  Switch_3_Event_4_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);


/**** Switch 4 State **********************************************************/
const uint8 Switch_4_Event_1_StatePath[] = {2, 3, 3, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_State,
  // Path
  Switch_4_Event_1_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_4_Event_2_StatePath[] = {2, 3, 3, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_State,
  // Path
  Switch_4_Event_2_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_4_Event_3_StatePath[] = {2, 3, 3, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_State,
  // Path
  Switch_4_Event_3_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_4_Event_4_StatePath[] = {2, 3, 3, 3, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_State,
  // Path
  Switch_4_Event_4_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);


/**** Switch 5 State **********************************************************/
const uint8 Switch_5_Event_1_StatePath[] = {2, 3, 4, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_State,
  // Path
  Switch_5_Event_1_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_5_Event_2_StatePath[] = {2, 3, 4, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_State,
  // Path
  Switch_5_Event_2_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_5_Event_3_StatePath[] = {2, 3, 4, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_State,
  // Path
  Switch_5_Event_3_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_5_Event_4_StatePath[] = {2, 3, 4, 3, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_State,
  // Path
  Switch_5_Event_4_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);


/**** Switch 6 State ****/
const uint8 Switch_6_Event_1_StatePath[] = {2, 3, 5, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_State,
  // Path
  Switch_6_Event_1_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_6_Event_2_StatePath[] = {2, 3, 5, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_State,
  // Path
  Switch_6_Event_2_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_6_Event_3_StatePath[] = {2, 3, 5, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_State,
  // Path
  Switch_6_Event_3_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);

const uint8 Switch_6_Event_4_StatePath[] = {2, 3, 5, 3, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_State,
  // Path
  Switch_6_Event_4_StatePath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  SW_Event_State_DisplayName
);


/**** Switch 1 Dependency *****************************************************/
const uint8 Switch_1_Event_1_SetDependencyPath[] = {2, 3, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_SetDependency,
  // Path
  Switch_1_Event_1_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_1_Event_2_SetDependencyPath[] = {2, 3, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_SetDependency,
  // Path
  Switch_1_Event_2_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_1_Event_3_SetDependencyPath[] = {2, 3, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_SetDependency,
  // Path
  Switch_1_Event_3_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_1_Event_4_SetDependencyPath[] = {2, 3, 0, 3, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_SetDependency,
  // Path
  Switch_1_Event_4_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);


/**** Switch 2 Dependency *****************************************************/
const uint8 Switch_2_Event_1_SetDependencyPath[] = {2, 3, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_SetDependency,
  // Path
  Switch_2_Event_1_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_2_Event_2_SetDependencyPath[] = {2, 3, 1, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_SetDependency,
  // Path
  Switch_2_Event_2_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_2_Event_3_SetDependencyPath[] = {2, 3, 1, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_SetDependency,
  // Path
  Switch_2_Event_3_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_2_Event_4_SetDependencyPath[] = {2, 3, 1, 3, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_SetDependency,
  // Path
  Switch_2_Event_4_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);


/**** Switch 3 Dependency *****************************************************/
const uint8 Switch_3_Event_1_SetDependencyPath[] = {2, 3, 2, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_SetDependency,
  // Path
  Switch_3_Event_1_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_3_Event_2_SetDependencyPath[] = {2, 3, 2, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_SetDependency,
  // Path
  Switch_3_Event_2_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_3_Event_3_SetDependencyPath[] = {2, 3, 2, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_SetDependency,
  // Path
  Switch_3_Event_3_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_3_Event_4_SetDependencyPath[] = {2, 3, 2, 3, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_SetDependency,
  // Path
  Switch_3_Event_4_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);


/**** Switch 4 Dependency *****************************************************/
const uint8 Switch_4_Event_1_SetDependencyPath[] = {2, 3, 3, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_SetDependency,
  // Path
  Switch_4_Event_1_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_4_Event_2_SetDependencyPath[] = {2, 3, 3, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_SetDependency,
  // Path
  Switch_4_Event_2_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_4_Event_3_SetDependencyPath[] = {2, 3, 3, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_SetDependency,
  // Path
  Switch_4_Event_3_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_4_Event_4_SetDependencyPath[] = {2, 3, 3, 3, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_SetDependency,
  // Path
  Switch_4_Event_4_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);


/**** Switch 5 Dependency *****************************************************/
const uint8 Switch_5_Event_1_SetDependencyPath[] = {2, 3, 4, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_SetDependency,
  // Path
  Switch_5_Event_1_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_5_Event_2_SetDependencyPath[] = {2, 3, 4, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_SetDependency,
  // Path
  Switch_5_Event_2_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_5_Event_3_SetDependencyPath[] = {2, 3, 4, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_SetDependency,
  // Path
  Switch_5_Event_3_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_5_Event_4_SetDependencyPath[] = {2, 3, 4, 3, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_SetDependency,
  // Path
  Switch_5_Event_4_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);


/**** Switch 6 Dependency *****************************************************/
const uint8 Switch_6_Event_1_SetDependencyPath[] = {2, 3, 5, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_SetDependency,
  // Path
  Switch_6_Event_1_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_6_Event_2_SetDependencyPath[] = {2, 3, 5, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_SetDependency,
  // Path
  Switch_6_Event_2_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_6_Event_3_SetDependencyPath[] = {2, 3, 5, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_SetDependency,
  // Path
  Switch_6_Event_3_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);

const uint8 Switch_6_Event_4_SetDependencyPath[] = {2, 3, 5, 3, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_SetDependency,
  // Path
  Switch_6_Event_4_SetDependencyPath,
  // Max Level
  5,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Set_Dependency,
  // String
  "Set Dependency"
);


/**** Switch 1 Save ***********************************************************/
const uint8 Switch_1_Event_1_SavePath[] = {2, 3, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Save,
  // Path
  Switch_1_Event_1_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_1_Event_2_SavePath[] = {2, 3, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Save,
  // Path
  Switch_1_Event_2_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_1_Event_3_SavePath[] = {2, 3, 0, 2, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Save,
  // Path
  Switch_1_Event_3_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_1_Event_4_SavePath[] = {2, 3, 0, 3, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Save,
  // Path
  Switch_1_Event_4_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);


/**** Switch 2 Save ***********************************************************/
const uint8 Switch_2_Event_1_SavePath[] = {2, 3, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Save,
  // Path
  Switch_2_Event_1_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_2_Event_2_SavePath[] = {2, 3, 1, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Save,
  // Path
  Switch_2_Event_2_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_2_Event_3_SavePath[] = {2, 3, 1, 2, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Save,
  // Path
  Switch_2_Event_3_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_2_Event_4_SavePath[] = {2, 3, 1, 3, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Save,
  // Path
  Switch_2_Event_4_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);


/**** Switch 3 Save ***********************************************************/
const uint8 Switch_3_Event_1_SavePath[] = {2, 3, 2, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Save,
  // Path
  Switch_3_Event_1_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_3_Event_2_SavePath[] = {2, 3, 2, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Save,
  // Path
  Switch_3_Event_2_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_3_Event_3_SavePath[] = {2, 3, 2, 2, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Save,
  // Path
  Switch_3_Event_3_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_3_Event_4_SavePath[] = {2, 3, 2, 3, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Save,
  // Path
  Switch_3_Event_4_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);


/**** Switch 4 Save ***********************************************************/
const uint8 Switch_4_Event_1_SavePath[] = {2, 3, 3, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Save,
  // Path
  Switch_4_Event_1_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_4_Event_2_SavePath[] = {2, 3, 3, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Save,
  // Path
  Switch_4_Event_2_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_4_Event_3_SavePath[] = {2, 3, 3, 2, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Save,
  // Path
  Switch_4_Event_3_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_4_Event_4_SavePath[] = {2, 3, 3, 3, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Save,
  // Path
  Switch_4_Event_4_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);


/**** Switch 5 Save ***********************************************************/
const uint8 Switch_5_Event_1_SavePath[] = {2, 3, 4, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Save,
  // Path
  Switch_5_Event_1_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_5_Event_2_SavePath[] = {2, 3, 4, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Save,
  // Path
  Switch_5_Event_2_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_5_Event_3_SavePath[] = {2, 3, 4, 2, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Save,
  // Path
  Switch_5_Event_3_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_5_Event_4_SavePath[] = {2, 3, 4, 3, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Save,
  // Path
  Switch_5_Event_4_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);


/**** Switch 6 Save ***********************************************************/
const uint8 Switch_6_Event_1_SavePath[] = {2, 3, 5, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Save,
  // Path
  Switch_6_Event_1_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_6_Event_2_SavePath[] = {2, 3, 5, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Save,
  // Path
  Switch_6_Event_2_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_6_Event_3_SavePath[] = {2, 3, 5, 2, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Save,
  // Path
  Switch_6_Event_3_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);

const uint8 Switch_6_Event_4_SavePath[] = {2, 3, 5, 3, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Save,
  // Path
  Switch_6_Event_4_SavePath,
  // Max Level
  5,
  // Flags
  MENU_LAST_STATE |
  MENU_FORCE_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Event_Save,
  // String
  SW_Event_SaveName
);


/*******************************************************************************
 * Level 6
 ******************************************************************************/

/**** Switch 1 State **********************************************************/
const uint8 Switch_1_Event_1_SetStatePath[] = {2, 3, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_SetState,
  // Path
  Switch_1_Event_1_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_1_Event_2_SetStatePath[] = {2, 3, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_SetState,
  // Path
  Switch_1_Event_2_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_1_Event_3_SetStatePath[] = {2, 3, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_SetState,
  // Path
  Switch_1_Event_3_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_1_Event_4_SetStatePath[] = {2, 3, 0, 3, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_SetState,
  // Path
  Switch_1_Event_4_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);


/**** Switch 2 State **********************************************************/
const uint8 Switch_2_Event_1_SetStatePath[] = {2, 3, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_SetState,
  // Path
  Switch_2_Event_1_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_2_Event_2_SetStatePath[] = {2, 3, 1, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_SetState,
  // Path
  Switch_2_Event_2_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_2_Event_3_SetStatePath[] = {2, 3, 1, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_SetState,
  // Path
  Switch_2_Event_3_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_2_Event_4_SetStatePath[] = {2, 3, 1, 3, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_SetState,
  // Path
  Switch_2_Event_4_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);


/**** Switch 3 State **********************************************************/
const uint8 Switch_3_Event_1_SetStatePath[] = {2, 3, 2, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_SetState,
  // Path
  Switch_3_Event_1_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_3_Event_2_SetStatePath[] = {2, 3, 2, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_SetState,
  // Path
  Switch_3_Event_2_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_3_Event_3_SetStatePath[] = {2, 3, 2, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_SetState,
  // Path
  Switch_3_Event_3_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_3_Event_4_SetStatePath[] = {2, 3, 2, 3, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_SetState,
  // Path
  Switch_3_Event_4_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);


/**** Switch 4 State **********************************************************/
const uint8 Switch_4_Event_1_SetStatePath[] = {2, 3, 3, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_SetState,
  // Path
  Switch_4_Event_1_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_4_Event_2_SetStatePath[] = {2, 3, 3, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_SetState,
  // Path
  Switch_4_Event_2_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_4_Event_3_SetStatePath[] = {2, 3, 3, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_SetState,
  // Path
  Switch_4_Event_3_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_4_Event_4_SetStatePath[] = {2, 3, 3, 3, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_SetState,
  // Path
  Switch_4_Event_4_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);


/**** Switch 5 State **********************************************************/
const uint8 Switch_5_Event_1_SetStatePath[] = {2, 3, 4, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_SetState,
  // Path
  Switch_5_Event_1_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_5_Event_2_SetStatePath[] = {2, 3, 4, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_SetState,
  // Path
  Switch_5_Event_2_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_5_Event_3_SetStatePath[] = {2, 3, 4, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_SetState,
  // Path
  Switch_5_Event_3_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_5_Event_4_SetStatePath[] = {2, 3, 4, 3, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_SetState,
  // Path
  Switch_5_Event_4_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);


/**** Switch 6 State **********************************************************/
const uint8 Switch_6_Event_1_SetStatePath[] = {2, 3, 5, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_SetState,
  // Path
  Switch_6_Event_1_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_6_Event_2_SetStatePath[] = {2, 3, 5, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_SetState,
  // Path
  Switch_6_Event_2_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_6_Event_3_SetStatePath[] = {2, 3, 5, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_SetState,
  // Path
  Switch_6_Event_3_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);

const uint8 Switch_6_Event_4_SetStatePath[] = {2, 3, 5, 3, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_SetState,
  // Path
  Switch_6_Event_4_SetStatePath,
  // Max Level
  6,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Event_Set_State,
  // String
  ""
);


/**** Switch 1 Time Dep *******************************************************/
const uint8 Switch_1_Event_1_SetTimeDepPath[] = {2, 3, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_SetTimeDep,
  // Path
  Switch_1_Event_1_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_1_Event_2_SetTimeDepPath[] = {2, 3, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_SetTimeDep,
  // Path
  Switch_1_Event_2_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_1_Event_3_SetTimeDepPath[] = {2, 3, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_SetTimeDep,
  // Path
  Switch_1_Event_3_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_1_Event_4_SetTimeDepPath[] = {2, 3, 0, 3, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_SetTimeDep,
  // Path
  Switch_1_Event_4_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);


/**** Switch 2 Time Dep *******************************************************/
const uint8 Switch_2_Event_1_SetTimeDepPath[] = {2, 3, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_SetTimeDep,
  // Path
  Switch_2_Event_1_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_2_Event_2_SetTimeDepPath[] = {2, 3, 1, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_SetTimeDep,
  // Path
  Switch_2_Event_2_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_2_Event_3_SetTimeDepPath[] = {2, 3, 1, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_SetTimeDep,
  // Path
  Switch_2_Event_3_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_2_Event_4_SetTimeDepPath[] = {2, 3, 1, 3, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_SetTimeDep,
  // Path
  Switch_2_Event_4_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);


/**** Switch 3 Time Dep *******************************************************/
const uint8 Switch_3_Event_1_SetTimeDepPath[] = {2, 3, 2, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_SetTimeDep,
  // Path
  Switch_3_Event_1_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_3_Event_2_SetTimeDepPath[] = {2, 3, 2, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_SetTimeDep,
  // Path
  Switch_3_Event_2_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_3_Event_3_SetTimeDepPath[] = {2, 3, 2, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_SetTimeDep,
  // Path
  Switch_3_Event_3_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_3_Event_4_SetTimeDepPath[] = {2, 3, 2, 3, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_SetTimeDep,
  // Path
  Switch_3_Event_4_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);


/**** Switch 4 Time Dep *******************************************************/
const uint8 Switch_4_Event_1_SetTimeDepPath[] = {2, 3, 3, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_SetTimeDep,
  // Path
  Switch_4_Event_1_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_4_Event_2_SetTimeDepPath[] = {2, 3, 3, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_SetTimeDep,
  // Path
  Switch_4_Event_2_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_4_Event_3_SetTimeDepPath[] = {2, 3, 3, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_SetTimeDep,
  // Path
  Switch_4_Event_3_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_4_Event_4_SetTimeDepPath[] = {2, 3, 3, 3, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_SetTimeDep,
  // Path
  Switch_4_Event_4_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);


/**** Switch 5 Time Dep *******************************************************/
const uint8 Switch_5_Event_1_SetTimeDepPath[] = {2, 3, 4, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_SetTimeDep,
  // Path
  Switch_5_Event_1_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_5_Event_2_SetTimeDepPath[] = {2, 3, 4, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_SetTimeDep,
  // Path
  Switch_5_Event_2_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_5_Event_3_SetTimeDepPath[] = {2, 3, 4, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_SetTimeDep,
  // Path
  Switch_5_Event_3_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_5_Event_4_SetTimeDepPath[] = {2, 3, 4, 3, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_SetTimeDep,
  // Path
  Switch_5_Event_4_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);


/**** Switch 6 Time Dep *******************************************************/
const uint8 Switch_6_Event_1_SetTimeDepPath[] = {2, 3, 5, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_SetTimeDep,
  // Path
  Switch_6_Event_1_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_6_Event_2_SetTimeDepPath[] = {2, 3, 5, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_SetTimeDep,
  // Path
  Switch_6_Event_2_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_6_Event_3_SetTimeDepPath[] = {2, 3, 5, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_SetTimeDep,
  // Path
  Switch_6_Event_3_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);

const uint8 Switch_6_Event_4_SetTimeDepPath[] = {2, 3, 5, 3, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_SetTimeDep,
  // Path
  Switch_6_Event_4_SetTimeDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Dependency,
  // String
  SW_Event_TimeDependencyName
);


/**** Switch 1 Temp Dep *******************************************************/
const uint8 Switch_1_Event_1_SetTempDepPath[] = {2, 3, 0, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_SetTempDep,
  // Path
  Switch_1_Event_1_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_1_Event_2_SetTempDepPath[] = {2, 3, 0, 1, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_SetTempDep,
  // Path
  Switch_1_Event_2_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_1_Event_3_SetTempDepPath[] = {2, 3, 0, 2, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_SetTempDep,
  // Path
  Switch_1_Event_3_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_1_Event_4_SetTempDepPath[] = {2, 3, 0, 3, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_SetTempDep,
  // Path
  Switch_1_Event_4_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);


/**** Switch 2 Temp Dep *******************************************************/
const uint8 Switch_2_Event_1_SetTempDepPath[] = {2, 3, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_SetTempDep,
  // Path
  Switch_2_Event_1_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_2_Event_2_SetTempDepPath[] = {2, 3, 1, 1, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_SetTempDep,
  // Path
  Switch_2_Event_2_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_2_Event_3_SetTempDepPath[] = {2, 3, 1, 2, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_SetTempDep,
  // Path
  Switch_2_Event_3_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_2_Event_4_SetTempDepPath[] = {2, 3, 1, 3, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_SetTempDep,
  // Path
  Switch_2_Event_4_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);


/**** Switch 3 Temp Dep *******************************************************/
const uint8 Switch_3_Event_1_SetTempDepPath[] = {2, 3, 2, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_SetTempDep,
  // Path
  Switch_3_Event_1_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_3_Event_2_SetTempDepPath[] = {2, 3, 2, 1, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_SetTempDep,
  // Path
  Switch_3_Event_2_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_3_Event_3_SetTempDepPath[] = {2, 3, 2, 2, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_SetTempDep,
  // Path
  Switch_3_Event_3_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_3_Event_4_SetTempDepPath[] = {2, 3, 2, 3, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_SetTempDep,
  // Path
  Switch_3_Event_4_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);


/**** Switch 4 Temp Dep *******************************************************/
const uint8 Switch_4_Event_1_SetTempDepPath[] = {2, 3, 3, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_SetTempDep,
  // Path
  Switch_4_Event_1_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_4_Event_2_SetTempDepPath[] = {2, 3, 3, 1, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_SetTempDep,
  // Path
  Switch_4_Event_2_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_4_Event_3_SetTempDepPath[] = {2, 3, 3, 2, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_SetTempDep,
  // Path
  Switch_4_Event_3_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_4_Event_4_SetTempDepPath[] = {2, 3, 3, 3, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_SetTempDep,
  // Path
  Switch_4_Event_4_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);


/**** Switch 5 Temp Dep *******************************************************/
const uint8 Switch_5_Event_1_SetTempDepPath[] = {2, 3, 4, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_SetTempDep,
  // Path
  Switch_5_Event_1_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_5_Event_2_SetTempDepPath[] = {2, 3, 4, 1, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_SetTempDep,
  // Path
  Switch_5_Event_2_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_5_Event_3_SetTempDepPath[] = {2, 3, 4, 2, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_SetTempDep,
  // Path
  Switch_5_Event_3_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_5_Event_4_SetTempDepPath[] = {2, 3, 4, 3, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_SetTempDep,
  // Path
  Switch_5_Event_4_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);


/**** Switch 6 Temp Dep *******************************************************/
const uint8 Switch_6_Event_1_SetTempDepPath[] = {2, 3, 5, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_SetTempDep,
  // Path
  Switch_6_Event_1_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_6_Event_2_SetTempDepPath[] = {2, 3, 5, 1, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_SetTempDep,
  // Path
  Switch_6_Event_2_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_6_Event_3_SetTempDepPath[] = {2, 3, 5, 2, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_SetTempDep,
  // Path
  Switch_6_Event_3_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);

const uint8 Switch_6_Event_4_SetTempDepPath[] = {2, 3, 5, 3, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_SetTempDep,
  // Path
  Switch_6_Event_4_SetTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Temp_Dependency,
  // String
  SW_Event_TempDependencyName
);


/**** Switch 1 Time & Temp Dep ************************************************/
const uint8 Switch_1_Event_1_SetTimeTempDepPath[] = {2, 3, 0, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_SetTimeTempDep,
  // Path
  Switch_1_Event_1_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_1_Event_2_SetTimeTempDepPath[] = {2, 3, 0, 1, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_SetTimeTempDep,
  // Path
  Switch_1_Event_2_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_1_Event_3_SetTimeTempDepPath[] = {2, 3, 0, 2, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_SetTimeTempDep,
  // Path
  Switch_1_Event_3_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_1_Event_4_SetTimeTempDepPath[] = {2, 3, 0, 3, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_SetTimeTempDep,
  // Path
  Switch_1_Event_4_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);


/**** Switch 2 Time & Temp Dep ************************************************/
const uint8 Switch_2_Event_1_SetTimeTempDepPath[] = {2, 3, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_SetTimeTempDep,
  // Path
  Switch_2_Event_1_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_2_Event_2_SetTimeTempDepPath[] = {2, 3, 1, 1, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_SetTimeTempDep,
  // Path
  Switch_2_Event_2_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_2_Event_3_SetTimeTempDepPath[] = {2, 3, 1, 2, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_SetTimeTempDep,
  // Path
  Switch_2_Event_3_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_2_Event_4_SetTimeTempDepPath[] = {2, 3, 1, 3, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_SetTimeTempDep,
  // Path
  Switch_2_Event_4_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);


/**** Switch 3 Time & Temp Dep ************************************************/
const uint8 Switch_3_Event_1_SetTimeTempDepPath[] = {2, 3, 2, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_SetTimeTempDep,
  // Path
  Switch_3_Event_1_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_3_Event_2_SetTimeTempDepPath[] = {2, 3, 2, 1, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_SetTimeTempDep,
  // Path
  Switch_3_Event_2_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_3_Event_3_SetTimeTempDepPath[] = {2, 3, 2, 2, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_SetTimeTempDep,
  // Path
  Switch_3_Event_3_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_3_Event_4_SetTimeTempDepPath[] = {2, 3, 2, 3, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_SetTimeTempDep,
  // Path
  Switch_3_Event_4_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);


/**** Switch 4 Time & Temp Dep ************************************************/
const uint8 Switch_4_Event_1_SetTimeTempDepPath[] = {2, 3, 3, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_SetTimeTempDep,
  // Path
  Switch_4_Event_1_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_4_Event_2_SetTimeTempDepPath[] = {2, 3, 3, 1, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_SetTimeTempDep,
  // Path
  Switch_4_Event_2_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_4_Event_3_SetTimeTempDepPath[] = {2, 3, 3, 2, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_SetTimeTempDep,
  // Path
  Switch_4_Event_3_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_4_Event_4_SetTimeTempDepPath[] = {2, 3, 3, 3, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_SetTimeTempDep,
  // Path
  Switch_4_Event_4_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);


/**** Switch 5 Time & Temp Dep ************************************************/
const uint8 Switch_5_Event_1_SetTimeTempDepPath[] = {2, 3, 4, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_SetTimeTempDep,
  // Path
  Switch_5_Event_1_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_5_Event_2_SetTimeTempDepPath[] = {2, 3, 4, 1, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_SetTimeTempDep,
  // Path
  Switch_5_Event_2_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_5_Event_3_SetTimeTempDepPath[] = {2, 3, 4, 2, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_SetTimeTempDep,
  // Path
  Switch_5_Event_3_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_5_Event_4_SetTimeTempDepPath[] = {2, 3, 4, 3, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_SetTimeTempDep,
  // Path
  Switch_5_Event_4_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);


/**** Switch 6 Time & Temp Dep ************************************************/
const uint8 Switch_6_Event_1_SetTimeTempDepPath[] = {2, 3, 5, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_SetTimeTempDep,
  // Path
  Switch_6_Event_1_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_6_Event_2_SetTimeTempDepPath[] = {2, 3, 5, 1, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_SetTimeTempDep,
  // Path
  Switch_6_Event_2_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_6_Event_3_SetTimeTempDepPath[] = {2, 3, 5, 2, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_SetTimeTempDep,
  // Path
  Switch_6_Event_3_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);

const uint8 Switch_6_Event_4_SetTimeTempDepPath[] = {2, 3, 5, 3, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_SetTimeTempDep,
  // Path
  Switch_6_Event_4_SetTimeTempDepPath,
  // Max Level
  6,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Time_Temp_Dependency,
  // String
  SW_Event_TimeTempDependencyName
);
