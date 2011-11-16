#include "rtc.h"

uint8 AlarmIntType_Beckup = 0;
uint8 IncIntType_Beckup = 0;

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
static uint8 Is_Leap_Year (uint16 Year)
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
 *		true -- valid day
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
  Function_IN(RTC_INIT);
  unsigned int PreInt;
  
  if(CCR_bit.CLKEN == TRUE && ClkSource == FALSE)
    RETURN_SUCCESS();
  
  RTC_Disable();
  
  if(ClkSource)
  {
    // initialize prescaler of RTC
    PreInt = (int)(30000000 / RTC_COUNT_PER_SEC) - 1;
    CONTROL(PreInt > 0, RTC_INIT_ERROR);
	
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
  CONTROL(!RTC_Set_Date_Time(&RTC_InitDateTime), RTC_SET_ERROR);

//  RTC_Enable();
  
  RETURN_SUCCESS_FUNC(RTC_INIT);
}

/*************************************************************************
 * Function Name: RTC_SetDate
 * @in: RtcDate_t *Date_p
 * @out: Status_t
 * Description: Set your specifying date
 *************************************************************************/
Status_t RTC_Set_Date(RtcDate_t *Date_p)
{
  Function_IN(RTC_SET_DATE);
  
  // Valid Judge
  CONTROL(Is_Valid_Day(Date_p -> Year, Date_p -> Month, Date_p -> Day) == TRUE, RTC_INVALID_DATE_ERROR);

  // Calculate DOW, DOY
  Date_p -> DoY = Get_DoY(Date_p -> Year, Date_p -> Month, Date_p -> Day);
  Date_p -> DoW = Get_DoW(Date_p -> Year, Date_p -> Month, Date_p -> Day);

  DOM = Date_p -> Day;
  MONTH = Date_p -> Month;
  YEAR = Date_p -> Year;
  DOW = Date_p -> DoW;
  DOY = Date_p -> DoY;

  RETURN_SUCCESS_FUNC(RTC_SET_DATE);
}

/*************************************************************************
 * Function Name: RTC_Set_Time
 * @in: RtcTime_t *Time_p
 * @out: Status_t 
 * Description: Set your specifying time
 *************************************************************************/
Status_t RTC_Set_Time(RtcTime_t *Time_p)
{
  Function_IN(RTC_SET_TIME);
  
  // Valid Judge
  CONTROL(!(Time_p -> Hour > 23 || Time_p -> Minute > 59 || Time_p -> Second > 59), RTC_INVALID_TIME_ERROR);
  
  HOUR = Time_p -> Hour;
  MIN = Time_p -> Minute;
  SEC = Time_p -> Second;

  RETURN_SUCCESS();
}

/*************************************************************************
 * Function Name: RTC_Set_Date_Time
 * @in: RtcDateTime_t *DateTime_p
 * @out: Status_t 
 * Description: Set your specifying date and time
 *************************************************************************/
Status_t RTC_Set_Date_Time(RtcDateTime_t *DateTime_p)
{
  Function_IN(RTC_SET_DATE_TIME);
  
  // Valid Judge
  CONTROL(Is_Valid_Day(DateTime_p -> Year, DateTime_p -> Month, DateTime_p -> Day) == TRUE, RTC_INVALID_DATE_ERROR);
  CONTROL(!(DateTime_p -> Hour > 23 || DateTime_p -> Minute > 59 || DateTime_p -> Second > 59), RTC_INVALID_TIME_ERROR);

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

  RETURN_SUCCESS_FUNC(RTC_SET_DATE_TIME);
}

/*************************************************************************
 * Function Name: RTC_Get_Date
 * @in: RtcDate_t *Date_p
 * @out: Status_t
 * Description: Get the current date
 *************************************************************************/
Status_t RTC_Get_Date(RtcDate_t *Date_p)
{
  Function_IN(RTC_GET_DATE);
  
  Date_p -> Day = DOM;
  Date_p -> Month = MONTH;
  Date_p -> Year = YEAR;

  Date_p -> DoW = DOW;
  Date_p -> DoY = DOY;
  
  RETURN_SUCCESS();
}

/*************************************************************************
 * Function Name: RTC_Get_Time
 * @in: RtcTime_t *Time_p
 * @out: Status_t
 * Description: Get the current time
 *************************************************************************/
Status_t RTC_Get_Time(RtcTime_t *Time_p)
{
  Function_IN(RTC_GET_TIME);
  
  Time_p -> Hour = HOUR;
  Time_p -> Minute = MIN;
  Time_p -> Second = SEC;

  RETURN_SUCCESS();
}

/*************************************************************************
 * Function Name: RTC_Get_Date_Time
 * @in: RtcDateTime_t *DateTime_p
 * @out: Status_t
 * Description: Get the current date and time
 *************************************************************************/
