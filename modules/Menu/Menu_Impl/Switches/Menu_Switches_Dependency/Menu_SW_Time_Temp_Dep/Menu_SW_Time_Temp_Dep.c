#include <stdio.h>
#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"

#include "Menu.h"
#include "Menu_Func.h"
#include "Menu_Switches.h"
#include "Menu_Switches_Dependency.h"
#include "Menu_Utilities.h"

#include "Menu_SW_Time_Dep.h"
#include "Menu_SW_Temp_Dep.h"

/**** Global Variables ****/
//uint8 SetTimeFlag = 0;
//char Time_1_Name[SWITCHES_SET_STRING_LENGTH] = {0};
//char Time_2_Name[SWITCHES_SET_STRING_LENGTH] = {0};
//char Time_Response_Name[SWITCHES_SET_STRING_LENGTH] = {0};
//char Time_State_Name[SWITCHES_SET_STRING_LENGTH] = {0};
//char Set_Time_Name[SWITCHES_SET_STRING_LENGTH] = {0};
//char Set_Date_Name[SWITCHES_SET_STRING_LENGTH] = {0};
//char Set_Repeat_Name[SWITCHES_SET_STRING_LENGTH] = {0};

/**** Functions ****/

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Temp_Dep_Set_Time_Name(void)
{
  FuncIN(MENU_TIME_TEMP_DEP_SET_TIME_NAME);

  switch(SW_M_Event_g.Time_Start.State)
  {
    case SW_TIME_ALARM_ON:
      strcpy(Time_1_Name, "Start Time : ON");
      break;
    case SW_TIME_ALARM_OFF:
      strcpy(Time_1_Name, "Start Time : OFF");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }

  switch(SW_M_Event_g.Time_Stop.State)
  {
    case SW_TIME_ALARM_ON:
      strcpy(Time_2_Name, "Stop Time : ON");
      break;
    case SW_TIME_ALARM_OFF:
      strcpy(Time_2_Name, "Stop Time : OFF");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }

  EXIT_SUCCESS_FUNC(MENU_TIME_TEMP_DEP_SET_TIME_NAME);
}
FUNC_REGISTER(MENU_TIME_TEMP_DEP_SET_TIME_NAME, Menu_Time_Temp_Dep_Set_Time_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_SW_Dep_Set_Time_Name(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SW_DEP_SET_TIME_NAME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      Menu_Time_Temp_Dep_Set_Time_Name();
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SW_DEP_SET_TIME_NAME);
}
FUNC_REGISTER(MENU_SW_DEP_SET_TIME_NAME, Menu_SW_Dep_Set_Time_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_SW_Dep_Set_Temp_Name(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SW_DEP_SET_TEMP_NAME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      Menu_Temp_Dep_Set_Temp_Name();
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SW_DEP_SET_TEMP_NAME);
}
FUNC_REGISTER(MENU_SW_DEP_SET_TEMP_NAME, Menu_SW_Dep_Set_Temp_Name);
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Temp_Dep_Set_Start_Time(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_TEMP_DEP_SET_START_TIME);

  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetTimeFlag = 1;
      Menu_Time_Dep_Set_Time_Response_Name();
      Menu_Time_Dep_Set_Time_State_Name();
      Menu_Time_Dep_Setting_Time_Name();
      break;
    case CANCEL_KEY_EVENT:
      SetTimeFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_TIME_TEMP_DEP_SET_START_TIME);
}
FUNC_REGISTER(MENU_TIME_TEMP_DEP_SET_START_TIME, Menu_Time_Temp_Dep_Set_Start_Time);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Temp_Dep_Set_Stop_Time(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_TEMP_DEP_SET_STOP_TIME);

  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetTimeFlag = 2;
      Menu_Time_Dep_Set_Time_Response_Name();
      Menu_Time_Dep_Set_Time_State_Name();
      Menu_Time_Dep_Setting_Time_Name();
      break;
    case CANCEL_KEY_EVENT:
      SetTimeFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_TIME_TEMP_DEP_SET_STOP_TIME);
}
FUNC_REGISTER(MENU_TIME_TEMP_DEP_SET_STOP_TIME, Menu_Time_Temp_Dep_Set_Stop_Time);
/*******************************************************************************
 * Menu States
 ******************************************************************************/

