#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "SurfaceFlinger.h"
#include "RTC.h"
#include "Console.h"
#include "Menu_Utilities.h"

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Set_Date(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SET_DATE);
  
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
      
      Date_s.Year = Year;
      Date_s.Month = Month;
      Date_s.Day = Day;
      
      Status = RTC_Set_Date(&Date_s);
      VERIFY(Status, Status);
      
      if(Status == SUCCESS)
        printd(2, "%02u.%02u.%04u Date Set!", Day, Month, Year);
      else
        printd(2, "%02u.%02u.%04u ERROR!!!", Day, Month, Year);
      
      break;
    case CANCEL_KEY_EVENT:
      clrd();
      
      PointerPosition = 1;
      EnterFlag = 0;
      
      EXIT_SUCCESS_FUNC(MENU_SET_DATE);
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
      
      EXIT_SUCCESS_FUNC(MENU_SET_DATE);
    case MENU_KEY_EVENT:
      clrd();
      
      PointerPosition = 1;
      EnterFlag = 0;
      
      EXIT_SUCCESS_FUNC(MENU_SET_DATE);
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
  
  EXIT_SUCCESS_FUNC(MENU_SET_DATE);
}
FUNC_REGISTER(MENU_SET_DATE, Menu_Set_Date);

uint8 DatePath[] = {1};
MENU_STATE_CREATE(
  // Name
  Date,
  // Path
  DatePath,
  // Max Level
  1,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Set_Date,
  // String
  "Date"
);

uint8 SettingDatePath[] = {1, 0};
MENU_STATE_CREATE(
  // Name
  SettingDate,
  // Path
  SettingDatePath,
  // Max Level
  2,
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
  Menu_Set_Date,
  // String
  ""
);