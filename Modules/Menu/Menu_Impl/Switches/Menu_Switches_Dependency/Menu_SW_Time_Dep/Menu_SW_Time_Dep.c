#include <stdio.h>
#include <string.h>

#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"

#include "Menu.h"
#include "Menu_Func.h"
#include "Menu_Switches.h"
#include "Menu_Switches_Dependency.h"
#include "Menu_Utilities.h"

/**** Global Variables ****/
uint8 SetTimeFlag = 0;
char Time_1_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Time_2_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Time_Response_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Time_State_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Set_Time_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Set_Date_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Set_Repeat_Name[SWITCHES_SET_STRING_LENGTH] = {0};

/**** Functions ****/

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Set_Time_Name(void)
{
  FuncIN(MENU_TIME_DEP_SET_TIME_NAME);

  switch(SW_M_Event_g.Time_Start.State)
  {
    case SW_TIME_ALARM_ON:
      strcpy(Time_1_Name, "Time 1 : ON");
      break;
    case SW_TIME_ALARM_OFF:
      strcpy(Time_1_Name, "Time 1 : OFF");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }

  switch(SW_M_Event_g.Time_Stop.State)
  {
    case SW_TIME_ALARM_ON:
      strcpy(Time_2_Name, "Time 2 : ON");
      break;
    case SW_TIME_ALARM_OFF:
      strcpy(Time_2_Name, "Time 2 : OFF");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME_NAME);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME_NAME, Menu_Time_Dep_Set_Time_Name);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Set_Time_State_Name(void)
{
  FuncIN(MENU_TIME_DEP_SET_TIME_STATE_NAME);

  switch(SetTimeFlag)
  {
    case 1:
      switch(SW_M_Event_g.Time_Start.State)
      {
        case SW_TIME_ALARM_ON:
          strcpy(Time_State_Name, "State : ON");
          break;
        case SW_TIME_ALARM_OFF:
          strcpy(Time_State_Name, "State : OFF");
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      }
      break;
    case 2:
      switch(SW_M_Event_g.Time_Stop.State)
      {
        case SW_TIME_ALARM_ON:
          strcpy(Time_State_Name, "State : ON");
          break;
        case SW_TIME_ALARM_OFF:
          strcpy(Time_State_Name, "State : OFF");
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      }
      break;
    default:
      Fatal_Abort(-NOT_INITIALIZED_ERROR);
  }

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME_STATE_NAME);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME_STATE_NAME, Menu_Time_Dep_Set_Time_State_Name);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Set_Time_Response_Name(void)
{
  FuncIN(MENU_TIME_DEP_SET_TIME_RESPONSE_NAME);

  switch(SetTimeFlag)
  {
    case 1:
      switch(SW_M_Event_g.Config & SW_EVENT_RESPONSE_1_ON)
      {
        case SW_EVENT_RESPONSE_1_ON:
          strcpy(Time_Response_Name, "Response : ON");
          break;
        case SW_EVENT_RESPONSE_1_OFF:
          strcpy(Time_Response_Name, "Response : OFF");
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      }
      break;
    case 2:
      switch(SW_M_Event_g.Config & SW_EVENT_RESPONSE_2_ON)
      {
        case SW_EVENT_RESPONSE_2_ON:
          strcpy(Time_Response_Name, "Response : ON");
          break;
        case SW_EVENT_RESPONSE_2_OFF:
          strcpy(Time_Response_Name, "Response : OFF");
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      }
      break;
    default:
      Fatal_Abort(-NOT_INITIALIZED_ERROR);
  }

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME_RESPONSE_NAME);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME_RESPONSE_NAME, Menu_Time_Dep_Set_Time_Response_Name);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Setting_Time_Name(void)
{
  FuncIN(MENU_TIME_DEP_SETTING_TIME_NAME);

  switch(SetTimeFlag)
  {
    case 1:
      snprintf(Set_Time_Name, 16, "Time (%02u:%02u:%02u)",
               SW_M_Event_g.Time_Start.Hour,
               SW_M_Event_g.Time_Start.Minute,
               SW_M_Event_g.Time_Start.Second);
      break;
    case 2:
      snprintf(Set_Time_Name, 16, "Time (%02u:%02u:%02u)",
               SW_M_Event_g.Time_Stop.Hour,
               SW_M_Event_g.Time_Stop.Minute,
               SW_M_Event_g.Time_Stop.Second);
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SETTING_TIME_NAME);
}
FUNC_REGISTER(MENU_TIME_DEP_SETTING_TIME_NAME, Menu_Time_Dep_Setting_Time_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_Setting_Date_Name(void)
{
  FuncIN(MENU_TIME_DEP_SETTING_DATE_NAME);

  if(0 == SW_M_Event_g.Date.Repeat) {
    if(0 == SW_M_Event_g.Date.Day &&
       0 == SW_M_Event_g.Date.Month &&
       0 == SW_M_Event_g.Date.Year) {
      strcpy(Set_Date_Name, "  Event Date");
    } else {
     strcpy(Set_Date_Name, "# Event Date");
    }
    strcpy(Set_Repeat_Name, "  Event Repeat");
  } else {
    strcpy(Set_Date_Name, "  Event Date");
    strcpy(Set_Repeat_Name, "# Event Repeat");
  }

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SETTING_DATE_NAME);
}
FUNC_REGISTER(MENU_TIME_DEP_SETTING_DATE_NAME, Menu_Time_Dep_Setting_Date_Name);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Set_Time_1(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_SET_TIME_1);

  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetTimeFlag = 1;
      Menu_Time_Dep_Set_Time_Response_Name();
      Menu_Time_Dep_Set_Time_State_Name();
      Menu_Time_Dep_Setting_Time_Name();
      break;
    case CANCEL_KEY_EVENT:
      SetTimeFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME_1);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME_1, Menu_Time_Dep_Set_Time_1);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Set_Time_2(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_SET_TIME_2);

  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetTimeFlag = 2;
      Menu_Time_Dep_Set_Time_Response_Name();
      Menu_Time_Dep_Set_Time_State_Name();
      Menu_Time_Dep_Setting_Time_Name();
      break;
    case CANCEL_KEY_EVENT:
      SetTimeFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME_2);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME_2, Menu_Time_Dep_Set_Time_2);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Date(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_DATE);

  switch(Key)
  {
    case ENTER_KEY_EVENT:
      Menu_Time_Dep_Setting_Date_Name();
      break;
    case CANCEL_KEY_EVENT:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_DATE);
}
FUNC_REGISTER(MENU_TIME_DEP_DATE, Menu_Time_Dep_Date);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Set_Time(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_SET_TIME);

  static uint32 EnterFlag = 0;
  clrd();

  switch(SetTimeFlag)
  {
    case 1:
      printd(1, "Set Start Time");
      break;
    case 2:
      printd(1, "Set Stop Time");
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }

  if(EnterFlag == 0)
  {
    switch(SetTimeFlag)
    {
      case 1:
        Hour = SW_M_Event_g.Time_Start.Hour;
        Minute = SW_M_Event_g.Time_Start.Minute;
        Second = SW_M_Event_g.Time_Start.Second;
        break;
      case 2:
        Hour = SW_M_Event_g.Time_Stop.Hour;
        Minute = SW_M_Event_g.Time_Stop.Minute;
        Second = SW_M_Event_g.Time_Stop.Second;
        break;
    }
  }
  printd(2, "%02u:%02u:%02u", Hour, Minute, Second);
  Menu_Time_Update_Disp_Ptr_Pos();

  switch(Key)
  {
    case ENTER_KEY_EVENT:
      // First enter in this state
      if(EnterFlag == 0)
      {
        EnterFlag = 1;
        break;
      }
      switch(SetTimeFlag)
      {
        case 1:
          SW_M_Event_g.Time_Start.Hour = Hour;
          SW_M_Event_g.Time_Start.Minute = Minute;
          SW_M_Event_g.Time_Start.Second = Second;
          break;
        case 2:
          SW_M_Event_g.Time_Stop.Hour = Hour;
          SW_M_Event_g.Time_Stop.Minute = Minute;
          SW_M_Event_g.Time_Stop.Second = Second;
          break;
        default:
          Fatal_Abort(-INVALID_INPUT_PARAMETER);
      }
      printd(4, "Time set!");

      break;
    case CANCEL_KEY_EVENT:
      clrd();
      Menu_Time_Dep_Setting_Time_Name();

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

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_SET_TIME);
}
FUNC_REGISTER(MENU_TIME_DEP_SET_TIME, Menu_Time_Dep_Set_Time);


