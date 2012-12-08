#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"

uint8 DatePath[] = {1};
MENU_STATE_CREATE(
  Date,
  DatePath,
  1,
  0x00,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  NULL,
  "Date"
);