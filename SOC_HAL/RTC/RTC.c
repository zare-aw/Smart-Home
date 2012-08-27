#include "Global_Defines.h"
#include "RTC.h"
#include "RTC_Debug.h"
#include "RTC_Defconfig.h"
#include "RTC_Func.h"


 /* RTC interrupt type */
#define RTCIncrementInt  0x1
#define RTCAlarmInt      0x2
#define RTCALLInt        0x3

uint8 AlarmIntType_Beckup = 0;

void *Sys_Time_Update[RTC_INC_CALLBACKS] = {NULL};
uint8 Sys_Time_Type[RTC_INC_CALLBACKS] = {0};
RtcSwAlarm_t SwAlarm[NO_OF_SW_ALARMS] = {0};

uint8 SwAlarmCount = 0;
uint8 SwAlarmCallbackID = 255;

void (*Alarm)(void) = NULL;
Status_t RTC_SW_Alarm_Callback(void *InPtr);

/*************************************************************************
 * Function Name: IsLeapYear
 * @in: uint16 Year
 * @out: uint8
 * Description: Judge whether the specifying year is leap year. 
 *************************************************************************/
static uint8 Is_Leap_Year(uint16 Year)
{
  if (!(Year % 4) && (Year % 100) || !(Year % 400))
    return TRUE;
  return FALSE;
}

/*************************************************************************
 * Function Name: GetDoY
 * @in: uint16 Year
 * @in: uint8 Month
 * @in: uint8 Day
 * @out: uint16 (Day of Year)
 * Description: Get the Day of year according to the date
 *************************************************************************/
static uint16 Get_DoY(uint16 Year, uint8 Month, uint8 Day)
{
  uint16 DoY = 0, i;

  for(i = 1; i < Month; i++)
    DoY += RTC_MonthVal[i];

  if(Month > 2)
    if(Is_Leap_Year(Year))
      DoY ++;

  return (DoY + Day);
}

/*************************************************************************
 * Function Name: GetDoW
 * @in: uint16 Year
 * @in: uint8 Month
 * @in: uint8 Day
 * @out: uint8 -- (0~6)
 * Description: Get the day of week according to the date.
 * NOTE: Year is not smaller than RTC_YEARMIN (1901).
 *************************************************************************/
static uint8 Get_DoW(uint16 Year, uint8 Month, uint8 Day)
{
  int i, DoW=0;

  for (i = RTC_BASEYEAR, DoW = 0; i < Year; i++)
  {
    DoW += 365;
    if(Is_Leap_Year(i))
      DoW++;
  }

  DoW +=  Get_DoY(Year, Month, Day) - 1;
  DoW = (DoW + RTC_BASEDOW) % 7;

  return DoW;
}

/*************************************************************************
 * Function Name: Is_Valid_Day
 * @in: uint16 Year
 * @in: uint8 Month
 * @in: uint8 Day
 * @out: uint8  false -- not valid day
 *        true -- valid day
 * Description: Check if the specify day is valid
 * NOTE: Year is not smaller than RTC_YEARMIN (1901).
 *************************************************************************/
static uint8 Is_Valid_Day(uint16 Year, uint8 Month, uint8 Day)
{
  /* Valid Judge */
  if(Year < RTC_YEARMIN || Year > RTC_YEARMAX || Day < 1)
    return FALSE;

  switch(Month)
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      if(Day > 31)
        return FALSE;
      else
        break;
    case 4:
    case 6:
    case 9:
    case 11:
      if(Day > 30)
        return FALSE;
      else
        break;
    case 2:
      if(Is_Leap_Year(Year))
        if(Day > 29)
          return FALSE;
        else
          break;
      else
        if(Day > 28)
          return FALSE;
        else
          break;
    default:
      return FALSE;
  }

  return TRUE;
}

/*************************************************************************
 * Function Name: RTC_Enable
 * @in: void
 * @out: void 
 * Description: Enable RTC, let RTC run.
 *************************************************************************/
void RTC_Enable(void)
{
  CCR_bit.CLKEN = TRUE;
  return ;
}

/*************************************************************************
 * Function Name: RTC_Disable
 * @in: void
 * @out: void 
 * Description: Disable RTC, let RTC stop.
 *************************************************************************/
