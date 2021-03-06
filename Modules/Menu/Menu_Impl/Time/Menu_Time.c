#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "SurfaceFlinger.h"
#include "Console.h"
#include "RTC.h"
#include "Menu_Utilities.h"

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Set_Time(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SET_TIME);
  
  Status_t Status = GENERAL_ERROR;
  RtcTime_t Time_s;
  static uint32 EnterFlag = 0;
  
  if(EnterFlag == 0)
  {
    RTC_Get_Time(&Time_s);
    
    Hour = Time_s.Hour;
    Minute = Time_s.Minute;
    Second = Time_s.Second;
  }
  
  clrd();
  printd(1, "Set Time");
  printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
  Menu_Time_Update_Disp_Ptr_Pos();
  
  printc("(%s): Enter! Key = 0x%08X\n", __func__, Key);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      // First enter in this state
      if(EnterFlag == 0)
      {
        EnterFlag = 1;
        break;
      }
      
      Time_s.Hour = Hour;
      Time_s.Minute = Minute;
      Time_s.Second = Second;
      
      Status = RTC_Set_Time(&Time_s);
      VERIFY(Status, Status);
      
      if(Status == SUCCESS)
        printd(2, "%02u:%02u:%02u Time Set!", Hour, Minute, Second);
      else
        printd(2, "%02u:%02u:%02u ERROR!!!", Hour, Minute, Second);
      
      break;
    case CANCEL_KEY_EVENT:
      clrd();
      
      Hour = 0;
      Minute = 0;
      Second = 0;
      
      PointerPosition = 1;
      
      EnterFlag = 0;
      
      EXIT_SUCCESS_FUNC(MENU_SET_TIME);
    case UP_KEY_EVENT:
      Menu_Time_Increment_Ptr_Pos_Number();
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case DOWN_KEY_EVENT:
      Menu_Time_Decrement_Ptr_Pos_Number();
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case LEFT_KEY_EVENT:
      if(PointerPosition > 1)
      {
        PointerPosition--;
        Menu_Time_Update_Disp_Ptr_Pos();
      }
      break;
    case RIGHT_KEY_EVENT:
      if(PointerPosition < 6)
      {
        PointerPosition++;
        Menu_Time_Update_Disp_Ptr_Pos();
      }
      break;
    case EXIT_KEY_EVENT:
      clrd();
      
      Hour = 0;
      Minute = 0;
      Second = 0;
      
      PointerPosition = 1;
      
      EnterFlag = 0;
      
      EXIT_SUCCESS_FUNC(MENU_SET_TIME);
    case MENU_KEY_EVENT:
      clrd();
      
      Hour = 0;
      Minute = 0;
      Second = 0;
      
      PointerPosition = 1;
      
      EnterFlag = 0;
      
      EXIT_SUCCESS_FUNC(MENU_SET_TIME);
    case NUM1_KEY_EVENT:
      Menu_Time_Set_Ptr_Pos_Number(1);
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case NUM2_KEY_EVENT:
      Menu_Time_Set_Ptr_Pos_Number(2);
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case NUM3_KEY_EVENT:
      Menu_Time_Set_Ptr_Pos_Number(3);
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case NUM4_KEY_EVENT:
      Menu_Time_Set_Ptr_Pos_Number(4);
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case NUM5_KEY_EVENT:
      Menu_Time_Set_Ptr_Pos_Number(5);
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case NUM6_KEY_EVENT:
      Menu_Time_Set_Ptr_Pos_Number(6);
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case NUM7_KEY_EVENT:
      Menu_Time_Set_Ptr_Pos_Number(7);
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case NUM8_KEY_EVENT:
      Menu_Time_Set_Ptr_Pos_Number(8);
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case NUM9_KEY_EVENT:
      Menu_Time_Set_Ptr_Pos_Number(9);
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    case NUM0_KEY_EVENT:
      Menu_Time_Set_Ptr_Pos_Number(0);
      printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  syncd();
  
  EXIT_SUCCESS_FUNC(MENU_SET_TIME);
}
FUNC_REGISTER(MENU_SET_TIME, Menu_Set_Time);


uint8 TimePath[] = {0};
MENU_STATE_CREATE(
  Time,
  TimePath,
  1,
  0x00,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  NULL,
  "Time"
);

uint8 TimeAlarmPath[] = {0, 0};
MENU_STATE_CREATE(
  TimeAlarm,
  TimeAlarmPath,
  2,
  0x00,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  NULL,
  "Time Alarm"
);

uint8 SetTimePath[] = {0, 1};
MENU_STATE_CREATE(
  SetTime,
  SetTimePath,
  2,
  0x00,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  Menu_Set_Time,
  "Set Time"
);

uint8 SettingTimePath[] = {0, 1, 0};
MENU_STATE_CREATE(
  // Name
  SettingTime,
  // Path
  SettingTimePath,
  // Max Level
  3,
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
  Menu_Set_Time,
  // String
  ""
);