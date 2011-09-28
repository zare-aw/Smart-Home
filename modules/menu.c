#include "Includes.h"

uint8 LocationChange = 0;
uint16 Level = 0;
uint16 Location[NO_OF_LEVELS] = {0};
uint8 Sec_Callback_ID = 0;

uint8 TempExtID = 0xFF;
uint8 TempIntID = 0xFF;

char MainViewBuffer[12][21] = {0};

static Status_t Display_Menu_Update(const uint8 Level, const uint16 *Location);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Menu_Init(void)
{
  Function_IN(MENU_INIT);
  
  RTC_Enable_Inc_Int(IncIntType_SEC);
  Sec_Callback_ID = RTC_Register_Inc_Int((void *)Menu_Sec_Int_Callback, IncIntType_SEC);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Menu(uint32 Event)
{
  Function_IN(MENU);
  
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
      CONTROL(0, UNKNOWN_ERROR);
      break;
  }
  
  if(LocationChange == 1)
    CONTROL(!Display_Menu_Update(Level, Location), MENU_DISPLAY_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Display_Menu_Update(const uint8 Level, const uint16 *Location)
{
  Function_IN(DISPLAY_MENU_UPDATE);
  CONTROL(Level < NO_OF_LEVELS, INVALID_INPUT_PARAMETER);
  
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
        CONTROL(!printd(1, "%s", MainViewBuffer[0]), GENERAL_ERROR);
        CONTROL(!printd(2, "%s", MainViewBuffer[1]), GENERAL_ERROR);
        CONTROL(!printd(3, "%s", MainViewBuffer[2]), GENERAL_ERROR);
        CONTROL(!printd(4, "%s", MainViewBuffer[3]), GENERAL_ERROR);
        syncd();
      }
      break;
    case 1:
      clrd();
      CONTROL(!printd(1, "%s", MainViewBuffer[4]), GENERAL_ERROR);
      CONTROL(!printd(2, "%s", MainViewBuffer[5]), GENERAL_ERROR);
      CONTROL(!printd(3, "%s", MainViewBuffer[6]), GENERAL_ERROR);
      CONTROL(!printd(4, "%s", MainViewBuffer[7]), GENERAL_ERROR);
      syncd();
      break;
    case 2:
      clrd();
      CONTROL(!printd(1, "%s", MainViewBuffer[8]), GENERAL_ERROR);
      CONTROL(!printd(2, "%s", MainViewBuffer[9]), GENERAL_ERROR);
      CONTROL(!printd(3, "%s", MainViewBuffer[10]), GENERAL_ERROR);
      CONTROL(!printd(4, "%s", MainViewBuffer[11]), GENERAL_ERROR);
      syncd();
      break;
    default:
      LocationChange = 0;
      CONTROL(0, INVALID_INPUT_POINTER);
      break;
  }
  
  LocationChange = 0;
  RETURN_SUCCESS();
}

/*******************************************************************************
* This function update MainViewBuffer, 1-st and 2-nd line with Time and Date.
*******************************************************************************/
static Status_t Display_Date_Time_Update(RtcTime_t *Time_p, RtcDate_t *Date_p)
{
  Function_IN(DISPLAY_DATE_TIME_UPDATE);
  CONTROL(Time_p != NULL, INVALID_INPUT_POINTER);
  CONTROL(Date_p != NULL, INVALID_INPUT_POINTER);
  
  char Time_S[10] = {0};
  char Date_S[32] = {0};
  int i;
  
  CONTROL(!Format_Time(1, Time_p, Time_S), RTC_GENERAL_ERROR);
  CONTROL(!Format_Date(2, Date_p, Date_S), RTC_GENERAL_ERROR);
  
  for(i = 0; Time_S[i] != 0; i++);
  CONTROL(i <= 9, RTC_GENERAL_ERROR);
  
  for(i = 0; Date_S[i] != 0; i++);
  CONTROL(i <= 30, RTC_GENERAL_ERROR);
      
  strcpy(MainViewBuffer[0], Time_S);
  MainViewBuffer[0][8] = ' ';
  MainViewBuffer[0][9] = ' ';
  
  for(i = 0; (Date_S[i] != ' ') && (i < 10); i++)
    MainViewBuffer[0][i + 10] = Date_S[i];
  MainViewBuffer[0][i + 10] = '\0';
  
  i += 2;
  for(int j = 0; (Date_S[i] != 0) && (j < 19); i++, j++)
    MainViewBuffer[1][j] = Date_S[i];
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Display_Temp_Update(const int TempInt, const int TempExt)
{
  Function_IN(DISPLAY_TEMP_UPDATE);
  
  if(TempInt != NO_SENSOR)
    sprintf(MainViewBuffer[2] + 5, "%d'C    ", TempInt);
  if(TempExt != NO_SENSOR)
    sprintf(MainViewBuffer[2] + 15, "%d'C", TempExt);
  
  RETURN_SUCCESS_FUNC(DISPLAY_TEMP_UPDATE);
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Register_Menu_Temp(const uint8 Source, const uint8 ID)
{
  Function_IN(REGISTER_MENU_TEMP);
  
  switch(Source)
  {
    case INTERNAL_SENSOR:
      TempIntID = ID;
      sprintf(MainViewBuffer[2], "Tint=     ");
      break;
    case EXTERNAL_SENSOR:
      TempExtID = ID;
      sprintf(MainViewBuffer[2] + 10, "Text=");
      break;
    default:
      CONTROL(0, INVALID_INPUT_PARAMETER);
      break;
  }
  
  RETURN_SUCCESS_FUNC(REGISTER_MENU_TEMP);
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Unregister_Menu_Temp(const uint8 Source)
{
  Function_IN(UNREGISTER_MENU_TEMP);
  
  switch(Source)
  {
    case INTERNAL_SENSOR:
      TempIntID = 0xFF;
      sprintf(MainViewBuffer[2], "          ");
      break;
    case EXTERNAL_SENSOR:
      TempExtID = 0xFF;
      sprintf(MainViewBuffer[2] + 10, "          ");
      break;
    default:
      CONTROL(0, INVALID_INPUT_PARAMETER);
      break;
  }
  
  RETURN_SUCCESS_FUNC(REGISTER_MENU_TEMP);
}

/*******************************************************************************
* 
*******************************************************************************/
void Menu_Sec_Int_Callback(void)
{
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
}