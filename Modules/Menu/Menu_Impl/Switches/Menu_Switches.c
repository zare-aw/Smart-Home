#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "Menu_Switches.h"
#include "Out.h"
#include "SurfaceFlinger.h"

/**** Gloval Variables ****/
char SW_Name[NO_OF_SWITCHES][SWITCHES_STRING_LENGTH] = {"SW_1", "SW_2",
                                                        "SW_3", "SW_4",
                                                        "SW_5", "SW_6"};


/*******************************************************************************
 * Menu States
 ******************************************************************************/

uint8 SwitchesPath[] = {2};
MENU_STATE_CREATE(
  // Name
  Switches,
  // Path
  SwitchesPath,
  // Max Level
  1,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  NULL,
  // String
  "Switches"
);