void RTC_Disable(void)
{
  CCR_bit.CLKEN = FALSE;
  return ;
}

/*************************************************************************
 * Function Name: RTC_Init
 * @in: void
 * @out: Status_t
 * Description: Initialize RTC, configure prescaler, CIIR and AMR register
 *************************************************************************/
Status_t RTC_Init(uint8 ClkSource)
{
  FuncIN(RTC_INIT);
  unsigned int PreInt;
  
  if(CCR_bit.CLKEN == TRUE && ClkSource == FALSE)
    EXIT_SUCCESS_FUNC(RTC_INIT);
  
  RTC_Disable();
  
  if(ClkSource)
  {
    // initialize prescaler of RTC
    PreInt = (int)(30000000 / RTC_COUNT_PER_SEC) - 1;
    ASSERT(PreInt > 0, -RTC_INIT_ERROR);
    
    PREINT = PreInt;
    PREFRAC = 30000000 - (PreInt + 1) * RTC_COUNT_PER_SEC;
    CCR_bit.CLKSRC = 0;   // AHB Clk source
  }
  else
  {
    CCR_bit.CLKSRC = 1;   // 32kHz watch quartz
  }
  
  CCR_bit.CTCRST = 1;   // Reset
  CCR_bit.CTCRST = CCR_bit.CTTEST = 0;    // test disable and reset
  
  // initialize interrupt mask register of RTC
  AMR = 0;
  CIIR_bit.IMSEC = 1;

  ILR = 0x3;    // clear all interrupt of RTC
    
  // initialize Date and Time
  VERIFY(RTC_Set_Date_Time(&RTC_InitDateTime), -RTC_SET_ERROR);

//  RTC_Enable();
  
  EXIT_SUCCESS_FUNC(RTC_INIT);
}
FUNC_REGISTER(RTC_INIT, RTC_Init);

/*************************************************************************
 * Function Name: RTC_SetDate
 * @in: RtcDate_t *Date_p
 * @out: Status_t
 * Description: Set your specifying date
 *************************************************************************/
Status_t RTC_Set_Date(RtcDate_t *Date_p)
{
  FuncIN(RTC_SET_DATE);
  
  ASSERT(Date_p != NULL, -INVALID_INPUT_POINTER);
  
  // Valid Judge
  if(Is_Valid_Day(Date_p -> Year, Date_p -> Month, Date_p -> Day) != TRUE)
    EXIT_FUNC(RTC_INVALID_DATE_ERROR, RTC_SET_DATE);

  // Calculate DOW, DOY
  Date_p -> DoY = Get_DoY(Date_p -> Year, Date_p -> Month, Date_p -> Day);
  Date_p -> DoW = Get_DoW(Date_p -> Year, Date_p -> Month, Date_p -> Day);

  DOM = Date_p -> Day;
  MONTH = Date_p -> Month;
  YEAR = Date_p -> Year;
  DOW = Date_p -> DoW;
  DOY = Date_p -> DoY;

  EXIT_SUCCESS_FUNC(RTC_SET_DATE);
}
FUNC_REGISTER(RTC_SET_DATE, RTC_Set_Date);

/*************************************************************************
 * Function Name: RTC_Set_Time
 * @in: RtcTime_t *Time_p
 * @out: Status_t 
 * Description: Set your specifying time
 *************************************************************************/
Status_t RTC_Set_Time(RtcTime_t *Time_p)
{
  FuncIN(RTC_SET_TIME);
  
  ASSERT(Time_p != NULL, -INVALID_INPUT_POINTER);
  
  // Valid Judge
  if(Time_p -> Hour > 23 || Time_p -> Minute > 59 || Time_p -> Second > 59)
    EXIT_FUNC(RTC_INVALID_TIME_ERROR, RTC_SET_TIME);
  
  HOUR = Time_p -> Hour;
  MIN = Time_p -> Minute;
  SEC = Time_p -> Second;

  EXIT_SUCCESS_FUNC(RTC_SET_TIME);
}
FUNC_REGISTER(RTC_SET_TIME, RTC_Set_Time);

/*************************************************************************
 * Function Name: RTC_Set_Date_Time
 * @in: RtcDateTime_t *DateTime_p
 * @out: Status_t 
 * Description: Set your specifying date and time
 *************************************************************************/
