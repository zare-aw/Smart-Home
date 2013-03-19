#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "SurfaceFlinger.h"
#include "RTC.h"
#include "Console.h"
#include "Alarm.h"
#include "Menu_Utilities.h"
#include <string.h>

#define MAX_STRING_LENGTH 20

TimeAlarm_t TimeAlarm = {0};

char AlarmDay[MAX_STRING_LENGTH] = "  Alarm Day";
char RepeatDays[MAX_STRING_LENGTH] = "  Repeat Days";
/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Set_Alarm_Time(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SET_ALARM_TIME);
  
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
  printd(1, "Set Alarm Time");
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
      
      TimeAlarm.DateTime.Hour = Hour;
      TimeAlarm.DateTime.Minute = Minute;
      TimeAlarm.DateTime.Second = Second;
      TimeAlarm.State = ALARM_ON;
      TimeAlarm.Callback = (void *)Time_Alarm_Dummy_Handler;
      
      if(NO_TIME_ALARM_ID == TimeAlarm.AlarmID)
      {
        if(0 != TimeAlarm.Repeat || 0 != TimeAlarm.DateTime.Year)
        {
          Status = Register_Time_Alarm(&TimeAlarm);
          VERIFY(Status, Status);
        } 
        else
          printd(4, "Date not set!!!");
      }
      else
      {
        Status = Set_Time_Alarm(&TimeAlarm);
        VERIFY(Status, Status);
      }
      
      if(Status == SUCCESS)
      {
        printd(2, "%02u:%02u:%02u Alarm Set!", Hour, Minute, Second);
        if(0 != TimeAlarm.Repeat)
          printd(4, "Repetitive Alarm!");
        else
          printd(4, "Single Alarm!");
      }
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
      
      EXIT_SUCCESS_FUNC(MENU_SET_ALARM_TIME);
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
      
      EXIT_SUCCESS_FUNC(MENU_SET_ALARM_TIME);
    case MENU_KEY_EVENT:
      clrd();
      
      Hour = 0;
      Minute = 0;
      Second = 0;
      
      PointerPosition = 1;
      
      EnterFlag = 0;
      
      EXIT_SUCCESS_FUNC(MENU_SET_ALARM_TIME);
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
  
  EXIT_SUCCESS_FUNC(MENU_SET_ALARM_TIME);
}
FUNC_REGISTER(MENU_SET_ALARM_TIME, Menu_Set_Alarm_Time);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Set_Alarm_Date(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SET_ALARM_DATE);
  
  Status_t Status = GENERAL_ERROR;
  RtcDate_t Date_s;
  static uint32 EnterFlag = 0;
  
  if(EnterFlag == 0)
  {
    RTC_Get_Date(&Date_s);
    
    Year = Date_s.Year;
    Month = Date_s.Month;
    Day = Date_s.Day;
  }
  
  clrd();
  printd(1, "Set Date");
  printd(2, "%02u.%02u.%04u", Day, Month, Year);
  Menu_Date_Update_Disp_Ptr_Pos();
  
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
      Status = Is_Valid_Day(Year, Month, Day);
      
      if(TRUE == Status) {
        TimeAlarm.DateTime.Year = Year;
        TimeAlarm.DateTime.Month = Month;
        TimeAlarm.DateTime.Day = Day;
    
        printd(2, "%02u.%02u.%04u Date Set!", Day, Month, Year);
      }
      else
        printd(2, "%02u.%02u.%04u ERROR!!!", Day, Month, Year);
      
      break;
    case CANCEL_KEY_EVENT:
      clrd();
      
      PointerPosition = 1;
      EnterFlag = 0;
      
      if(0 == TimeAlarm.Repeat && 0 != TimeAlarm.DateTime.Year)
        strcpy(AlarmDay, "#  Alarm Day");

      EXIT_SUCCESS_FUNC(MENU_SET_ALARM_DATE);
    case UP_KEY_EVENT:
      Menu_Date_Increment_Ptr_Pos_Number();
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case DOWN_KEY_EVENT:
      Menu_Date_Decrement_Ptr_Pos_Number();
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case LEFT_KEY_EVENT:
      if(PointerPosition > 1)
      {
        PointerPosition--;
        Menu_Date_Update_Disp_Ptr_Pos();
      }
      break;
    case RIGHT_KEY_EVENT:
      if(PointerPosition < 6)
      {
        PointerPosition++;
        Menu_Date_Update_Disp_Ptr_Pos();
      }
      break;
    case EXIT_KEY_EVENT:
      clrd();
      
      PointerPosition = 1;
      EnterFlag = 0;
      
      if(0 == TimeAlarm.Repeat && 0 != TimeAlarm.DateTime.Year)
        strcpy(AlarmDay,"#  Alarm Day");
      
      EXIT_SUCCESS_FUNC(MENU_SET_ALARM_DATE);
    case MENU_KEY_EVENT:
      clrd();
      
      PointerPosition = 1;
      EnterFlag = 0;

      if(0 == TimeAlarm.Repeat && 0 != TimeAlarm.DateTime.Year)
        strcpy(AlarmDay, "#  Alarm Day");
      EXIT_SUCCESS_FUNC(MENU_SET_ALARM_DATE);
    case NUM1_KEY_EVENT:
      Menu_Date_Set_Ptr_Pos_Number(1);
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case NUM2_KEY_EVENT:
      Menu_Date_Set_Ptr_Pos_Number(2);
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case NUM3_KEY_EVENT:
      Menu_Date_Set_Ptr_Pos_Number(3);
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case NUM4_KEY_EVENT:
      Menu_Date_Set_Ptr_Pos_Number(4);
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case NUM5_KEY_EVENT:
      Menu_Date_Set_Ptr_Pos_Number(5);
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case NUM6_KEY_EVENT:
      Menu_Date_Set_Ptr_Pos_Number(6);
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case NUM7_KEY_EVENT:
      Menu_Date_Set_Ptr_Pos_Number(7);
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case NUM8_KEY_EVENT:
      Menu_Date_Set_Ptr_Pos_Number(8);
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case NUM9_KEY_EVENT:
      Menu_Date_Set_Ptr_Pos_Number(9);
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    case NUM0_KEY_EVENT:
      Menu_Date_Set_Ptr_Pos_Number(0);
      printd(2, "%02u.%02u.%04u", Day, Month, Year);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  syncd();
  
  EXIT_SUCCESS_FUNC(MENU_SET_ALARM_DATE);
}
FUNC_REGISTER(MENU_SET_ALARM_DATE, Menu_Set_Alarm_Date);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Set_Alarm_Repeat_Days(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SET_ALARM_REPEAT_DAYS);
  
  static uint32 EnterFlag = 0;
  static uint8 Offset = 0;

  if(EnterFlag == 0)
  {
    Offset = 0;
    PointerPosition = 1;
    Menu_Repeat_Update_Display(Offset, PointerPosition, TimeAlarm.Repeat);
  }
  
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
      TimeAlarm.Repeat = TimeAlarm.Repeat ^ (1 << (PointerPosition - 1));
      Menu_Repeat_Update_Display(Offset, PointerPosition, TimeAlarm.Repeat);
      
      break;
    case CANCEL_KEY_EVENT:
      clrd();
      
      PointerPosition = 1;
      EnterFlag = 0;
      if(0 != TimeAlarm.Repeat)
      {
        strcpy(AlarmDay, "  Alarm Day");
        strcpy(RepeatDays, "# Repeat Days");
      }
      else
        strcpy(RepeatDays, "  Repeat Days");
      EXIT_SUCCESS_FUNC(MENU_SET_ALARM_REPEAT_DAYS);
    case UP_KEY_EVENT:
      if(PointerPosition > 1)
      {
        PointerPosition--;
        if((PointerPosition - Offset) < 1)
        {
          Offset--;
        }
      }
      Menu_Repeat_Update_Display(Offset, PointerPosition, TimeAlarm.Repeat);
      break;
    case DOWN_KEY_EVENT:
      if(PointerPosition < NO_OF_DAYS)
      {
        PointerPosition++;
        if((PointerPosition - Offset) > 4)
        {
          Offset++;
        }
      }
      Menu_Repeat_Update_Display(Offset, PointerPosition, TimeAlarm.Repeat);
      break;
    case LEFT_KEY_EVENT:
      TimeAlarm.Repeat = TimeAlarm.Repeat ^ (1 << (PointerPosition - 1));
      Menu_Repeat_Update_Display(Offset, PointerPosition, TimeAlarm.Repeat);
      break;
    case RIGHT_KEY_EVENT:
      TimeAlarm.Repeat = TimeAlarm.Repeat ^ (1 << (PointerPosition - 1));
      Menu_Repeat_Update_Display(Offset, PointerPosition, TimeAlarm.Repeat);
      break;
    case EXIT_KEY_EVENT:
      clrd();
      
      PointerPosition = 1;
      EnterFlag = 0;
      
      if(0 != TimeAlarm.Repeat)
      {
        strcpy(AlarmDay, "  Alarm Day");
        strcpy(RepeatDays, "# Repeat Days");
      }
      else
        strcpy(RepeatDays, "  Repeat Days");
      EXIT_SUCCESS_FUNC(MENU_SET_ALARM_REPEAT_DAYS);
    case MENU_KEY_EVENT:
      clrd();
      
      PointerPosition = 1;
      EnterFlag = 0;
      
      if(0 != TimeAlarm.Repeat)
      {
        strcpy(AlarmDay, "  Alarm Day");
        strcpy(RepeatDays, "# Repeat Days");
      }
      else
        strcpy(RepeatDays, "  Repeat Days");
      EXIT_SUCCESS_FUNC(MENU_SET_ALARM_REPEAT_DAYS);
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  syncd();
  
  EXIT_SUCCESS_FUNC(MENU_SET_ALARM_REPEAT_DAYS);
}
FUNC_REGISTER(MENU_SET_ALARM_REPEAT_DAYS, Menu_Set_Alarm_Repeat_Days);

