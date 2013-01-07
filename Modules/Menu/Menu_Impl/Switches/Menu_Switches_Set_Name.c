#include <stdio.h>
#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "Menu_Switches.h"
#include "Out.h"
#include "SurfaceFlinger.h"

/**** Defines ****/
#define DIRECTION_UP      1
#define DIRECTION_DOWN    2

/**** Gloval Variables ****/
uint8 SwitchSetNameFlag = 0;
uint8 SwitchNamePointerPosition = 1;
char SW_Name_Setting[SWITCHES_SET_STRING_LENGTH] = {0};

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switches_Set_Name(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCHES_SET_NAME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      Menu_Switches_Set_Display_String(SW_1_SET_STR |
                                       SW_2_SET_STR |
                                       SW_3_SET_STR |
                                       SW_4_SET_STR |
                                       SW_5_SET_STR |
                                       SW_6_SET_STR);
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCHES_SET_NAME);
}
FUNC_REGISTER(MENU_SWITCHES_SET_NAME, Menu_Switches_Set_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_SW_Name_Update_Disp_Ptr_Pos(void)
{
  FuncIN(MENU_SW_NAME_UPDATE_DISP_PTR_POS);
  
  switch(SwitchNamePointerPosition)
  {
    case 1:
      printd(3, "^      ");
      break;
    case 2:
      printd(3, " ^     ");
      break;
    case 3:
      printd(3, "  ^    ");
      break;
    case 4:
      printd(3, "   ^   ");
      break;
    case 5:
      printd(3, "    ^  ");
      break;
    case 6:
      printd(3, "     ^ ");
      break;
    case 7:
      printd(3, "      ^");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  EXIT_SUCCESS_FUNC(MENU_SW_NAME_UPDATE_DISP_PTR_POS);
}
FUNC_REGISTER(MENU_SW_NAME_UPDATE_DISP_PTR_POS, Menu_SW_Name_Update_Disp_Ptr_Pos);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_Name_Get_Next_Char(const char CurrentChar, char *NextChar, uint32 Direction)
{
  FuncIN(MENU_SWITCH_NAME_GET_NEXT_CHAR);
  
  switch(CurrentChar)
  {
    case ' ':
      if(Direction == DIRECTION_UP)
        *NextChar = 'A';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '&';
      break;
    case 'A':
      if(Direction == DIRECTION_UP)
        *NextChar = 'B';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = ' ';
      break;
    case 'B':
      if(Direction == DIRECTION_UP)
        *NextChar = 'C';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'A';
      break;
    case 'C':
      if(Direction == DIRECTION_UP)
        *NextChar = 'D';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'B';
      break;
    case 'D':
      if(Direction == DIRECTION_UP)
        *NextChar = 'E';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'C';
      break;
    case 'E':
      if(Direction == DIRECTION_UP)
        *NextChar = 'F';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'D';
      break;
    case 'F':
      if(Direction == DIRECTION_UP)
        *NextChar = 'G';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'E';
      break;
    case 'G':
      if(Direction == DIRECTION_UP)
        *NextChar = 'H';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'F';
      break;
    case 'H':
      if(Direction == DIRECTION_UP)
        *NextChar = 'I';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'G';
      break;
    case 'I':
      if(Direction == DIRECTION_UP)
        *NextChar = 'J';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'H';
      break;
    case 'J':
      if(Direction == DIRECTION_UP)
        *NextChar = 'K';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'I';
      break;
    case 'K':
      if(Direction == DIRECTION_UP)
        *NextChar = 'L';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'J';
      break;
    case 'L':
      if(Direction == DIRECTION_UP)
        *NextChar = 'M';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'K';
      break;
    case 'M':
      if(Direction == DIRECTION_UP)
        *NextChar = 'N';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'L';
      break;
    case 'N':
      if(Direction == DIRECTION_UP)
        *NextChar = 'O';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'M';
      break;
    case 'O':
      if(Direction == DIRECTION_UP)
        *NextChar = 'P';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'N';
      break;
    case 'P':
      if(Direction == DIRECTION_UP)
        *NextChar = 'Q';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'O';
      break;
    case 'Q':
      if(Direction == DIRECTION_UP)
        *NextChar = 'R';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'P';
      break;
    case 'R':
      if(Direction == DIRECTION_UP)
        *NextChar = 'S';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'Q';
      break;
    case 'S':
      if(Direction == DIRECTION_UP)
        *NextChar = 'T';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'R';
      break;
    case 'T':
      if(Direction == DIRECTION_UP)
        *NextChar = 'U';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'S';
      break;
    case 'U':
      if(Direction == DIRECTION_UP)
        *NextChar = 'V';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'T';
      break;
    case 'V':
      if(Direction == DIRECTION_UP)
        *NextChar = 'W';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'U';
      break;
    case 'W':
      if(Direction == DIRECTION_UP)
        *NextChar = 'X';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'V';
      break;
    case 'X':
      if(Direction == DIRECTION_UP)
        *NextChar = 'Y';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'W';
      break;
    case 'Y':
      if(Direction == DIRECTION_UP)
        *NextChar = 'Z';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'X';
      break;
    case 'Z':
      if(Direction == DIRECTION_UP)
        *NextChar = 'a';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'Y';
      break;
    case 'a':
      if(Direction == DIRECTION_UP)
        *NextChar = 'b';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'Z';
      break;
    case 'b':
      if(Direction == DIRECTION_UP)
        *NextChar = 'c';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'a';
      break;
    case 'c':
      if(Direction == DIRECTION_UP)
        *NextChar = 'd';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'b';
      break;
    case 'd':
      if(Direction == DIRECTION_UP)
        *NextChar = 'e';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'c';
      break;
    case 'e':
      if(Direction == DIRECTION_UP)
        *NextChar = 'f';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'd';
      break;
    case 'f':
      if(Direction == DIRECTION_UP)
        *NextChar = 'g';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'e';
      break;
    case 'g':
      if(Direction == DIRECTION_UP)
        *NextChar = 'h';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'f';
      break;
    case 'h':
      if(Direction == DIRECTION_UP)
        *NextChar = 'i';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'g';
      break;
    case 'i':
      if(Direction == DIRECTION_UP)
        *NextChar = 'j';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'h';
      break;
    case 'j':
      if(Direction == DIRECTION_UP)
        *NextChar = 'k';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'i';
      break;
    case 'k':
      if(Direction == DIRECTION_UP)
        *NextChar = 'l';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'j';
      break;
    case 'l':
      if(Direction == DIRECTION_UP)
        *NextChar = 'm';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'k';
      break;
    case 'm':
      if(Direction == DIRECTION_UP)
        *NextChar = 'n';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'l';
      break;
    case 'n':
      if(Direction == DIRECTION_UP)
        *NextChar = 'o';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'm';
      break;
    case 'o':
      if(Direction == DIRECTION_UP)
        *NextChar = 'p';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'n';
      break;
    case 'p':
      if(Direction == DIRECTION_UP)
        *NextChar = 'q';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'o';
      break;
    case 'q':
      if(Direction == DIRECTION_UP)
        *NextChar = 'r';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'p';
      break;
    case 'r':
      if(Direction == DIRECTION_UP)
        *NextChar = 's';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'q';
      break;
    case 's':
      if(Direction == DIRECTION_UP)
        *NextChar = 't';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'r';
      break;
    case 't':
      if(Direction == DIRECTION_UP)
        *NextChar = 'u';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 's';
      break;
    case 'u':
      if(Direction == DIRECTION_UP)
        *NextChar = 'v';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 't';
      break;
    case 'v':
      if(Direction == DIRECTION_UP)
        *NextChar = 'w';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'u';
      break;
    case 'w':
      if(Direction == DIRECTION_UP)
        *NextChar = 'x';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'v';
      break;
    case 'x':
      if(Direction == DIRECTION_UP)
        *NextChar = 'y';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'w';
      break;
    case 'y':
      if(Direction == DIRECTION_UP)
        *NextChar = 'z';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'x';
      break;
    case 'z':
      if(Direction == DIRECTION_UP)
        *NextChar = '0';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'y';
      break;
    case '0':
      if(Direction == DIRECTION_UP)
        *NextChar = '1';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = 'z';
      break;
    case '1':
      if(Direction == DIRECTION_UP)
        *NextChar = '2';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '0';
      break;
    case '2':
      if(Direction == DIRECTION_UP)
        *NextChar = '3';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '1';
      break;
    case '3':
      if(Direction == DIRECTION_UP)
        *NextChar = '4';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '2';
      break;
    case '4':
      if(Direction == DIRECTION_UP)
        *NextChar = '5';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '3';
      break;
    case '5':
      if(Direction == DIRECTION_UP)
        *NextChar = '6';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '4';
      break;
    case '6':
      if(Direction == DIRECTION_UP)
        *NextChar = '7';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '5';
      break;
    case '7':
      if(Direction == DIRECTION_UP)
        *NextChar = '8';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '6';
      break;
    case '8':
      if(Direction == DIRECTION_UP)
        *NextChar = '9';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '7';
      break;
    case '9':
      if(Direction == DIRECTION_UP)
        *NextChar = '\'';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '8';
      break;
    case '\'':
      if(Direction == DIRECTION_UP)
        *NextChar = '(';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '9';
      break;
    case '(':
      if(Direction == DIRECTION_UP)
        *NextChar = ')';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '\'';
      break;
    case ')':
      if(Direction == DIRECTION_UP)
        *NextChar = '{';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '(';
      break;
    case '{':
      if(Direction == DIRECTION_UP)
        *NextChar = '}';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = ')';
      break;
    case '}':
      if(Direction == DIRECTION_UP)
        *NextChar = '[';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '{';
      break;
    case '[':
      if(Direction == DIRECTION_UP)
        *NextChar = ']';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '}';
      break;
    case ']':
      if(Direction == DIRECTION_UP)
        *NextChar = '?';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '[';
      break;
    case '?':
      if(Direction == DIRECTION_UP)
        *NextChar = '.';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = ']';
      break;
    case '.':
      if(Direction == DIRECTION_UP)
        *NextChar = ',';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '?';
      break;
    case ',':
      if(Direction == DIRECTION_UP)
        *NextChar = ':';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '.';
      break;
    case ':':
      if(Direction == DIRECTION_UP)
        *NextChar = ';';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = ',';
      break;
    case ';':
      if(Direction == DIRECTION_UP)
        *NextChar = '-';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = ':';
      break;
    case '-':
      if(Direction == DIRECTION_UP)
        *NextChar = '+';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = ';';
      break;
    case '+':
      if(Direction == DIRECTION_UP)
        *NextChar = '=';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '-';
      break;
    case '=':
      if(Direction == DIRECTION_UP)
        *NextChar = '!';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '+';
      break;
    case '!':
      if(Direction == DIRECTION_UP)
        *NextChar = '@';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '=';
      break;
    case '@':
      if(Direction == DIRECTION_UP)
        *NextChar = '$';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '!';
      break;
    case '$':
      if(Direction == DIRECTION_UP)
        *NextChar = '*';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '@';
      break;
    case '*':
      if(Direction == DIRECTION_UP)
        *NextChar = '#';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '$';
      break;
    case '#':
      if(Direction == DIRECTION_UP)
        *NextChar = '&';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '*';
      break;
    case '&':
      if(Direction == DIRECTION_UP)
        *NextChar = ' ';
      else if(Direction == DIRECTION_DOWN)
        *NextChar = '#';
      break;
    default:
      *NextChar = ' ';
      break;
  } // switch(CurrentChar)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_NAME_GET_NEXT_CHAR);
}
FUNC_REGISTER(MENU_SWITCH_NAME_GET_NEXT_CHAR, Menu_Switch_Name_Get_Next_Char);

/*******************************************************************************
 *
 ******************************************************************************/
uint32 Sw_Set_Str_Get_Mask(uint32 SwitchNo)
{
  switch(SwitchNo)
  {
    case 1:
      return SW_1_SET_STR;
    case 2:
      return SW_2_SET_STR;
    case 3:
      return SW_3_SET_STR;
    case 4:
      return SW_4_SET_STR;
    case 5:
      return SW_5_SET_STR;
    case 6:
      return SW_6_SET_STR;
    default:
      return SW_1_SET_STR |
             SW_2_SET_STR |
             SW_3_SET_STR |
             SW_4_SET_STR |
             SW_5_SET_STR |
             SW_6_SET_STR;
  }
}

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_Name_Setting(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_NAME_SETTING);
  
  ASSERT(SwitchSetNameFlag > 0, -UNKNOWN_ERROR);
  
  clrd();
  printd(1, "Set SW %d Name", SwitchSetNameFlag);
  printd(2, "%s", SW_Name_Setting);
  Menu_SW_Name_Update_Disp_Ptr_Pos();
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      for(uint32 i = SWITCHES_STRING_LENGTH - 1; i != 0; i--)
      {
        if(SW_Name_Setting[i] == ' ')
          SW_Name_Setting[i] = '\0';
        else if(SW_Name_Setting[i] != '\0')
          break;
      }
      
      strcpy(SW_Name[SwitchSetNameFlag - 1], SW_Name_Setting);
      
      Menu_Switches_Set_Display_String(Sw_Set_Str_Get_Mask(SwitchSetNameFlag));
      
      printd(4, "Switch Name Set!");
      break;
    case CANCEL_KEY_EVENT:
      SwitchNamePointerPosition = 1;
      strcpy(SW_Name_Setting, "");
      break;
    case UP_KEY_EVENT:
      Menu_Switch_Name_Get_Next_Char(SW_Name_Setting[SwitchNamePointerPosition - 1],
                                     &SW_Name_Setting[SwitchNamePointerPosition - 1],
                                     DIRECTION_UP);
  
      printd(2, "%s", SW_Name_Setting);
      break;
    case DOWN_KEY_EVENT:
      Menu_Switch_Name_Get_Next_Char(SW_Name_Setting[SwitchNamePointerPosition - 1],
                                     &SW_Name_Setting[SwitchNamePointerPosition - 1],
                                     DIRECTION_DOWN);
  
      printd(2, "%s", SW_Name_Setting);
      break;
    case LEFT_KEY_EVENT:
      if(SwitchNamePointerPosition > 1)
      {
        SwitchNamePointerPosition--;
        Menu_SW_Name_Update_Disp_Ptr_Pos();
      }
      break;
    case RIGHT_KEY_EVENT:
      if(SwitchNamePointerPosition < 7)
      {
        SwitchNamePointerPosition++;
        Menu_SW_Name_Update_Disp_Ptr_Pos();
      }
      break;
    case FLAG_1_KEY_EVENT:
      snprintf(SW_Name_Setting, 7, "%s%*c", SW_Name[SwitchSetNameFlag - 1],
                        (7 - strlen(SW_Name[SwitchSetNameFlag - 1])), ' ');
      printd(2, "%s", SW_Name_Setting);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  syncd();
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_NAME_SETTING);
}
FUNC_REGISTER(MENU_SWITCH_NAME_SETTING, Menu_Switch_Name_Setting);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_1_Set_Name(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_1_SET_NAME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchSetNameFlag = 1;
      Menu_Switch_Name_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SwitchSetNameFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_1_SET_NAME);
}
FUNC_REGISTER(MENU_SWITCH_1_SET_NAME, Menu_Switch_1_Set_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_2_Set_Name(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_2_SET_NAME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchSetNameFlag = 2;
      Menu_Switch_Name_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SwitchSetNameFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_2_SET_NAME);
}
FUNC_REGISTER(MENU_SWITCH_2_SET_NAME, Menu_Switch_2_Set_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_3_Set_Name(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_3_SET_NAME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchSetNameFlag = 3;
      Menu_Switch_Name_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SwitchSetNameFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_3_SET_NAME);
}
FUNC_REGISTER(MENU_SWITCH_3_SET_NAME, Menu_Switch_3_Set_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_4_Set_Name(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_4_SET_NAME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchSetNameFlag = 4;
      Menu_Switch_Name_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SwitchSetNameFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_4_SET_NAME);
}
FUNC_REGISTER(MENU_SWITCH_4_SET_NAME, Menu_Switch_4_Set_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_5_Set_Name(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_5_SET_NAME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchSetNameFlag = 5;
      Menu_Switch_Name_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SwitchSetNameFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_5_SET_NAME);
}
FUNC_REGISTER(MENU_SWITCH_5_SET_NAME, Menu_Switch_5_Set_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Switch_6_Set_Name(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_SWITCH_6_SET_NAME);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SwitchSetNameFlag = 6;
      Menu_Switch_Name_Setting(Menu_State_p, FLAG_1_KEY_EVENT, NULL);
      break;
    case CANCEL_KEY_EVENT:
      SwitchSetNameFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_SWITCH_6_SET_NAME);
}
FUNC_REGISTER(MENU_SWITCH_6_SET_NAME, Menu_Switch_6_Set_Name);