Status_t RTC_Set_Date_Time(RtcDateTime_t *DateTime_p)
{
  FuncIN(RTC_SET_DATE_TIME);
  
  ASSERT(DateTime_p != NULL, -INVALID_INPUT_POINTER);
  
  // Valid Judge
  if(Is_Valid_Day(DateTime_p -> Year, DateTime_p -> Month, DateTime_p -> Day) != TRUE)
    EXIT_FUNC(RTC_INVALID_DATE_ERROR, RTC_SET_DATE_TIME);
  if(DateTime_p -> Hour > 23 || DateTime_p -> Minute > 59 || DateTime_p -> Second > 59)
    EXIT_FUNC(RTC_INVALID_TIME_ERROR, RTC_SET_DATE_TIME);

  // Calculate DoW, DoY
  DateTime_p -> DoY = Get_DoY(DateTime_p -> Year, DateTime_p -> Month, DateTime_p -> Day);
  DateTime_p -> DoW = Get_DoW(DateTime_p -> Year, DateTime_p -> Month, DateTime_p -> Day);
    
  DOM = DateTime_p -> Day;
  MONTH = DateTime_p -> Month;
  YEAR = DateTime_p -> Year;
  DOW = DateTime_p -> DoW;
  DOY = DateTime_p -> DoY;

  HOUR = DateTime_p -> Hour;
  MIN = DateTime_p -> Minute;
  SEC = DateTime_p -> Second;

  EXIT_SUCCESS_FUNC(RTC_SET_DATE_TIME);
}
FUNC_REGISTER(RTC_SET_DATE_TIME, RTC_Set_Date_Time);

/*************************************************************************
 * Function Name: RTC_Get_Date
 * @in: RtcDate_t *Date_p
 * @out: Status_t
 * Description: Get the current date
 *************************************************************************/
Status_t RTC_Get_Date(RtcDate_t *Date_p)
{
  FuncIN(RTC_GET_DATE);
  
  ASSERT(Date_p != NULL, -INVALID_INPUT_POINTER);
  
  Date_p -> Day = DOM;
  Date_p -> Month = MONTH;
  Date_p -> Year = YEAR;

  Date_p -> DoW = DOW;
  Date_p -> DoY = DOY;
  
  EXIT_SUCCESS_FUNC(RTC_GET_DATE);
}
FUNC_REGISTER(RTC_GET_DATE, RTC_Get_Date);

/*************************************************************************
 * Function Name: RTC_Get_Time
 * @in: RtcTime_t *Time_p
 * @out: Status_t
 * Description: Get the current time
 *************************************************************************/
Status_t RTC_Get_Time(RtcTime_t *Time_p)
{
  FuncIN(RTC_GET_TIME);
  
  ASSERT(Time_p != NULL, -INVALID_INPUT_POINTER);
  
  Time_p -> Hour = HOUR;
  Time_p -> Minute = MIN;
  Time_p -> Second = SEC;

  EXIT_SUCCESS_FUNC(RTC_GET_TIME);
}
FUNC_REGISTER(RTC_GET_TIME, RTC_Get_Time);

/*************************************************************************
 * Function Name: RTC_Get_Date_Time
 * @in: RtcDateTime_t *DateTime_p
 * @out: Status_t
 * Description: Get the current date and time
 *************************************************************************/
Status_t RTC_Get_Date_Time(RtcDateTime_t *DateTime_p)
{
  FuncIN(RTC_GET_DATE_TIME);
  
  ASSERT(DateTime_p != NULL, -INVALID_INPUT_POINTER);
  
  DateTime_p -> Day = DOM;
  DateTime_p -> Month = MONTH;
  DateTime_p -> Year = YEAR;

  DateTime_p -> Hour = HOUR;
  DateTime_p -> Minute = MIN;
  DateTime_p -> Second = SEC;

  DateTime_p -> DoW = DOW;
  DateTime_p -> DoY = DOY;

  EXIT_SUCCESS_FUNC(RTC_GET_DATE_TIME);
}
FUNC_REGISTER(RTC_GET_DATE_TIME, RTC_Get_Date_Time);

