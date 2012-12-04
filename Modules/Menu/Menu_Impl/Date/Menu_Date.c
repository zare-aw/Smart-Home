#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"

MENU_STATE_CREATE(
  1, 1, 0, 0x00,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  NULL,
  "Date"
);