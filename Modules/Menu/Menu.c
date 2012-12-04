#include <string.h>
#include <stdio.h>
#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu_Func.h"
#include "Menu_Debug.h"
#include "Menu.h"
#include "RTC.h"
#include "Console.h"
#include "SurfaceFlinger.h"
#include "Temperature.h"


uint8 LocationChange = 0;
uint8 Level = 0;
uint8 State = 0;
uint8 PrevLevel = 0;
uint8 PrevState = 0;
uint8 MenuPointerPos = 0;
uint8 Sec_Callback_ID = 0;

uint8 TempExtID = 0xFF;
uint8 TempIntID = 0xFF;

char MainViewBuffer[MAIN_VIEW_BUFFER_LINE][MAIN_VIEW_BUFFER_COL] = {0};

static Status_t Display_Menu_Update();

/*******************************************************************************
* Function for get start address of menu section
*******************************************************************************/
inline Menu_State_t *Get_Menu_Section_Begin(void)
{
  return __section_begin(".menu");
}

/*******************************************************************************
* Function for get end address of menu section
*******************************************************************************/
inline Menu_State_t *Get_Menu_Section_End(void)
{
  return __section_end(".menu");
}

/*******************************************************************************
* Function for get size on menu section
*******************************************************************************/
uint32 Get_Menu_Section_Size(void)
{
  return __section_size(".menu");
}

/*******************************************************************************
 * Function for find Menu_State table entry for a Menu_State
 * @in Level
 * @in State
 * @out **Menu_State_p - Double pointer for returning Menu_State_t structire
 *                      of the Menu_State
 * @out Status_t - Status
 ******************************************************************************/
