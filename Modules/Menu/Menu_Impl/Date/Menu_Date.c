#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu.h"
#include "Menu_Func.h"
#include "SurfaceFlinger.h"
#include "RTC.h"

uint16 Year;
uint8 Month;
uint8 Day;
static uint8 PointerPosition = 1;

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t Menu_Date_Update_Disp_Ptr_Pos(void)
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
static Status_t Menu_Date_Increment_Ptr_Pos_Number(void)
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
static Status_t Menu_Date_Decrement_Ptr_Pos_Number(void)
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
static Status_t Menu_Date_Set_Ptr_Pos_Number(uint32 Number)
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
        Year = (Year % 10) + Number * 10;
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


uint8 DatePath[] = {1};
MENU_STATE_CREATE(
  Date,
  DatePath,
  1,
  0x00,
  ENTER_KEY_EVENT | \
  CANCEL_KEY_EVENT,
  NULL,
  "Date"
);