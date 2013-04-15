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

#include "Temperature.h"

/**** Global Variables ****/
uint8 SetTempFlag = 0;
char Temp_1_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Temp_2_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Temp_State_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Temp_Response_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Set_Temp_Name[SWITCHES_SET_STRING_LENGTH] = {0};
char Set_Sensor_Name[SWITCHES_SET_STRING_LENGTH] = {0};

/**** Functions ****/

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Dep_Set_Temp_Name(void)
{
  FuncIN(MENU_TEMP_DEP_SET_TEMP_NAME);
  
  switch(SW_M_Event_g.Temp_1.State)
  {
    case SW_TEMP_ALARM_ON:
      strcpy(Temp_1_Name, "Temp 1 : ON");
      break;
    case SW_TEMP_ALARM_OFF:
      strcpy(Temp_1_Name, "Temp 1 : OFF");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }
  
  switch(SW_M_Event_g.Temp_2.State)
  {
    case SW_TEMP_ALARM_ON:
      strcpy(Temp_2_Name, "Temp 2 : ON");
      break;
    case SW_TEMP_ALARM_OFF:
      strcpy(Temp_2_Name, "Temp 2 : OFF");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }
  
  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_TEMP_NAME);
}
FUNC_REGISTER(MENU_TEMP_DEP_SET_TEMP_NAME, Menu_Temp_Dep_Set_Temp_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Temp_Dep_Set_Temp_State_Name(void)
{
  FuncIN(MENU_TEMP_DEP_SET_TEMP_STATE_NAME);
  
  switch(SetTempFlag)
  {
    case 1:
      switch(SW_M_Event_g.Temp_1.State)
      {
        case SW_TEMP_ALARM_ON:
          strcpy(Temp_State_Name, "State : ON");
          break;
        case SW_TEMP_ALARM_OFF:
          strcpy(Temp_State_Name, "State : OFF");
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      }
      break;
    case 2:
      switch(SW_M_Event_g.Temp_2.State)
      {
        case SW_TEMP_ALARM_ON:
          strcpy(Temp_State_Name, "State : ON");
          break;
        case SW_TEMP_ALARM_OFF:
          strcpy(Temp_State_Name, "State : OFF");
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      }
      break;
    default:
      Fatal_Abort(-NOT_INITIALIZED_ERROR);
  }
  
  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_TEMP_STATE_NAME);
}
FUNC_REGISTER(MENU_TEMP_DEP_SET_TEMP_STATE_NAME, Menu_Temp_Dep_Set_Temp_State_Name);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Dep_Set_Temp_Response_Name(void)
{
  FuncIN(MENU_TEMP_DEP_SET_TEMP_RESPONSE_NAME);

  switch(SetTempFlag)
  {
    case 1:
      switch(SW_M_Event_g.Config & SW_EVENT_RESPONSE_1_ON)
      {
        case SW_EVENT_RESPONSE_1_ON:
          strcpy(Temp_Response_Name, "Response : ON");
          break;
        case SW_EVENT_RESPONSE_1_OFF:
          strcpy(Temp_Response_Name, "Response : OFF");
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      }
      break;
    case 2:
      switch(SW_M_Event_g.Config & SW_EVENT_RESPONSE_2_ON)
      {
        case SW_EVENT_RESPONSE_2_ON:
          strcpy(Temp_Response_Name, "Response : ON");
          break;
        case SW_EVENT_RESPONSE_2_OFF:
          strcpy(Temp_Response_Name, "Response : OFF");
          break;
        default:
          Fatal_Abort(-UNKNOWN_ERROR);
      }
      break;
    default:
      Fatal_Abort(-NOT_INITIALIZED_ERROR);
  }

  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_TEMP_RESPONSE_NAME);
}
FUNC_REGISTER(MENU_TEMP_DEP_SET_TEMP_RESPONSE_NAME, Menu_Temp_Dep_Set_Temp_Response_Name);
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Temp_Dep_Setting_Temp_Name(void)
{
  FuncIN(MENU_TEMP_DEP_SETTING_TEMP_NAME);
  
  switch(SetTempFlag)
  {
    case 1:
      snprintf(Set_Temp_Name, 18, "Temp 1 (%d'C)", SW_M_Event_g.Temp_1.Temp);
      break;
    case 2:
      snprintf(Set_Temp_Name, 18, "Temp 2 (%d'C)", SW_M_Event_g.Temp_2.Temp);
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }
  
  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SETTING_TEMP_NAME);
}
FUNC_REGISTER(MENU_TEMP_DEP_SETTING_TEMP_NAME, Menu_Temp_Dep_Setting_Temp_Name);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Temp_Dep_Setting_Sensor_Name(void)
{
  FuncIN(MENU_TEMP_DEP_SETTING_SENSOR_NAME);
  
  switch(SetTempFlag)
  {
    case 1:
      snprintf(Set_Sensor_Name, 18, "Sensor 1 ID:%d", SW_M_Event_g.Temp_1.Sensor);
      break;
    case 2:
      snprintf(Set_Sensor_Name, 18, "Sensor 2 ID:%d", SW_M_Event_g.Temp_2.Sensor);
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  }
  
  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SETTING_SENSOR_NAME);
}
FUNC_REGISTER(MENU_TEMP_DEP_SETTING_SENSOR_NAME, Menu_Temp_Dep_Setting_Sensor_Name);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Dep_Set_Temp_1(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TEMP_DEP_SET_TEMP_1);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetTempFlag = 1;
      Menu_Temp_Dep_Set_Temp_State_Name();
      Menu_Temp_Dep_Set_Temp_Response_Name();
      Menu_Temp_Dep_Setting_Temp_Name();
      Menu_Temp_Dep_Setting_Sensor_Name();
      break;
    case CANCEL_KEY_EVENT:
      SetTempFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_TEMP_1);
}
FUNC_REGISTER(MENU_TEMP_DEP_SET_TEMP_1, Menu_Temp_Dep_Set_Temp_1);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Dep_Set_Temp_2(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TEMP_DEP_SET_TEMP_2);
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      SetTempFlag = 2;
      Menu_Temp_Dep_Set_Temp_State_Name();
      Menu_Temp_Dep_Set_Temp_Response_Name();
      Menu_Temp_Dep_Setting_Temp_Name();
      Menu_Temp_Dep_Setting_Sensor_Name();
      break;
    case CANCEL_KEY_EVENT:
      SetTempFlag = 0;
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_TEMP_2);
}
FUNC_REGISTER(MENU_TEMP_DEP_SET_TEMP_2, Menu_Temp_Dep_Set_Temp_2);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Temp_Dep_State_Update_Display(const uint32 Ptr_Pos)
{
  FuncIN(MENU_TEMP_DEP_STATE_UPDATE_DISPLAY);
  
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
  
  printd(1, "Set State : Temp %u", SetTempFlag);
  
  switch(SetTempFlag)
  {
    case 1:
      State = SW_M_Event_g.Temp_1.State;
      break;
    case 2:
      State = SW_M_Event_g.Temp_2.State;
      break;
    default:
      Fatal_Abort(-NOT_INITIALIZED_ERROR);
  } // switch(SetTempFlag)
  
  switch(State)
  {
    case SW_TEMP_ALARM_OFF:
      printd(2, "%s# OFF", PointerString_1);
      printd(3, "%s  ON", PointerString_2);
      break;
    case SW_TEMP_ALARM_ON:
      printd(2, "%s  OFF", PointerString_1);
      printd(3, "%s# ON", PointerString_2);
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
  } // switch(State)
  
  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_STATE_UPDATE_DISPLAY);
}
FUNC_REGISTER(MENU_TEMP_DEP_STATE_UPDATE_DISPLAY, Menu_Temp_Dep_State_Update_Display);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Dep_Temp_State(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TEMP_DEP_TEMP_STATE);
  
  static uint32 Ptr_Pos = 0;
  
  clrd();
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      if(Ptr_Pos == 0)
      {
        Ptr_Pos = 1;
        Menu_Temp_Dep_State_Update_Display(Ptr_Pos);
      }
      else
      {
        switch(SetTempFlag)
        {
          case 1:
            switch(Ptr_Pos)
            {
              case 1:
                SW_M_Event_g.Temp_1.State = SW_TEMP_ALARM_OFF;
                break;
              case 2:
                SW_M_Event_g.Temp_1.State = SW_TEMP_ALARM_ON;
                break;
              default:
                Fatal_Abort(-NOT_INITIALIZED_ERROR);
            }
            break;
          case 2:
            switch(Ptr_Pos)
            {
              case 1:
                SW_M_Event_g.Temp_2.State = SW_TEMP_ALARM_OFF;
                break;
              case 2:
                SW_M_Event_g.Temp_2.State = SW_TEMP_ALARM_ON;
                break;
              default:
                Fatal_Abort(-NOT_INITIALIZED_ERROR);
            }
            break;
          default:
            Fatal_Abort(-NOT_INITIALIZED_ERROR);
        } // switch(SetTempFlag)
        
        Menu_Temp_Dep_State_Update_Display(Ptr_Pos);
        printd(4, "State Set!");
        
      }
      break;
    case CANCEL_KEY_EVENT:
      Menu_Temp_Dep_Set_Temp_State_Name();
      Menu_Temp_Dep_Set_Temp_Response_Name();
      Menu_Temp_Dep_Set_Temp_Name();
      Ptr_Pos = 0;
      break;
    case UP_KEY_EVENT:
      Ptr_Pos = 1;
      Menu_Temp_Dep_State_Update_Display(Ptr_Pos);
      break;
    case DOWN_KEY_EVENT:
      Ptr_Pos = 2;
      Menu_Temp_Dep_State_Update_Display(Ptr_Pos);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  syncd();

  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_TEMP_STATE);
}
FUNC_REGISTER(MENU_TEMP_DEP_TEMP_STATE, Menu_Temp_Dep_Temp_State);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Temp_Dep_Response_Update_Display(const uint32 Ptr_Pos)
{
  FuncIN(MENU_TEMP_DEP_RESPONSE_UPDATE_DISPLAY);

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

  printd(1, "Set Response:Temp%u", SetTempFlag);

  switch(SetTempFlag)
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

  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_RESPONSE_UPDATE_DISPLAY);
}
FUNC_REGISTER(MENU_TEMP_DEP_RESPONSE_UPDATE_DISPLAY, Menu_Temp_Dep_Response_Update_Display);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Dep_Temp_Response(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TEMP_DEP_TEMP_RESPONSE);

  static uint32 Ptr_Pos = 0;

  clrd();

  switch(Key)
  {
    case ENTER_KEY_EVENT:
      if(Ptr_Pos == 0)
      {
        Ptr_Pos = 1;
        Menu_Temp_Dep_Response_Update_Display(Ptr_Pos);
      }
      else
      {
        switch(SetTempFlag)
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

        Menu_Temp_Dep_Response_Update_Display(Ptr_Pos);
        printd(4, "Response Set!");

      }
      break;
    case CANCEL_KEY_EVENT:
      Menu_Temp_Dep_Set_Temp_State_Name();
      Menu_Temp_Dep_Set_Temp_Response_Name();
      Menu_Temp_Dep_Set_Temp_Name();
      Ptr_Pos = 0;
      break;
    case UP_KEY_EVENT:
      Ptr_Pos = 1;
      Menu_Temp_Dep_Response_Update_Display(Ptr_Pos);
      break;
    case DOWN_KEY_EVENT:
      Ptr_Pos = 2;
      Menu_Temp_Dep_Response_Update_Display(Ptr_Pos);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)

  syncd();

  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_TEMP_RESPONSE);
}
FUNC_REGISTER(MENU_TEMP_DEP_TEMP_RESPONSE, Menu_Temp_Dep_Temp_Response);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Dep_Set_Temp(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TEMP_DEP_SET_TEMP);
  
  static uint32 EnterFlag = 0;
  static sint16 TempSW = 0;
  
  if(EnterFlag == 0)
  {
    PointerPosition = 1;
    TempSW = SetTempFlag == 1 ? SW_M_Event_g.Temp_1.Temp : SW_M_Event_g.Temp_2.Temp;
  }
  
  clrd();
  printd(1, "Set Temp %d", SetTempFlag);
  printd(2, "% 05d'C", TempSW);
  printd(3, "%*s ",PointerPosition, "^");
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      // First enter in this state
      if(EnterFlag == 0)
      {
        EnterFlag = 1;
        break;
      }
     
      printd(2, "% 05d'C Temp Set!", TempSW);
      if(SetTempFlag == 1)
        SW_M_Event_g.Temp_1.Temp = TempSW;
      else
        SW_M_Event_g.Temp_2.Temp = TempSW;
      
      break;
    case CANCEL_KEY_EVENT:
      clrd();
      
      TempSW = 0;
      
      PointerPosition = 1;
      
      EnterFlag = 0;
      Menu_Temp_Dep_Setting_Temp_Name();
      
      EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_TEMP_STATE);
    case UP_KEY_EVENT:
      Menu_Temp_Increment_Ptr_Pos_Number(&TempSW);
      printd(2, "% 05d'C", TempSW);
      break;
    case DOWN_KEY_EVENT:
      Menu_Temp_Decrement_Ptr_Pos_Number(&TempSW);
      printd(2, "% 05d'C", TempSW);
      break;
    case LEFT_KEY_EVENT:
      if(PointerPosition > 1)
      {
        PointerPosition--;
        printd(3, "%*s ",PointerPosition, "^");
      }
      break;
    case RIGHT_KEY_EVENT:
      if(PointerPosition < 5)
      {
        PointerPosition++;
        printd(3, "%*s ",PointerPosition, "^");
      }
      break;
    case EXIT_KEY_EVENT:
      clrd();
      
      TempSW = 0;
      
      PointerPosition = 1;
      
      EnterFlag = 0;
      Menu_Temp_Dep_Setting_Temp_Name();
      
      EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_TEMP_STATE);
    case MENU_KEY_EVENT:
      clrd();
      
      TempSW = 0;
      
      PointerPosition = 1;
      
      EnterFlag = 0;
      Menu_Temp_Dep_Setting_Temp_Name();
      
      EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_TEMP_STATE);
    case NUM1_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number(&TempSW, 1);
      printd(2, "% 05d'C", TempSW);
      break;
    case NUM2_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number(&TempSW, 2);
      printd(2, "% 05d'C", TempSW);
      break;
    case NUM3_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number(&TempSW, 3);
      printd(2, "% 05d'C", TempSW);
      break;
    case NUM4_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number(&TempSW, 4);
      printd(2, "% 05d'C", TempSW);
      break;
    case NUM5_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number(&TempSW, 5);
      printd(2, "% 05d'C", TempSW);
      break;
    case NUM6_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number(&TempSW, 6);
      printd(2, "% 05d'C", TempSW);
      break;
    case NUM7_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number(&TempSW, 7);
      printd(2, "% 05d'C", TempSW);
      break;
    case NUM8_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number(&TempSW, 8);
      printd(2, "% 05d'C", TempSW);
      break;
    case NUM9_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number(&TempSW, 9);
      printd(2, "% 05d'C", TempSW);
      break;
    case NUM0_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number(&TempSW, 0);
      printd(2, "% 05d'C", TempSW);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  syncd();
  
  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_TEMP);
}
FUNC_REGISTER(MENU_TEMP_DEP_SET_TEMP, Menu_Temp_Dep_Set_Temp);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Dep_Set_Sensor(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TEMP_DEP_SET_SENSOR);
  
  static uint32 EnterFlag = 0;
  static uint16 Sensor = 0;
  
  if(EnterFlag == 0)
  {
    PointerPosition = 4;
    Sensor = SetTempFlag == 1 ? SW_M_Event_g.Temp_1.Sensor : SW_M_Event_g.Temp_2.Sensor;
  }
  
  clrd();
  printd(1, "Set Sensor %d", SetTempFlag);
  printd(2, "   %02d", Sensor);
  printd(3, "%*s ",PointerPosition, "^");
  
  switch(Key)
  {
    case ENTER_KEY_EVENT:
      // First enter in this state
      if(EnterFlag == 0)
      {
        EnterFlag = 1;
        break;
      }
      if(Check_Sensor_Availability(Sensor))
      {
        printd(2, "   %02d Temp Set!", Sensor);
        if(SetTempFlag == 1)
          SW_M_Event_g.Temp_1.Sensor = (uint8)Sensor;
        else
          SW_M_Event_g.Temp_2.Sensor = (uint8)Sensor;
      }
      else
      {
        printd(3, "Not available!");
      }

      break;
    case CANCEL_KEY_EVENT:
      clrd();
      
      Sensor = 0;
      
      PointerPosition = 1;
      
      EnterFlag = 0;
      Menu_Temp_Dep_Setting_Sensor_Name();
      
      EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_TEMP_STATE);
    case UP_KEY_EVENT:
      Menu_Temp_Increment_Ptr_Pos_Number((sint16 *)&Sensor);
      printd(2, "   %02d", Sensor);
      break;
    case DOWN_KEY_EVENT:
      Menu_Temp_Decrement_Ptr_Pos_Number((sint16 *)&Sensor);
      printd(2, "   %02d", Sensor);
      break;
    case LEFT_KEY_EVENT:
      if(PointerPosition > 4)
      {
        PointerPosition--;
        printd(3, "%*s ",PointerPosition, "^");
      }
      break;
    case RIGHT_KEY_EVENT:
      if(PointerPosition < 5)
      {
        PointerPosition++;
        printd(3, "%*s ",PointerPosition, "^");
      }
      break;
    case EXIT_KEY_EVENT:
      clrd();
      
      Sensor = 0;
      
      PointerPosition = 1;
      
      EnterFlag = 0;
      Menu_Temp_Dep_Setting_Sensor_Name();
      
      EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_SENSOR);
    case MENU_KEY_EVENT:
      clrd();
      
      Sensor = 0;
      
      PointerPosition = 1;
      
      EnterFlag = 0;
      Menu_Temp_Dep_Setting_Sensor_Name();
      
      EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_SENSOR);
    case NUM1_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number((sint16 *)&Sensor, 1);
      printd(2, "   %02d", Sensor);
      break;
    case NUM2_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number((sint16 *)&Sensor, 2);
      printd(2, "   %02d", Sensor);
      break;
    case NUM3_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number((sint16 *)&Sensor, 3);
      printd(2, "   %02d", Sensor);
      break;
    case NUM4_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number((sint16 *)&Sensor, 4);
      printd(2, "   %02d", Sensor);
      break;
    case NUM5_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number((sint16 *)&Sensor, 5);
      printd(2, "   %02d", Sensor);
      break;
    case NUM6_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number((sint16 *)&Sensor, 6);
      printd(2, "   %02d", Sensor);
      break;
    case NUM7_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number((sint16 *)&Sensor, 7);
      printd(2, "   %02d", Sensor);
      break;
    case NUM8_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number((sint16 *)&Sensor, 8);
      printd(2, "   %02d", Sensor);
      break;
    case NUM9_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number((sint16 *)&Sensor, 9);
      printd(2, "   %02d", Sensor);
      break;
    case NUM0_KEY_EVENT:
      Menu_Temp_Set_Ptr_Pos_Number((sint16 *)&Sensor, 0);
      printd(2, "   %02d", Sensor);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)
  
  syncd();
  
  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_SENSOR);
}
FUNC_REGISTER(MENU_TEMP_DEP_SET_SENSOR, Menu_Temp_Dep_Set_Sensor);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t  Menu_Temp_Dep_Set_Event(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr)
{
  FuncIN(MENU_TEMP_DEP_SET_EVENT);

  static uint32 EnterFlag = 0;
  static uint8 Offset = 0;
  static uint8 Event = 0;

  if(EnterFlag == 0)
  {
    Offset = 0;
    PointerPosition = 1;
    Event = SetTempFlag == 1 ? SW_M_Event_g.Temp_1.Event : SW_M_Event_g.Temp_2.Event;
    Menu_Temp_Update_Event(Offset, PointerPosition, Event);
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
      Event = PointerPosition;
      Menu_Temp_Update_Event(Offset, PointerPosition, Event); 
        if(SetTempFlag == 1)
          SW_M_Event_g.Temp_1.Event = Event;
        else
          SW_M_Event_g.Temp_2.Event = Event;
        
      break;
    case CANCEL_KEY_EVENT:
      clrd();

      PointerPosition = 1;
      EnterFlag = 0;
      Event = 0;
        
      EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_EVENT);
    case UP_KEY_EVENT:
      if(PointerPosition > 1)
      {
        PointerPosition--;
        if((PointerPosition - Offset) < 1)
        {
          Offset--;
        }
      }
      Menu_Temp_Update_Event(Offset, PointerPosition, Event);
      break;
    case DOWN_KEY_EVENT:
      if(PointerPosition < NO_OF_EVENTS)
      {
        PointerPosition++;
        if((PointerPosition - Offset) > 4)
        {
          Offset++;
        }
      }
      Menu_Temp_Update_Event(Offset, PointerPosition, Event); 
      break;
    case EXIT_KEY_EVENT:
      clrd();

      PointerPosition = 1;
      EnterFlag = 0;
      Event = 0;

      EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_EVENT);
    case MENU_KEY_EVENT:
      clrd();

      PointerPosition = 1;
      EnterFlag = 0;
      Event = 0;

      EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_EVENT);
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } // switch(Key)

  syncd();

  EXIT_SUCCESS_FUNC(MENU_TEMP_DEP_SET_EVENT);
}
FUNC_REGISTER(MENU_TEMP_DEP_SET_EVENT, Menu_Temp_Dep_Set_Event);
/*******************************************************************************
 * Menu States
 ******************************************************************************/