/*******************************************************************************
 * Menu States
 ******************************************************************************/

uint8 SwitchesSetNamePath[] = {2, 2};
MENU_STATE_CREATE(
  // Name
  SwitchesSetName,
  // Path
  SwitchesSetNamePath,
  // Max Level
  2,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switches_Set_Name,
  // String
  "Switches Set Name"
);

uint8 SwitchesSetName_SW_1_Path[] = {2, 2, 0};
MENU_STATE_CREATE(
  // Name
  SwitchesSetName_SW_1,
  // Path
  SwitchesSetName_SW_1_Path,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_1_Set_Name,
  // String
  SW_Display_Name[0]
);

uint8 SwitchesSetName_SW_2_Path[] = {2, 2, 1};
MENU_STATE_CREATE(
  // Name
  SwitchesSetName_SW_2,
  // Path
  SwitchesSetName_SW_2_Path,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_2_Set_Name,
  // String
  SW_Display_Name[1]
);

uint8 SwitchesSetName_SW_3_Path[] = {2, 2, 2};
MENU_STATE_CREATE(
  // Name
  SwitchesSetName_SW_3,
  // Path
  SwitchesSetName_SW_3_Path,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_3_Set_Name,
  // String
  SW_Display_Name[2]
);

uint8 SwitchesSetName_SW_4_Path[] = {2, 2, 3};
MENU_STATE_CREATE(
  // Name
  SwitchesSetName_SW_4,
  // Path
  SwitchesSetName_SW_4_Path,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_4_Set_Name,
  // String
  SW_Display_Name[3]
);