Status_t RTC_Get_Date_Time(RtcDateTime_t *DateTime_p)
{
  Function_IN(RTC_GET_DATE_TIME);
  
  DateTime_p -> Day = DOM;
  DateTime_p -> Month = MONTH;
  DateTime_p -> Year = YEAR;

  DateTime_p -> Hour = HOUR;
  DateTime_p -> Minute = MIN;
  DateTime_p -> Second = SEC;

  DateTime_p -> DoW = DOW;
  DateTime_p -> DoY = DOY;

  RETURN_SUCCESS();
}

/*************************************************************************
 * Function Name: RTC_Set_Inct_Int
 * @in: uint8 IncIntType
 * @in: void* Callback_p
 * @out: void 
 * Description: Set increment interrupt type
 *************************************************************************/
void RTC_Enable_Inc_Int(uint8 IncIntType)
{
  if(IncIntType != NULL)
    CIIR = IncIntType & 0xFF;
  else
  {
    CIIR = IncIntType_Beckup & 0xFF;
    IncIntType_Beckup = IncIntType;
  }
  
  return;
}

/*************************************************************************
 * 
*************************************************************************/
uint8 RTC_Register_Inc_Int(void *Callback_p, uint32 Type)
{
  int i;
  for(i = 0; i < RTC_INC_CALLBACKS; i++)
    if(Sys_Time_Update[i] == NULL)
    {
      Sys_Time_Update[i] = Callback_p;
      Sys_Time_Type[i] = Type;
      RTC_DEBUG(printc("\r # RTC increment interrupt callback registered, Type = %d, ID = %d\n", Type, i));
      break;
    }
  
  if(i == RTC_INC_CALLBACKS)
    return 255;
  else
    return i;
}

/*************************************************************************
 * 
*************************************************************************/
void RTC_Unregister_Inc_Int(uint8 ID)
{
  Sys_Time_Update[ID] = NULL;
}

/*************************************************************************
 * Function Name: RTC_Disable_Inc_Int
 * @in: void
 * @out: void 
 * Description: Disable RTC increment interrupt.
 *************************************************************************/
void RTC_Disable_Inc_Int(void)
{
  CIIR = 0;
  return ;
}

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
  Function_IN(RTC_ENABLE_ALARM);
  
  if(DateTime_p != NULL)
  {
    // Valid Judge
    CONTROL(Is_Valid_Day(DateTime_p -> Year, DateTime_p -> Month, DateTime_p -> Day) == TRUE, RTC_INVALID_DATE_ERROR);
    CONTROL(!(DateTime_p -> Hour > 23 || DateTime_p -> Minute > 59 || DateTime_p -> Second > 59), RTC_INVALID_TIME_ERROR);
    
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
  
  RETURN_SUCCESS_FUNC(RTC_ENABLE_ALARM);
}

/*************************************************************************
 * Function Name: RTC_Clear Int
 * @in: uint32 IntType
 * @out: Status_t
 * Description: Clear RTC interrupt.
 *************************************************************************/
Status_t RTC_Clear_Int(uint32 IntType)
{
  Function_IN(RTC_CLEAR_INT);
  
  CONTROL(!(IntType < 1 || IntType > 3), RTC_GENERAL_ERROR);
  
  ILR = (IntType & 0x3);
  
  RETURN_SUCCESS();
}

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
  Function_IN(RTC_REGISTER_SW_ALARM);
  
  for(int i = 0; i < NO_OF_SW_ALARMS; i++)
  {
    if(SwAlarm[i].State == NO_ALARM_SET)
    {
      SwAlarm[i] = *AlarmData_p;
      *AlarmID = i;
      break;
    }
  }
  
  CONTROL(*AlarmID < NO_OF_SW_ALARMS, RTC_SW_ALARM_SLOTS_ERROR);
  
  if(SwAlarmCount == 0)
  {
    SwAlarmCallbackID = RTC_Register_Inc_Int((void *)RTC_SW_Alarm_Callback, AlarmIntType_MIN);
    RTC_DEBUG(printc("\r # Software Alarm callback registered on RTC icrement interrupt with ID = %d\n", SwAlarmCallbackID));
  }
  
  SwAlarmCount++;
  CONTROL(SwAlarmCount <= NO_OF_SW_ALARMS, RTC_SW_ALARM_SLOTS_ERROR);
  
  RETURN_SUCCESS_FUNC(RTC_REGISTER_SW_ALARM);
}

/*************************************************************************
 * Function Name: RTC_Unregister_SW_Alarm
 * @in: 
 * @out: Status_t, AlarmID - ID on registered alarm
 * Description: Register RTC software alarm.
 *************************************************************************/
