#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"


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