#include <stdio.h>
#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"

#include "Menu.h"
#include "Menu_Func.h"
#include "Menu_Switches.h"
#include "Menu_Switches_Dependency.h"


/**** Global Variables ****/
uint8 SetTimeFlag = 0;
char Time_1_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Time_2_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Time_State_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Set_Time_Name[SWITCHES_SET_STRING_LENGTH] = {0};


/**** Functions ****/

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Set_Time_Name(void)
{
  FuncIN(MENU_TIME_DEP_SET_TIME_NAME);
  
  switch(SW_M_Event_g.Time_Start.State)
  {
    case SW_TIME_ALARM_ON:
      strcpy(Time_1_Name, "Time 1 : ON");
      break;
    case SW_TIME_ALARM_OFF:
      strcpy(Time_1_Name, "Time 1 : OFF");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }
  
  switch(SW_M_Event_g.Time_Stop.State)
  {
    case SW_TIME_ALARM_ON:
      strcpy(Time_2_Name, "Time 2 : ON");
      break;
    case SW_TIME_ALARM_OFF:
      strcpy(Time_2_Name, "Time 2 : OFF");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }
  
  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME_NAME);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME_NAME, Menu_Time_Dep_Set_Time_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_Set_Time_State_Name(void)
{
  FuncIN(MENU_TIME_DEP_SET_TIME_STATE_NAME);
  
  switch(SetTimeFlag)
  {
    case 1:
      switch(SW_M_Event_g.Time_Start.State)
      {
        case SW_TIME_ALARM_ON:
          strcpy(Time_State_Name, "State : ON");
          break;
        case SW_TIME_ALARM_OFF:
          strcpy(Time_State_Name, "State : OFF");
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      }
      break;
    case 2:
      switch(SW_M_Event_g.Time_Stop.State)
      {
        case SW_TIME_ALARM_ON:
          strcpy(Time_State_Name, "State : ON");
          break;
        case SW_TIME_ALARM_OFF:
          strcpy(Time_State_Name, "State : OFF");
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      }
      break;
    default:
      Fatal_Abort(-NOT_INITIALIZED_ERROR);
  }
  
  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME_STATE_NAME);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME_STATE_NAME, Menu_Time_Dep_Set_Time_State_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_Setting_Time_Name(void)
{
  FuncIN(MENU_TIME_DEP_SETTING_TIME_NAME);
  
  switch(SetTimeFlag)
  {
    case 1:
      snprintf(Set_Time_Name, 16, "Time (%02u:%02u:%02u)",
               SW_M_Event_g.Time_Start.Hour,
               SW_M_Event_g.Time_Start.Minute,
               SW_M_Event_g.Time_Start.Second);
      break;
    case 2:
      snprintf(Set_Time_Name, 16, "Time (%02u:%02u:%02u)",
               SW_M_Event_g.Time_Stop.Hour,
               SW_M_Event_g.Time_Stop.Minute,
               SW_M_Event_g.Time_Stop.Second);
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }
  
  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SETTING_TIME_NAME);
}
FUNC_REGISTER(MENU_TIME_DEP_SETTING_TIME_NAME, Menu_Time_Dep_Setting_Time_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_Set_Time_1(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_SET_TIME_1);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetTimeFlag = 1;
      Menu_Time_Dep_Set_Time_State_Name();
      Menu_Time_Dep_Setting_Time_Name();
      break;
    case CANCEL_KEY_EVENT:
      SetTimeFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME_1);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME_1, Menu_Time_Dep_Set_Time_1);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_Set_Time_2(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_SET_TIME_2);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetTimeFlag = 2;
      Menu_Time_Dep_Set_Time_State_Name();
      Menu_Time_Dep_Setting_Time_Name();
      break;
    case CANCEL_KEY_EVENT:
      SetTimeFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME_2);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME_2, Menu_Time_Dep_Set_Time_2);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_Date(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_DATE);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  
  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_DATE);
}
FUNC_REGISTER(MENU_TIME_DEP_DATE, Menu_Time_Dep_Date);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_Set_Time(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_SET_TIME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME, Menu_Time_Dep_Set_Time);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_State_Update_Display(const uint32 Ptr_Pos)
{
  FuncIN(MENU_TIME_DEP_STATE_UPDATE_DISPLAY);
  
  uint8 State;
  char PointerString_1[3] = {0};
  char PointerString_2[3] = {0};
  
  switch(Ptr_Pos)
  {
    case 1:
      strcpy(PointerString_1, "> ");
      strcpy(PointerString_2, "  ");
      break;
    case 2:
      strcpy(PointerString_1, "  ");
      strcpy(PointerString_2, "> ");
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  printd(1, "Set State : Time %u", SetTimeFlag);
  
  switch(SetTimeFlag)
  {
    case 1:
      State = SW_M_Event_g.Time_Start.State;
      break;
    case 2:
      State = SW_M_Event_g.Time_Stop.State;
      break;
    default:
      Fatal_Abort(-NOT_INITIALIZED_ERROR);
  } // switch(SetTimeFlag)
  
  switch(State)
  {
    case SW_TIME_ALARM_OFF:
      printd(2, "%s# OFF", PointerString_1);
      printd(3, "%s  ON", PointerString_2);
      break;
    case SW_TIME_ALARM_ON:
      printd(2, "%s  OFF", PointerString_1);
      printd(3, "%s# ON", PointerString_2);
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  } // switch(State)
  
  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_STATE_UPDATE_DISPLAY);
}
FUNC_REGISTER(MENU_TIME_DEP_STATE_UPDATE_DISPLAY, Menu_Time_Dep_State_Update_Display);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_Time_State(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_TIME_STATE);
  
  static uint32 Ptr_Pos = 0;
  
  clrd();
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      if(Ptr_Pos == 0)
      {
        Ptr_Pos = 1;
        Menu_Time_Dep_State_Update_Display(Ptr_Pos);
      }
      else
      {
        switch(SetTimeFlag)
        {
          case 1:
            switch(Ptr_Pos)
            {
              case 1:
                SW_M_Event_g.Time_Start.State = SW_TIME_ALARM_OFF;
                break;
              case 2:
                SW_M_Event_g.Time_Start.State = SW_TIME_ALARM_ON;
                break;
              default:
                Fatal_Abort(-NOT_INITIALIZED_ERROR);
            }
            break;
          case 2:
            switch(Ptr_Pos)
            {
              case 1:
                SW_M_Event_g.Time_Stop.State = SW_TIME_ALARM_OFF;
                break;
              case 2:
                SW_M_Event_g.Time_Stop.State = SW_TIME_ALARM_ON;
                break;
              default:
                Fatal_Abort(-NOT_INITIALIZED_ERROR);
            }
            break;
          default:
            Fatal_Abort(-NOT_INITIALIZED_ERROR);
        } // switch(SetTimeFlag)
        
        Menu_Time_Dep_State_Update_Display(Ptr_Pos);
        printd(4, "State Set!");
        
        Menu_Time_Dep_Set_Time_State_Name();
        Menu_Time_Dep_Set_Time_Name();
      }
      break;
    case CANCEL_KEY_EVENT:
      Ptr_Pos = 0;
      break;
    case UP_KEY_EVENT:
      Ptr_Pos = 1;
      Menu_Time_Dep_State_Update_Display(Ptr_Pos);
      break;
    case DOWN_KEY_EVENT:
      Ptr_Pos = 2;
      Menu_Time_Dep_State_Update_Display(Ptr_Pos);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  syncd();
    
  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_TIME_STATE);
}
FUNC_REGISTER(MENU_TIME_DEP_TIME_STATE, Menu_Time_Dep_Time_State);


