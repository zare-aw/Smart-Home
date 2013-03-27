#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "SurfaceFlinger.h"
#include "Menu_Utilities.h"

/**** Gloval Variables ****/
uint16 Year = 1930;
uint8 Month = 1;
uint8 Day = 1;
uint8 Hour = 0;
uint8 Minute = 0;
uint8 Second = 0;

char const Days_Name[NO_OF_DAYS][MAX_DAY_STRING_LENGTH] = { "MONDAY",
                                                            "TUESDAY",
                                                            "WEDNESDAY",
                                                            "THURSDAY",
                                                            "FRIDAY",
                                                            "SATURDAY",
                                                            "SUNDAY"};


char const Events_Name[NO_OF_EVENTS][MAX_EVENT_STRING_LENGTH] = { "ABOVE",
                                                                  "BELOW",
                                                                  "EQUAL",
                                                                  "ABOVE_OR_EQUAL",
                                                                  "BELOW_OR_EQUAL",
                                                                  "DIFFERENT"};

uint8 PointerPosition = 1;
/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Update_Disp_Ptr_Pos(void)
{
  FuncIN(MENU_TIME_UPDATE_DISP_PTR_POS);
  
  switch(PointerPosition)
  {
    case 1:
      printd(3, "^       ");
      break;
    case 2:
      printd(3, " ^      ");
      break;
    case 3:
      printd(3, "   ^    ");
      break;
    case 4:
      printd(3, "    ^   ");
      break;
    case 5:
      printd(3, "      ^ ");
      break;
    case 6:
      printd(3, "       ^");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  EXIT_SUCCESS_FUNC(MENU_TIME_UPDATE_DISP_PTR_POS);
}
FUNC_REGISTER(MENU_TIME_UPDATE_DISP_PTR_POS, Menu_Time_Update_Disp_Ptr_Pos);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Increment_Ptr_Pos_Number(void)
{
  FuncIN(MENU_TIME_INCREMENT_PTR_POS_NUMBER);
  
  switch(PointerPosition)
  {
    case 1:
      if(Hour > 19)
        Hour -= 20;
      else
        Hour += 10;
      break;
    case 2:
      if(Hour%10 == 9)
        Hour -= 9;
      else
        Hour++;
      break;
    case 3:
      if(Minute > 49)
        Minute -= 50;
      else
        Minute += 10;
      break;
    case 4:
      if(Minute%10 == 9)
        Minute -= 9;
      else
        Minute++;
      break;
    case 5:
      if(Second > 49)
        Second -= 50;
      else
        Second += 10;
      break;
    case 6:
      if(Second%10 == 9)
        Second -= 9;
      else
        Second++;
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  EXIT_SUCCESS_FUNC(MENU_TIME_INCREMENT_PTR_POS_NUMBER);
}
FUNC_REGISTER(MENU_TIME_INCREMENT_PTR_POS_NUMBER, Menu_Time_Increment_Ptr_Pos_Number);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Decrement_Ptr_Pos_Number(void)
{
  FuncIN(MENU_TIME_DECREMENT_PTR_POS_NUMBER);
  
  switch(PointerPosition)
  {
    case 1:
      if(Hour < 10)
        Hour += 20;
      else
        Hour -= 10;
      break;
    case 2:
      if(Hour%10 == 0)
        Hour += 9;
      else
        Hour--;
      break;
    case 3:
      if(Minute < 10)
        Minute += 50;
      else
        Minute -= 10;
      break;
    case 4:
      if(Minute%10 == 0)
        Minute += 9;
      else
        Minute--;
      break;
    case 5:
      if(Second < 10)
        Second += 50;
      else
        Second -= 10;
      break;
    case 6:
      if(Second%10 == 0)
        Second += 9;
      else
        Second--;
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  EXIT_SUCCESS_FUNC(MENU_TIME_DECREMENT_PTR_POS_NUMBER);
}
FUNC_REGISTER(MENU_TIME_DECREMENT_PTR_POS_NUMBER, Menu_Time_Decrement_Ptr_Pos_Number);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Time_Set_Ptr_Pos_Number(uint32 Number)
{
  FuncIN(MENU_TIME_SET_PTR_POS_NUMBER);
  
  switch(PointerPosition)
  {
    case 1:
      if(Number < 3)
        Hour = (Hour % 10) + Number * 10;
      else
        EXIT_FUNC(INVALID_INPUT_PARAMETER, MENU_TIME_SET_PTR_POS_NUMBER);
      break;
    case 2:
      Hour = ((Hour / 10) * 10) + Number;
      break;
    case 3:
      if(Number < 6)
        Minute = (Minute % 10) + Number * 10;
      else
        EXIT_FUNC(INVALID_INPUT_PARAMETER, MENU_TIME_SET_PTR_POS_NUMBER);
      break;
    case 4:
      Minute = ((Minute / 10) * 10) + Number;
      break;
    case 5:
      if(Number < 6)
        Second = (Second % 10) + Number * 10;
      else
        EXIT_FUNC(INVALID_INPUT_PARAMETER, MENU_TIME_SET_PTR_POS_NUMBER);
      break;
    case 6:
      Second = ((Second / 10) * 10) + Number;
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  EXIT_SUCCESS_FUNC(MENU_TIME_SET_PTR_POS_NUMBER);
}
FUNC_REGISTER(MENU_TIME_SET_PTR_POS_NUMBER, Menu_Time_Set_Ptr_Pos_Number);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Date_Update_Disp_Ptr_Pos(void)
{
  FuncIN(MENU_DATE_UPDATE_DISP_PTR_POS);
  
  switch(PointerPosition)
  {
    case 1:
      printd(3, "^         ");
      break;
    case 2:
      printd(3, " ^        ");
      break;
    case 3:
      printd(3, "   ^      ");
      break;
    case 4:
      printd(3, "    ^     ");
      break;
    case 5:
      printd(3, "        ^ ");
      break;
    case 6:
      printd(3, "         ^");
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  EXIT_SUCCESS_FUNC(MENU_DATE_UPDATE_DISP_PTR_POS);
}
FUNC_REGISTER(MENU_DATE_UPDATE_DISP_PTR_POS, Menu_Date_Update_Disp_Ptr_Pos);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Date_Increment_Ptr_Pos_Number(void)
{
  FuncIN(MENU_DATE_INCREMENT_PTR_POS_NUMBER);
  
  switch(PointerPosition)
  {
    case 1:
      if(Day > 29)
        Day -= 30;
      else
        Day += 10;
      break;
    case 2:
      if(Day%10 == 9)
        Day -= 9;
      else
        Day++;
      break;
    case 3:
      if(Month > 9)
        Month -= 10;
      else
        Month += 10;
      break;
    case 4:
      if(Month%10 == 9)
        Month -= 9;
      else
        Month++;
      break;
    case 5:
      if(Year > 2089)
        Year -= 90;
      else
        Year += 10;
      break;
    case 6:
      if(Year%10 == 9)
        Year -= 9;
      else
        Year++;
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  EXIT_SUCCESS_FUNC(MENU_DATE_INCREMENT_PTR_POS_NUMBER);
}
FUNC_REGISTER(MENU_DATE_INCREMENT_PTR_POS_NUMBER, Menu_Date_Increment_Ptr_Pos_Number);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Date_Decrement_Ptr_Pos_Number(void)
{
  FuncIN(MENU_DATE_DECREMENT_PTR_POS_NUMBER);
  
  switch(PointerPosition)
  {
    case 1:
      if(Day < 10)
        Day += 30;
      else
        Day -= 10;
      break;
    case 2:
      if(Day%10 == 0)
        Day += 9;
      else
        Day--;
      break;
    case 3:
      if(Month < 10)
        Month += 10;
      else
        Month -= 10;
      break;
    case 4:
      if(Month%10 == 0)
        Month += 9;
      else
        Month--;
      break;
    case 5:
      if(Year < 2010)
        Year += 90;
      else
        Year -= 10;
      break;
    case 6:
      if(Year%10 == 0)
        Year += 9;
      else
        Year--;
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  EXIT_SUCCESS_FUNC(MENU_DATE_DECREMENT_PTR_POS_NUMBER);
}
FUNC_REGISTER(MENU_DATE_DECREMENT_PTR_POS_NUMBER, Menu_Date_Decrement_Ptr_Pos_Number);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Date_Set_Ptr_Pos_Number(uint32 Number)
{
  FuncIN(MENU_DATE_SET_PTR_POS_NUMBER);
  
  switch(PointerPosition)
  {
    case 1:
      if(Number < 4)
        Day = (Day % 10) + Number * 10;
      else
        EXIT_FUNC(INVALID_INPUT_PARAMETER, MENU_DATE_SET_PTR_POS_NUMBER);
      break;
    case 2:
      Day = ((Day / 10) * 10) + Number;
      break;
    case 3:
      if(Number < 2)
        Month = (Month % 10) + Number * 10;
      else
        EXIT_FUNC(INVALID_INPUT_PARAMETER, MENU_DATE_SET_PTR_POS_NUMBER);
      break;
    case 4:
      Month = ((Month / 10) * 10) + Number;
      break;
    case 5:
        Year = 2000 + (Year % 10) + Number * 10;
      break;
    case 6:
      Year = ((Year / 10) * 10) + Number;
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  EXIT_SUCCESS_FUNC(MENU_DATE_SET_PTR_POS_NUMBER);
}
FUNC_REGISTER(MENU_DATE_SET_PTR_POS_NUMBER, Menu_Date_Set_Ptr_Pos_Number);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Repeat_Update_Display(uint8 Offset, const uint32 Menu_Ptr_Pos, uint8 Repeat)
{
  FuncIN(MENU_REPEAT_UPDATE_DISPLAY);
  int i;
  clrd();
  for(i = 1; i <= 4; i++)
  {
    printd(i , "%s %s %s", Menu_Ptr_Pos == (Offset + i) ? ">" : " ", Repeat & 1 << (Offset + i - 1) ? "#" : " ", Days_Name[Offset + i - 1]);  
  }
  EXIT_SUCCESS_FUNC(MENU_REPEAT_UPDATE_DISPLAY);
}
FUNC_REGISTER(MENU_REPEAT_UPDATE_DISPLAY, Menu_Repeat_Update_Display);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Increment_Ptr_Pos_Number(sint16 *Number_)
{
  FuncIN(MENU_TEMP_INCREMENT_PTR_POS_NUMBER);
  sint16 Number = *Number_;
  
  switch(PointerPosition)
  {
    case 1:
        Number *= -1;
      break;
    case 2:
      if(Number >= 0)
      {
        if(Number / 1000 == 9)
          Number -= 9000;
        else
          Number += 1000;
      } 
      else 
      {
        if(Number / 1000 == -9)
          Number += 9000;
        else
          Number -= 1000;
      }
      break;
    case 3:
      if(Number >= 0)
      {
        if((Number / 100) % 10 == 9)
          Number -= 900;
        else
          Number += 100;
      }
      else
      {
        if((Number / 100) % 10 == 9)
          Number += 900;
        else
          Number -= 100;
      }        
      break;
    case 4:
      if(Number >= 0)
      {
        if((Number / 10) % 10 == 9)
          Number -= 90;
        else
          Number += 10;
      }
      else
      {
        if((Number / 10) % 10 == 9)
          Number += 90;
        else
          Number -= 10;
      }
      break;
    case 5:
      if(Number >= 0)
      {
        if(Number%10 == 9)
          Number -= 9;
        else
          Number++;
      }
      else
      {
        if(Number%10 == 9)
          Number += 9;
        else
          Number--;
      }
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  
  *Number_ = Number;
  EXIT_SUCCESS_FUNC(MENU_TEMP_INCREMENT_PTR_POS_NUMBER);
}
FUNC_REGISTER(MENU_TEMP_INCREMENT_PTR_POS_NUMBER, Menu_Temp_Increment_Ptr_Pos_Number);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Decrement_Ptr_Pos_Number(sint16 *Number_)
{
  FuncIN(MENU_TEMP_DECREMENT_PTR_POS_NUMBER);
  
  sint16 Number = *Number_;
  switch(PointerPosition)
  {
  case 1:
    Number *= -1;
    break;
  case 2:
      if(Number >= 0)
      {
        if(Number / 1000 == 0)
          Number += 9000;
        else
          Number -= 1000;
      }
      else
      {
        if(Number / 1000 == 0)
          Number -= 9000;
        else
          Number += 1000;
      }
      break;
    case 3:
      if(Number >= 0)
      {
        if((Number / 100) % 10 == 0)
          Number += 900;
        else
          Number -= 100;
      }
      else
      {
        if((Number / 100) % 10 == 0)
          Number -= 900;
        else
          Number += 100;
      }
        break;
    case 4:
      if(Number >= 0)
      {      
        if((Number / 10) % 10 == 0)
          Number += 90;
        else
          Number -= 10;
      }
      else
      {
        if((Number / 10) % 10 == 0)
          Number -= 90;
        else
          Number += 10; 
      }
      break;
    case 5:
      if(Number >= 0)
      {      
        if(Number%10 == 0)
          Number += 9;
        else
          Number--;
      }
      else
      {
        if(Number%10 == 0)
          Number -= 9;
        else
          Number++;
      }
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  *Number_ = Number;
  EXIT_SUCCESS_FUNC(MENU_TEMP_DECREMENT_PTR_POS_NUMBER);
}
FUNC_REGISTER(MENU_TEMP_DECREMENT_PTR_POS_NUMBER, Menu_Temp_Decrement_Ptr_Pos_Number);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Set_Ptr_Pos_Number(sint16 *Number_, sint8 Digit)
{
  FuncIN(MENU_TEMP_SET_PTR_POS_NUMBER);

  sint16 Number = *Number_;
  if(Number < 0)
    Digit *= -1;
    
  switch(PointerPosition)
  {
    case 1:
      break;
    case 2:
      Number = (Number % 1000) + Digit * 1000;
      break;
    case 3:
      Number += (-((Number / 100) % 10) + Digit) * 100;
      break;
    case 4:
      Number += (-((Number % 100) / 10) + Digit) * 10;
      break;
    case 5:
      Number += -(Number % 10) + Digit;
      break;
    default:
      Fatal_Abort(-UNKNOWN_ERROR);
      break;
  }
  *Number_ = Number;
  EXIT_SUCCESS_FUNC(MENU_TEMP_SET_PTR_POS_NUMBER);
}
FUNC_REGISTER(MENU_TEMP_SET_PTR_POS_NUMBER, Menu_Temp_Set_Ptr_Pos_Number);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Menu_Temp_Update_Event(uint8 Offset, const uint32 Menu_Ptr_Pos, uint8 Event)
{
  FuncIN(MENU_TEMP_UPDATE_EVENT);
  int i;
  clrd();
  for(i = 1; i <= 4; i++)
  {
    printd(i , "%s %s %s", Menu_Ptr_Pos == (Offset + i) ? ">" : " ", Event == Offset + i ? "#" : " ", Events_Name[Offset + i - 1]);  
  }
  EXIT_SUCCESS_FUNC(MENU_TEMP_UPDATE_EVENT);
}
FUNC_REGISTER(MENU_TEMP_UPDATE_EVENT, Menu_Temp_Update_Event);