/*******************************************************************************
 * Level 7
 ******************************************************************************/


/**** Switch 1, Event 1, Temp 1 Dep *******************************************/
const uint8 Switch_1_Event_1_Temp1Path[] = {2, 3, 0, 0, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp1,
  // Path
  Switch_1_Event_1_Temp1Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Temp_1,
  // String
  Temp_1_Name
);

/**** Switch 1, Event 1, Temp 2 Dep *******************************************/
const uint8 Switch_1_Event_1_Temp2Path[] = {2, 3, 0, 0, 1, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp2,
  // Path
  Switch_1_Event_1_Temp2Path,
  // Max Level
  7,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Temp_2,
  // String
  Temp_2_Name
);

/*******************************************************************************
 * Level 8
 ******************************************************************************/


/**** Switch 1, Event 1, Temp 1, State Dep ************************************/
const uint8 Switch_1_Event_1_Temp_1_StatePath[] = {2, 3, 0, 0, 1, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_1_State,
  // Path
  Switch_1_Event_1_Temp_1_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_State,
  // String
  Temp_State_Name
);

/**** Switch 1, Event 1, Temp 1, Responce Dep *********************************/
const uint8 Switch_1_Event_1_Temp_1_Responce_Path[] = {2, 3, 0, 0, 1, 1, 0, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_1_Responce,
  // Path
  Switch_1_Event_1_Temp_1_Responce_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_Response,
  // String
  Temp_Response_Name
);

