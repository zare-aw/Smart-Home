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

char SW_Display_Name[NO_OF_SWITCHES][SWITCHES_SET_STRING_LENGTH] = {0};

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Switches_Set_Display_String(const uint32 SwitchesFlags)
{
  FuncIN(MENU_SWITCHES_SET_DISPLAY_STRING);

  if(SwitchesFlags & SW_1_SET_STR)
  {
    /**** Set Switch 1 String ****/
    strcpy(SW_Display_Name[0], "Sw 1: ");
    strcat(SW_Display_Name[0], SW_Name[0]);
  }
  
  if(SwitchesFlags & SW_2_SET_STR)
  {
    /**** Set Switch 2 String ****/
    strcpy(SW_Display_Name[1], "Sw 2: ");
    strcat(SW_Display_Name[1], SW_Name[1]);
  }
  
  if(SwitchesFlags & SW_3_SET_STR)
  {
    /**** Set Switch 3 String ****/
    strcpy(SW_Display_Name[2], "Sw 3: ");
    strcat(SW_Display_Name[2], SW_Name[2]);
  }
  
  if(SwitchesFlags & SW_4_SET_STR)
  {
    /**** Set Switch 4 String ****/
    strcpy(SW_Display_Name[3], "Sw 4: ");
    strcat(SW_Display_Name[3], SW_Name[3]);
  }
  
  if(SwitchesFlags & SW_5_SET_STR)
  {
    /**** Set Switch 5 String ****/
    strcpy(SW_Display_Name[4], "Sw 5: ");
    strcat(SW_Display_Name[4], SW_Name[4]);
  }
  
  if(SwitchesFlags & SW_6_SET_STR)
  {
    /**** Set Switch 6 String ****/
    strcpy(SW_Display_Name[5], "Sw 6: ");
    strcat(SW_Display_Name[5], SW_Name[5]);
  }
  
  EXIT_SUCCESS_FUNC(MENU_SWITCHES_SET_DISPLAY_STRING);
}
FUNC_REGISTER(MENU_SWITCHES_SET_DISPLAY_STRING, Menu_Switches_Set_Display_String);

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