/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_State_Update_Display(const uint32 Ptr_Pos)
{
  FuncIN(MENU_TIME_DEP_STATE_UPDATE_DISPLAY);

  uint8 State;
  char PointerString_1[3] = {0};
  char PointerString_2[3] = {0};

  switch(Ptr_Pos)
  {
    case 1:
      strcpy(PointerString_1, "> ");
      strcpy(PointerString_2, "  ");
      break;
    case 2:
      strcpy(PointerString_1, "  ");
      strcpy(PointerString_2, "> ");
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }

  printd(1, "Set State : Time %u", SetTimeFlag);

  switch(SetTimeFlag)
  {
    case 1:
      State = SW_M_Event_g.Time_Start.State;
      break;
    case 2:
      State = SW_M_Event_g.Time_Stop.State;
      break;
    default:
      Fatal_Abort(-NOT_INITIALIZED_ERROR);
  } // switch(SetTimeFlag)

  switch(State)
  {
    case SW_TIME_ALARM_OFF:
      printd(2, "%s# OFF", PointerString_1);
      printd(3, "%s  ON", PointerString_2);
      break;
    case SW_TIME_ALARM_ON:
      printd(2, "%s  OFF", PointerString_1);
      printd(3, "%s# ON", PointerString_2);
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  } // switch(State)

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_STATE_UPDATE_DISPLAY);
}
FUNC_REGISTER(MENU_TIME_DEP_STATE_UPDATE_DISPLAY, Menu_Time_Dep_State_Update_Display);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Time_State(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_TIME_STATE);

  static uint32 Ptr_Pos = 0;

  clrd();

  switch(Key)
  {
    case ENTER_KEY_EVENT:
      if(Ptr_Pos == 0)
      {
        Ptr_Pos = 1;
        Menu_Time_Dep_State_Update_Display(Ptr_Pos);
      }
      else
      {
        switch(SetTimeFlag)
        {
          case 1:
            switch(Ptr_Pos)
            {
              case 1:
                SW_M_Event_g.Time_Start.State = SW_TIME_ALARM_OFF;
                break;
              case 2:
                SW_M_Event_g.Time_Start.State = SW_TIME_ALARM_ON;
                break;
              default:
                Fatal_Abort(-NOT_INITIALIZED_ERROR);
            }
            break;
          case 2:
            switch(Ptr_Pos)
            {
              case 1:
                SW_M_Event_g.Time_Stop.State = SW_TIME_ALARM_OFF;
                break;
              case 2:
                SW_M_Event_g.Time_Stop.State = SW_TIME_ALARM_ON;
                break;
              default:
                Fatal_Abort(-NOT_INITIALIZED_ERROR);
            }
            break;
          default:
            Fatal_Abort(-NOT_INITIALIZED_ERROR);
        } // switch(SetTimeFlag)

        Menu_Time_Dep_State_Update_Display(Ptr_Pos);
        printd(4, "State Set!");

      }
      break;
    case CANCEL_KEY_EVENT:
      Menu_Time_Dep_Set_Time_Response_Name();
      Menu_Time_Dep_Set_Time_State_Name();
      Menu_Time_Dep_Set_Time_Name();
      Ptr_Pos = 0;
      break;
    case UP_KEY_EVENT:
      Ptr_Pos = 1;
      Menu_Time_Dep_State_Update_Display(Ptr_Pos);
      break;
    case DOWN_KEY_EVENT:
      Ptr_Pos = 2;
      Menu_Time_Dep_State_Update_Display(Ptr_Pos);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)

  syncd();

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_TIME_STATE);
}
FUNC_REGISTER(MENU_TIME_DEP_TIME_STATE, Menu_Time_Dep_Time_State);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Time_Dep_Response_Update_Display(const uint32 Ptr_Pos)
{
  FuncIN(MENU_TIME_DEP_RESPONSE_UPDATE_DISPLAY);

  uint8 Response;
  char PointerString_1[3] = {0};
  char PointerString_2[3] = {0};

  switch(Ptr_Pos)
  {
    case 1:
      strcpy(PointerString_1, "> ");
      strcpy(PointerString_2, "  ");
      break;
    case 2:
      strcpy(PointerString_1, "  ");
      strcpy(PointerString_2, "> ");
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }

  printd(1, "Set Response:Time%u", SetTimeFlag);

  switch(SetTimeFlag)
  {
    case 1:
      Response = SW_M_Event_g.Config & SW_EVENT_RESPONSE_1_ON;
      break;
    case 2:
      Response = SW_M_Event_g.Config & SW_EVENT_RESPONSE_2_ON;
      break;
    default:
      Fatal_Abort(-NOT_INITIALIZED_ERROR);
  } // switch(SetTimeFlag)

  switch(Response)
  {
    case SW_EVENT_RESPONSE_1_OFF:
      printd(2, "%s# OFF", PointerString_1);
      printd(3, "%s  ON", PointerString_2);
      break;
    case SW_EVENT_RESPONSE_1_ON:
      printd(2, "%s  OFF", PointerString_1);
      printd(3, "%s# ON", PointerString_2);
    case SW_EVENT_RESPONSE_2_ON:
      printd(2, "%s  OFF", PointerString_1);
      printd(3, "%s# ON", PointerString_2);
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  } // switch(Response)

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_RESPONSE_UPDATE_DISPLAY);
}
FUNC_REGISTER(MENU_TIME_DEP_RESPONSE_UPDATE_DISPLAY, Menu_Time_Dep_Response_Update_Display);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Time_Response(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_TIME_RESPONSE);

  static uint32 Ptr_Pos = 0;

  clrd();

  switch(Key)
  {
    case ENTER_KEY_EVENT:
      if(Ptr_Pos == 0)
      {
        Ptr_Pos = 1;
        Menu_Time_Dep_Response_Update_Display(Ptr_Pos);
      }
      else
      {
        switch(SetTimeFlag)
        {
          case 1:
            switch(Ptr_Pos)
            {
              case 1:
                SW_M_Event_g.Config &= ~SW_EVENT_RESPONSE_1_ON;
                break;
              case 2:
                SW_M_Event_g.Config |= SW_EVENT_RESPONSE_1_ON;
                break;
              default:
                Fatal_Abort(-NOT_INITIALIZED_ERROR);
            }
            break;
          case 2:
            switch(Ptr_Pos)
            {
              case 1:
                SW_M_Event_g.Config &= ~SW_EVENT_RESPONSE_2_ON;
                break;
              case 2:
                SW_M_Event_g.Config |= SW_EVENT_RESPONSE_2_ON;
                break;
              default:
                Fatal_Abort(-NOT_INITIALIZED_ERROR);
            }
            break;
          default:
            Fatal_Abort(-NOT_INITIALIZED_ERROR);
        } // switch(SetTimeFlag)

        Menu_Time_Dep_Response_Update_Display(Ptr_Pos);
        printd(4, "Response Set!");

      }
      break;
    case CANCEL_KEY_EVENT:
      Menu_Time_Dep_Set_Time_Response_Name();
      Menu_Time_Dep_Set_Time_State_Name();
      Menu_Time_Dep_Set_Time_Name();
      Ptr_Pos = 0;
      break;
    case UP_KEY_EVENT:
      Ptr_Pos = 1;
      Menu_Time_Dep_Response_Update_Display(Ptr_Pos);
      break;
    case DOWN_KEY_EVENT:
      Ptr_Pos = 2;
      Menu_Time_Dep_Response_Update_Display(Ptr_Pos);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)

  syncd();

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_TIME_RESPONSE);
}
FUNC_REGISTER(MENU_TIME_DEP_TIME_RESPONSE, Menu_Time_Dep_Time_Response);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Date_Set_Date(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_DATE_SET_DATE);

  Status_t Status = GENERAL_ERROR;
  RtcDate_t Date_s;
  static uint32 EnterFlag = 0;

  if(EnterFlag == 0)
  {
    if(SW_M_Event_g.Date.Year == 0 &&
       SW_M_Event_g.Date.Month == 0 &&
       SW_M_Event_g.Date.Day == 0) {
      RTC_Get_Date(&Date_s);

      Year = Date_s.Year;
      Month = Date_s.Month;
      Day = Date_s.Day;
    } else {
      Year = SW_M_Event_g.Date.Year;
      Month = SW_M_Event_g.Date.Month;
      Day = SW_M_Event_g.Date.Day;
    }
  }

  clrd();
  printd(1, "Set Date");
  printd(2, "%02u.%02u.%04u", Day, Month, Year);
  Menu_Date_Update_Disp_Ptr_Pos();

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
        SW_M_Event_g.Date.Year = Year;
        SW_M_Event_g.Date.Month = Month;
        SW_M_Event_g.Date.Day = Day;

        printd(2, "%02u.%02u.%04u Date Set!", Day, Month, Year);
      }
      else
        printd(2, "%02u.%02u.%04u ERROR!!!", Day, Month, Year);

      break;
    case CANCEL_KEY_EVENT:
      clrd();

      PointerPosition = 1;
      EnterFlag = 0;

      Menu_Time_Dep_Setting_Date_Name();

      EXIT_SUCCESS_FUNC(MENU_TIME_DEP_DATE_SET_DATE);
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

      Menu_Time_Dep_Setting_Date_Name();

      EXIT_SUCCESS_FUNC(MENU_TIME_DEP_DATE_SET_DATE);
    case MENU_KEY_EVENT:
      clrd();

      PointerPosition = 1;
      EnterFlag = 0;

      Menu_Time_Dep_Setting_Date_Name();
      EXIT_SUCCESS_FUNC(MENU_TIME_DEP_DATE_SET_DATE);
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

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_DATE_SET_DATE);
}
FUNC_REGISTER(MENU_TIME_DEP_DATE_SET_DATE, Menu_Time_Dep_Date_Set_Date);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Dep_Date_Set_Repeat(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TIME_DEP_DATE_SET_REPEAT);

  static uint32 EnterFlag = 0;
  static uint8 Offset = 0;

  if(EnterFlag == 0)
  {
    Offset = 0;
    PointerPosition = 1;
    Menu_Repeat_Update_Display(Offset, PointerPosition, SW_M_Event_g.Date.Repeat);
  }

  switch(Key)
  {
    case ENTER_KEY_EVENT:
      // First enter in this state
      if(EnterFlag == 0)
      {
        EnterFlag = 1;
        break;
      }
      SW_M_Event_g.Date.Repeat = SW_M_Event_g.Date.Repeat ^ (1 << (7 - PointerPosition));
      Menu_Repeat_Update_Display(Offset, PointerPosition, SW_M_Event_g.Date.Repeat);

      break;
    case CANCEL_KEY_EVENT:
      clrd();

      PointerPosition = 1;
      EnterFlag = 0;

      Menu_Time_Dep_Setting_Date_Name();
      EXIT_SUCCESS_FUNC(MENU_TIME_DEP_DATE_SET_REPEAT);
    case UP_KEY_EVENT:
      if(PointerPosition > 1)
      {
        PointerPosition--;
        if((PointerPosition - Offset) < 1)
        {
          Offset--;
        }
      }
      Menu_Repeat_Update_Display(Offset, PointerPosition, SW_M_Event_g.Date.Repeat);
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
      Menu_Repeat_Update_Display(Offset, PointerPosition, SW_M_Event_g.Date.Repeat);
      break;
    case LEFT_KEY_EVENT:
      SW_M_Event_g.Date.Repeat = SW_M_Event_g.Date.Repeat ^ (1 << (7 - PointerPosition));
      Menu_Repeat_Update_Display(Offset, PointerPosition, SW_M_Event_g.Date.Repeat);
      break;
    case RIGHT_KEY_EVENT:
      SW_M_Event_g.Date.Repeat = SW_M_Event_g.Date.Repeat ^ (1 << (7 - PointerPosition));
      Menu_Repeat_Update_Display(Offset, PointerPosition, SW_M_Event_g.Date.Repeat);
      break;
    case EXIT_KEY_EVENT:
      clrd();

      PointerPosition = 1;
      EnterFlag = 0;

      Menu_Time_Dep_Setting_Date_Name();
      EXIT_SUCCESS_FUNC(MENU_TIME_DEP_DATE_SET_REPEAT);
    case MENU_KEY_EVENT:
      clrd();

      PointerPosition = 1;
      EnterFlag = 0;

      Menu_Time_Dep_Setting_Date_Name();
      EXIT_SUCCESS_FUNC(MENU_TIME_DEP_DATE_SET_REPEAT);
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)

  syncd();

  EXIT_SUCCESS_FUNC(MENU_TIME_DEP_DATE_SET_REPEAT);
}
FUNC_REGISTER(MENU_TIME_DEP_DATE_SET_REPEAT, Menu_Time_Dep_Date_Set_Repeat);

/*******************************************************************************
 * Menu States
 ******************************************************************************/

/*******************************************************************************
 * Level 7
 ******************************************************************************/

/*******************************************************************************
 * Switch 1
 ******************************************************************************/