/**** Switch 1, Event 1, Temp 1, Set Temp Dep *********************************/
const uint8 Switch_1_Event_1_Temp_1_Set_Temp_Path[] = {2, 3, 0, 0, 1, 1, 0, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_1_Set_Temp,
  // Path
  Switch_1_Event_1_Temp_1_Set_Temp_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Temp,
  // String
  Set_Temp_Name
);

/**** Switch 1, Event 1, Temp 1, Set Sensor Dep *********************************/
const uint8 Switch_1_Event_1_Temp_1_Set_Sensor_Path[] = {2, 3, 0, 0, 1, 1, 0, 3};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_1_Set_Sensor,
  // Path
  Switch_1_Event_1_Temp_1_Set_Sensor_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Sensor,
  // String
  Set_Sensor_Name
);

/**** Switch 1, Event 1, Temp 1, Set Event Dep *********************************/
const uint8 Switch_1_Event_1_Temp_1_Set_Event_Path[] = {2, 3, 0, 0, 1, 1, 0, 4};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_1_Set_Event,
  // Path
  Switch_1_Event_1_Temp_1_Set_Event_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Event,
  // String
  "Event 1"
);

/**** Switch 1, Event 1, Temp 2, State Dep ************************************/
const uint8 Switch_1_Event_1_Temp_2_StatePath[] = {2, 3, 0, 0, 1, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_2_State,
  // Path
  Switch_1_Event_1_Temp_2_StatePath,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_State,
  // String
  Temp_State_Name
);

