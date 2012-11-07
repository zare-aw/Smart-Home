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
uint16 Level = 0;
uint16 Location[NO_OF_LEVELS] = {0};
uint8 Sec_Callback_ID = 0;

uint8 TempExtID = 0xFF;
uint8 TempIntID = 0xFF;

char MainViewBuffer[MAIN_VIEW_BUFFER_LINE][MAIN_VIEW_BUFFER_COL] = {0};

static Status_t Display_Menu_Update(const uint8 Level, const uint16 *Location);

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
  
  switch(Location[0])
  {
    case 0:
      if(Level > 0)
        switch(Location[1])
        {
          case 0:
            break;
          case 1:
            break;
          default:
            break;
        }
      else
        switch(Event)
        {
          case DOWN_KEY_EVENT:
            Location[0] = 1;
            LocationChange = 1;
            break;
          case MENU_KEY_EVENT:
            Location[0] = 0;
            Level = 1;
            LocationChange = 1;
            break;
          default:
            MENU_INFO(printc("\r # This Key is not used in this state of Menu. Event = %d\n", Event));
            break;
        }
      break;
    case 1:
      switch(Event)
      {
        case UP_KEY_EVENT:
          Location[0] = 0;
          LocationChange = 1;
          break;
        case DOWN_KEY_EVENT:
          Location[0] = 2;
          LocationChange = 1;
          break;
        case MENU_KEY_EVENT:
          Location[0] = 0;
          Level = 1;
          LocationChange = 1;
          break;
        default:
          MENU_INFO(printc("\r # This Key is not used in this state of Menu. Event = %d\n", Event));
          break;
      }
      break;
    case 2:
      switch(Event)
      {
        case UP_KEY_EVENT:
          Location[0] = 1;
          LocationChange = 1;
          break;
        case MENU_KEY_EVENT:
          Location[0] = 0;
          Level = 1;
          LocationChange = 1;
          break;
        default:
          MENU_INFO(printc("\r # This Key is not used in this state of Menu. Event = %d\n", Event));
          break;
      }
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  if(LocationChange == 1)
    VERIFY(Display_Menu_Update(Level, Location), -MENU_DISPLAY_ERROR);
  
  EXIT_SUCCESS_FUNC(MENU);
}
FUNC_REGISTER(MENU, Menu);

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Display_Menu_Update(const uint8 Level, const uint16 *Location)
{
  FuncIN(DISPLAY_MENU_UPDATE);
  
  ASSERT(Level < NO_OF_LEVELS, -INVALID_INPUT_PARAMETER);
  
  switch(Location[0])
  {
    case 0:
      if(Level > 0)
        switch(Location[1])
        {
          case 0:
            break;
          case 1:
            break;
          default:
            break;
        }
      else
      {
        clrd();
        
        VERIFY(printd(1, "%s", MainViewBuffer[0]), -GENERAL_ERROR);
        VERIFY(printd(2, "%s", MainViewBuffer[1]), -GENERAL_ERROR);
        VERIFY(printd(3, "%s", MainViewBuffer[2]), -GENERAL_ERROR);
        VERIFY(printd(4, "%s", MainViewBuffer[3]), -GENERAL_ERROR);
        
        syncd();
      }
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
  }
  
  LocationChange = 0;
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
  
  if((Level == 0) && (Location[0] == 0))
    Display_Menu_Update(Level, Location);
  
  EXIT_SUCCESS_FUNC(MENU_SEC_INT_CALLBACK);
}
FUNC_REGISTER(MENU_SEC_INT_CALLBACK, Menu_Sec_Int_Callback);