/**** Switch 1, Event 1, Time 1 Dep *******************************************/
const uint8 Switch_1_Event_1_Time1Path[] = {2, 3, 0, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time1,
  // Path
  Switch_1_Event_1_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 1, Event 1, Time 2 Dep *******************************************/
const uint8 Switch_1_Event_1_Time2Path[] = {2, 3, 0, 0, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time2,
  // Path
  Switch_1_Event_1_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 1, Event 1, Date Dep *********************************************/
const uint8 Switch_1_Event_1_DatePath[] = {2, 3, 0, 0, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Date,
  // Path
  Switch_1_Event_1_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 1, Event 2, Time 1 Dep *******************************************/
const uint8 Switch_1_Event_2_Time1Path[] = {2, 3, 0, 1, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time1,
  // Path
  Switch_1_Event_2_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 1, Event 2, Time 2 Dep *******************************************/
const uint8 Switch_1_Event_2_Time2Path[] = {2, 3, 0, 1, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time2,
  // Path
  Switch_1_Event_2_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 1, Event 2, Date Dep *********************************************/
const uint8 Switch_1_Event_2_DatePath[] = {2, 3, 0, 1, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Date,
  // Path
  Switch_1_Event_2_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 1, Event 3, Time 1 Dep *******************************************/
const uint8 Switch_1_Event_3_Time1Path[] = {2, 3, 0, 2, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time1,
  // Path
  Switch_1_Event_3_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 1, Event 3, Time 2 Dep *******************************************/
const uint8 Switch_1_Event_3_Time2Path[] = {2, 3, 0, 2, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time2,
  // Path
  Switch_1_Event_3_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 1, Event 3, Date Dep *********************************************/
const uint8 Switch_1_Event_3_DatePath[] = {2, 3, 0, 2, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Date,
  // Path
  Switch_1_Event_3_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 1, Event 4, Time 1 Dep *******************************************/
const uint8 Switch_1_Event_4_Time1Path[] = {2, 3, 0, 3, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time1,
  // Path
  Switch_1_Event_4_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 1, Event 4, Time 2 Dep *******************************************/
const uint8 Switch_1_Event_4_Time2Path[] = {2, 3, 0, 3, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time2,
  // Path
  Switch_1_Event_4_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 1, Event 4, Date Dep *********************************************/
const uint8 Switch_1_Event_4_DatePath[] = {2, 3, 0, 3, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Date,
  // Path
  Switch_1_Event_4_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/*******************************************************************************
 * Switch 2
 ******************************************************************************/

/**** Switch 2, Event 1, Time 1 Dep *******************************************/
const uint8 Switch_2_Event_1_Time1Path[] = {2, 3, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time1,
  // Path
  Switch_2_Event_1_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 2, Event 1, Time 2 Dep *******************************************/
const uint8 Switch_2_Event_1_Time2Path[] = {2, 3, 1, 0, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time2,
  // Path
  Switch_2_Event_1_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 2, Event 1, Date Dep *********************************************/
const uint8 Switch_2_Event_1_DatePath[] = {2, 3, 1, 0, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Date,
  // Path
  Switch_2_Event_1_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 2, Event 2, Time 1 Dep *******************************************/
const uint8 Switch_2_Event_2_Time1Path[] = {2, 3, 1, 1, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time1,
  // Path
  Switch_2_Event_2_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 2, Event 2, Time 2 Dep *******************************************/
const uint8 Switch_2_Event_2_Time2Path[] = {2, 3, 1, 1, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time2,
  // Path
  Switch_2_Event_2_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 2, Event 2, Date Dep *********************************************/
const uint8 Switch_2_Event_2_DatePath[] = {2, 3, 1, 1, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Date,
  // Path
  Switch_2_Event_2_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 2, Event 3, Time 1 Dep *******************************************/
const uint8 Switch_2_Event_3_Time1Path[] = {2, 3, 1, 2, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time1,
  // Path
  Switch_2_Event_3_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 2, Event 3, Time 2 Dep *******************************************/
const uint8 Switch_2_Event_3_Time2Path[] = {2, 3, 1, 2, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time2,
  // Path
  Switch_2_Event_3_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 2, Event 3, Date Dep *********************************************/
const uint8 Switch_2_Event_3_DatePath[] = {2, 3, 1, 2, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Date,
  // Path
  Switch_2_Event_3_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 2, Event 4, Time 1 Dep *******************************************/
const uint8 Switch_2_Event_4_Time1Path[] = {2, 3, 1, 3, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time1,
  // Path
  Switch_2_Event_4_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 2, Event 4, Time 2 Dep *******************************************/
const uint8 Switch_2_Event_4_Time2Path[] = {2, 3, 1, 3, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time2,
  // Path
  Switch_2_Event_4_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 2, Event 4, Date Dep *********************************************/
const uint8 Switch_2_Event_4_DatePath[] = {2, 3, 1, 3, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Date,
  // Path
  Switch_2_Event_4_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/*******************************************************************************
 * Switch 3
 ******************************************************************************/

/**** Switch 3, Event 1, Time 1 Dep *******************************************/
const uint8 Switch_3_Event_1_Time1Path[] = {2, 3, 2, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time1,
  // Path
  Switch_3_Event_1_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 3, Event 1, Time 2 Dep *******************************************/
const uint8 Switch_3_Event_1_Time2Path[] = {2, 3, 2, 0, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time2,
  // Path
  Switch_3_Event_1_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 3, Event 1, Date Dep *********************************************/
const uint8 Switch_3_Event_1_DatePath[] = {2, 3, 2, 0, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Date,
  // Path
  Switch_3_Event_1_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 3, Event 2, Time 1 Dep *******************************************/
const uint8 Switch_3_Event_2_Time1Path[] = {2, 3, 2, 1, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time1,
  // Path
  Switch_3_Event_2_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 3, Event 2, Time 2 Dep *******************************************/
const uint8 Switch_3_Event_2_Time2Path[] = {2, 3, 2, 1, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time2,
  // Path
  Switch_3_Event_2_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 3, Event 2, Date Dep *********************************************/
const uint8 Switch_3_Event_2_DatePath[] = {2, 3, 2, 1, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Date,
  // Path
  Switch_3_Event_2_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 3, Event 3, Time 1 Dep *******************************************/
const uint8 Switch_3_Event_3_Time1Path[] = {2, 3, 2, 2, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time1,
  // Path
  Switch_3_Event_3_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 1, Event 3, Time 2 Dep *******************************************/
const uint8 Switch_3_Event_3_Time2Path[] = {2, 3, 2, 2, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time2,
  // Path
  Switch_3_Event_3_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 3, Event 3, Date Dep *********************************************/
const uint8 Switch_3_Event_3_DatePath[] = {2, 3, 2, 2, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Date,
  // Path
  Switch_3_Event_3_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 3, Event 4, Time 1 Dep *******************************************/
const uint8 Switch_3_Event_4_Time1Path[] = {2, 3, 2, 3, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time1,
  // Path
  Switch_3_Event_4_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 3, Event 4, Time 2 Dep *******************************************/
const uint8 Switch_3_Event_4_Time2Path[] = {2, 3, 2, 3, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time2,
  // Path
  Switch_3_Event_4_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 3, Event 4, Date Dep *********************************************/
const uint8 Switch_3_Event_4_DatePath[] = {2, 3, 2, 3, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Date,
  // Path
  Switch_3_Event_4_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/*******************************************************************************
 * Switch 4
 ******************************************************************************/

/**** Switch 4, Event 1, Time 1 Dep *******************************************/
const uint8 Switch_4_Event_1_Time1Path[] = {2, 3, 3, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time1,
  // Path
  Switch_4_Event_1_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 4, Event 1, Time 2 Dep *******************************************/
const uint8 Switch_4_Event_1_Time2Path[] = {2, 3, 3, 0, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time2,
  // Path
  Switch_4_Event_1_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 4, Event 1, Date Dep *********************************************/
const uint8 Switch_4_Event_1_DatePath[] = {2, 3, 3, 0, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Date,
  // Path
  Switch_4_Event_1_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 4, Event 2, Time 1 Dep *******************************************/
const uint8 Switch_4_Event_2_Time1Path[] = {2, 3, 3, 1, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time1,
  // Path
  Switch_4_Event_2_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 4, Event 2, Time 2 Dep *******************************************/
const uint8 Switch_4_Event_2_Time2Path[] = {2, 3, 3, 1, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time2,
  // Path
  Switch_4_Event_2_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 4, Event 2, Date Dep *********************************************/
const uint8 Switch_4_Event_2_DatePath[] = {2, 3, 3, 1, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Date,
  // Path
  Switch_4_Event_2_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 4, Event 3, Time 1 Dep *******************************************/
const uint8 Switch_4_Event_3_Time1Path[] = {2, 3, 3, 2, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time1,
  // Path
  Switch_4_Event_3_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 4, Event 3, Time 2 Dep *******************************************/
const uint8 Switch_4_Event_3_Time2Path[] = {2, 3, 3, 2, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time2,
  // Path
  Switch_4_Event_3_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 4, Event 3, Date Dep *********************************************/
const uint8 Switch_4_Event_3_DatePath[] = {2, 3, 3, 2, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Date,
  // Path
  Switch_4_Event_3_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 4, Event 4, Time 1 Dep *******************************************/
const uint8 Switch_4_Event_4_Time1Path[] = {2, 3, 3, 3, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time1,
  // Path
  Switch_4_Event_4_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 4, Event 4, Time 2 Dep *******************************************/
const uint8 Switch_4_Event_4_Time2Path[] = {2, 3, 3, 3, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time2,
  // Path
  Switch_4_Event_4_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 4, Event 4, Date Dep *********************************************/
const uint8 Switch_4_Event_4_DatePath[] = {2, 3, 3, 3, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Date,
  // Path
  Switch_4_Event_4_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/*******************************************************************************
 * Switch 5
 ******************************************************************************/

/**** Switch 5, Event 1, Time 1 Dep *******************************************/
const uint8 Switch_5_Event_1_Time1Path[] = {2, 3, 4, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time1,
  // Path
  Switch_5_Event_1_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 5, Event 1, Time 2 Dep *******************************************/
const uint8 Switch_5_Event_1_Time2Path[] = {2, 3, 4, 0, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time2,
  // Path
  Switch_5_Event_1_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 5, Event 1, Date Dep *********************************************/
const uint8 Switch_5_Event_1_DatePath[] = {2, 3, 4, 0, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Date,
  // Path
  Switch_5_Event_1_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 5, Event 2, Time 1 Dep *******************************************/
const uint8 Switch_5_Event_2_Time1Path[] = {2, 3, 4, 1, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time1,
  // Path
  Switch_5_Event_2_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 5, Event 2, Time 2 Dep *******************************************/
const uint8 Switch_5_Event_2_Time2Path[] = {2, 3, 4, 1, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time2,
  // Path
  Switch_5_Event_2_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 5, Event 2, Date Dep *********************************************/
const uint8 Switch_5_Event_2_DatePath[] = {2, 3, 4, 1, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Date,
  // Path
  Switch_5_Event_2_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 5, Event 3, Time 1 Dep *******************************************/
const uint8 Switch_5_Event_3_Time1Path[] = {2, 3, 4, 2, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time1,
  // Path
  Switch_5_Event_3_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 5, Event 3, Time 2 Dep *******************************************/
const uint8 Switch_5_Event_3_Time2Path[] = {2, 3, 4, 2, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time2,
  // Path
  Switch_5_Event_3_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 5, Event 3, Date Dep *********************************************/
const uint8 Switch_5_Event_3_DatePath[] = {2, 3, 4, 2, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Date,
  // Path
  Switch_5_Event_3_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 5, Event 4, Time 1 Dep *******************************************/
const uint8 Switch_5_Event_4_Time1Path[] = {2, 3, 4, 3, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time1,
  // Path
  Switch_5_Event_4_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 5, Event 4, Time 2 Dep *******************************************/
const uint8 Switch_5_Event_4_Time2Path[] = {2, 3, 4, 3, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time2,
  // Path
  Switch_5_Event_4_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 5, Event 4, Date Dep *********************************************/
const uint8 Switch_5_Event_4_DatePath[] = {2, 3, 4, 3, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Date,
  // Path
  Switch_5_Event_4_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/*******************************************************************************
 * Switch 6
 ******************************************************************************/

/**** Switch 6, Event 1, Time 1 Dep *******************************************/
const uint8 Switch_6_Event_1_Time1Path[] = {2, 3, 5, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time1,
  // Path
  Switch_6_Event_1_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 6, Event 1, Time 2 Dep *******************************************/
const uint8 Switch_6_Event_1_Time2Path[] = {2, 3, 5, 0, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time2,
  // Path
  Switch_6_Event_1_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 6, Event 1, Date Dep *********************************************/
const uint8 Switch_6_Event_1_DatePath[] = {2, 3, 5, 0, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Date,
  // Path
  Switch_6_Event_1_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 6, Event 2, Time 1 Dep *******************************************/
const uint8 Switch_6_Event_2_Time1Path[] = {2, 3, 5, 1, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time1,
  // Path
  Switch_6_Event_2_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 6, Event 2, Time 2 Dep *******************************************/
const uint8 Switch_6_Event_2_Time2Path[] = {2, 3, 5, 1, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time2,
  // Path
  Switch_6_Event_2_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 6, Event 2, Date Dep *********************************************/
const uint8 Switch_6_Event_2_DatePath[] = {2, 3, 5, 1, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Date,
  // Path
  Switch_6_Event_2_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 6, Event 3, Time 1 Dep *******************************************/
const uint8 Switch_6_Event_3_Time1Path[] = {2, 3, 5, 2, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time1,
  // Path
  Switch_6_Event_3_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 6, Event 3, Time 2 Dep *******************************************/
const uint8 Switch_6_Event_3_Time2Path[] = {2, 3, 5, 2, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time2,
  // Path
  Switch_6_Event_3_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 6, Event 3, Date Dep *********************************************/
const uint8 Switch_6_Event_3_DatePath[] = {2, 3, 5, 2, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Date,
  // Path
  Switch_6_Event_3_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);

/**** Switch 6, Event 4, Time 1 Dep *******************************************/
const uint8 Switch_6_Event_4_Time1Path[] = {2, 3, 5, 3, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time1,
  // Path
  Switch_6_Event_4_Time1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_1,
  // String
  Time_1_Name
);

/**** Switch 6, Event 4, Time 2 Dep *******************************************/
const uint8 Switch_6_Event_4_Time2Path[] = {2, 3, 5, 3, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time2,
  // Path
  Switch_6_Event_4_Time2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time_2,
  // String
  Time_2_Name
);

/**** Switch 6, Event 4, Date Dep *********************************************/
const uint8 Switch_6_Event_4_DatePath[] = {2, 3, 5, 3, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Date,
  // Path
  Switch_6_Event_4_DatePath,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date,
  // String
  "Date"
);
/*******************************************************************************
 * Level 8
 ******************************************************************************/
/*******************************************************************************
 * Switch 1
 ******************************************************************************/

/**** Switch 1, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_1_StatePath[] = {2, 3, 0, 0, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_1_State,
  // Path
  Switch_1_Event_1_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 1, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_1_Event_1_Time_1_ResponsePath[] = {2, 3, 0, 0, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_1_Response,
  // Path
  Switch_1_Event_1_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 1, Event 1, Time 1, Set Time Dep *********************************/
const uint8 Switch_1_Event_1_Time_1_Set_Time_Path[] = {2, 3, 0, 0, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_1_Set_Time,
  // Path
  Switch_1_Event_1_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 1, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_2_StatePath[] = {2, 3, 0, 0, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_2_State,
  // Path
  Switch_1_Event_1_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 1, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_1_Event_1_Time_2_ResponsePath[] = {2, 3, 0, 0, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_2_Response,
  // Path
  Switch_1_Event_1_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 1, Event 1, Time 2, Set Time Dep *********************************/
const uint8 Switch_1_Event_1_Time_2_Set_Time_Path[] = {2, 3, 0, 0, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_2_Set_Time,
  // Path
  Switch_1_Event_1_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 1, Event 1, Date Dep *********************************************/
const uint8 Switch_1_Event_1_Date_Set_Date_Path[] = {2, 3, 0, 0, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Date_Set_Date,
  // Path
  Switch_1_Event_1_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 1, Event 1, Date Dep *********************************************/
const uint8 Switch_1_Event_1_Date_Set_Repeat_Path[] = {2, 3, 0, 0, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Date_Set_Repeat,
  // Path
  Switch_1_Event_1_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 1, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_2_Time_1_StatePath[] = {2, 3, 0, 1, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time_1_State,
  // Path
  Switch_1_Event_2_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 1, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_1_Event_2_Time_1_ResponsePath[] = {2, 3, 0, 1, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time_1_Response,
  // Path
  Switch_1_Event_2_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 1, Event 2, Time 1, Set Time Dep *********************************/
const uint8 Switch_1_Event_2_Time_1_Set_Time_Path[] = {2, 3, 0, 1, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time_1_Set_Time,
  // Path
  Switch_1_Event_2_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 1, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_1_Event_2_Time_2_StatePath[] = {2, 3, 0, 1, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time_2_State,
  // Path
  Switch_1_Event_2_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 1, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_1_Event_2_Time_2_ResponsePath[] = {2, 3, 0, 1, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time_2_Response,
  // Path
  Switch_1_Event_2_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 1, Event 2, Time 2, Set Time Dep *********************************/
const uint8 Switch_1_Event_2_Time_2_Set_Time_Path[] = {2, 3, 0, 1, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time_2_Set_Time,
  // Path
  Switch_1_Event_2_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 1, Event 2, Date Dep *********************************************/
const uint8 Switch_1_Event_2_Date_Set_Date_Path[] = {2, 3, 0, 1, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Date_Set_Date,
  // Path
  Switch_1_Event_2_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 1, Event 2, Date Dep *********************************************/
const uint8 Switch_1_Event_2_Date_Set_Repeat_Path[] = {2, 3, 0, 1, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Date_Set_Repeat,
  // Path
  Switch_1_Event_2_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 1, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_3_Time_1_StatePath[] = {2, 3, 0, 2, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time_1_State,
  // Path
  Switch_1_Event_3_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 1, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_1_Event_3_Time_1_ResponsePath[] = {2, 3, 0, 2, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time_1_Response,
  // Path
  Switch_1_Event_3_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 1, Event 3, Time 1, Set Time Dep *********************************/
const uint8 Switch_1_Event_3_Time_1_Set_Time_Path[] = {2, 3, 0, 2, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time_1_Set_Time,
  // Path
  Switch_1_Event_3_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 1, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_1_Event_3_Time_2_StatePath[] = {2, 3, 0, 2, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time_2_State,
  // Path
  Switch_1_Event_3_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 1, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_1_Event_3_Time_2_ResponsePath[] = {2, 3, 0, 2, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time_2_Response,
  // Path
  Switch_1_Event_3_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 1, Event 3, Time 2, Set Time Dep *********************************/
const uint8 Switch_1_Event_3_Time_2_Set_Time_Path[] = {2, 3, 0, 2, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time_2_Set_Time,
  // Path
  Switch_1_Event_3_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 1, Event 3, Date Dep *********************************************/
const uint8 Switch_1_Event_3_Date_Set_Date_Path[] = {2, 3, 0, 2, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Date_Set_Date,
  // Path
  Switch_1_Event_3_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 1, Event 3, Date Dep *********************************************/
const uint8 Switch_1_Event_3_Date_Set_Repeat_Path[] = {2, 3, 0, 2, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Date_Set_Repeat,
  // Path
  Switch_1_Event_3_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 1, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_4_Time_1_StatePath[] = {2, 3, 0, 3, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time_1_State,
  // Path
  Switch_1_Event_4_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 1, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_1_Event_4_Time_1_ResponsePath[] = {2, 3, 0, 3, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time_1_Response,
  // Path
  Switch_1_Event_4_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 1, Event 4, Time 1, Set Time Dep *********************************/
const uint8 Switch_1_Event_4_Time_1_Set_Time_Path[] = {2, 3, 0, 3, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time_1_Set_Time,
  // Path
  Switch_1_Event_4_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 1, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_1_Event_4_Time_2_StatePath[] = {2, 3, 0, 3, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time_2_State,
  // Path
  Switch_1_Event_4_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 1, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_1_Event_4_Time_2_ResponsePath[] = {2, 3, 0, 3, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time_2_Response,
  // Path
  Switch_1_Event_4_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 1, Event 4, Time 2, Set Time Dep *********************************/
const uint8 Switch_1_Event_4_Time_2_Set_Time_Path[] = {2, 3, 0, 3, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time_2_Set_Time,
  // Path
  Switch_1_Event_4_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 1, Event 4, Date Dep *********************************************/
const uint8 Switch_1_Event_4_Date_Set_Date_Path[] = {2, 3, 0, 3, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Date_Set_Date,
  // Path
  Switch_1_Event_4_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 1, Event 4, Date Dep *********************************************/
const uint8 Switch_1_Event_4_Date_Set_Repeat_Path[] = {2, 3, 0, 3, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Date_Set_Repeat,
  // Path
  Switch_1_Event_4_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/*******************************************************************************
 * Switch 2
 ******************************************************************************/

/**** Switch 2, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_2_Event_1_Time_1_StatePath[] = {2, 3, 1, 0, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time_1_State,
  // Path
  Switch_2_Event_1_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 2, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_2_Event_1_Time_1_ResponsePath[] = {2, 3, 1, 0, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time_1_Response,
  // Path
  Switch_2_Event_1_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 2, Event 1, Time 1, Set Time Dep *********************************/
const uint8 Switch_2_Event_1_Time_1_Set_Time_Path[] = {2, 3, 1, 0, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time_1_Set_Time,
  // Path
  Switch_2_Event_1_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 2, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_2_Event_1_Time_2_StatePath[] = {2, 3, 1, 0, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time_2_State,
  // Path
  Switch_2_Event_1_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 2, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_2_Event_1_Time_2_ResponsePath[] = {2, 3, 1, 0, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time_2_Response,
  // Path
  Switch_2_Event_1_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 2, Event 1, Time 2, Set Time Dep *********************************/
const uint8 Switch_2_Event_1_Time_2_Set_Time_Path[] = {2, 3, 1, 0, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time_2_Set_Time,
  // Path
  Switch_2_Event_1_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 2, Event 1, Date Dep *********************************************/
const uint8 Switch_2_Event_1_Date_Set_Date_Path[] = {2, 3, 1, 0, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Date_Set_Date,
  // Path
  Switch_2_Event_1_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 2, Event 1, Date Dep *********************************************/
const uint8 Switch_2_Event_1_Date_Set_Repeat_Path[] = {2, 3, 1, 0, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Date_Set_Repeat,
  // Path
  Switch_2_Event_1_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 2, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_2_Event_2_Time_1_StatePath[] = {2, 3, 1, 1, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time_1_State,
  // Path
  Switch_2_Event_2_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 2, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_2_Event_2_Time_1_ResponsePath[] = {2, 3, 1, 1, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time_1_Response,
  // Path
  Switch_2_Event_2_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 2, Event 2, Time 1, Set Time Dep *********************************/
const uint8 Switch_2_Event_2_Time_1_Set_Time_Path[] = {2, 3, 1, 1, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time_1_Set_Time,
  // Path
  Switch_2_Event_2_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 2, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_2_Event_2_Time_2_StatePath[] = {2, 3, 1, 1, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time_2_State,
  // Path
  Switch_2_Event_2_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 2, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_2_Event_2_Time_2_ResponsePath[] = {2, 3, 1, 1, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time_2_Response,
  // Path
  Switch_2_Event_2_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 2, Event 2, Time 2, Set Time Dep *********************************/
const uint8 Switch_2_Event_2_Time_2_Set_Time_Path[] = {2, 3, 1, 1, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time_2_Set_Time,
  // Path
  Switch_2_Event_2_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 2, Event 2, Date Dep *********************************************/
const uint8 Switch_2_Event_2_Date_Set_Date_Path[] = {2, 3, 1, 1, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Date_Set_Date,
  // Path
  Switch_2_Event_2_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 2, Event 2, Date Dep *********************************************/
const uint8 Switch_2_Event_2_Date_Set_Repeat_Path[] = {2, 3, 1, 1, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Date_Set_Repeat,
  // Path
  Switch_2_Event_2_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 2, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_2_Event_3_Time_1_StatePath[] = {2, 3, 1, 2, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time_1_State,
  // Path
  Switch_2_Event_3_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 2, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_2_Event_3_Time_1_ResponsePath[] = {2, 3, 1, 2, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time_1_Response,
  // Path
  Switch_2_Event_3_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 2, Event 3, Time 1, Set Time Dep *********************************/
const uint8 Switch_2_Event_3_Time_1_Set_Time_Path[] = {2, 3, 1, 2, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time_1_Set_Time,
  // Path
  Switch_2_Event_3_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 2, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_2_Event_3_Time_2_StatePath[] = {2, 3, 1, 2, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time_2_State,
  // Path
  Switch_2_Event_3_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 2, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_2_Event_3_Time_2_ResponsePath[] = {2, 3, 1, 2, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time_2_Response,
  // Path
  Switch_2_Event_3_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 2, Event 3, Time 2, Set Time Dep *********************************/
const uint8 Switch_2_Event_3_Time_2_Set_Time_Path[] = {2, 3, 1, 2, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time_2_Set_Time,
  // Path
  Switch_2_Event_3_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 2, Event 3, Date Dep *********************************************/
const uint8 Switch_2_Event_3_Date_Set_Date_Path[] = {2, 3, 1, 2, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Date_Set_Date,
  // Path
  Switch_2_Event_3_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 2, Event 3, Date Dep *********************************************/
const uint8 Switch_2_Event_3_Date_Set_Repeat_Path[] = {2, 3, 1, 2, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Date_Set_Repeat,
  // Path
  Switch_2_Event_3_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 2, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_2_Event_4_Time_1_StatePath[] = {2, 3, 1, 3, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time_1_State,
  // Path
  Switch_2_Event_4_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 2, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_2_Event_4_Time_1_ResponsePath[] = {2, 3, 1, 3, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time_1_Response,
  // Path
  Switch_2_Event_4_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 2, Event 4, Time 1, Set Time Dep *********************************/
const uint8 Switch_2_Event_4_Time_1_Set_Time_Path[] = {2, 3, 1, 3, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time_1_Set_Time,
  // Path
  Switch_2_Event_4_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 2, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_2_Event_4_Time_2_StatePath[] = {2, 3, 1, 3, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time_2_State,
  // Path
  Switch_2_Event_4_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 2, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_2_Event_4_Time_2_ResponsePath[] = {2, 3, 1, 3, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time_2_Response,
  // Path
  Switch_2_Event_4_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 2, Event 4, Time 2, Set Time Dep *********************************/
const uint8 Switch_2_Event_4_Time_2_Set_Time_Path[] = {2, 3, 1, 3, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time_2_Set_Time,
  // Path
  Switch_2_Event_4_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 2, Event 4, Date Dep *********************************************/
const uint8 Switch_2_Event_4_Date_Set_Date_Path[] = {2, 3, 1, 3, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Date_Set_Date,
  // Path
  Switch_2_Event_4_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 2, Event 4, Date Dep *********************************************/
const uint8 Switch_2_Event_4_Date_Set_Repeat_Path[] = {2, 3, 1, 3, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Date_Set_Repeat,
  // Path
  Switch_2_Event_4_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/*******************************************************************************
 * Switch 3
 ******************************************************************************/

/**** Switch 3, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_3_Event_1_Time_1_StatePath[] = {2, 3, 2, 0, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time_1_State,
  // Path
  Switch_3_Event_1_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 3, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_3_Event_1_Time_1_ResponsePath[] = {2, 3, 2, 0, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time_1_Response,
  // Path
  Switch_3_Event_1_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 3, Event 1, Time 1, Set Time Dep *********************************/
const uint8 Switch_3_Event_1_Time_1_Set_Time_Path[] = {2, 3, 2, 0, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time_1_Set_Time,
  // Path
  Switch_3_Event_1_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 3, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_3_Event_1_Time_2_StatePath[] = {2, 3, 2, 0, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time_2_State,
  // Path
  Switch_3_Event_1_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 3, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_3_Event_1_Time_2_ResponsePath[] = {2, 3, 2, 0, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time_2_Response,
  // Path
  Switch_3_Event_1_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 3, Event 1, Time 2, Set Time Dep *********************************/
const uint8 Switch_3_Event_1_Time_2_Set_Time_Path[] = {2, 3, 2, 0, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time_2_Set_Time,
  // Path
  Switch_3_Event_1_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 3, Event 1, Date Dep *********************************************/
const uint8 Switch_3_Event_1_Date_Set_Date_Path[] = {2, 3, 2, 0, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Date_Set_Date,
  // Path
  Switch_3_Event_1_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 3, Event 1, Date Dep *********************************************/
const uint8 Switch_3_Event_1_Date_Set_Repeat_Path[] = {2, 3, 2, 0, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Date_Set_Repeat,
  // Path
  Switch_3_Event_1_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 3, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_3_Event_2_Time_1_StatePath[] = {2, 3, 2, 1, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time_1_State,
  // Path
  Switch_3_Event_2_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 3, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_3_Event_2_Time_1_ResponsePath[] = {2, 3, 2, 1, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time_1_Response,
  // Path
  Switch_3_Event_2_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 3, Event 2, Time 1, Set Time Dep *********************************/
const uint8 Switch_3_Event_2_Time_1_Set_Time_Path[] = {2, 3, 2, 1, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time_1_Set_Time,
  // Path
  Switch_3_Event_2_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 3, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_3_Event_2_Time_2_StatePath[] = {2, 3, 2, 1, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time_2_State,
  // Path
  Switch_3_Event_2_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 3, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_3_Event_2_Time_2_ResponsePath[] = {2, 3, 2, 1, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time_2_Response,
  // Path
  Switch_3_Event_2_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 3, Event 2, Time 2, Set Time Dep *********************************/
const uint8 Switch_3_Event_2_Time_2_Set_Time_Path[] = {2, 3, 2, 1, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time_2_Set_Time,
  // Path
  Switch_3_Event_2_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 3, Event 2, Date Dep *********************************************/
const uint8 Switch_3_Event_2_Date_Set_Date_Path[] = {2, 3, 2, 1, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Date_Set_Date,
  // Path
  Switch_3_Event_2_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 3, Event 2, Date Dep *********************************************/
const uint8 Switch_3_Event_2_Date_Set_Repeat_Path[] = {2, 3, 2, 1, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Date_Set_Repeat,
  // Path
  Switch_3_Event_2_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 3, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_3_Event_3_Time_1_StatePath[] = {2, 3, 2, 2, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time_1_State,
  // Path
  Switch_3_Event_3_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 3, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_3_Event_3_Time_1_ResponsePath[] = {2, 3, 2, 2, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time_1_Response,
  // Path
  Switch_3_Event_3_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 3, Event 3, Time 1, Set Time Dep *********************************/
const uint8 Switch_3_Event_3_Time_1_Set_Time_Path[] = {2, 3, 2, 2, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time_1_Set_Time,
  // Path
  Switch_3_Event_3_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 3, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_3_Event_3_Time_2_StatePath[] = {2, 3, 2, 2, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time_2_State,
  // Path
  Switch_3_Event_3_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 3, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_3_Event_3_Time_2_ResponsePath[] = {2, 3, 2, 2, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time_2_Response,
  // Path
  Switch_3_Event_3_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 3, Event 3, Time 2, Set Time Dep *********************************/
const uint8 Switch_3_Event_3_Time_2_Set_Time_Path[] = {2, 3, 2, 2, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time_2_Set_Time,
  // Path
  Switch_3_Event_3_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 3, Event 3, Date Dep *********************************************/
const uint8 Switch_3_Event_3_Date_Set_Date_Path[] = {2, 3, 2, 2, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Date_Set_Date,
  // Path
  Switch_3_Event_3_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 3, Event 3, Date Dep *********************************************/
const uint8 Switch_3_Event_3_Date_Set_Repeat_Path[] = {2, 3, 2, 2, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Date_Set_Repeat,
  // Path
  Switch_3_Event_3_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 3, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_3_Event_4_Time_1_StatePath[] = {2, 3, 2, 3, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time_1_State,
  // Path
  Switch_3_Event_4_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 3, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_3_Event_4_Time_1_ResponsePath[] = {2, 3, 2, 3, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time_1_Response,
  // Path
  Switch_3_Event_4_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 3, Event 4, Time 1, Set Time Dep *********************************/
const uint8 Switch_3_Event_4_Time_1_Set_Time_Path[] = {2, 3, 2, 3, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time_1_Set_Time,
  // Path
  Switch_3_Event_4_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 3, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_3_Event_4_Time_2_StatePath[] = {2, 3, 2, 3, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time_2_State,
  // Path
  Switch_3_Event_4_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 3, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_3_Event_4_Time_2_ResponsePath[] = {2, 3, 2, 3, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time_2_Response,
  // Path
  Switch_3_Event_4_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 3, Event 4, Time 2, Set Time Dep *********************************/
const uint8 Switch_3_Event_4_Time_2_Set_Time_Path[] = {2, 3, 2, 3, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time_2_Set_Time,
  // Path
  Switch_3_Event_4_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 3, Event 4, Date Dep *********************************************/
const uint8 Switch_3_Event_4_Date_Set_Date_Path[] = {2, 3, 2, 3, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Date_Set_Date,
  // Path
  Switch_3_Event_4_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 3, Event 4, Date Dep *********************************************/
const uint8 Switch_3_Event_4_Date_Set_Repeat_Path[] = {2, 3, 2, 3, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Date_Set_Repeat,
  // Path
  Switch_3_Event_4_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/*******************************************************************************
 * Switch 4
 ******************************************************************************/

/**** Switch 4, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_4_Event_1_Time_1_StatePath[] = {2, 3, 3, 0, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time_1_State,
  // Path
  Switch_4_Event_1_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 4, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_4_Event_1_Time_1_ResponsePath[] = {2, 3, 3, 0, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time_1_Response,
  // Path
  Switch_4_Event_1_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 4, Event 1, Time 1, Set Time Dep *********************************/
const uint8 Switch_4_Event_1_Time_1_Set_Time_Path[] = {2, 3, 3, 0, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time_1_Set_Time,
  // Path
  Switch_4_Event_1_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 4, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_4_Event_1_Time_2_StatePath[] = {2, 3, 3, 0, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time_2_State,
  // Path
  Switch_4_Event_1_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 4, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_4_Event_1_Time_2_ResponsePath[] = {2, 3, 3, 0, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time_2_Response,
  // Path
  Switch_4_Event_1_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 4, Event 1, Time 2, Set Time Dep *********************************/
const uint8 Switch_4_Event_1_Time_2_Set_Time_Path[] = {2, 3, 3, 0, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time_2_Set_Time,
  // Path
  Switch_4_Event_1_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 4, Event 1, Date Dep *********************************************/
const uint8 Switch_4_Event_1_Date_Set_Date_Path[] = {2, 3, 3, 0, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Date_Set_Date,
  // Path
  Switch_4_Event_1_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 4, Event 1, Date Dep *********************************************/
const uint8 Switch_4_Event_1_Date_Set_Repeat_Path[] = {2, 3, 3, 0, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Date_Set_Repeat,
  // Path
  Switch_4_Event_1_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 4, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_4_Event_2_Time_1_StatePath[] = {2, 3, 3, 1, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time_1_State,
  // Path
  Switch_4_Event_2_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 4, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_4_Event_2_Time_1_ResponsePath[] = {2, 3, 3, 1, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time_1_Response,
  // Path
  Switch_4_Event_2_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 4, Event 2, Time 1, Set Time Dep *********************************/
const uint8 Switch_4_Event_2_Time_1_Set_Time_Path[] = {2, 3, 3, 1, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time_1_Set_Time,
  // Path
  Switch_4_Event_2_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 4, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_4_Event_2_Time_2_StatePath[] = {2, 3, 3, 1, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time_2_State,
  // Path
  Switch_4_Event_2_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 4, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_4_Event_2_Time_2_ResponsePath[] = {2, 3, 3, 1, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time_2_Response,
  // Path
  Switch_4_Event_2_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 4, Event 2, Time 2, Set Time Dep *********************************/
const uint8 Switch_4_Event_2_Time_2_Set_Time_Path[] = {2, 3, 3, 1, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time_2_Set_Time,
  // Path
  Switch_4_Event_2_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 4, Event 2, Date Dep *********************************************/
const uint8 Switch_4_Event_2_Date_Set_Date_Path[] = {2, 3, 3, 1, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Date_Set_Date,
  // Path
  Switch_4_Event_2_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 4, Event 2, Date Dep *********************************************/
const uint8 Switch_4_Event_2_Date_Set_Repeat_Path[] = {2, 3, 3, 1, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Date_Set_Repeat,
  // Path
  Switch_4_Event_2_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 4, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_4_Event_3_Time_1_StatePath[] = {2, 3, 3, 2, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time_1_State,
  // Path
  Switch_4_Event_3_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 4, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_4_Event_3_Time_1_ResponsePath[] = {2, 3, 3, 2, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time_1_Response,
  // Path
  Switch_4_Event_3_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 4, Event 3, Time 1, Set Time Dep *********************************/
const uint8 Switch_4_Event_3_Time_1_Set_Time_Path[] = {2, 3, 3, 2, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time_1_Set_Time,
  // Path
  Switch_4_Event_3_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 4, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_4_Event_3_Time_2_StatePath[] = {2, 3, 3, 2, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time_2_State,
  // Path
  Switch_4_Event_3_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 4, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_4_Event_3_Time_2_ResponsePath[] = {2, 3, 3, 2, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time_2_Response,
  // Path
  Switch_4_Event_3_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 4, Event 3, Time 2, Set Time Dep *********************************/
const uint8 Switch_4_Event_3_Time_2_Set_Time_Path[] = {2, 3, 3, 2, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time_2_Set_Time,
  // Path
  Switch_4_Event_3_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 4, Event 3, Date Dep *********************************************/
const uint8 Switch_4_Event_3_Date_Set_Date_Path[] = {2, 3, 3, 2, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Date_Set_Date,
  // Path
  Switch_4_Event_3_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 4, Event 3, Date Dep *********************************************/
const uint8 Switch_4_Event_3_Date_Set_Repeat_Path[] = {2, 3, 3, 2, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Date_Set_Repeat,
  // Path
  Switch_4_Event_3_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 4, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_4_Event_4_Time_1_StatePath[] = {2, 3, 3, 3, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time_1_State,
  // Path
  Switch_4_Event_4_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 4, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_4_Event_4_Time_1_ResponsePath[] = {2, 3, 3, 3, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time_1_Response,
  // Path
  Switch_4_Event_4_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 4, Event 4, Time 1, Set Time Dep *********************************/
const uint8 Switch_4_Event_4_Time_1_Set_Time_Path[] = {2, 3, 3, 3, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time_1_Set_Time,
  // Path
  Switch_4_Event_4_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 4, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_4_Event_4_Time_2_StatePath[] = {2, 3, 3, 3, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time_2_State,
  // Path
  Switch_4_Event_4_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 4, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_4_Event_4_Time_2_ResponsePath[] = {2, 3, 3, 3, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time_2_Response,
  // Path
  Switch_4_Event_4_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 4, Event 4, Time 2, Set Time Dep *********************************/
const uint8 Switch_4_Event_4_Time_2_Set_Time_Path[] = {2, 3, 3, 3, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time_2_Set_Time,
  // Path
  Switch_4_Event_4_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 4, Event 4, Date Dep *********************************************/
const uint8 Switch_4_Event_4_Date_Set_Date_Path[] = {2, 3, 3, 3, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Date_Set_Date,
  // Path
  Switch_4_Event_4_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 4, Event 4, Date Dep *********************************************/
const uint8 Switch_4_Event_4_Date_Set_Repeat_Path[] = {2, 3, 3, 3, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Date_Set_Repeat,
  // Path
  Switch_4_Event_4_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/*******************************************************************************
 * Switch 5
 ******************************************************************************/

/**** Switch 5, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_5_Event_1_Time_1_StatePath[] = {2, 3, 4, 0, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time_1_State,
  // Path
  Switch_5_Event_1_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 5, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_5_Event_1_Time_1_ResponsePath[] = {2, 3, 4, 0, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time_1_Response,
  // Path
  Switch_5_Event_1_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 5, Event 1, Time 1, Set Time Dep *********************************/
const uint8 Switch_5_Event_1_Time_1_Set_Time_Path[] = {2, 3, 4, 0, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time_1_Set_Time,
  // Path
  Switch_5_Event_1_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 5, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_5_Event_1_Time_2_StatePath[] = {2, 3, 4, 0, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time_2_State,
  // Path
  Switch_5_Event_1_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 5, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_5_Event_1_Time_2_ResponsePath[] = {2, 3, 4, 0, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time_2_Response,
  // Path
  Switch_5_Event_1_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 5, Event 1, Time 2, Set Time Dep *********************************/
const uint8 Switch_5_Event_1_Time_2_Set_Time_Path[] = {2, 3, 4, 0, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time_2_Set_Time,
  // Path
  Switch_5_Event_1_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 5, Event 1, Date Dep *********************************************/
const uint8 Switch_5_Event_1_Date_Set_Date_Path[] = {2, 3, 4, 0, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Date_Set_Date,
  // Path
  Switch_5_Event_1_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 5, Event 1, Date Dep *********************************************/
const uint8 Switch_5_Event_1_Date_Set_Repeat_Path[] = {2, 3, 4, 0, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Date_Set_Repeat,
  // Path
  Switch_5_Event_1_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 5, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_5_Event_2_Time_1_StatePath[] = {2, 3, 4, 1, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time_1_State,
  // Path
  Switch_5_Event_2_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 5, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_5_Event_2_Time_1_ResponsePath[] = {2, 3, 4, 1, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time_1_Response,
  // Path
  Switch_5_Event_2_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 5, Event 2, Time 1, Set Time Dep *********************************/
const uint8 Switch_5_Event_2_Time_1_Set_Time_Path[] = {2, 3, 4, 1, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time_1_Set_Time,
  // Path
  Switch_5_Event_2_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 5, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_5_Event_2_Time_2_StatePath[] = {2, 3, 4, 1, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time_2_State,
  // Path
  Switch_5_Event_2_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 5, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_5_Event_2_Time_2_ResponsePath[] = {2, 3, 4, 1, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time_2_Response,
  // Path
  Switch_5_Event_2_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 5, Event 2, Time 2, Set Time Dep *********************************/
const uint8 Switch_5_Event_2_Time_2_Set_Time_Path[] = {2, 3, 4, 1, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time_2_Set_Time,
  // Path
  Switch_5_Event_2_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 5, Event 2, Date Dep *********************************************/
const uint8 Switch_5_Event_2_Date_Set_Date_Path[] = {2, 3, 4, 1, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Date_Set_Date,
  // Path
  Switch_5_Event_2_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 5, Event 2, Date Dep *********************************************/
const uint8 Switch_5_Event_2_Date_Set_Repeat_Path[] = {2, 3, 4, 1, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Date_Set_Repeat,
  // Path
  Switch_5_Event_2_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 5, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_5_Event_3_Time_1_StatePath[] = {2, 3, 4, 2, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time_1_State,
  // Path
  Switch_5_Event_3_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 5, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_5_Event_3_Time_1_ResponsePath[] = {2, 3, 4, 2, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time_1_Response,
  // Path
  Switch_5_Event_3_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 5, Event 3, Time 1, Set Time Dep *********************************/
const uint8 Switch_5_Event_3_Time_1_Set_Time_Path[] = {2, 3, 4, 2, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time_1_Set_Time,
  // Path
  Switch_5_Event_3_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 5, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_5_Event_3_Time_2_StatePath[] = {2, 3, 4, 2, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time_2_State,
  // Path
  Switch_5_Event_3_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 5, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_5_Event_3_Time_2_ResponsePath[] = {2, 3, 4, 2, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time_2_Response,
  // Path
  Switch_5_Event_3_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 5, Event 3, Time 2, Set Time Dep *********************************/
const uint8 Switch_5_Event_3_Time_2_Set_Time_Path[] = {2, 3, 4, 2, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time_2_Set_Time,
  // Path
  Switch_5_Event_3_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 5, Event 3, Date Dep *********************************************/
const uint8 Switch_5_Event_3_Date_Set_Date_Path[] = {2, 3, 4, 2, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Date_Set_Date,
  // Path
  Switch_5_Event_3_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 5, Event 3, Date Dep *********************************************/
const uint8 Switch_5_Event_3_Date_Set_Repeat_Path[] = {2, 3, 4, 2, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Date_Set_Repeat,
  // Path
  Switch_5_Event_3_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 5, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_5_Event_4_Time_1_StatePath[] = {2, 3, 4, 3, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time_1_State,
  // Path
  Switch_5_Event_4_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 5, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_5_Event_4_Time_1_ResponsePath[] = {2, 3, 4, 3, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time_1_Response,
  // Path
  Switch_5_Event_4_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 5, Event 4, Time 1, Set Time Dep *********************************/
const uint8 Switch_5_Event_4_Time_1_Set_Time_Path[] = {2, 3, 4, 3, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time_1_Set_Time,
  // Path
  Switch_5_Event_4_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 5, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_5_Event_4_Time_2_StatePath[] = {2, 3, 4, 3, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time_2_State,
  // Path
  Switch_5_Event_4_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 5, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_5_Event_4_Time_2_ResponsePath[] = {2, 3, 4, 3, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time_2_Response,
  // Path
  Switch_5_Event_4_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 5, Event 4, Time 2, Set Time Dep *********************************/
const uint8 Switch_5_Event_4_Time_2_Set_Time_Path[] = {2, 3, 4, 3, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time_2_Set_Time,
  // Path
  Switch_5_Event_4_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 5, Event 4, Date Dep *********************************************/
const uint8 Switch_5_Event_4_Date_Set_Date_Path[] = {2, 3, 4, 3, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Date_Set_Date,
  // Path
  Switch_5_Event_4_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 5, Event 4, Date Dep *********************************************/
const uint8 Switch_5_Event_4_Date_Set_Repeat_Path[] = {2, 3, 4, 3, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Date_Set_Repeat,
  // Path
  Switch_5_Event_4_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/*******************************************************************************
 * Switch 6
 ******************************************************************************/

/**** Switch 6, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_6_Event_1_Time_1_StatePath[] = {2, 3, 5, 0, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time_1_State,
  // Path
  Switch_6_Event_1_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 6, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_6_Event_1_Time_1_ResponsePath[] = {2, 3, 5, 0, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time_1_Response,
  // Path
  Switch_6_Event_1_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 6, Event 1, Time 1, Set Time Dep *********************************/
const uint8 Switch_6_Event_1_Time_1_Set_Time_Path[] = {2, 3, 5, 0, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time_1_Set_Time,
  // Path
  Switch_6_Event_1_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 6, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_6_Event_1_Time_2_StatePath[] = {2, 3, 5, 0, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time_2_State,
  // Path
  Switch_6_Event_1_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 6, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_6_Event_1_Time_2_ResponsePath[] = {2, 3, 5, 0, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time_2_Response,
  // Path
  Switch_6_Event_1_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 6, Event 1, Time 2, Set Time Dep *********************************/
const uint8 Switch_6_Event_1_Time_2_Set_Time_Path[] = {2, 3, 5, 0, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time_2_Set_Time,
  // Path
  Switch_6_Event_1_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 6, Event 1, Date Dep *********************************************/
const uint8 Switch_6_Event_1_Date_Set_Date_Path[] = {2, 3, 5, 0, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Date_Set_Date,
  // Path
  Switch_6_Event_1_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 6, Event 1, Date Dep *********************************************/
const uint8 Switch_6_Event_1_Date_Set_Repeat_Path[] = {2, 3, 5, 0, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Date_Set_Repeat,
  // Path
  Switch_6_Event_1_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 6, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_6_Event_2_Time_1_StatePath[] = {2, 3, 5, 1, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time_1_State,
  // Path
  Switch_6_Event_2_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 6, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_6_Event_2_Time_1_ResponsePath[] = {2, 3, 5, 1, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time_1_Response,
  // Path
  Switch_6_Event_2_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 6, Event 2, Time 1, Set Time Dep *********************************/
const uint8 Switch_6_Event_2_Time_1_Set_Time_Path[] = {2, 3, 5, 1, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time_1_Set_Time,
  // Path
  Switch_6_Event_2_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 6, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_6_Event_2_Time_2_StatePath[] = {2, 3, 5, 1, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time_2_State,
  // Path
  Switch_6_Event_2_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 6, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_6_Event_2_Time_2_ResponsePath[] = {2, 3, 5, 1, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time_2_Response,
  // Path
  Switch_6_Event_2_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 6, Event 2, Time 2, Set Time Dep *********************************/
const uint8 Switch_6_Event_2_Time_2_Set_Time_Path[] = {2, 3, 5, 1, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time_2_Set_Time,
  // Path
  Switch_6_Event_2_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 6, Event 2, Date Dep *********************************************/
const uint8 Switch_6_Event_2_Date_Set_Date_Path[] = {2, 3, 5, 1, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Date_Set_Date,
  // Path
  Switch_6_Event_2_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 6, Event 2, Date Dep *********************************************/
const uint8 Switch_6_Event_2_Date_Set_Repeat_Path[] = {2, 3, 5, 1, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Date_Set_Repeat,
  // Path
  Switch_6_Event_2_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 6, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_6_Event_3_Time_1_StatePath[] = {2, 3, 5, 2, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time_1_State,
  // Path
  Switch_6_Event_3_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 6, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_6_Event_3_Time_1_ResponsePath[] = {2, 3, 5, 2, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time_1_Response,
  // Path
  Switch_6_Event_3_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 6, Event 3, Time 1, Set Time Dep *********************************/
const uint8 Switch_6_Event_3_Time_1_Set_Time_Path[] = {2, 3, 5, 2, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time_1_Set_Time,
  // Path
  Switch_6_Event_3_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 6, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_6_Event_3_Time_2_StatePath[] = {2, 3, 5, 2, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time_2_State,
  // Path
  Switch_6_Event_3_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 6, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_6_Event_3_Time_2_ResponsePath[] = {2, 3, 5, 2, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time_2_Response,
  // Path
  Switch_6_Event_3_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 6, Event 3, Time 2, Set Time Dep *********************************/
const uint8 Switch_6_Event_3_Time_2_Set_Time_Path[] = {2, 3, 5, 2, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time_2_Set_Time,
  // Path
  Switch_6_Event_3_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 6, Event 3, Date Dep *********************************************/
const uint8 Switch_6_Event_3_Date_Set_Date_Path[] = {2, 3, 5, 2, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Date_Set_Date,
  // Path
  Switch_6_Event_3_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 6, Event 3, Date Dep *********************************************/
const uint8 Switch_6_Event_3_Date_Set_Repeat_Path[] = {2, 3, 5, 2, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Date_Set_Repeat,
  // Path
  Switch_6_Event_3_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/**** Switch 6, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_6_Event_4_Time_1_StatePath[] = {2, 3, 5, 3, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time_1_State,
  // Path
  Switch_6_Event_4_Time_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 6, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_6_Event_4_Time_1_ResponsePath[] = {2, 3, 5, 3, 1, 0, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time_1_Response,
  // Path
  Switch_6_Event_4_Time_1_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 6, Event 4, Time 1, Set Time Dep *********************************/
const uint8 Switch_6_Event_4_Time_1_Set_Time_Path[] = {2, 3, 5, 3, 1, 0, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time_1_Set_Time,
  // Path
  Switch_6_Event_4_Time_1_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 6, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_6_Event_4_Time_2_StatePath[] = {2, 3, 5, 3, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time_2_State,
  // Path
  Switch_6_Event_4_Time_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  Time_State_Name
);

/**** Switch 6, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_6_Event_4_Time_2_ResponsePath[] = {2, 3, 5, 3, 1, 0, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time_2_Response,
  // Path
  Switch_6_Event_4_Time_2_ResponsePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  Time_Response_Name
);

/**** Switch 6, Event 4, Time 2, Set Time Dep *********************************/
const uint8 Switch_6_Event_4_Time_2_Set_Time_Path[] = {2, 3, 5, 3, 1, 0, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time_2_Set_Time,
  // Path
  Switch_6_Event_4_Time_2_Set_Time_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Set_Time,
  // String
  Set_Time_Name
);

/**** Switch 6, Event 4, Date Dep *********************************************/
const uint8 Switch_6_Event_4_Date_Set_Date_Path[] = {2, 3, 5, 3, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Date_Set_Date,
  // Path
  Switch_6_Event_4_Date_Set_Date_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Date,
  // String
  Set_Date_Name
);

/**** Switch 6, Event 4, Date Dep *********************************************/
const uint8 Switch_6_Event_4_Date_Set_Repeat_Path[] = {2, 3, 5, 3, 1, 0, 2, 1};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Date_Set_Repeat,
  // Path
  Switch_6_Event_4_Date_Set_Repeat_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  Set_Repeat_Name
);

/*******************************************************************************
 * Level 9
 ******************************************************************************/

/*******************************************************************************
 * Switch 1
 ******************************************************************************/

/**** Switch 1, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_1_Set_StatePath[] = {2, 3, 0, 0, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_1_Set_State,
  // Path
  Switch_1_Event_1_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 1, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_1_Event_1_Time_2_Set_StatePath[] = {2, 3, 0, 0, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_2_Set_State,
  // Path
  Switch_1_Event_1_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 1, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_1_Event_1_Time_1_Set_ResponsePath[] = {2, 3, 0, 0, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_1_Set_Response,
  // Path
  Switch_1_Event_1_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 1, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_1_Event_1_Time_2_Set_ResponsePath[] = {2, 3, 0, 0, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Time_2_Set_Response,
  // Path
  Switch_1_Event_1_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 1, Event 1, Time 1, State Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Time_1_Set_Time_Path[] = {2, 3, 0, 0, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_1_Set_Time,
  // Path
  Setting_Switch_1_Event_1_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 1, Event 1, Time 2, State Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Time_2_Set_Time_Path[] = {2, 3, 0, 0, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Time_2_Set_Time,
  // Path
  Setting_Switch_1_Event_1_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 1, Event 1, Date Dep *********************************************/
const uint8 Setting_Switch_1_Event_1_Date_Set_Date_Path[] = {2, 3, 0, 0, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Date_Set_Date,
  // Path
  Setting_Switch_1_Event_1_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_1_Event_1_Date_Set_Repeat_Path[] = {2, 3, 0, 0, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Date_Set_Repeat,
  // Path
  Setting_Switch_1_Event_1_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 1, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_2_Time_1_Set_StatePath[] = {2, 3, 0, 1, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time_1_Set_State,
  // Path
  Switch_1_Event_2_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 1, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_1_Event_2_Time_2_Set_StatePath[] = {2, 3, 0, 1, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time_2_Set_State,
  // Path
  Switch_1_Event_2_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 1, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_1_Event_2_Time_1_Set_ResponsePath[] = {2, 3, 0, 1, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time_1_Set_Response,
  // Path
  Switch_1_Event_2_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 1, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_1_Event_2_Time_2_Set_ResponsePath[] = {2, 3, 0, 1, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_2_Time_2_Set_Response,
  // Path
  Switch_1_Event_2_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 1, Event 2, Time 1, State Dep ************************************/
const uint8 Setting_Switch_1_Event_2_Time_1_Set_Time_Path[] = {2, 3, 0, 1, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_2_Time_1_Set_Time,
  // Path
  Setting_Switch_1_Event_2_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 1, Event 2, Time 2, State Dep ************************************/
const uint8 Setting_Switch_1_Event_2_Time_2_Set_Time_Path[] = {2, 3, 0, 1, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_2_Time_2_Set_Time,
  // Path
  Setting_Switch_1_Event_2_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 1, Event 2, Date Dep *********************************************/
const uint8 Setting_Switch_1_Event_2_Date_Set_Date_Path[] = {2, 3, 0, 1, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_2_Date_Set_Date,
  // Path
  Setting_Switch_1_Event_2_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_1_Event_2_Date_Set_Repeat_Path[] = {2, 3, 0, 1, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_2_Date_Set_Repeat,
  // Path
  Setting_Switch_1_Event_2_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 1, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_3_Time_1_Set_StatePath[] = {2, 3, 0, 2, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time_1_Set_State,
  // Path
  Switch_1_Event_3_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 1, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_1_Event_3_Time_2_Set_StatePath[] = {2, 3, 0, 2, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time_2_Set_State,
  // Path
  Switch_1_Event_3_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 1, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_1_Event_3_Time_1_Set_ResponsePath[] = {2, 3, 0, 2, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time_1_Set_Response,
  // Path
  Switch_1_Event_3_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 1, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_1_Event_3_Time_2_Set_ResponsePath[] = {2, 3, 0, 2, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_3_Time_2_Set_Response,
  // Path
  Switch_1_Event_3_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 1, Event 3, Time 1, State Dep ************************************/
const uint8 Setting_Switch_1_Event_3_Time_1_Set_Time_Path[] = {2, 3, 0, 2, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_3_Time_1_Set_Time,
  // Path
  Setting_Switch_1_Event_3_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 1, Event 3, Time 2, State Dep ************************************/
const uint8 Setting_Switch_1_Event_3_Time_2_Set_Time_Path[] = {2, 3, 0, 2, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_3_Time_2_Set_Time,
  // Path
  Setting_Switch_1_Event_3_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 1, Event 3, Date Dep *********************************************/
const uint8 Setting_Switch_1_Event_3_Date_Set_Date_Path[] = {2, 3, 0, 2, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_3_Date_Set_Date,
  // Path
  Setting_Switch_1_Event_3_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_1_Event_3_Date_Set_Repeat_Path[] = {2, 3, 0, 2, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_3_Date_Set_Repeat,
  // Path
  Setting_Switch_1_Event_3_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 1, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_1_Event_4_Time_1_Set_StatePath[] = {2, 3, 0, 3, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time_1_Set_State,
  // Path
  Switch_1_Event_4_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 1, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_1_Event_4_Time_2_Set_StatePath[] = {2, 3, 0, 3, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time_2_Set_State,
  // Path
  Switch_1_Event_4_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 1, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_1_Event_4_Time_1_Set_ResponsePath[] = {2, 3, 0, 3, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time_1_Set_Response,
  // Path
  Switch_1_Event_4_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 1, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_1_Event_4_Time_2_Set_ResponsePath[] = {2, 3, 0, 3, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_4_Time_2_Set_Response,
  // Path
  Switch_1_Event_4_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 1, Event 4, Time 1, State Dep ************************************/
const uint8 Setting_Switch_1_Event_4_Time_1_Set_Time_Path[] = {2, 3, 0, 3, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_4_Time_1_Set_Time,
  // Path
  Setting_Switch_1_Event_4_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 1, Event 4, Time 2, State Dep ************************************/
const uint8 Setting_Switch_1_Event_4_Time_2_Set_Time_Path[] = {2, 3, 0, 3, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_4_Time_2_Set_Time,
  // Path
  Setting_Switch_1_Event_4_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 1, Event 4, Date Dep *********************************************/
const uint8 Setting_Switch_1_Event_4_Date_Set_Date_Path[] = {2, 3, 0, 3, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_4_Date_Set_Date,
  // Path
  Setting_Switch_1_Event_4_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_1_Event_4_Date_Set_Repeat_Path[] = {2, 3, 0, 3, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_4_Date_Set_Repeat,
  // Path
  Setting_Switch_1_Event_4_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/*******************************************************************************
 * Switch 2
 ******************************************************************************/

/**** Switch 2, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_2_Event_1_Time_1_Set_StatePath[] = {2, 3, 1, 0, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time_1_Set_State,
  // Path
  Switch_2_Event_1_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 2, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_2_Event_1_Time_2_Set_StatePath[] = {2, 3, 1, 0, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time_2_Set_State,
  // Path
  Switch_2_Event_1_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 2, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_2_Event_1_Time_1_Set_ResponsePath[] = {2, 3, 1, 0, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time_1_Set_Response,
  // Path
  Switch_2_Event_1_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 2, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_2_Event_1_Time_2_Set_ResponsePath[] = {2, 3, 1, 0, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_1_Time_2_Set_Response,
  // Path
  Switch_2_Event_1_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 2, Event 1, Time 1, State Dep ************************************/
const uint8 Setting_Switch_2_Event_1_Time_1_Set_Time_Path[] = {2, 3, 1, 0, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_1_Time_1_Set_Time,
  // Path
  Setting_Switch_2_Event_1_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 2, Event 1, Time 2, State Dep ************************************/
const uint8 Setting_Switch_2_Event_1_Time_2_Set_Time_Path[] = {2, 3, 1, 0, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_1_Time_2_Set_Time,
  // Path
  Setting_Switch_2_Event_1_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 2, Event 1, Date Dep *********************************************/
const uint8 Setting_Switch_2_Event_1_Date_Set_Date_Path[] = {2, 3, 1, 0, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_1_Date_Set_Date,
  // Path
  Setting_Switch_2_Event_1_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_2_Event_1_Date_Set_Repeat_Path[] = {2, 3, 1, 0, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_1_Date_Set_Repeat,
  // Path
  Setting_Switch_2_Event_1_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 2, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_2_Event_2_Time_1_Set_StatePath[] = {2, 3, 1, 1, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time_1_Set_State,
  // Path
  Switch_2_Event_2_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 2, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_2_Event_2_Time_2_Set_StatePath[] = {2, 3, 1, 1, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time_2_Set_State,
  // Path
  Switch_2_Event_2_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 2, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_2_Event_2_Time_1_Set_ResponsePath[] = {2, 3, 1, 1, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time_1_Set_Response,
  // Path
  Switch_2_Event_2_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 2, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_2_Event_2_Time_2_Set_ResponsePath[] = {2, 3, 1, 1, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_2_Time_2_Set_Response,
  // Path
  Switch_2_Event_2_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 2, Event 2, Time 1, State Dep ************************************/
const uint8 Setting_Switch_2_Event_2_Time_1_Set_Time_Path[] = {2, 3, 1, 1, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_2_Time_1_Set_Time,
  // Path
  Setting_Switch_2_Event_2_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 2, Event 2, Time 2, State Dep ************************************/
const uint8 Setting_Switch_2_Event_2_Time_2_Set_Time_Path[] = {2, 3, 1, 1, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_2_Time_2_Set_Time,
  // Path
  Setting_Switch_2_Event_2_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 2, Event 2, Date Dep *********************************************/
const uint8 Setting_Switch_2_Event_2_Date_Set_Date_Path[] = {2, 3, 1, 1, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_2_Date_Set_Date,
  // Path
  Setting_Switch_2_Event_2_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_2_Event_2_Date_Set_Repeat_Path[] = {2, 3, 1, 1, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_2_Date_Set_Repeat,
  // Path
  Setting_Switch_2_Event_2_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 2, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_2_Event_3_Time_1_Set_StatePath[] = {2, 3, 1, 2, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time_1_Set_State,
  // Path
  Switch_2_Event_3_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 2, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_2_Event_3_Time_2_Set_StatePath[] = {2, 3, 1, 2, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time_2_Set_State,
  // Path
  Switch_2_Event_3_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 2, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_2_Event_3_Time_1_Set_ResponsePath[] = {2, 3, 1, 2, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time_1_Set_Response,
  // Path
  Switch_2_Event_3_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 2, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_2_Event_3_Time_2_Set_ResponsePath[] = {2, 3, 1, 2, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_3_Time_2_Set_Response,
  // Path
  Switch_2_Event_3_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 2, Event 3, Time 1, State Dep ************************************/
const uint8 Setting_Switch_2_Event_3_Time_1_Set_Time_Path[] = {2, 3, 1, 2, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_3_Time_1_Set_Time,
  // Path
  Setting_Switch_2_Event_3_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 2, Event 3, Time 2, State Dep ************************************/
const uint8 Setting_Switch_2_Event_3_Time_2_Set_Time_Path[] = {2, 3, 1, 2, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_3_Time_2_Set_Time,
  // Path
  Setting_Switch_2_Event_3_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 2, Event 3, Date Dep *********************************************/
const uint8 Setting_Switch_2_Event_3_Date_Set_Date_Path[] = {2, 3, 1, 2, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_3_Date_Set_Date,
  // Path
  Setting_Switch_2_Event_3_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_2_Event_3_Date_Set_Repeat_Path[] = {2, 3, 1, 2, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_3_Date_Set_Repeat,
  // Path
  Setting_Switch_2_Event_3_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 2, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_2_Event_4_Time_1_Set_StatePath[] = {2, 3, 1, 3, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time_1_Set_State,
  // Path
  Switch_2_Event_4_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 2, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_2_Event_4_Time_2_Set_StatePath[] = {2, 3, 1, 3, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time_2_Set_State,
  // Path
  Switch_2_Event_4_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 2, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_2_Event_4_Time_1_Set_ResponsePath[] = {2, 3, 1, 3, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time_1_Set_Response,
  // Path
  Switch_2_Event_4_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 2, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_2_Event_4_Time_2_Set_ResponsePath[] = {2, 3, 1, 3, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_2_Event_4_Time_2_Set_Response,
  // Path
  Switch_2_Event_4_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 2, Event 4, Time 1, State Dep ************************************/
const uint8 Setting_Switch_2_Event_4_Time_1_Set_Time_Path[] = {2, 3, 1, 3, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_4_Time_1_Set_Time,
  // Path
  Setting_Switch_2_Event_4_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 2, Event 4, Time 2, State Dep ************************************/
const uint8 Setting_Switch_2_Event_4_Time_2_Set_Time_Path[] = {2, 3, 1, 3, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_4_Time_2_Set_Time,
  // Path
  Setting_Switch_2_Event_4_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 2, Event 4, Date Dep *********************************************/
const uint8 Setting_Switch_2_Event_4_Date_Set_Date_Path[] = {2, 3, 1, 3, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_4_Date_Set_Date,
  // Path
  Setting_Switch_2_Event_4_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_2_Event_4_Date_Set_Repeat_Path[] = {2, 3, 1, 3, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_2_Event_4_Date_Set_Repeat,
  // Path
  Setting_Switch_2_Event_4_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/*******************************************************************************
 * Switch 3
 ******************************************************************************/

/**** Switch 3, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_3_Event_1_Time_1_Set_StatePath[] = {2, 3, 2, 0, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time_1_Set_State,
  // Path
  Switch_3_Event_1_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 3, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_3_Event_1_Time_2_Set_StatePath[] = {2, 3, 2, 0, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time_2_Set_State,
  // Path
  Switch_3_Event_1_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 3, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_3_Event_1_Time_1_Set_ResponsePath[] = {2, 3, 2, 0, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time_1_Set_Response,
  // Path
  Switch_3_Event_1_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 3, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_3_Event_1_Time_2_Set_ResponsePath[] = {2, 3, 2, 0, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_1_Time_2_Set_Response,
  // Path
  Switch_3_Event_1_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 3, Event 1, Time 1, State Dep ************************************/
const uint8 Setting_Switch_3_Event_1_Time_1_Set_Time_Path[] = {2, 3, 2, 0, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_1_Time_1_Set_Time,
  // Path
  Setting_Switch_3_Event_1_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 3, Event 1, Time 2, State Dep ************************************/
const uint8 Setting_Switch_3_Event_1_Time_2_Set_Time_Path[] = {2, 3, 2, 0, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_1_Time_2_Set_Time,
  // Path
  Setting_Switch_3_Event_1_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 3, Event 1, Date Dep *********************************************/
const uint8 Setting_Switch_3_Event_1_Date_Set_Date_Path[] = {2, 3, 2, 0, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_1_Date_Set_Date,
  // Path
  Setting_Switch_3_Event_1_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_3_Event_1_Date_Set_Repeat_Path[] = {2, 3, 2, 0, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_1_Date_Set_Repeat,
  // Path
  Setting_Switch_3_Event_1_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 3, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_3_Event_2_Time_1_Set_StatePath[] = {2, 3, 2, 1, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time_1_Set_State,
  // Path
  Switch_3_Event_2_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 3, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_3_Event_2_Time_2_Set_StatePath[] = {2, 3, 2, 1, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time_2_Set_State,
  // Path
  Switch_3_Event_2_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 3, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_3_Event_2_Time_1_Set_ResponsePath[] = {2, 3, 2, 1, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time_1_Set_Response,
  // Path
  Switch_3_Event_2_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 3, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_3_Event_2_Time_2_Set_ResponsePath[] = {2, 3, 2, 1, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_2_Time_2_Set_Response,
  // Path
  Switch_3_Event_2_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 3, Event 2, Time 1, State Dep ************************************/
const uint8 Setting_Switch_3_Event_2_Time_1_Set_Time_Path[] = {2, 3, 2, 1, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_2_Time_1_Set_Time,
  // Path
  Setting_Switch_3_Event_2_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 3, Event 2, Time 2, State Dep ************************************/
const uint8 Setting_Switch_3_Event_2_Time_2_Set_Time_Path[] = {2, 3, 2, 1, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_2_Time_2_Set_Time,
  // Path
  Setting_Switch_3_Event_2_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 3, Event 2, Date Dep *********************************************/
const uint8 Setting_Switch_3_Event_2_Date_Set_Date_Path[] = {2, 3, 2, 1, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_2_Date_Set_Date,
  // Path
  Setting_Switch_3_Event_2_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_3_Event_2_Date_Set_Repeat_Path[] = {2, 3, 2, 1, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_2_Date_Set_Repeat,
  // Path
  Setting_Switch_3_Event_2_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 3, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_3_Event_3_Time_1_Set_StatePath[] = {2, 3, 2, 2, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time_1_Set_State,
  // Path
  Switch_3_Event_3_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 3, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_3_Event_3_Time_2_Set_StatePath[] = {2, 3, 2, 2, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time_2_Set_State,
  // Path
  Switch_3_Event_3_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 3, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_3_Event_3_Time_1_Set_ResponsePath[] = {2, 3, 2, 2, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time_1_Set_Response,
  // Path
  Switch_3_Event_3_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 3, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_3_Event_3_Time_2_Set_ResponsePath[] = {2, 3, 2, 2, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_3_Time_2_Set_Response,
  // Path
  Switch_3_Event_3_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 3, Event 3, Time 1, State Dep ************************************/
const uint8 Setting_Switch_3_Event_3_Time_1_Set_Time_Path[] = {2, 3, 2, 2, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_3_Time_1_Set_Time,
  // Path
  Setting_Switch_3_Event_3_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 3, Event 3, Time 2, State Dep ************************************/
const uint8 Setting_Switch_3_Event_3_Time_2_Set_Time_Path[] = {2, 3, 2, 2, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_3_Time_2_Set_Time,
  // Path
  Setting_Switch_3_Event_3_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 3, Event 3, Date Dep *********************************************/
const uint8 Setting_Switch_3_Event_3_Date_Set_Date_Path[] = {2, 3, 2, 2, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_3_Date_Set_Date,
  // Path
  Setting_Switch_3_Event_3_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_3_Event_3_Date_Set_Repeat_Path[] = {2, 3, 2, 2, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_3_Date_Set_Repeat,
  // Path
  Setting_Switch_3_Event_3_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 3, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_3_Event_4_Time_1_Set_StatePath[] = {2, 3, 2, 3, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time_1_Set_State,
  // Path
  Switch_3_Event_4_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 3, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_3_Event_4_Time_2_Set_StatePath[] = {2, 3, 2, 3, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time_2_Set_State,
  // Path
  Switch_3_Event_4_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 3, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_3_Event_4_Time_1_Set_ResponsePath[] = {2, 3, 2, 3, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time_1_Set_Response,
  // Path
  Switch_3_Event_4_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 3, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_3_Event_4_Time_2_Set_ResponsePath[] = {2, 3, 2, 3, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_3_Event_4_Time_2_Set_Response,
  // Path
  Switch_3_Event_4_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 3, Event 4, Time 1, State Dep ************************************/
const uint8 Setting_Switch_3_Event_4_Time_1_Set_Time_Path[] = {2, 3, 2, 3, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_4_Time_1_Set_Time,
  // Path
  Setting_Switch_3_Event_4_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 3, Event 4, Time 2, State Dep ************************************/
const uint8 Setting_Switch_3_Event_4_Time_2_Set_Time_Path[] = {2, 3, 2, 3, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_4_Time_2_Set_Time,
  // Path
  Setting_Switch_3_Event_4_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 3, Event 4, Date Dep *********************************************/
const uint8 Setting_Switch_3_Event_4_Date_Set_Date_Path[] = {2, 3, 2, 3, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_4_Date_Set_Date,
  // Path
  Setting_Switch_3_Event_4_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_3_Event_4_Date_Set_Repeat_Path[] = {2, 3, 2, 3, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_3_Event_4_Date_Set_Repeat,
  // Path
  Setting_Switch_3_Event_4_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/*******************************************************************************
 * Switch 4
 ******************************************************************************/

/**** Switch 4, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_4_Event_1_Time_1_Set_StatePath[] = {2, 3, 3, 0, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time_1_Set_State,
  // Path
  Switch_4_Event_1_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 4, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_4_Event_1_Time_2_Set_StatePath[] = {2, 3, 3, 0, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time_2_Set_State,
  // Path
  Switch_4_Event_1_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 4, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_4_Event_1_Time_1_Set_ResponsePath[] = {2, 3, 3, 0, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time_1_Set_Response,
  // Path
  Switch_4_Event_1_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 4, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_4_Event_1_Time_2_Set_ResponsePath[] = {2, 3, 3, 0, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_1_Time_2_Set_Response,
  // Path
  Switch_4_Event_1_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 4, Event 1, Time 1, State Dep ************************************/
const uint8 Setting_Switch_4_Event_1_Time_1_Set_Time_Path[] = {2, 3, 3, 0, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_1_Time_1_Set_Time,
  // Path
  Setting_Switch_4_Event_1_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 4, Event 1, Time 2, State Dep ************************************/
const uint8 Setting_Switch_4_Event_1_Time_2_Set_Time_Path[] = {2, 3, 3, 0, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_1_Time_2_Set_Time,
  // Path
  Setting_Switch_4_Event_1_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 4, Event 1, Date Dep *********************************************/
const uint8 Setting_Switch_4_Event_1_Date_Set_Date_Path[] = {2, 3, 3, 0, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_1_Date_Set_Date,
  // Path
  Setting_Switch_4_Event_1_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_4_Event_1_Date_Set_Repeat_Path[] = {2, 3, 3, 0, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_1_Date_Set_Repeat,
  // Path
  Setting_Switch_4_Event_1_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 4, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_4_Event_2_Time_1_Set_StatePath[] = {2, 3, 3, 1, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time_1_Set_State,
  // Path
  Switch_4_Event_2_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 4, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_4_Event_2_Time_2_Set_StatePath[] = {2, 3, 3, 1, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time_2_Set_State,
  // Path
  Switch_4_Event_2_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 4, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_4_Event_2_Time_1_Set_ResponsePath[] = {2, 3, 3, 1, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time_1_Set_Response,
  // Path
  Switch_4_Event_2_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 4, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_4_Event_2_Time_2_Set_ResponsePath[] = {2, 3, 3, 1, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_2_Time_2_Set_Response,
  // Path
  Switch_4_Event_2_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 4, Event 2, Time 1, State Dep ************************************/
const uint8 Setting_Switch_4_Event_2_Time_1_Set_Time_Path[] = {2, 3, 3, 1, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_2_Time_1_Set_Time,
  // Path
  Setting_Switch_4_Event_2_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 4, Event 2, Time 2, State Dep ************************************/
const uint8 Setting_Switch_4_Event_2_Time_2_Set_Time_Path[] = {2, 3, 3, 1, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_2_Time_2_Set_Time,
  // Path
  Setting_Switch_4_Event_2_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 4, Event 2, Date Dep *********************************************/
const uint8 Setting_Switch_4_Event_2_Date_Set_Date_Path[] = {2, 3, 3, 1, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_2_Date_Set_Date,
  // Path
  Setting_Switch_4_Event_2_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_4_Event_2_Date_Set_Repeat_Path[] = {2, 3, 3, 1, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_2_Date_Set_Repeat,
  // Path
  Setting_Switch_4_Event_2_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 4, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_4_Event_3_Time_1_Set_StatePath[] = {2, 3, 3, 2, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time_1_Set_State,
  // Path
  Switch_4_Event_3_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 4, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_4_Event_3_Time_2_Set_StatePath[] = {2, 3, 3, 2, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time_2_Set_State,
  // Path
  Switch_4_Event_3_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 4, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_4_Event_3_Time_1_Set_ResponsePath[] = {2, 3, 3, 2, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time_1_Set_Response,
  // Path
  Switch_4_Event_3_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 4, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_4_Event_3_Time_2_Set_ResponsePath[] = {2, 3, 3, 2, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_3_Time_2_Set_Response,
  // Path
  Switch_4_Event_3_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 4, Event 3, Time 1, State Dep ************************************/
const uint8 Setting_Switch_4_Event_3_Time_1_Set_Time_Path[] = {2, 3, 3, 2, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_3_Time_1_Set_Time,
  // Path
  Setting_Switch_4_Event_3_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 4, Event 3, Time 2, State Dep ************************************/
const uint8 Setting_Switch_4_Event_3_Time_2_Set_Time_Path[] = {2, 3, 3, 2, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_3_Time_2_Set_Time,
  // Path
  Setting_Switch_4_Event_3_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 4, Event 3, Date Dep *********************************************/
const uint8 Setting_Switch_4_Event_3_Date_Set_Date_Path[] = {2, 3, 3, 2, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_3_Date_Set_Date,
  // Path
  Setting_Switch_4_Event_3_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_4_Event_3_Date_Set_Repeat_Path[] = {2, 3, 3, 2, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_3_Date_Set_Repeat,
  // Path
  Setting_Switch_4_Event_3_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 4, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_4_Event_4_Time_1_Set_StatePath[] = {2, 3, 3, 3, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time_1_Set_State,
  // Path
  Switch_4_Event_4_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 4, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_4_Event_4_Time_2_Set_StatePath[] = {2, 3, 3, 3, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time_2_Set_State,
  // Path
  Switch_4_Event_4_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 4, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_4_Event_4_Time_1_Set_ResponsePath[] = {2, 3, 3, 3, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time_1_Set_Response,
  // Path
  Switch_4_Event_4_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 4, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_4_Event_4_Time_2_Set_ResponsePath[] = {2, 3, 3, 3, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_4_Event_4_Time_2_Set_Response,
  // Path
  Switch_4_Event_4_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 4, Event 4, Time 1, State Dep ************************************/
const uint8 Setting_Switch_4_Event_4_Time_1_Set_Time_Path[] = {2, 3, 3, 3, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_4_Time_1_Set_Time,
  // Path
  Setting_Switch_4_Event_4_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 4, Event 4, Time 2, State Dep ************************************/
const uint8 Setting_Switch_4_Event_4_Time_2_Set_Time_Path[] = {2, 3, 3, 3, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_4_Time_2_Set_Time,
  // Path
  Setting_Switch_4_Event_4_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 4, Event 4, Date Dep *********************************************/
const uint8 Setting_Switch_4_Event_4_Date_Set_Date_Path[] = {2, 3, 3, 3, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_4_Date_Set_Date,
  // Path
  Setting_Switch_4_Event_4_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_4_Event_4_Date_Set_Repeat_Path[] = {2, 3, 3, 3, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_4_Event_4_Date_Set_Repeat,
  // Path
  Setting_Switch_4_Event_4_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/*******************************************************************************
 * Switch 5
 ******************************************************************************/

/**** Switch 5, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_5_Event_1_Time_1_Set_StatePath[] = {2, 3, 4, 0, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time_1_Set_State,
  // Path
  Switch_5_Event_1_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 5, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_5_Event_1_Time_2_Set_StatePath[] = {2, 3, 4, 0, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time_2_Set_State,
  // Path
  Switch_5_Event_1_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 5, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_5_Event_1_Time_1_Set_ResponsePath[] = {2, 3, 4, 0, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time_1_Set_Response,
  // Path
  Switch_5_Event_1_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 5, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_5_Event_1_Time_2_Set_ResponsePath[] = {2, 3, 4, 0, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_1_Time_2_Set_Response,
  // Path
  Switch_5_Event_1_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 5, Event 1, Time 1, State Dep ************************************/
const uint8 Setting_Switch_5_Event_1_Time_1_Set_Time_Path[] = {2, 3, 4, 0, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_1_Time_1_Set_Time,
  // Path
  Setting_Switch_5_Event_1_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 5, Event 1, Time 2, State Dep ************************************/
const uint8 Setting_Switch_5_Event_1_Time_2_Set_Time_Path[] = {2, 3, 4, 0, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_1_Time_2_Set_Time,
  // Path
  Setting_Switch_5_Event_1_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 5, Event 1, Date Dep *********************************************/
const uint8 Setting_Switch_5_Event_1_Date_Set_Date_Path[] = {2, 3, 4, 0, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_1_Date_Set_Date,
  // Path
  Setting_Switch_5_Event_1_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_5_Event_1_Date_Set_Repeat_Path[] = {2, 3, 4, 0, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_1_Date_Set_Repeat,
  // Path
  Setting_Switch_5_Event_1_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 5, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_5_Event_2_Time_1_Set_StatePath[] = {2, 3, 4, 1, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time_1_Set_State,
  // Path
  Switch_5_Event_2_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 5, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_5_Event_2_Time_2_Set_StatePath[] = {2, 3, 4, 1, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time_2_Set_State,
  // Path
  Switch_5_Event_2_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 5, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_5_Event_2_Time_1_Set_ResponsePath[] = {2, 3, 4, 1, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time_1_Set_Response,
  // Path
  Switch_5_Event_2_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 5, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_5_Event_2_Time_2_Set_ResponsePath[] = {2, 3, 4, 1, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_2_Time_2_Set_Response,
  // Path
  Switch_5_Event_2_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 5, Event 2, Time 1, State Dep ************************************/
const uint8 Setting_Switch_5_Event_2_Time_1_Set_Time_Path[] = {2, 3, 4, 1, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_2_Time_1_Set_Time,
  // Path
  Setting_Switch_5_Event_2_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 5, Event 2, Time 2, State Dep ************************************/
const uint8 Setting_Switch_5_Event_2_Time_2_Set_Time_Path[] = {2, 3, 4, 1, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_2_Time_2_Set_Time,
  // Path
  Setting_Switch_5_Event_2_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 5, Event 2, Date Dep *********************************************/
const uint8 Setting_Switch_5_Event_2_Date_Set_Date_Path[] = {2, 3, 4, 1, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_2_Date_Set_Date,
  // Path
  Setting_Switch_5_Event_2_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_5_Event_2_Date_Set_Repeat_Path[] = {2, 3, 4, 1, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_2_Date_Set_Repeat,
  // Path
  Setting_Switch_5_Event_2_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 5, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_5_Event_3_Time_1_Set_StatePath[] = {2, 3, 4, 2, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time_1_Set_State,
  // Path
  Switch_5_Event_3_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 5, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_5_Event_3_Time_2_Set_StatePath[] = {2, 3, 4, 2, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time_2_Set_State,
  // Path
  Switch_5_Event_3_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 5, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_5_Event_3_Time_1_Set_ResponsePath[] = {2, 3, 4, 2, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time_1_Set_Response,
  // Path
  Switch_5_Event_3_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 5, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_5_Event_3_Time_2_Set_ResponsePath[] = {2, 3, 4, 2, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_3_Time_2_Set_Response,
  // Path
  Switch_5_Event_3_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 5, Event 3, Time 1, State Dep ************************************/
const uint8 Setting_Switch_5_Event_3_Time_1_Set_Time_Path[] = {2, 3, 4, 2, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_3_Time_1_Set_Time,
  // Path
  Setting_Switch_5_Event_3_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 5, Event 3, Time 2, State Dep ************************************/
const uint8 Setting_Switch_5_Event_3_Time_2_Set_Time_Path[] = {2, 3, 4, 2, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_3_Time_2_Set_Time,
  // Path
  Setting_Switch_5_Event_3_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 5, Event 3, Date Dep *********************************************/
const uint8 Setting_Switch_5_Event_3_Date_Set_Date_Path[] = {2, 3, 4, 2, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_3_Date_Set_Date,
  // Path
  Setting_Switch_5_Event_3_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_5_Event_3_Date_Set_Repeat_Path[] = {2, 3, 4, 2, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_3_Date_Set_Repeat,
  // Path
  Setting_Switch_5_Event_3_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 5, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_5_Event_4_Time_1_Set_StatePath[] = {2, 3, 4, 3, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time_1_Set_State,
  // Path
  Switch_5_Event_4_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 5, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_5_Event_4_Time_2_Set_StatePath[] = {2, 3, 4, 3, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time_2_Set_State,
  // Path
  Switch_5_Event_4_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 5, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_5_Event_4_Time_1_Set_ResponsePath[] = {2, 3, 4, 3, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time_1_Set_Response,
  // Path
  Switch_5_Event_4_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 5, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_5_Event_4_Time_2_Set_ResponsePath[] = {2, 3, 4, 3, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_5_Event_4_Time_2_Set_Response,
  // Path
  Switch_5_Event_4_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 5, Event 4, Time 1, State Dep ************************************/
const uint8 Setting_Switch_5_Event_4_Time_1_Set_Time_Path[] = {2, 3, 4, 3, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_4_Time_1_Set_Time,
  // Path
  Setting_Switch_5_Event_4_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 5, Event 4, Time 2, State Dep ************************************/
const uint8 Setting_Switch_5_Event_4_Time_2_Set_Time_Path[] = {2, 3, 4, 3, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_4_Time_2_Set_Time,
  // Path
  Setting_Switch_5_Event_4_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 5, Event 4, Date Dep *********************************************/
const uint8 Setting_Switch_5_Event_4_Date_Set_Date_Path[] = {2, 3, 4, 3, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_4_Date_Set_Date,
  // Path
  Setting_Switch_5_Event_4_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_5_Event_4_Date_Set_Repeat_Path[] = {2, 3, 4, 3, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_5_Event_4_Date_Set_Repeat,
  // Path
  Setting_Switch_5_Event_4_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/*******************************************************************************
 * Switch 6
 ******************************************************************************/

/**** Switch 6, Event 1, Time 1, State Dep ************************************/
const uint8 Switch_6_Event_1_Time_1_Set_StatePath[] = {2, 3, 5, 0, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time_1_Set_State,
  // Path
  Switch_6_Event_1_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 6, Event 1, Time 2, State Dep ************************************/
const uint8 Switch_6_Event_1_Time_2_Set_StatePath[] = {2, 3, 5, 0, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time_2_Set_State,
  // Path
  Switch_6_Event_1_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 6, Event 1, Time 1, Response Dep ************************************/
const uint8 Switch_6_Event_1_Time_1_Set_ResponsePath[] = {2, 3, 5, 0, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time_1_Set_Response,
  // Path
  Switch_6_Event_1_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 6, Event 1, Time 2, Response Dep ************************************/
const uint8 Switch_6_Event_1_Time_2_Set_ResponsePath[] = {2, 3, 5, 0, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_1_Time_2_Set_Response,
  // Path
  Switch_6_Event_1_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 6, Event 1, Time 1, State Dep ************************************/
const uint8 Setting_Switch_6_Event_1_Time_1_Set_Time_Path[] = {2, 3, 5, 0, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_1_Time_1_Set_Time,
  // Path
  Setting_Switch_6_Event_1_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 6, Event 1, Time 2, State Dep ************************************/
const uint8 Setting_Switch_6_Event_1_Time_2_Set_Time_Path[] = {2, 3, 5, 0, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_1_Time_2_Set_Time,
  // Path
  Setting_Switch_6_Event_1_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 6, Event 1, Date Dep *********************************************/
const uint8 Setting_Switch_6_Event_1_Date_Set_Date_Path[] = {2, 3, 5, 0, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_1_Date_Set_Date,
  // Path
  Setting_Switch_6_Event_1_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_6_Event_1_Date_Set_Repeat_Path[] = {2, 3, 5, 0, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_1_Date_Set_Repeat,
  // Path
  Setting_Switch_6_Event_1_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 6, Event 2, Time 1, State Dep ************************************/
const uint8 Switch_6_Event_2_Time_1_Set_StatePath[] = {2, 3, 5, 1, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time_1_Set_State,
  // Path
  Switch_6_Event_2_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 6, Event 2, Time 2, State Dep ************************************/
const uint8 Switch_6_Event_2_Time_2_Set_StatePath[] = {2, 3, 5, 1, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time_2_Set_State,
  // Path
  Switch_6_Event_2_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 6, Event 2, Time 1, Response Dep ************************************/
const uint8 Switch_6_Event_2_Time_1_Set_ResponsePath[] = {2, 3, 5, 1, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time_1_Set_Response,
  // Path
  Switch_6_Event_2_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 6, Event 2, Time 2, Response Dep ************************************/
const uint8 Switch_6_Event_2_Time_2_Set_ResponsePath[] = {2, 3, 5, 1, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_2_Time_2_Set_Response,
  // Path
  Switch_6_Event_2_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 6, Event 2, Time 1, State Dep ************************************/
const uint8 Setting_Switch_6_Event_2_Time_1_Set_Time_Path[] = {2, 3, 5, 1, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_2_Time_1_Set_Time,
  // Path
  Setting_Switch_6_Event_2_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 6, Event 2, Time 2, State Dep ************************************/
const uint8 Setting_Switch_6_Event_2_Time_2_Set_Time_Path[] = {2, 3, 5, 1, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_2_Time_2_Set_Time,
  // Path
  Setting_Switch_6_Event_2_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 6, Event 2, Date Dep *********************************************/
const uint8 Setting_Switch_6_Event_2_Date_Set_Date_Path[] = {2, 3, 5, 1, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_2_Date_Set_Date,
  // Path
  Setting_Switch_6_Event_2_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_6_Event_2_Date_Set_Repeat_Path[] = {2, 3, 5, 1, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_2_Date_Set_Repeat,
  // Path
  Setting_Switch_6_Event_2_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 6, Event 3, Time 1, State Dep ************************************/
const uint8 Switch_6_Event_3_Time_1_Set_StatePath[] = {2, 3, 5, 2, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time_1_Set_State,
  // Path
  Switch_6_Event_3_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 6, Event 3, Time 2, State Dep ************************************/
const uint8 Switch_6_Event_3_Time_2_Set_StatePath[] = {2, 3, 5, 2, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time_2_Set_State,
  // Path
  Switch_6_Event_3_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 6, Event 3, Time 1, Response Dep ************************************/
const uint8 Switch_6_Event_3_Time_1_Set_ResponsePath[] = {2, 3, 5, 2, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time_1_Set_Response,
  // Path
  Switch_6_Event_3_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 6, Event 3, Time 2, Response Dep ************************************/
const uint8 Switch_6_Event_3_Time_2_Set_ResponsePath[] = {2, 3, 5, 2, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_3_Time_2_Set_Response,
  // Path
  Switch_6_Event_3_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 6, Event 3, Time 1, State Dep ************************************/
const uint8 Setting_Switch_6_Event_3_Time_1_Set_Time_Path[] = {2, 3, 5, 2, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_3_Time_1_Set_Time,
  // Path
  Setting_Switch_6_Event_3_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 6, Event 3, Time 2, State Dep ************************************/
const uint8 Setting_Switch_6_Event_3_Time_2_Set_Time_Path[] = {2, 3, 5, 2, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_3_Time_2_Set_Time,
  // Path
  Setting_Switch_6_Event_3_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 6, Event 3, Date Dep *********************************************/
const uint8 Setting_Switch_6_Event_3_Date_Set_Date_Path[] = {2, 3, 5, 2, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_3_Date_Set_Date,
  // Path
  Setting_Switch_6_Event_3_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_6_Event_3_Date_Set_Repeat_Path[] = {2, 3, 5, 2, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_3_Date_Set_Repeat,
  // Path
  Setting_Switch_6_Event_3_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

/**** Switch 6, Event 4, Time 1, State Dep ************************************/
const uint8 Switch_6_Event_4_Time_1_Set_StatePath[] = {2, 3, 5, 3, 1, 0, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time_1_Set_State,
  // Path
  Switch_6_Event_4_Time_1_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 6, Event 4, Time 2, State Dep ************************************/
const uint8 Switch_6_Event_4_Time_2_Set_StatePath[] = {2, 3, 5, 3, 1, 0, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time_2_Set_State,
  // Path
  Switch_6_Event_4_Time_2_Set_StatePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_State,
  // String
  ""
);

/**** Switch 6, Event 4, Time 1, Response Dep ************************************/
const uint8 Switch_6_Event_4_Time_1_Set_ResponsePath[] = {2, 3, 5, 3, 1, 0, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time_1_Set_Response,
  // Path
  Switch_6_Event_4_Time_1_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 6, Event 4, Time 2, Response Dep ************************************/
const uint8 Switch_6_Event_4_Time_2_Set_ResponsePath[] = {2, 3, 5, 3, 1, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_6_Event_4_Time_2_Set_Response,
  // Path
  Switch_6_Event_4_Time_2_Set_ResponsePath,
  // Max Level
  9,
  // Flags
  MENU_LAST_STATE | \
  MENU_NO_DISPLAY_UPDATE,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT | \
  UP_KEY_EVENT | \
  DOWN_KEY_EVENT,
  // Callback
  Menu_Time_Dep_Time_Response,
  // String
  ""
);

/**** Switch 6, Event 4, Time 1, State Dep ************************************/
const uint8 Setting_Switch_6_Event_4_Time_1_Set_Time_Path[] = {2, 3, 5, 3, 1, 0, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_4_Time_1_Set_Time,
  // Path
  Setting_Switch_6_Event_4_Time_1_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 6, Event 4, Time 2, State Dep ************************************/
const uint8 Setting_Switch_6_Event_4_Time_2_Set_Time_Path[] = {2, 3, 5, 3, 1, 0, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_4_Time_2_Set_Time,
  // Path
  Setting_Switch_6_Event_4_Time_2_Set_Time_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Set_Time,
  // String
  ""
);

/**** Switch 6, Event 4, Date Dep *********************************************/
const uint8 Setting_Switch_6_Event_4_Date_Set_Date_Path[] = {2, 3, 5, 3, 1, 0, 2, 0, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_4_Date_Set_Date,
  // Path
  Setting_Switch_6_Event_4_Date_Set_Date_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Date,
  // String
  ""
);

const uint8 Setting_Switch_6_Event_4_Date_Set_Repeat_Path[] = {2, 3, 5, 3, 1, 0, 2, 1, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_6_Event_4_Date_Set_Repeat,
  // Path
  Setting_Switch_6_Event_4_Date_Set_Repeat_Path,
  // Max Level
  9,
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
  Menu_Time_Dep_Date_Set_Repeat,
  // String
  ""
);