Status_t RTC_Unregister_SW_Alarm(uint8 AlarmID)
{
  Function_IN(RTC_UNREGISTER_SW_ALARM);
  CONTROL(SwAlarmCount > 0, RTC_GENERAL_ERROR);
  
  SwAlarm[AlarmID].State = NO_ALARM_SET;
  
  SwAlarmCount--;
  
  if(SwAlarmCount == 0)
  {
    RTC_Unregister_Inc_Int(SwAlarmCallbackID);
    RTC_DEBUG(printc("\r # Software Alarm callback Unregistered on RTC icrement interrupt with ID = %d\n", SwAlarmCallbackID));
  }
  
  RETURN_SUCCESS_FUNC(RTC_UNREGISTER_SW_ALARM);
}

/*************************************************************************
 * Function Name: RTC_SW_Alarm_Callback
 * @in: 
 * @out: Status_t
 * Description: RTC software alarm callback.
 *************************************************************************/
Status_t RTC_SW_Alarm_Callback(void *InPtr)
{
  Function_IN(RTC_SW_ALARM_CALLBACK);
  RtcDateTime_t DateTime = {0};
  
  for(int i = 0; i < NO_OF_SW_ALARMS; i++)
  {
    if(SwAlarm[i].State == RTC_ALARM_ON)
    {
      CONTROL(RTC_Get_Date_Time(&DateTime), RTC_GENERAL_ERROR);
      
      if((SwAlarm[i].Minute == DateTime.Minute) && (SwAlarm[i].Hour == DateTime.Hour))
      {
        if(SwAlarm[i].Year != 0)
        {
          if((SwAlarm[i].Year == DateTime.Year) && (SwAlarm[i].Month == DateTime.Month) && (SwAlarm[i].Day == DateTime.Day))
          {
            CONTROL(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), RTC_GENERAL_ERROR);
            SwAlarm[i].State = RTC_ALARM_OFF;
          }
        }
        else
        {
          if(SwAlarm[i].Mode == SINGLE_ALARM)
          {
            CONTROL(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), RTC_GENERAL_ERROR);
            SwAlarm[i].State = RTC_ALARM_OFF;
          }
          else if(SwAlarm[i].Mode == REPETITIVE_ALARM)
          {
            switch(DateTime.DoW)
            {
              case 1:
                if(SwAlarm[i].DoW & MONDAY)
                  CONTROL(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), RTC_GENERAL_ERROR);
                break;
              case 2:
                if(SwAlarm[i].DoW & TUESDAY)
                  CONTROL(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), RTC_GENERAL_ERROR);
                break;
              case 3:
                if(SwAlarm[i].DoW & WEDNESDAY)
                  CONTROL(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), RTC_GENERAL_ERROR);
                break;
              case 4:
                if(SwAlarm[i].DoW & THURSDAY)
                  CONTROL(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), RTC_GENERAL_ERROR);
                break;
              case 5:
                if(SwAlarm[i].DoW & FRIDAY)
                  CONTROL(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), RTC_GENERAL_ERROR);
                break;
              case 6:
                if(SwAlarm[i].DoW & SATURDAY)
                  CONTROL(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), RTC_GENERAL_ERROR);
                break;
              case 0:
                if(SwAlarm[i].DoW & SUNDAY)
                  CONTROL(((Status_t(*)(void *))(SwAlarm[i].Callback))(NULL), RTC_GENERAL_ERROR);
                break;
              default:
                CONTROL(0, REGISTER_ERROR);
            } // switch(DateTime.DoW)
          }
          else
            CONTROL(0, RTC_GENERAL_ERROR);
        }
      }
    }
  } // for
  
  RETURN_SUCCESS_FUNC(RTC_SW_ALARM_CALLBACK);
}

/*************************************************************************
 * Function Name: RTC_ISR
 * @in:  void
 * @out: void
 * Description: Rtc interrupt subroutine
 *************************************************************************/