uint8 AlarmDatePath[] = {0, 0, 0};
MENU_STATE_CREATE(
  AlarmDate,
  AlarmDatePath,
  3,
  0x00,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  NULL,
  "Alarm Date"
);

uint8 AlarmDayDatePath[] = {0, 0, 0, 0};
MENU_STATE_CREATE(
  AlarmDayDate,
  AlarmDayDatePath,
  4,
  0x00,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  Menu_Set_Alarm_Date,
  AlarmDay
);

uint8 SettingAlarmDayDatePath[] = {0, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  SettingAlarmDayDate,
  // Path
  SettingAlarmDayDatePath,
  // Max Level
  5,
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
  Menu_Set_Alarm_Date,
  // String
  ""
);

uint8 AlarmRepeatDatePath[] = {0, 0, 0, 1};
MENU_STATE_CREATE(
  AlarmRepeatDate,
  AlarmRepeatDatePath,
  4,
  0x00,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  Menu_Set_Alarm_Repeat_Days,
  RepeatDays
);

uint8 SettingAlarmRepeatPath[] = {0, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  SettingRepeatDays,
  // Path
  SettingAlarmRepeatPath,
  // Max Level
  5,
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
  Menu_Set_Alarm_Repeat_Days,
  // String
  ""
);

uint8 AlarmTimePath[] = {0, 0, 1};
MENU_STATE_CREATE(
  AlarmTime,
  AlarmTimePath,
  3,
  0x00,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  Menu_Set_Alarm_Time,
  "Alarm Time"
);

uint8 SettingAlarmTimePath[] = {0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  SettingAlarmTime,
  // Path
  SettingAlarmTimePath,
  // Max Level
  4,
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
  Menu_Set_Alarm_Time,
  // String
  ""
);