Status_t Find_Menu_State(const uint8 Level, const uint8 State, Menu_State_t **Menu_State_p)
{
  FuncIN(FIND_MENU_STATE);
  
  Menu_State_t *Menu_Section_Begin = Get_Menu_Section_Begin();
  Menu_State_t *Menu_Section_End = Get_Menu_Section_End();
  Menu_State_t *Menu_State;
  
  ASSERT(Menu_State_p != NULL, -INVALID_INPUT_POINTER);
  
  for(Menu_State = Menu_Section_Begin; Menu_State != Menu_Section_End; Menu_State++)
  {
    if((Menu_State -> Level == Level) && (Menu_State -> State == State))
    {
      *Menu_State_p = Menu_State;
      EXIT_SUCCESS_FUNC(FIND_MENU_STATE);
    }
  } // for
  
  EXIT_FUNC(MENU_STATE_NOT_FOUND, FIND_MENU_STATE);
}
FUNC_REGISTER(FIND_MENU_STATE, Find_Menu_State);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Menu_Init(void)
{
  FuncIN(MENU_INIT);
  
  for(int i = 0; i < MAIN_VIEW_BUFFER_LINE; i++)
    for(int j = 0; j < MAIN_VIEW_BUFFER_COL; j++)
      MainViewBuffer[i][j] = '\0';
  
  RTC_Register_Inc_Int((void *)Menu_Sec_Int_Callback, IncIntType_SEC, &Sec_Callback_ID);
  
  EXIT_SUCCESS_FUNC(MENU_INIT);
}
FUNC_REGISTER(MENU_INIT, Menu_Init);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Menu(uint32 Event)
{
  FuncIN(MENU);
  
  Status_t Status = GENERAL_ERROR;
  Menu_State_t *Menu_State_p;
  Menu_State_t *Menu_State_Temp_p;
  
  if(Level == 0)
  {
    switch(Event)
    {
      case UP_KEY_EVENT:
        if(State > 0)
        {
          State--;
          LocationChange = 1;
        }
        break;
      case DOWN_KEY_EVENT:
        if(State < (NO_OF_DESKTOPS - 1))
        {
          State++;
          LocationChange = 1;
        }
        break;
      case ENTER_KEY_EVENT:
        Level = 1;
        State = 1;
        LocationChange = 1;
        break;
      case MENU_KEY_EVENT:
        Level = 1;
        State = 1;
        LocationChange = 1;
        break;
      case VOL_UP_KEY_EVENT:
        
        break;
      case VOL_DOWN_KEY_EVENT:
        
        break;
      default:
        MENU_INFO(printc("\r # Menu: Unsupported Key (0x%X)\n", Event));
        break;
    } // switch(State)
  } // if(Level == 0)
  else
  {
    // Find registered state
    Status = Find_Menu_State(Level, State, &Menu_State_p);
    VERIFY(Status, Status);
    if(Status == MENU_STATE_NOT_FOUND)
      Fatal_Abort(-FATAL_ERROR);
    
    // Valid Event?
    if(!(Event & (DEFAULT_KEY_MASK | Menu_State_p -> PossibleKeys)))
      EXIT_FUNC(MENU_INVALID_EVENT, MENU);
    
    switch(Event)
    {
      case UP_KEY_EVENT:
        if(State > 0)
        {
          State--;
          LocationChange = 1;
        }
        break;
      case DOWN_KEY_EVENT:
        Status = Find_Menu_State(Level, State + 1, &Menu_State_Temp_p);
        VERIFY(Status, Status);
        
        if(Status == SUCCESS)
        {
          State++;
          LocationChange = 1;
        }
        break;
      case ENTER_KEY_EVENT:
        if((Event | Menu_State_p -> PossibleKeys) && (Menu_State_p -> Callback != NULL))
          VERIFY((Menu_State_p -> Callback)(Menu_State_p, Event, NULL), -MENU_STATE_EXECUTION_FAILED);
        
        if((Menu_State_p -> Flags & MENU_LAST_STATE) != MENU_LAST_STATE)
        {
          Status = Find_Menu_State(Level + 1, 1, &Menu_State_Temp_p);
          VERIFY(Status, Status);
          
          if(Status == SUCCESS)
          {
            Level++;
            State = 0;
            LocationChange = 1;
          }
        }
        break;
      case CANCEL_KEY_EVENT:
        if((Event & Menu_State_p -> PossibleKeys) && (Menu_State_p -> Callback != NULL))
          VERIFY((Menu_State_p -> Callback)(Menu_State_p, Event, NULL), -MENU_STATE_EXECUTION_FAILED);
        
        Level--;
        State = Menu_State_p -> Parent;
        LocationChange = 1;
        break;
     case MENU_KEY_EVENT:
        if((Event | Menu_State_p -> PossibleKeys) && (Menu_State_p -> Callback != NULL))
          VERIFY((Menu_State_p -> Callback)(Menu_State_p, Event, NULL), -MENU_STATE_EXECUTION_FAILED);
        
        Level = 1;
        State = 0;
        LocationChange = 1;
        break;
      case EXIT_KEY_EVENT:
        if((Event | Menu_State_p -> PossibleKeys) && (Menu_State_p -> Callback != NULL))
          VERIFY((Menu_State_p -> Callback)(Menu_State_p, Event, NULL), -MENU_STATE_EXECUTION_FAILED);
        
        Level = 0;
        State = 0;
        LocationChange = 1;
        break;
      default:
        if(Event | Menu_State_p -> PossibleKeys)
          VERIFY((Menu_State_p -> Callback)(Menu_State_p, Event, NULL), -MENU_STATE_EXECUTION_FAILED);
        break;
    }
  }
  
  if(LocationChange == 1)
    VERIFY(Display_Menu_Update(), -MENU_DISPLAY_ERROR);
  
  EXIT_SUCCESS_FUNC(MENU);
}
FUNC_REGISTER(MENU, Menu);

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Display_Menu_Update(void)
{
  FuncIN(DISPLAY_MENU_UPDATE);
  
  Status_t Status = GENERAL_ERROR;
  Menu_State_t *Menu_State_p;
  Menu_State_t *Menu_State_Buf[(Y_SIZE * 2) - 1] = {0};
  uint32 i, j, Find;
    
  if(Level == 0)
  {
    switch(State)
    {
      case 0:
        clrd();
        
        VERIFY(printd(1, "%s", MainViewBuffer[0]), -GENERAL_ERROR);
        VERIFY(printd(2, "%s", MainViewBuffer[1]), -GENERAL_ERROR);
        VERIFY(printd(3, "%s", MainViewBuffer[2]), -GENERAL_ERROR);
        VERIFY(printd(4, "%s", MainViewBuffer[3]), -GENERAL_ERROR);
        
        syncd();
        break;
      case 1:
        clrd();
        
        VERIFY(printd(1, "%s", MainViewBuffer[4]), -GENERAL_ERROR);
        VERIFY(printd(2, "%s", MainViewBuffer[5]), -GENERAL_ERROR);
        VERIFY(printd(3, "%s", MainViewBuffer[6]), -GENERAL_ERROR);
        VERIFY(printd(4, "%s", MainViewBuffer[7]), -GENERAL_ERROR);
        
        syncd();
        break;
      case 2:
        clrd();
        
        VERIFY(printd(1, "%s", MainViewBuffer[8]), -GENERAL_ERROR);
        VERIFY(printd(2, "%s", MainViewBuffer[9]), -GENERAL_ERROR);
        VERIFY(printd(3, "%s", MainViewBuffer[10]), -GENERAL_ERROR);
        VERIFY(printd(4, "%s", MainViewBuffer[11]), -GENERAL_ERROR);
        
        syncd();
        break;
      default:
        LocationChange = 0;
        Fatal_Abort(-INVALID_INPUT_POINTER);
        break;
    } // switch(State)
  } // if(Level == 0)
  else
  {
    /**** Level changed ****/
    if(PrevLevel != Level)
    {
      memset(Menu_State_Buf, NULL, sizeof(Menu_State_t *) * ((Y_SIZE * 2) - 1));
      
      /**** Update Menu_State_Buf with next states ****/
      for(i = 0; i < Y_SIZE; i++)
      {
        Status = Find_Menu_State(Level, State + i, &Menu_State_p);
        if(Status == MENU_STATE_NOT_FOUND)
          break;
        else
          if(Status == SUCCESS)
            Menu_State_Buf[(Y_SIZE - 1) + i] = Menu_State_p;
      }
      
      /**** Update Menu_State_Buf with previous states if exist ****/
      if(i < Y_SIZE)
      {
        Find = Y_SIZE - i;
        
        if(State > 0)
        {
          for(i = 1; i <= Find; i++)
          {
            Status = Find_Menu_State(Level, State - i, &Menu_State_p);
            if(Status == MENU_STATE_NOT_FOUND)
              break;
            else
              if(Status == SUCCESS)
                Menu_State_Buf[(Y_SIZE - 1) - i] = Menu_State_p;
            
            if((State - i) == 0)
              break;
          }
        } // if(State != 0)
      } // if(i < Y_SIZE)
      
      clrd();
      
      /**** Update Surface Flinger ****/
      for(i = 0, j = 1; i < ((Y_SIZE *  2) - 1); i++)
      {
        if(Menu_State_Buf[i] != NULL)
        {
          if(i == (Y_SIZE - 1))
          {
            VERIFY(printd(j, MENU_POINTER_STRING "%s", Menu_State_Buf[i] -> String), -GENERAL_ERROR);
            MenuPointerPos = j;
          }
          else
            VERIFY(printd(j, EMPTY_MENU_POINTER_STRING "%s", Menu_State_Buf[i] -> String), -GENERAL_ERROR);
          j++;
        }
      }
      
      syncd();
      
    } // if(PrevLevel != Level)
    
    /**** Level not changed ****/
    else
    {
      /**** Calsulate next MenuPointerPos ****/
      if((MenuPointerPos > 0) && (MenuPointerPos < Y_SIZE))
      {
        if(PrevState < State)
          MenuPointerPos++;
        else if(PrevState > State)
          MenuPointerPos--;
      }
      
      clrd();
      
      /**** Update Surface Flinger with next states ****/
      for(i = MenuPointerPos, j = 0; i <= Y_SIZE; i++, j++)
      {
        Status = Find_Menu_State(Level, State + j, &Menu_State_p);
        if(Status == MENU_STATE_NOT_FOUND)
          break;
        else
          if(Status == SUCCESS)
          {
            if(i == MenuPointerPos)
              VERIFY(printd(i, MENU_POINTER_STRING "%s", Menu_State_p -> String), -GENERAL_ERROR);
            else
              VERIFY(printd(i, EMPTY_MENU_POINTER_STRING "%s", Menu_State_p -> String), -GENERAL_ERROR);
          }
      }
      
      /**** Update Surface Flinger with previous states ****/
      for(i = MenuPointerPos, j = 1; i > 1; i--, j++)
      {
        Status = Find_Menu_State(Level, State - j, &Menu_State_p);
        if(Status != SUCCESS)
          Fatal_Abort(Status);
        else
          VERIFY(printd(i - 1, EMPTY_MENU_POINTER_STRING "%s", Menu_State_p -> String), -GENERAL_ERROR);
      }
      
      syncd();
    }
  }
  
  LocationChange = 0;
  PrevLevel = Level;
  PrevState = State;
  
  EXIT_SUCCESS_FUNC(DISPLAY_MENU_UPDATE);
}
FUNC_REGISTER(DISPLAY_MENU_UPDATE, Display_Menu_Update);