/**** Switch 1, Event 1, Temp 2, Responce Dep *********************************/
const uint8 Switch_1_Event_1_Temp_2_Responce_Path[] = {2, 3, 0, 0, 1, 1, 1, 1};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_2_Responce,
  // Path
  Switch_1_Event_1_Temp_2_Responce_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Temp_Response,
  // String
  Temp_Response_Name
);

/**** Switch 1, Event 1, Temp 2, Set Temp Dep *********************************/
const uint8 Switch_1_Event_1_Temp_2_Set_Temp_Path[] = {2, 3, 0, 0, 1, 1, 1, 2};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_2_Set_Temp,
  // Path
  Switch_1_Event_1_Temp_2_Set_Temp_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Temp,
  // String
  Set_Temp_Name
);

/**** Switch 1, Event 1, Temp 2, Set Sensor Dep *********************************/
const uint8 Switch_1_Event_1_Temp_2_Set_Sensor_Path[] = {2, 3, 0, 0, 1, 1, 1, 3};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_2_Set_Sensor,
  // Path
  Switch_1_Event_1_Temp_2_Set_Sensor_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Sensor,
  // String
  Set_Sensor_Name
);

/**** Switch 1, Event 1, Temp 2, Set Event Dep *********************************/
const uint8 Switch_1_Event_1_Temp_2_Set_Event_Path[] = {2, 3, 0, 0, 1, 1, 1, 4};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_2_Set_Event,
  // Path
  Switch_1_Event_1_Temp_2_Set_Event_Path,
  // Max Level
  8,
  // Flags
  0x00,
  // Possible Keys
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Event,
  // String
  "Event 2"
);
/*******************************************************************************
 * Level 9
 ******************************************************************************/