/*************************************************************************
 * Function Name: RTC_Enable_Inct_Int
 * @in: uint8 IncIntType
 * @in: void* Callback_p
 * @out: void 
 * Description: Set increment interrupt type
 *************************************************************************/
static Status_t RTC_Enable_Inc_Int(uint8 IncIntType)
{
  FuncIN(RTC_ENABLE_INC_INT);
  
  switch(IncIntType)
  {
    case IncIntType_SEC:
    case IncIntType_MIN:
    case IncIntType_HOUR:
    case IncIntType_DAY:
    case IncIntType_MON:
    case IncIntType_YEAR:
    case IncIntType_DOW:
    case IncIntType_DOY:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  CIIR |= IncIntType;
  
  EXIT_SUCCESS_FUNC(RTC_ENABLE_INC_INT);
}
FUNC_REGISTER(RTC_ENABLE_INC_INT, RTC_Enable_Inc_Int);

/*************************************************************************
 * Function Name: RTC_Disable_Inc_Int
 * @in: void
 * @out: void 
 * Description: Disable RTC increment interrupt.
 *************************************************************************/
static Status_t RTC_Disable_Inc_Int(uint8 IncIntType)
{
  FuncIN(RTC_DISABLE_INC_INT);
  
  switch(IncIntType)
  {
    case IncIntType_SEC:
    case IncIntType_MIN:
    case IncIntType_HOUR:
    case IncIntType_DAY:
    case IncIntType_MON:
    case IncIntType_YEAR:
    case IncIntType_DOW:
    case IncIntType_DOY:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  CIIR &= ~IncIntType;
  
  EXIT_SUCCESS_FUNC(RTC_DISABLE_INC_INT);
}
FUNC_REGISTER(RTC_DISABLE_INC_INT, RTC_Disable_Inc_Int);

/*************************************************************************
 * 
*************************************************************************/
Status_t RTC_Register_Inc_Int(void *Callback_p, uint32 Type, uint8 *Alarm_ID)
{
  FuncIN(RTC_REGISTER_INC_INT);
  
  int i;
  
  ASSERT(Callback_p != NULL, -INVALID_INPUT_POINTER);
  ASSERT(Alarm_ID != NULL, -INVALID_INPUT_POINTER);
  
  for(i = 0; i < RTC_INC_CALLBACKS; i++)
    if(Sys_Time_Update[i] == NULL)
    {
      Sys_Time_Update[i] = Callback_p;
      Sys_Time_Type[i] = Type;
      RTC_Enable_Inc_Int(Type);
      *Alarm_ID = i;
      RTC_DEBUG(printc("\r # RTC increment interrupt callback registered, Type = %d, ID = %d\n", Type, i));
      break;
    }
  
  if(i >= RTC_INC_CALLBACKS)
    EXIT_FUNC(RTC_INC_INT_SLOTS_ERROR, RTC_REGISTER_INC_INT);
  
  RETURN_SUCCESS_FUNC(RTC_REGISTER_INC_INT);
}
FUNC_REGISTER(RTC_REGISTER_INC_INT, RTC_Register_Inc_Int);

/*************************************************************************
 * 
*************************************************************************/
Status_t RTC_Unregister_Inc_Int(uint8 Alarm_ID)
{
  FuncIN(RTC_UNREGISTER_INC_INT);
  
  int i;
  
  if(Sys_Time_Update[Alarm_ID] == NULL)
    EXIT_FUNC(RTC_INC_INT_NOT_VALID, RTC_UNREGISTER_INC_INT);
  
  Sys_Time_Update[Alarm_ID] = NULL;
  
  for(i = 0; i < RTC_INC_CALLBACKS; i++)
    if(Sys_Time_Type[i] == Sys_Time_Type[Alarm_ID])
      break;
  
  if(i >= RTC_INC_CALLBACKS)
    RTC_Disable_Inc_Int(Sys_Time_Type[Alarm_ID]);
  
  EXIT_SUCCESS_FUNC(RTC_UNREGISTER_INC_INT);
}
FUNC_REGISTER(RTC_UNREGISTER_INC_INT, RTC_Unregister_Inc_Int);

/*************************************************************************
 * Function Name: RTC_Disable_Alarm
 * @in: void
 * @out: void 
 * Description: Disable RTC alarm interrupt.
 *************************************************************************/
void RTC_Disable_Alarm(void)
{
  AMR = 0xFF;
}

/*************************************************************************
 * Function Name: RTC_Set_Alarm
 * @in: RtcDateTime_t *DateTime_p
 * @in: uint8 AlarmIntType
 * @in: void* Callback_p
 * @out: Status_t
 * Description: Set your specifying alarm date, time and callback function
 *              and enable interrupt
 *************************************************************************/
Status_t RTC_Enable_Alarm(uint8 AlarmIntType, RtcDateTime_t *DateTime_p, void *Callback_p)
{
  FuncIN(RTC_ENABLE_ALARM);
  
  if(DateTime_p != NULL)
  {
    // Valid Judge
    if(Is_Valid_Day(DateTime_p -> Year, DateTime_p -> Month, DateTime_p -> Day) != TRUE)
      EXIT_FUNC(RTC_INVALID_DATE_ERROR, RTC_ENABLE_ALARM);
    if(DateTime_p -> Hour > 23 || DateTime_p -> Minute > 59 || DateTime_p -> Second > 59)
      EXIT_FUNC(RTC_INVALID_TIME_ERROR, RTC_ENABLE_ALARM);
    
    // Calculate DoW, DoY
    DateTime_p -> DoY = Get_DoY(DateTime_p -> Year, DateTime_p -> Month, DateTime_p -> Day);
    DateTime_p -> DoW = Get_DoW(DateTime_p -> Year, DateTime_p -> Month, DateTime_p -> Day);
    
    ALDOM = DateTime_p -> Day;
    ALMON = DateTime_p -> Month;
    ALYEAR = DateTime_p -> Year;
    ALDOW = DateTime_p -> DoW;
    ALDOY = DateTime_p -> DoY;
    
    ALHOUR = DateTime_p -> Hour;
    ALMIN = DateTime_p -> Minute;
    ALSEC = DateTime_p -> Second;
  }
    
  if(Callback_p != NULL)
    Alarm = (void(*)(void))Callback_p;
  
  if(AlarmIntType == NULL)
    AMR = ~AlarmIntType_Beckup & 0xFF;
  else
  {
    AMR = ~AlarmIntType & 0xFF;
    AlarmIntType_Beckup = AlarmIntType;
  }
  
  EXIT_SUCCESS_FUNC(RTC_ENABLE_ALARM);
}
FUNC_REGISTER(RTC_ENABLE_ALARM, RTC_Enable_Alarm);

/*************************************************************************
 * Function Name: RTC_Clear Int
 * @in: uint32 IntType
 * @out: Status_t
 * Description: Clear RTC interrupt.
 *************************************************************************/
Status_t RTC_Clear_Int(uint32 IntType)
{
  FuncIN(RTC_CLEAR_INT);
  
  switch(IntType)
  {
    case RTCIncrementInt:
    case RTCAlarmInt:
    case RTCALLInt:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
      break;
  }
  
  ILR = (IntType & 0x3);
  
  EXIT_SUCCESS_FUNC(RTC_CLEAR_INT);
}
FUNC_REGISTER(RTC_CLEAR_INT, RTC_Clear_Int);

/*************************************************************************
 * Function Name: RTC_Check_Int_Type
 * @in: void
 * @out:  uint32
 * Description: Get RTC interrupt Type.
 *************************************************************************/
uint32 RTC_Check_Int_Type(void)
{
  return (ILR & 0x3);
}

/*************************************************************************
 * Function Name: RTC_Register_SW_Alarm
 * @in: AlarmData_p - Data with alarm parameters
 * @out: Status_t, AlarmID - ID on registered alarm
 * Description: Register RTC software alarm.
 *************************************************************************/
Status_t RTC_Register_SW_Alarm(RtcSwAlarm_t *AlarmData_p, uint8 *AlarmID)
{
  FuncIN(RTC_REGISTER_SW_ALARM);
  
  int i;
  
  for(i = 0; i < NO_OF_SW_ALARMS; i++)
  {
    if(SwAlarm[i].State == NO_ALARM_SET)
    {
      SwAlarm[i] = *AlarmData_p;
      *AlarmID = i;
      break;
    }
  }
  
  if(i >= NO_OF_SW_ALARMS)
    EXIT_FUNC(RTC_SW_ALARM_SLOTS_ERROR, RTC_REGISTER_SW_ALARM);
  
  if(SwAlarmCount == 0)
  {
    RTC_Register_Inc_Int((void *)RTC_SW_Alarm_Callback, AlarmIntType_MIN, &SwAlarmCallbackID);
    RTC_DEBUG(printc("\r # Software Alarm callback registered on RTC icrement interrupt with ID = %d\n", SwAlarmCallbackID));
  }
  
  SwAlarmCount++;
  ASSERT(SwAlarmCount <= NO_OF_SW_ALARMS, -RTC_SW_ALARM_SLOTS_ERROR);
  
  EXIT_SUCCESS_FUNC(RTC_REGISTER_SW_ALARM);
}
FUNC_REGISTER(RTC_REGISTER_SW_ALARM, RTC_Register_SW_Alarm);

/*************************************************************************
 * Function Name: RTC_Unregister_SW_Alarm
 * @in: 
 * @out: Status_t, AlarmID - ID on registered alarm
 * Description: Register RTC software alarm.
 *************************************************************************/
Status_t RTC_Unregister_SW_Alarm(uint8 AlarmID)
{
  FuncIN(RTC_UNREGISTER_SW_ALARM);
  
  if(SwAlarmCount == 0)
    EXIT_FUNC(RTC_SW_ALARM_NOT_VALID, RTC_UNREGISTER_SW_ALARM);
  
  if(SwAlarm[AlarmID].State == NO_ALARM_SET)
    EXIT_FUNC(RTC_SW_ALARM_NOT_VALID, RTC_UNREGISTER_SW_ALARM);
  
  SwAlarm[AlarmID].State = NO_ALARM_SET;
  
  SwAlarmCount--;
  
  if(SwAlarmCount == 0)
  {
    RTC_Unregister_Inc_Int(SwAlarmCallbackID);
    RTC_DEBUG(printc("\r # Software Alarm callback Unregistered on RTC icrement interrupt with ID = %d\n", SwAlarmCallbackID));
  }
  
  EXIT_SUCCESS_FUNC(RTC_UNREGISTER_SW_ALARM);
}
FUNC_REGISTER(RTC_UNREGISTER_SW_ALARM, RTC_Unregister_SW_Alarm);

/*************************************************************************
 * Function Name: RTC_Register_SW_Alarm
 * @in: None
 * @out: Status_t, NoOfAlarms
 * @out: AlarmData_p - Array with data with alarm parameters. Size = NO_OF_SW_ALARMS
 * Description: Register RTC software alarm.
 *************************************************************************/
Status_t RTC_Get_Registered_Sw_Alarms(RtcSwAlarm_t *AlarmData, uint8 *NoOfAlarms)
{
  FuncIN(RTC_GET_REGISTERED_SW_ALARM);
  
  *NoOfAlarms = 0;
  
  for(int i = 0; i < NO_OF_SW_ALARMS; i++)
  {
    if(SwAlarm[i].State != NO_ALARM_SET)
    {
      AlarmData[*NoOfAlarms] = SwAlarm[i];
      *NoOfAlarms ++;
    }
  }
  
  EXIT_SUCCESS_FUNC(RTC_GET_REGISTERED_SW_ALARM);
}
FUNC_REGISTER(RTC_GET_REGISTERED_SW_ALARM, RTC_Get_Registered_Sw_Alarms);
  
/*************************************************************************
 * Function Name: RTC_SW_Alarm_Callback
 * @in: 
 * @out: Status_t
 * Description: RTC software alarm callback.
 *************************************************************************/
Status_t RTC_SW_Alarm_Callback(void *InPtr)
{
  FuncIN(RTC_SW_ALARM_CALLBACK);
  
  RtcDateTime_t DateTime = {0};
  
  for(int i = 0; i < NO_OF_SW_ALARMS; i++)
  {
    if(SwAlarm[i].State == RTC_ALARM_ON)
    {
      RTC_Get_Date_Time(&DateTime);
      
      if((SwAlarm[i].Minute == DateTime.Minute) && (SwAlarm[i].Hour == DateTime.Hour))
      {
        if(SwAlarm[i].Year != 0)
        {
          if((SwAlarm[i].Year == DateTime.Year) && (SwAlarm[i].Month == DateTime.Month) && (SwAlarm[i].Day == DateTime.Day))
          {
            VERIFY(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), -RTC_GENERAL_ERROR);
            SwAlarm[i].State = RTC_ALARM_OFF;
          }
        }
        else
        {
          if(SwAlarm[i].Mode == SINGLE_ALARM)
          {
            VERIFY(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), -RTC_GENERAL_ERROR);
            SwAlarm[i].State = RTC_ALARM_OFF;
          }
          else if(SwAlarm[i].Mode == REPETITIVE_ALARM)
          {
            switch(DateTime.DoW)
            {
              case 1:
                if(SwAlarm[i].DoW & MONDAY)
                  VERIFY(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), -RTC_GENERAL_ERROR);
                break;
              case 2:
                if(SwAlarm[i].DoW & TUESDAY)
                  VERIFY(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), -RTC_GENERAL_ERROR);
                break;
              case 3:
                if(SwAlarm[i].DoW & WEDNESDAY)
                  VERIFY(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), -RTC_GENERAL_ERROR);
                break;
              case 4:
                if(SwAlarm[i].DoW & THURSDAY)
                  VERIFY(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), -RTC_GENERAL_ERROR);
                break;
              case 5:
                if(SwAlarm[i].DoW & FRIDAY)
                  VERIFY(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), -RTC_GENERAL_ERROR);
                break;
              case 6:
                if(SwAlarm[i].DoW & SATURDAY)
                  VERIFY(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), -RTC_GENERAL_ERROR);
                break;
              case 0:
                if(SwAlarm[i].DoW & SUNDAY)
                  VERIFY(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), -RTC_GENERAL_ERROR);
                break;
              default:
                Fatal_Abort(-REGISTER_ERROR);
            } // switch(DateTime.DoW)
          }
          else
            Fatal_Abort(-RTC_GENERAL_ERROR);
        }
      }
    }
  } // for
  
  EXIT_SUCCESS_FUNC(RTC_SW_ALARM_CALLBACK);
}
FUNC_REGISTER(RTC_SW_ALARM_CALLBACK, RTC_SW_Alarm_Callback);