/*******************************************************************************
 * Level 7
 ******************************************************************************/
/**** Switch 1, Event 1, Set Time Dep *******************************************/
const uint8 Switch_1_Event_1_Time_Temp_Set_Time_Path[] = {2, 3, 0, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Set_Time,
  // Path
  Switch_1_Event_1_Time_Temp_Set_Time_Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_SW_Dep_Set_Time_Name,
  // String
  "Set Time"
);

/**** Switch 1, Event 1, Set Temp Dep *******************************************/
const uint8 Switch_1_Event_1_Time_Temp_Set_Temp_Path[] = {2, 3, 0, 0, 1, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Set_Temp,
  // Path
  Switch_1_Event_1_Time_Temp_Set_Temp_Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_SW_Dep_Set_Temp_Name,
  // String
  "Set Temp"
);

/*******************************************************************************
 * Level 8
 ******************************************************************************/

/**** Switch 1, Event 1, Time1 Dep *******************************************/
const uint8 Switch_1_Event_1_Time_Temp_1Path[] = {2, 3, 0, 0, 1, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_1,
  // Path
  Switch_1_Event_1_Time_Temp_1Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Temp_Dep_Set_Start_Time,
  // String
  Time_1_Name
);

/**** Switch 1, Event 1, Time 2 Dep *******************************************/
const uint8 Switch_1_Event_1_Time_Temp_2Path[] = {2, 3, 0, 0, 1, 2, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_2,
  // Path
  Switch_1_Event_1_Time_Temp_2Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Temp_Dep_Set_Stop_Time,
  // String
  Time_2_Name
);

