#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "SurfaceFlinger.h"
#include "Console.h"

Status_t Menu_Set_Time(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Temp_p)
{
  clrd();
  
  printd(1, "Test");
  
  syncd();
  
  return SUCCESS;
}

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
  SettingTime,
  SettingTimePath,
  3,
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  Menu_Set_Time,
  ""
);