/*************************************************************************
 * Function Name: RTC_ISR
 * @in:  void
 * @out: void
 * Description: Rtc interrupt subroutine
 *************************************************************************/
__irq __arm void RTC_Isr(void)
{
  FuncIN(RTC_ISR);
  
  uint32 IntStatus;
  RtcDateTime_t DateTime = {0};
  
  IntStatus = RTC_Check_Int_Type();
  if(RTC_Clear_Int(IntStatus) != SUCCESS)
    RTC_Clear_Int(RTCALLInt);
  
  if(IntStatus & RTCIncrementInt)    // Increment Interrupt
  {
    for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Second int
    {
      if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_SEC)
        VERIFY(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), -RTC_GENERAL_ERROR);
    }
    
    RTC_Get_Date_Time(&DateTime);
    
    if(DateTime.Second == 0)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Minute int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_MIN)
          VERIFY(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), -RTC_GENERAL_ERROR);
      }
    }
    
    if(DateTime.Minute == 0)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Hour int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_HOUR)
          VERIFY(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), -RTC_GENERAL_ERROR);
      }
    }
    
    if(DateTime.Hour == 0)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Day int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_DAY)
          VERIFY(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), -RTC_GENERAL_ERROR);
      }
    }
    
    if(DateTime.Day == 1)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Month int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_MON)
          VERIFY(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), -RTC_GENERAL_ERROR);
      }
    }
    
    if(DateTime.Month == 1)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Year int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_YEAR)
          VERIFY(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), -RTC_GENERAL_ERROR);
      }
    }
    
    if(DateTime.DoW == 1)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // DoW int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_DOW)
          VERIFY(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), -RTC_GENERAL_ERROR);
      }
    }
  } // if (IntStatus & RTCIncrementInt)
  
  if (IntStatus & RTCAlarmInt)            // Alarm Interrupt
  {
    if(Alarm != NULL)
      Alarm();
  }
  
  FuncOUT(RTC_ISR);
  
  VICVectAddr = 0;
}
FUNC_REGISTER(RTC_ISR, RTC_Isr);