/**** Switch 1, Event 1, Temp 1, State Dep ************************************/
const uint8 Switch_1_Event_1_Temp_1_Set_StatePath[] = {2, 3, 0, 0, 1, 1, 0, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_1_Set_State,
  // Path
  Switch_1_Event_1_Temp_1_Set_StatePath,
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
  Menu_Temp_Dep_Temp_State,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 2, State Dep ************************************/
const uint8 Switch_1_Event_1_Temp_2_Set_StatePath[] = {2, 3, 0, 0, 1, 1, 1, 0, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_2_Set_State,
  // Path
  Switch_1_Event_1_Temp_2_Set_StatePath,
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
  Menu_Temp_Dep_Temp_State,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 1, Response Dep ************************************/
const uint8 Switch_1_Event_1_Temp_1_Set_ResponsePath[] = {2, 3, 0, 0, 1, 1, 0, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_1_Set_Response,
  // Path
  Switch_1_Event_1_Temp_1_Set_ResponsePath,
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
  Menu_Temp_Dep_Temp_Response,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 2, Response Dep ************************************/
const uint8 Switch_1_Event_1_Temp_2_Set_ResponsePath[] = {2, 3, 0, 0, 1, 1, 1, 1, 0};
MENU_STATE_CREATE(
  // Name
  Switch_1_Event_1_Temp_2_Set_Response,
  // Path
  Switch_1_Event_1_Temp_2_Set_ResponsePath,
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
  Menu_Temp_Dep_Temp_Response,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 1, Set Temp Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Temp_1_Set_Temp_Path[] = {2, 3, 0, 0, 1, 1, 0, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Temp_1_Set_Temp,
  // Path
  Setting_Switch_1_Event_1_Temp_1_Set_Temp_Path,
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
  Menu_Temp_Dep_Set_Temp,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 2, Set Temp Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Temp_2_Set_Temp_Path[] = {2, 3, 0, 0, 1, 1, 1, 2, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Temp_2_Set_Temp,
  // Path
  Setting_Switch_1_Event_1_Temp_2_Set_Temp_Path,
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
  Menu_Temp_Dep_Set_Temp,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 1, Set Sensor Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Temp_1_Set_Sensor_Path[] = {2, 3, 0, 0, 1, 1, 0, 3, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Temp_1_Set_Sensor,
  // Path
  Setting_Switch_1_Event_1_Temp_1_Set_Sensor_Path,
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
  Menu_Temp_Dep_Set_Sensor,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 2, Set Sensor Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Temp_2_Set_Sensor_Path[] = {2, 3, 0, 0, 1, 1, 1, 3, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Temp_2_Set_Sensor,
  // Path
  Setting_Switch_1_Event_1_Temp_2_Set_Sensor_Path,
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
  Menu_Temp_Dep_Set_Sensor,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 1, Set Event Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Temp_1_Set_Event_Path[] = {2, 3, 0, 0, 1, 1, 0, 4, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Temp_1_Set_Event,
  // Path
  Setting_Switch_1_Event_1_Temp_1_Set_Event_Path,
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
  EXIT_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Event,
  // String
  ""
);

/**** Switch 1, Event 1, Temp 2, Set Event Dep ************************************/
const uint8 Setting_Switch_1_Event_1_Temp_2_Set_Event_Path[] = {2, 3, 0, 0, 1, 1, 1, 4, 0};
MENU_STATE_CREATE(
  // Name
  Setting_Switch_1_Event_1_Temp_2_Set_Event,
  // Path
  Setting_Switch_1_Event_1_Temp_2_Set_Event_Path,
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
  EXIT_KEY_EVENT,
  // Callback
  Menu_Temp_Dep_Set_Event,
  // String
  ""
);