__irq void RTC_ISR(void)
{
  uint32 IntStatus;
  RtcDateTime_t DateTime = {0};
  
  IntStatus = RTC_Check_Int_Type() & 0x3;
  if(RTC_Clear_Int(IntStatus) != SUCCESS)
    RTC_Clear_Int(RTCALLInt);
  
  if (IntStatus & RTCIncrementInt)	// Increment Interrupt
  {
    for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Second int
    {
      if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_SEC)
        CONTROL_ABORT(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), RTC_GENERAL_ERROR);
    }
    
    RTC_Get_Date_Time(&DateTime);
    
    if(DateTime.Second == 0)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Minute int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_MIN)
          CONTROL_ABORT(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), RTC_GENERAL_ERROR);
      }
    }
    
    if(DateTime.Minute == 0)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Hour int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_HOUR)
          CONTROL_ABORT(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), RTC_GENERAL_ERROR);
      }
    }
    
    if(DateTime.Hour == 0)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Day int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_DAY)
          CONTROL_ABORT(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), RTC_GENERAL_ERROR);
      }
    }
    
    if(DateTime.Day == 1)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Month int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_MON)
          CONTROL_ABORT(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), RTC_GENERAL_ERROR);
      }
    }
    
    if(DateTime.Month == 1)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // Year int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_YEAR)
          CONTROL_ABORT(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), RTC_GENERAL_ERROR);
      }
    }
    
    if(DateTime.DoW == 1)
    {
      for(int i = 0; i < RTC_INC_CALLBACKS; i++)  // DoW int
      {
        if((Sys_Time_Update[i] != NULL) && Sys_Time_Type[i] == IncIntType_DOW)
          CONTROL_ABORT(((Status_t(*)(void *))(Sys_Time_Update[i]))(NULL), RTC_GENERAL_ERROR);
      }
    }
  } // if (IntStatus & RTCIncrementInt)
  
  if (IntStatus & RTCAlarmInt)	        // Alarm Interrupt
  {
    if(Alarm != NULL)
      Alarm();
  }
  
  VICVectAddr = 0;
}

/*************************************************************************
 * Function Name: FormatDate
 * @in: uint8 Type
 * @in: RtcDate_t *Date_p
 * @in: char *s
 * @out: Status_t
 * Description: Format the current date into an ASCII string according to the Type.
 *		Type = 1, "DD-MM-YYYY" (11 chars)
 *		Type = 2, "DOW, DD Month  YYYY" (30 chars)
 *  
 *************************************************************************/
Status_t Format_Date(uint8 Type, RtcDate_t *Date_p, char *s)
{
  Function_IN(FORMAT_DATE);
  uint16 Year;
  uint8 Month, Day, DoW;
  char Str[5];
  
  CONTROL(Date_p != NULL, INVALID_INPUT_POINTER);
  
  Year = Date_p -> Year;
  Month = Date_p -> Month;
  Day = Date_p -> Day;
  DoW = Date_p -> DoW;
//  DoY = pDate->DoY;
	
  switch(Type)
  {
  case 1:
    strcpy(s, "DD-MM-YYYY");
    s[6] = Year / 1000 + '0';
    Year = Year % 1000;
    s[7] = Year / 100 + '0';
    Year = Year % 100;
    s[8] = Year / 10 + '0';
    s[9] = Year % 10 + '0';
    s[3] = Month / 10 + '0';
    s[4] = Month % 10 + '0';
    s[0] = Day / 10 + '0';
    s[1] = Day % 10 + '0';
    break;
  case 2:
    strcpy(s, RTC_DOWTbl[DoW]);
    strcat(s, " ");
    
    Str[0] = Day / 10 + '0';
    Str[1] = Day % 10 + '0';
    Str[2] = '\0';
    strcat(s, Str);
    strcat(s, ", ");
    
    strcat(s, RTC_MonthTbl[Month]);
    sprintf(Str,"%d",Year);
    strcat(s, Str);
    break;		
  default:
    strcpy(s,"?");
    break;
  } // switch
  RETURN_SUCCESS();
}

/*************************************************************************
 * Function Name: FormatTime
 * @in: uint8 Type
 * @in: RtcTime_t *Time_p
 * @in: char *s
 * @out: Status_t
 * Description: Format the current time into an ASCII string according to the Type.
 *		Type = 1, "HH:MM:SS" (9 chars)
 *		Type = 2, "HH:MM:SS AM" (13 chars)
 *************************************************************************/
Status_t Format_Time(uint8 Type, RtcTime_t *Time_p, char *s)
{
  Function_IN(FORMAT_TIME);
  uint8 Hour, Minute, Second;

  CONTROL(Time_p != NULL, INVALID_INPUT_POINTER);
  
  Hour = Time_p -> Hour;
  Minute = Time_p -> Minute;
  Second = Time_p -> Second;
	
  switch(Type)
  {
  case 1:
    strcpy(s, "HH:MM:SS");
    s[0] = Hour / 10 + '0';
    s[1] = Hour % 10 + '0';
    s[3] = Minute / 10 + '0';
    s[4] = Minute % 10 + '0';
    s[6] = Second / 10 + '0';
    s[7] = Second % 10 + '0';
    break;
  case 2:
    strcpy(s, "HH:MM:SS AM");
    s[9] = (Hour>=12) ? 'P' : 'A';
    if (Hour>12)
      Hour = Hour -12;	
			
    s[0] = Hour / 10 + '0';
    s[1] = Hour % 10 + '0';
    s[3] = Minute / 10 + '0';
    s[4] = Minute % 10 + '0';
    s[6] = Second / 10 + '0';
    s[7] = Second % 10 + '0';
    break;
  default:
    strcpy(s,"?");
    break;		
  } // switch
  RETURN_SUCCESS();
}