/*************************************************************************
 * Function Name: FormatDate
 * @in: uint8 Type
 * @in: RtcDate_t *Date_p
 * @in: char *s
 * @out: Status_t
 * Description: Format the current date into an ASCII string according to the Type.
 *        Type = 1, "DD-MM-YYYY" (11 chars)
 *        Type = 2, "DOW, DD Month  YYYY" (30 chars)
 *  
 *************************************************************************/
Status_t Format_Date(uint8 Type, RtcDate_t *Date_p, char *String)
{
  FuncIN(FORMAT_DATE);
  
  uint16 Year;
  uint8 Month, Day, DoW;
  char Str[5];
  
  ASSERT(Date_p != NULL, -INVALID_INPUT_POINTER);
  ASSERT(String != NULL, -INVALID_INPUT_POINTER);
  
  Year = Date_p -> Year;
  Month = Date_p -> Month;
  Day = Date_p -> Day;
  DoW = Date_p -> DoW;
//  DoY = pDate->DoY;
    
  switch(Type)
  {
    case 1:
      strcpy(String, "DD-MM-YYYY");
      String[6] = Year / 1000 + '0';
      Year = Year % 1000;
      String[7] = Year / 100 + '0';
      Year = Year % 100;
      String[8] = Year / 10 + '0';
      String[9] = Year % 10 + '0';
      String[3] = Month / 10 + '0';
      String[4] = Month % 10 + '0';
      String[0] = Day / 10 + '0';
      String[1] = Day % 10 + '0';
      break;
    case 2:
      strcpy(String, RTC_DOWTbl[DoW]);
      strcat(String, " ");
      
      Str[0] = Day / 10 + '0';
      Str[1] = Day % 10 + '0';
      Str[2] = '\0';
      strcat(String, Str);
      strcat(String, ", ");
      
      strcat(String, RTC_MonthTbl[Month]);
      sprintf(Str,"%d",Year);
      strcat(String, Str);
      break;        
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
      break;
  } // switch
  
  EXIT_SUCCESS_FUNC(FORMAT_DATE);
}
FUNC_REGISTER(FORMAT_DATE, Format_Date);