/*******************************************************************************
 * Menu States
 ******************************************************************************/

/*******************************************************************************
 * Level 7
 ******************************************************************************/


/**** Switch 1, Event 1, Time 1 Dep *******************************************/
const uint8 Switch_1_Event_1_Time1Path[] = {2, 3, 0, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time1,
  // Path
  Switch_1_Event_1_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 1, Event 1, Time 2 Dep *******************************************/
const uint8 Switch_1_Event_1_Time2Path[] = {2, 3, 0, 0, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time2,
  // Path
  Switch_1_Event_1_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 1, Event 1, Date Dep *********************************************/
const uint8 Switch_1_Event_1_DatePath[] = {2, 3, 0, 0, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Date,
  // Path
  Switch_1_Event_1_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);


/*******************************************************************************
 * Level 8
 ******************************************************************************/


/**** Switch 1, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_1_StatePath[] = {2, 3, 0, 0, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_1_State,
  // Path
  Switch_1_Event_1_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 1, Event 1, Time 1, Set Time Dep *********************************/
const uint8 Switch_1_Event_1_Time_1_Set_Time_Path[] = {2, 3, 0, 0, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_1_Set_Time,
  // Path
  Switch_1_Event_1_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 1, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_2_StatePath[] = {2, 3, 0, 0, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_2_State,
  // Path
  Switch_1_Event_1_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 1, Event 1, Time 2, Set Time Dep *********************************/
const uint8 Switch_1_Event_1_Time_2_Set_Time_Path[] = {2, 3, 0, 0, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_2_Set_Time,
  // Path
  Switch_1_Event_1_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);


/*******************************************************************************
 * Level 9
 ******************************************************************************/


/**** Switch 1, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_1_Set_StatePath[] = {2, 3, 0, 0, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_1_Set_State,
  // Path
  Switch_1_Event_1_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 1, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_2_Set_StatePath[] = {2, 3, 0, 0, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_2_Set_State,
  // Path
  Switch_1_Event_1_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);