/*******************************************************************************
* This function update MainViewBuffer, 1-st and 2-nd line with Time and Date.
*******************************************************************************/
static Status_t Display_Date_Time_Update(RtcTime_t *Time_p, RtcDate_t *Date_p)
{
  FuncIN(DISPLAY_DATE_TIME_UPDATE);
  
  ASSERT(Time_p != NULL, -INVALID_INPUT_POINTER);
  ASSERT(Date_p != NULL, -INVALID_INPUT_POINTER);
  
  char Time_S[10] = {0};
  char Date_S[32] = {0};
  int i;
  
  VERIFY(Format_Time(1, Time_p, Time_S), -RTC_GENERAL_ERROR);
  VERIFY(Format_Date(2, Date_p, Date_S), -RTC_GENERAL_ERROR);
  
  for(i = 0; Time_S[i] != 0; i++);
  ASSERT(i <= 9, -RTC_GENERAL_ERROR);
  
  for(i = 0; Date_S[i] != 0; i++);
  ASSERT(i <= 30, -RTC_GENERAL_ERROR);
      
  strcpy(MainViewBuffer[0], Time_S);
  MainViewBuffer[0][8] = ' ';
  MainViewBuffer[0][9] = ' ';
  
  for(i = 0; (Date_S[i] != ' ') && (i < 10); i++)
    MainViewBuffer[0][i + 10] = Date_S[i];
  MainViewBuffer[0][i + 10] = '\0';
  
  i += 2;
  for(int j = 0; (Date_S[i] != 0) && (j < 19); i++, j++)
    MainViewBuffer[1][j] = Date_S[i];
  
  EXIT_SUCCESS_FUNC(DISPLAY_DATE_TIME_UPDATE);
}
FUNC_REGISTER(DISPLAY_DATE_TIME_UPDATE, Display_Date_Time_Update);

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Display_Temp_Update(const int TempInt, const int TempExt)
{
  FuncIN(DISPLAY_TEMP_UPDATE);
  
  if(TempInt != NO_SENSOR)
  {
    sprintf(MainViewBuffer[2] + 5, "%d'C      ", TempInt);
    MainViewBuffer[2][14] = 0;
  }
  if(TempExt != NO_SENSOR)
  {
    sprintf(MainViewBuffer[2] + 10, "Text=%d'C", TempExt);
    MainViewBuffer[2][20] = 0;
  }
  
  EXIT_SUCCESS_FUNC(DISPLAY_TEMP_UPDATE);
}
FUNC_REGISTER(DISPLAY_TEMP_UPDATE, Display_Temp_Update);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Register_Menu_Temp(const uint8 Source, const uint8 ID)
{
  FuncIN(REGISTER_MENU_TEMP);
  
  switch(Source)
  {
    case INTERNAL_SENSOR:
      TempIntID = ID;
      MENU_INFO(printc("\r # Menu internal temperature sensor registered with ID = %u\n", ID)); 
      sprintf(MainViewBuffer[2], "Tint=     ");
      break;
    case EXTERNAL_SENSOR:
      TempExtID = ID;
      sprintf(MainViewBuffer[2] + 10, "Text=");
      MENU_INFO(printc("\r # Menu external temperature sensor registered with ID = %u\n", ID));
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
      break;
  }
  
  EXIT_SUCCESS_FUNC(REGISTER_MENU_TEMP);
}
FUNC_REGISTER(REGISTER_MENU_TEMP, Register_Menu_Temp);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Unregister_Menu_Temp(const uint8 Source)
{
  FuncIN(UNREGISTER_MENU_TEMP);
  
  switch(Source)
  {
    case INTERNAL_SENSOR:
      TempIntID = 0xFF;
      sprintf(MainViewBuffer[2], "          ");
      MENU_INFO(printc("\r # Menu internal temperature sensor unregistered\n"));
      break;
    case EXTERNAL_SENSOR:
      TempExtID = 0xFF;
      sprintf(MainViewBuffer[2] + 10, "          ");
      MENU_INFO(printc("\r # Menu external temperature sensor unregistered\n"));
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
      break;
  }
  
  EXIT_SUCCESS_FUNC(REGISTER_MENU_TEMP);
}
FUNC_REGISTER(UNREGISTER_MENU_TEMP, Unregister_Menu_Temp);

/*******************************************************************************
* 
*******************************************************************************/
__arm Status_t Menu_Sec_Int_Callback(void *Ptr)
{
  FuncIN(MENU_SEC_INT_CALLBACK);
  
  RtcTime_t Time;
  RtcDate_t Date;
  int TempInt = NO_SENSOR;
  int TempExt = NO_SENSOR;
  
  RTC_Get_Time(&Time);
  RTC_Get_Date(&Date);
  
  Display_Date_Time_Update(&Time, &Date);
  
  if(TempIntID != 0xFF)
    TempInt = ReadTemp(TempIntID);
  if(TempExtID != 0xFF)
    TempExt = ReadTemp(TempExtID);
  
  Display_Temp_Update(TempInt, TempExt);
  
  if((Level == 0) && (State == 0))
    Display_Menu_Update();
  
  EXIT_SUCCESS_FUNC(MENU_SEC_INT_CALLBACK);
}
FUNC_REGISTER(MENU_SEC_INT_CALLBACK, Menu_Sec_Int_Callback);