/*************************************************************************
 * Function Name: FormatTime
 * @in: uint8 Type
 * @in: RtcTime_t *Time_p
 * @in: char *s
 * @out: Status_t
 * Description: Format the current time into an ASCII string according to the Type.
 *        Type = 1, "HH:MM:SS" (9 chars)
 *        Type = 2, "HH:MM:SS AM" (13 chars)
 *************************************************************************/
Status_t Format_Time(uint8 Type, RtcTime_t *Time_p, char *String)
{
  FuncIN(FORMAT_TIME);
  
  uint8 Hour, Minute, Second;

  ASSERT(Time_p != NULL, -INVALID_INPUT_POINTER);
  ASSERT(String != NULL, -INVALID_INPUT_POINTER);
  
  Hour = Time_p -> Hour;
  Minute = Time_p -> Minute;
  Second = Time_p -> Second;
    
  switch(Type)
  {
    case 1:
      strcpy(String, "HH:MM:SS");
      String[0] = Hour / 10 + '0';
      String[1] = Hour % 10 + '0';
      String[3] = Minute / 10 + '0';
      String[4] = Minute % 10 + '0';
      String[6] = Second / 10 + '0';
      String[7] = Second % 10 + '0';
      break;
    case 2:
      strcpy(String, "HH:MM:SS AM");
      String[9] = (Hour>=12) ? 'P' : 'A';
      if (Hour>12)
      Hour = Hour -12;    
      
      String[0] = Hour / 10 + '0';
      String[1] = Hour % 10 + '0';
      String[3] = Minute / 10 + '0';
      String[4] = Minute % 10 + '0';
      String[6] = Second / 10 + '0';
      String[7] = Second % 10 + '0';
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
      break;        
  } // switch
  
  EXIT_SUCCESS_FUNC(FORMAT_TIME);
}
FUNC_REGISTER(FORMAT_TIME, Format_Time);