uint8 SwitchesSetName_SW_5_Path[] = {2, 2, 4};
MENU_STATE_CREATE(
  // Name
  SwitchesSetName_SW_5,
  // Path
  SwitchesSetName_SW_5_Path,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_5_Set_Name,
  // String
  SW_Display_Name[4]
);

uint8 SwitchesSetName_SW_6_Path[] = {2, 2, 5};
MENU_STATE_CREATE(
  // Name
  SwitchesSetName_SW_6,
  // Path
  SwitchesSetName_SW_6_Path,
  // Max Level
  3,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Switch_6_Set_Name,
  // String
  SW_Display_Name[5]
);


uint8 SwitchName1SettingPath[] = {2, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  SwitchName1Setting,
  // Path
  SwitchName1SettingPath,
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
  RIGHT_KEY_EVENT,
  // Callback
  Menu_Switch_Name_Setting,
  // String
  ""
);

uint8 SwitchName2SettingPath[] = {2, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  SwitchName2Setting,
  // Path
  SwitchName2SettingPath,
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
  RIGHT_KEY_EVENT,
  // Callback
  Menu_Switch_Name_Setting,
  // String
  ""
);

uint8 SwitchName3SettingPath[] = {2, 2, 2, 0};
MENU_STATE_CREATE(
  // Name
  SwitchName3Setting,
  // Path
  SwitchName3SettingPath,
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
  RIGHT_KEY_EVENT,
  // Callback
  Menu_Switch_Name_Setting,
  // String
  ""
);

uint8 SwitchName4SettingPath[] = {2, 2, 3, 0};
MENU_STATE_CREATE(
  // Name
  SwitchName4Setting,
  // Path
  SwitchName4SettingPath,
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
  RIGHT_KEY_EVENT,
  // Callback
  Menu_Switch_Name_Setting,
  // String
  ""
);

uint8 SwitchName5SettingPath[] = {2, 2, 4, 0};
MENU_STATE_CREATE(
  // Name
  SwitchName5Setting,
  // Path
  SwitchName5SettingPath,
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
  RIGHT_KEY_EVENT,
  // Callback
  Menu_Switch_Name_Setting,
  // String
  ""
);

uint8 SwitchName6SettingPath[] = {2, 2, 5, 0};
MENU_STATE_CREATE(
  // Name
  SwitchName6Setting,
  // Path
  SwitchName6SettingPath,
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
  RIGHT_KEY_EVENT,
  // Callback
  Menu_Switch_Name_Setting,
  // String
  ""
);
