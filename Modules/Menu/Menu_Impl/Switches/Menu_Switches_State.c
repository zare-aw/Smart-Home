#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "Menu_Switches.h"
#include "Out.h"
#include "SurfaceFlinger.h"

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Switches_State_Display(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(SWITCHES_STATE_DISPLAY);
  
  Out_t Out_s;
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      Out_Get_State(OUT_PINS, &Out_s);
      
      clrd();
      printd(1, "%s:%d%*c%s:%d", SW_Name[0], Out_s.S_1, (8 - strlen(SW_Name[0])), ' ', SW_Name[1], Out_s.S_2);
      printd(2, "%s:%d%*c%s:%d", SW_Name[2], Out_s.S_3, (8 - strlen(SW_Name[2])), ' ', SW_Name[3], Out_s.S_4);
      printd(3, "%s:%d%*c%s:%d", SW_Name[4], Out_s.S_5, (8 - strlen(SW_Name[4])), ' ', SW_Name[5], Out_s.S_6);
      syncd();
      break;
    case CANCEL_KEY_EVENT:
      clrd();
      break;
    case UP_KEY_EVENT:
      break;
    case DOWN_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(SWITCHES_STATE_DISPLAY);
}
FUNC_REGISTER(SWITCHES_STATE_DISPLAY, Switches_State_Display);


/*******************************************************************************
 * Menu States
 ******************************************************************************/

uint8 SwitchesStatePath[] = {2, 0};
MENU_STATE_CREATE(
  // Name
  SwitchesState,
  // Path
  SwitchesStatePath,
  // Max Level
  2,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Switches_State_Display,
  // String
  "Switches State"
);

uint8 SwitchesStateDisplayPath[] = {2, 0, 0};
MENU_STATE_CREATE(
  // Name
  SwitchesStateDisplay,
  // Path
  SwitchesStateDisplayPath,
  // Max Level
  3,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Switches_State_Display,
  // String
  ""
);