/**** Switch 1, Event 1, Date Dep *********************************************/
const uint8 Switch_1_Event_1_Time_Temp_DatePath[] = {2, 3, 0, 0, 1, 2, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp__Date,
  // Path
  Switch_1_Event_1_Time_Temp_DatePath,
  // Max Level
  8,
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

/**** Switch 1, Event 1, Temp 1 Dep *******************************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp1Path[] = {2, 3, 0, 0, 1, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp1,
  // Path
  Switch_1_Event_1_Time_Temp_Temp1Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Temp_1,
  // String
  Temp_1_Name
);

/**** Switch 1, Event 1, Temp 2 Dep *******************************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp2Path[] = {2, 3, 0, 0, 1, 2, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp2,
  // Path
  Switch_1_Event_1_Time_Temp_Temp2Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Temp_2,
  // String
  Temp_2_Name
);

/*******************************************************************************
 * Level 9
 ******************************************************************************/

/**** Switch 1, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_Temp_1_StatePath[] = {2, 3, 0, 0, 1, 2, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_1_State,
  // Path
  Switch_1_Event_1_Time_Temp_1_StatePath,
  // Max Level
  9,
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
const uint8 Switch_1_Event_1_Time_Temp_1_Set_Time_Path[] = {2, 3, 0, 0, 1, 2, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_1_Set_Time,
  // Path
  Switch_1_Event_1_Time_Temp_1_Set_Time_Path,
  // Max Level
  9,
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
const uint8 Switch_1_Event_1_Time_Temp_2_StatePath[] = {2, 3, 0, 0, 1, 2, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_2_State,
  // Path
  Switch_1_Event_1_Time_Temp_2_StatePath,
  // Max Level
  9,
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
const uint8 Switch_1_Event_1_Time_Temp_2_Set_Time_Path[] = {2, 3, 0, 0, 1, 2, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_2_Set_Time,
  // Path
  Switch_1_Event_1_Time_Temp_2_Set_Time_Path,
  // Max Level
  9,
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

/**** Switch 1, Event 1, Date Dep *********************************************/
const uint8 Switch_1_Event_1_Time_Temp_Set_Date_Path[] = {2, 3, 0, 0, 1, 2, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Set_Date,
  // Path
  Switch_1_Event_1_Time_Temp_Set_Date_Path,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 1, Event 1, Date Dep *********************************************/
const uint8 Switch_1_Event_1_Time_Temp_Set_Repeat_Path[] = {2, 3, 0, 0, 1, 2, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Set_Repeat,
  // Path
  Switch_1_Event_1_Time_Temp_Set_Repeat_Path,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 1, Event 1, Temp 1, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_1_StatePath[] = {2, 3, 0, 0, 1, 2, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_1_State,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_1_StatePath,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_State,
  // String
  Temp_State_Name
);

/**** Switch 1, Event 1, Temp 1, Responce Dep *********************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_1_Responce_Path[] = {2, 3, 0, 0, 1, 2, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_1_Responce,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_1_Responce_Path,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_Response,
  // String
  Temp_Response_Name
);

/**** Switch 1, Event 1, Temp 1, Set Temp Dep *********************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_1_Set_Temp_Path[] = {2, 3, 0, 0, 1, 2, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_1_Set_Temp,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_1_Set_Temp_Path,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Temp,
  // String
  Set_Temp_Name
);

/**** Switch 1, Event 1, Temp 1, Set Sensor Dep *********************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_1_Set_Sensor_Path[] = {2, 3, 0, 0, 1, 2, 1, 0, 3};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_1_Set_Sensor,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_1_Set_Sensor_Path,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Sensor,
  // String
  Set_Sensor_Name
);

/**** Switch 1, Event 1, Temp 1, Set Event Dep *********************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_1_Set_Event_Path[] = {2, 3, 0, 0, 1, 2, 1, 0, 4};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_1_Set_Event,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_1_Set_Event_Path,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Event,
  // String
  "Event 1"
);

/**** Switch 1, Event 1, Temp 2, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_2_StatePath[] = {2, 3, 0, 0, 1, 2, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_2_State,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_2_StatePath,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_State,
  // String
  Temp_State_Name
);

/**** Switch 1, Event 1, Temp 2, Responce Dep *********************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_2_Responce_Path[] = {2, 3, 0, 0, 1, 2, 1, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_2_Responce,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_2_Responce_Path,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_Response,
  // String
  Temp_Response_Name
);

/**** Switch 1, Event 1, Temp 2, Set Temp Dep *********************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_2_Set_Temp_Path[] = {2, 3, 0, 0, 1, 2, 1, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_2_Set_Temp,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_2_Set_Temp_Path,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Temp,
  // String
  Set_Temp_Name
);

/**** Switch 1, Event 1, Temp 2, Set Sensor Dep *********************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_2_Set_Sensor_Path[] = {2, 3, 0, 0, 1, 2, 1, 1, 3};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_2_Set_Sensor,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_2_Set_Sensor_Path,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Sensor,
  // String
  Set_Sensor_Name
);

/**** Switch 1, Event 1, Temp 2, Set Event Dep *********************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_2_Set_Event_Path[] = {2, 3, 0, 0, 1, 2, 1, 1, 4};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_2_Set_Event,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_2_Set_Event_Path,
  // Max Level
  9,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Event,
  // String
  "Event 2"
);
/*******************************************************************************
 * Level 10
 ******************************************************************************/

/**** Switch 1, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_Temp_1_Set_StatePath[] = {2, 3, 0, 0, 1, 2, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_1_Set_State,
  // Path
  Switch_1_Event_1_Time_Temp_1_Set_StatePath,
  // Max Level
  10,
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
const uint8 Switch_1_Event_1_Time_Temp_2_Set_StatePath[] = {2, 3, 0, 0, 1, 2, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_2_Set_State,
  // Path
  Switch_1_Event_1_Time_Temp_2_Set_StatePath,
  // Max Level
  10,
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

/**** Switch 1, Event 1, Time 1, Time Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Time_Temp_1_Set_Time_Path[] = {2, 3, 0, 0, 1, 2, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_Temp_1_Set_Time,
  // Path
  Setting_Switch_1_Event_1_Time_Temp_1_Set_Time_Path,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT | \
  LEFT_KEY_EVENT | \
  RIGHT_KEY_EVENT | \
  EXIT_KEY_EVENT | \
  NUM1_KEY_EVENT | \
  NUM2_KEY_EVENT | \
  NUM3_KEY_EVENT | \
  NUM4_KEY_EVENT | \
  NUM5_KEY_EVENT | \
  NUM6_KEY_EVENT | \
  NUM7_KEY_EVENT | \
  NUM8_KEY_EVENT | \
  NUM9_KEY_EVENT | \
  NUM0_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 1, Event 1, Time 2, Time Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Time_Temp_2_Set_Time_Path[] = {2, 3, 0, 0, 1, 2, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_Temp_2_Set_Time,
  // Path
  Setting_Switch_1_Event_1_Time_Temp_2_Set_Time_Path,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT | \
  LEFT_KEY_EVENT | \
  RIGHT_KEY_EVENT | \
  EXIT_KEY_EVENT | \
  NUM1_KEY_EVENT | \
  NUM2_KEY_EVENT | \
  NUM3_KEY_EVENT | \
  NUM4_KEY_EVENT | \
  NUM5_KEY_EVENT | \
  NUM6_KEY_EVENT | \
  NUM7_KEY_EVENT | \
  NUM8_KEY_EVENT | \
  NUM9_KEY_EVENT | \
  NUM0_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 1, Event 1, Date Dep *********************************************/
const uint8 Setting_Switch_1_Event_1_Time_Temp_Set_Date_Path[] = {2, 3, 0, 0, 1, 2, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_Temp_Set_Date,
  // Path
  Setting_Switch_1_Event_1_Time_Temp_Set_Date_Path,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT | \
  LEFT_KEY_EVENT | \
  RIGHT_KEY_EVENT | \
  EXIT_KEY_EVENT | \
  NUM1_KEY_EVENT | \
  NUM2_KEY_EVENT | \
  NUM3_KEY_EVENT | \
  NUM4_KEY_EVENT | \
  NUM5_KEY_EVENT | \
  NUM6_KEY_EVENT | \
  NUM7_KEY_EVENT | \
  NUM8_KEY_EVENT | \
  NUM9_KEY_EVENT | \
  NUM0_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

/**** Switch 1, Event 1, Repeat Dep *********************************************/
const uint8 Setting_Switch_1_Event_1_Time_Temp_Set_Repeat_Path[] = {2, 3, 0, 0, 1, 2, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_Temp_Set_Repeat,
  // Path
  Setting_Switch_1_Event_1_Time_Temp_Set_Repeat_Path,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT | \
  LEFT_KEY_EVENT | \
  RIGHT_KEY_EVENT | \
  EXIT_KEY_EVENT | \
  NUM1_KEY_EVENT | \
  NUM2_KEY_EVENT | \
  NUM3_KEY_EVENT | \
  NUM4_KEY_EVENT | \
  NUM5_KEY_EVENT | \
  NUM6_KEY_EVENT | \
  NUM7_KEY_EVENT | \
  NUM8_KEY_EVENT | \
  NUM9_KEY_EVENT | \
  NUM0_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 1, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_1_Set_StatePath[] = {2, 3, 0, 0, 1, 2, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_1_Set_State,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_1_Set_StatePath,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_State,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 2, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_2_Set_StatePath[] = {2, 3, 0, 0, 1, 2, 1, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_2_Set_State,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_2_Set_StatePath,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_State,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 1, Response Dep ************************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_1_Set_ResponsePath[] = {2, 3, 0, 0, 1, 2, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_1_Set_Response,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_1_Set_ResponsePath,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_Response,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 2, Response Dep ************************************/
const uint8 Switch_1_Event_1_Time_Temp_Temp_2_Set_ResponsePath[] = {2, 3, 0, 0, 1, 2, 1, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_Temp_Temp_2_Set_Response,
  // Path
  Switch_1_Event_1_Time_Temp_Temp_2_Set_ResponsePath,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_Response,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 1, Set Temp Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Time_Temp_Temp_1_Set_Temp_Path[] = {2, 3, 0, 0, 1, 2, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_Temp_Temp_1_Set_Temp,
  // Path
  Setting_Switch_1_Event_1_Time_Temp_Temp_1_Set_Temp_Path,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT | \
  LEFT_KEY_EVENT | \
  RIGHT_KEY_EVENT | \
  EXIT_KEY_EVENT | \
  NUM1_KEY_EVENT | \
  NUM2_KEY_EVENT | \
  NUM3_KEY_EVENT | \
  NUM4_KEY_EVENT | \
  NUM5_KEY_EVENT | \
  NUM6_KEY_EVENT | \
  NUM7_KEY_EVENT | \
  NUM8_KEY_EVENT | \
  NUM9_KEY_EVENT | \
  NUM0_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Temp,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 2, Set Temp Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Time_Temp_Temp_2_Set_Temp_Path[] = {2, 3, 0, 0, 1, 2, 1, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_Temp_Temp_2_Set_Temp,
  // Path
  Setting_Switch_1_Event_1_Time_Temp_Temp_2_Set_Temp_Path,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT | \
  LEFT_KEY_EVENT | \
  RIGHT_KEY_EVENT | \
  EXIT_KEY_EVENT | \
  NUM1_KEY_EVENT | \
  NUM2_KEY_EVENT | \
  NUM3_KEY_EVENT | \
  NUM4_KEY_EVENT | \
  NUM5_KEY_EVENT | \
  NUM6_KEY_EVENT | \
  NUM7_KEY_EVENT | \
  NUM8_KEY_EVENT | \
  NUM9_KEY_EVENT | \
  NUM0_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Temp,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 1, Set Sensor Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Time_Temp_Temp_1_Set_Sensor_Path[] = {2, 3, 0, 0, 1, 2, 1, 0, 3, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_Temp_Temp_1_Set_Sensor,
  // Path
  Setting_Switch_1_Event_1_Time_Temp_Temp_1_Set_Sensor_Path,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT | \
  LEFT_KEY_EVENT | \
  RIGHT_KEY_EVENT | \
  EXIT_KEY_EVENT | \
  NUM1_KEY_EVENT | \
  NUM2_KEY_EVENT | \
  NUM3_KEY_EVENT | \
  NUM4_KEY_EVENT | \
  NUM5_KEY_EVENT | \
  NUM6_KEY_EVENT | \
  NUM7_KEY_EVENT | \
  NUM8_KEY_EVENT | \
  NUM9_KEY_EVENT | \
  NUM0_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Sensor,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 2, Set Sensor Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Time_Temp_Temp_2_Set_Sensor_Path[] = {2, 3, 0, 0, 1, 2, 1, 1, 3, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_Temp_Temp_2_Set_Sensor,
  // Path
  Setting_Switch_1_Event_1_Time_Temp_Temp_2_Set_Sensor_Path,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT | \
  LEFT_KEY_EVENT | \
  RIGHT_KEY_EVENT | \
  EXIT_KEY_EVENT | \
  NUM1_KEY_EVENT | \
  NUM2_KEY_EVENT | \
  NUM3_KEY_EVENT | \
  NUM4_KEY_EVENT | \
  NUM5_KEY_EVENT | \
  NUM6_KEY_EVENT | \
  NUM7_KEY_EVENT | \
  NUM8_KEY_EVENT | \
  NUM9_KEY_EVENT | \
  NUM0_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Sensor,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 1, Set Event Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Time_Temp_Temp_1_Set_Event_Path[] = {2, 3, 0, 0, 1, 2, 1, 0, 4, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_Temp_Temp_1_Set_Event,
  // Path
  Setting_Switch_1_Event_1_Time_Temp_Temp_1_Set_Event_Path,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT | \
  EXIT_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Event,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 2, Set Event Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Time_Temp_Temp_2_Set_Event_Path[] = {2, 3, 0, 0, 1, 2, 1, 1, 4, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_Temp_Temp_2_Set_Event,
  // Path
  Setting_Switch_1_Event_1_Time_Temp_Temp_2_Set_Event_Path,
  // Max Level
  10,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT | \
  EXIT_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Event,
  // String
  ""
);

