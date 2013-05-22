#include <stdlib.h>
#include <string.h>
#include "Global_Defines.h"
#include "StatusHandling.h"
#include "Func_Trace.h"
#include "Console.h"
#include "RTC.h"

#include "Alarm.h"
#include "Alarm_Func.h"
#include "Alarm_Debug.h"


TimeAlarm_t AlarmWork[ALARM_WORK_BUFFER_SIZE] = {0};

/*******************************************************************************
* Function for compare two Alarms entity
* @in *A - Void pointer to first Alarm entity
* @in *B - Void pointer to second Alarm entity
* @out integer value which represent which alarm need to be performed first
* if value is pozitive A alarm is previous alarm for execution
* if value is 0, alarm have same advantage for performing
* if value is negative B alarm is previous alarm for execution
 ******************************************************************************/
static int Compare_AlarmWork(const void *A, const void *B)
{
  RtcDateTime_t DateTime_A = ((TimeAlarm_t *)A) -> DateTime;
  RtcDateTime_t DateTime_B = ((TimeAlarm_t *)B) -> DateTime;
  uint8 State_A = ((TimeAlarm_t *)A) -> State;
  uint8 State_B = ((TimeAlarm_t *)B) -> State;
  uint8 AlarmID_A = ((TimeAlarm_t *)A) -> AlarmID;
  uint8 AlarmID_B = ((TimeAlarm_t *)B) -> AlarmID;

  if((AlarmID_A == NO_TIME_ALARM_ID) || (AlarmID_B == NO_TIME_ALARM_ID))
  {
    if((AlarmID_A == NO_TIME_ALARM_ID) && (AlarmID_B == NO_TIME_ALARM_ID))
      return 0;
    else
    {
      if(AlarmID_A == NO_TIME_ALARM_ID)
        return 1;
      else
        return -1;
    }
  }

  if((State_A == ALARM_OFF) || (State_B == ALARM_OFF))
  {
    if((State_A == ALARM_OFF) && (State_B == ALARM_OFF))
      return 0;
    else
    {
      if(State_A == ALARM_OFF)
        return 1;
      else
        return -1;
    }
  }

  if(DateTime_A.Year != DateTime_B.Year)
    return DateTime_A.Year - DateTime_B.Year;

  if(DateTime_A.Month != DateTime_B.Month)
    return DateTime_A.Month - DateTime_B.Month;

  if(DateTime_A.Day != DateTime_B.Day)
    return DateTime_A.Day - DateTime_B.Day;

   if(DateTime_A.Hour != DateTime_B.Hour)
    return DateTime_A.Hour - DateTime_B.Hour;

  if(DateTime_A.Minute != DateTime_B.Minute)
    return DateTime_A.Minute - DateTime_B.Minute;

  if(DateTime_A.Second != DateTime_B.Second)
    return DateTime_A.Second - DateTime_B.Second;

  return 0;
}
/*******************************************************************************
*
*******************************************************************************/
static int Update_Repetitive_Alarms()
{
  FuncIN(UPDATE_REPETITIVE_ALARMS);
  RtcDateTime_t Current_Time = {0};
  RtcDateTime_t Repeat_Time = {0};
  uint8 Repeat = 0;
  uint8 Alarm_Repeat = 0;
  int i = 0;
  int j = 7;

  RTC_Get_Date_Time(&Current_Time);
  for(i = 0; i < ALARM_WORK_BUFFER_SIZE; i++)
  {
    if(AlarmWork[i].Repeat != 0)
    {
      Repeat_Time = Current_Time;
      Repeat = 1 << (8 - Repeat_Time.DoW);
      Alarm_Repeat = AlarmWork[i].Repeat << 1; //7 bits represent to days of week place in 8 bits
      j= 7;
      do{
        if(j == 7) {
          if(AlarmWork[i].DateTime.Hour <= Current_Time.Hour)
            if(AlarmWork[i].DateTime.Minute <= Current_Time.Minute)
              if(AlarmWork[i].DateTime.Second <= Current_Time.Second)
                goto Next_Day;
        }

        if(Repeat & Alarm_Repeat)
            break;
        else {
Next_Day:
          Repeat = (Repeat << 7) | (Repeat >> 1); //rotate to right
          if(Repeat == 1)
          Repeat = 0x80;
          Repeat_Time.Day++;
          if(FALSE == Is_Valid_Day(Repeat_Time.Year,Repeat_Time.Month,Repeat_Time.Day)){
            //if day is from next month, increment the month and set the day as first day into that month
            Repeat_Time.Month++;
            Repeat_Time.Day = 1;

             if(FALSE == Is_Valid_Day(Repeat_Time.Year,Repeat_Time.Month,Repeat_Time.Day)){
              //if day is from next year, increment the year and set the month to January
              Repeat_Time.Year++;
              Repeat_Time.Month = 1;
            }
          }
        }
          j--;
      }while(j != 0);

      AlarmWork[i].DateTime.Year =  Repeat_Time.Year;
      AlarmWork[i].DateTime.Month =  Repeat_Time.Month;
      AlarmWork[i].DateTime.Day =  Repeat_Time.Day;
    }
  }

  EXIT_SUCCESS_FUNC(UPDATE_REPETITIVE_ALARMS);
}
FUNC_REGISTER(UPDATE_REPETITIVE_ALARMS, Update_Repetitive_Alarms);

/*******************************************************************************
* @out: AlarmID_p - next free AlarmID slot.
*******************************************************************************/
static Status_t Get_Alarm_ID(uint8 *AlarmID_p)
{
  FuncIN(GET_ALARM_ID);
  uint8 Alarm_ID = 0;
  int i = 0;
  for(Alarm_ID = 1; Alarm_ID < ALARM_WORK_BUFFER_SIZE + 1; Alarm_ID++)
  {
    for(i = 0; i < ALARM_WORK_BUFFER_SIZE; i++)
    {
      if(AlarmWork[i].AlarmID == Alarm_ID)
        break;
    }
    if(i == ALARM_WORK_BUFFER_SIZE)
    {
       *AlarmID_p = Alarm_ID;
       ALARM_DEBUG(printc("\r # (%s) Alarm ID = %d\n",__func__, Alarm_ID));
       break;
    }
  }
  if(Alarm_ID == ALARM_WORK_BUFFER_SIZE)
    EXIT_FUNC(-TIME_ALARM_GET_ALARM_ID_ERROR, GET_ALARM_ID);

  EXIT_SUCCESS_FUNC(GET_ALARM_ID);
}
FUNC_REGISTER(GET_ALARM_ID, Get_Alarm_ID);
/*******************************************************************************
*
*******************************************************************************/
Status_t Register_Time_Alarm(TimeAlarm_t *TimeAlarm_p)
{
  FuncIN(REGISTER_TIME_ALARM);
  Status_t Status;
  int i;
  ASSERT(TimeAlarm_p != NULL, -INVALID_INPUT_POINTER);
  ASSERT(TimeAlarm_p -> Callback != NULL, -INVALID_INPUT_POINTER);
  ASSERT(TimeAlarm_p -> State != 0, -INVALID_INPUT_PARAMETER);
  VERIFY(Get_Alarm_ID(&TimeAlarm_p -> AlarmID), -TIME_ALARM_GET_ALARM_ID_ERROR);

  for(i = 0; i < ALARM_WORK_BUFFER_SIZE; i++)
  {
    if(AlarmWork[i].AlarmID == NO_TIME_ALARM_ID)
    {
      AlarmWork[i].State = TimeAlarm_p -> State;
      AlarmWork[i].AlarmID = TimeAlarm_p -> AlarmID;
      AlarmWork[i].Repeat = TimeAlarm_p -> Repeat;
      AlarmWork[i].DateTime = TimeAlarm_p -> DateTime;
      AlarmWork[i].Callback = TimeAlarm_p -> Callback;
      ALARM_DEBUG(printc("\r # Add element in %d field", i));
      break;
    }
  }

  if(i == ALARM_WORK_BUFFER_SIZE)
  {
    EXIT_FUNC(ALARM_QUEUE_FULL , REGISTER_TIME_ALARM);
  }

  Update_Repetitive_Alarms();
  qsort(AlarmWork, ALARM_WORK_BUFFER_SIZE, sizeof(TimeAlarm_t), Compare_AlarmWork);

  ALARM_DEBUG(printc("\r # (%s) input parameters for RTC_Enable_Alarm\n",__func__));
  ALARM_DEBUG(printc("\r # date = %02u.%02u.%02u\n",  AlarmWork[0].DateTime.Day,
                                                      AlarmWork[0].DateTime.Month,
                                                      AlarmWork[0].DateTime.Year));
  ALARM_DEBUG(printc("\r # time = %02u:%02u:%02u\n",  AlarmWork[0].DateTime.Hour,
                                                      AlarmWork[0].DateTime.Minute,
                                                      AlarmWork[0].DateTime.Second));
  ALARM_DEBUG(printc("\r # AlarmID = %d\n",           AlarmWork[0].AlarmID));
  ALARM_DEBUG(printc("\r # State = %d\n",             AlarmWork[0].State));
  ALARM_DEBUG(printc("\r # Repeat = 0x%X\n",          AlarmWork[0].Repeat));
  ALARM_DEBUG(printc("\r # Callback = 0x%X\n",        AlarmWork[0].Callback));

  Status = RTC_Enable_Alarm(0xFF, &AlarmWork[0].DateTime, (void *)Execute_Time_Alarm);

  VERIFY(Status, Status);

  EXIT_SUCCESS_FUNC(REGISTER_TIME_ALARM);
}
FUNC_REGISTER(REGISTER_TIME_ALARM, Register_Time_Alarm);

/*******************************************************************************
*
*******************************************************************************/
Status_t Execute_Time_Alarm()
{
  FuncIN(EXECUTE_TIME_ALARM);
  Status_t Status;

  ASSERT(AlarmWork[0].Callback != NULL, -NOT_REGISTERED_ERROR);
  printc("\r #(%s):(%d)***  Execute Callback = 0x%X\n", __func__,__LINE__, AlarmWork[0].Callback);
  ((void(*)(void *))(AlarmWork[0].Callback))(NULL);

  if(AlarmWork[0].Repeat == 0) {
    Status = Unregister_Time_Alarm(AlarmWork[0].AlarmID);
    VERIFY(Status, Status);
  }

  Update_Repetitive_Alarms();
  qsort(AlarmWork, ALARM_WORK_BUFFER_SIZE, sizeof(TimeAlarm_t), Compare_AlarmWork);

  ALARM_DEBUG(printc("\r # (%s) input parameters for RTC_Enable_Alarm\n",__func__));
  ALARM_DEBUG(printc("\r # date = %02u.%02u.%02u\n",  AlarmWork[0].DateTime.Day,
                                                      AlarmWork[0].DateTime.Month,
                                                      AlarmWork[0].DateTime.Year));
  ALARM_DEBUG(printc("\r # time = %02u:%02u:%02u\n",  AlarmWork[0].DateTime.Hour,
                                                      AlarmWork[0].DateTime.Minute,
                                                      AlarmWork[0].DateTime.Second));
  ALARM_DEBUG(printc("\r # AlarmID = %d\n",           AlarmWork[0].AlarmID));
  ALARM_DEBUG(printc("\r # State = %d\n",             AlarmWork[0].State));
  ALARM_DEBUG(printc("\r # Repeat = 0x%X\n",          AlarmWork[0].Repeat));
  ALARM_DEBUG(printc("\r # Callback = 0x%X\n",        AlarmWork[0].Callback));

  Status = RTC_Enable_Alarm(0xFF, &AlarmWork[0].DateTime, (void *)Execute_Time_Alarm);

  VERIFY(Status, Status);

  EXIT_SUCCESS_FUNC(EXECUTE_TIME_ALARM);
}
FUNC_REGISTER(EXECUTE_TIME_ALARM, Execute_Time_Alarm);

/*******************************************************************************
*
*******************************************************************************/
Status_t Unregister_Time_Alarm(uint8 AlarmID)
{
  FuncIN(UNREGISTER_TIME_ALARM);
  int i = 0;

  for(i = 0; i < ALARM_WORK_BUFFER_SIZE; i++)
  {
    if(AlarmWork[i].AlarmID == AlarmID){
      AlarmWork[i].State = ALARM_OFF;
      break;
    }
  }

  if(i == ALARM_WORK_BUFFER_SIZE)
    EXIT_FUNC(-TIME_ALARM_UNREGISTER_ERROR, UNREGISTER_TIME_ALARM);

  EXIT_SUCCESS_FUNC(UNREGISTER_TIME_ALARM);
}
FUNC_REGISTER(UNREGISTER_TIME_ALARM, Unregister_Time_Alarm);

/*******************************************************************************
*
*******************************************************************************/
Status_t Remove_Time_Alarm(uint8 AlarmID)
{
  FuncIN(REMOVE_TIME_ALARM);
  int i = 0;
  Status_t Status;

  for(i = 0; i < ALARM_WORK_BUFFER_SIZE; i++)
  {
    if(AlarmWork[i].AlarmID == AlarmID){
      AlarmWork[i].AlarmID = NO_TIME_ALARM_ID;
      AlarmWork[i].State = 0;
      memset((void *)&AlarmWork[i].DateTime, 0, sizeof(RtcDateTime_t));
      AlarmWork[i].Callback = NULL;
      break;
    }
  }

  if(i == ALARM_WORK_BUFFER_SIZE)
    EXIT_FUNC(-TIME_ALARM_REMOVE_ERROR, REMOVE_TIME_ALARM);

  if(AlarmWork[0].AlarmID == AlarmID) {
    Update_Repetitive_Alarms();
    qsort(AlarmWork, ALARM_WORK_BUFFER_SIZE, sizeof(TimeAlarm_t), Compare_AlarmWork);
    Status = RTC_Enable_Alarm(0xFF, &AlarmWork[0].DateTime, (void *)Execute_Time_Alarm);

    VERIFY(Status, Status);
  }
  EXIT_SUCCESS_FUNC(REMOVE_TIME_ALARM);
}
FUNC_REGISTER(REMOVE_TIME_ALARM, Remove_Time_Alarm);
/*******************************************************************************
*
*******************************************************************************/
Status_t Time_Alarm_Status(void *Ptr)
{
  FuncIN(TIME_ALARM_STATUS);
  int i;

  for(i = 0; i < ALARM_WORK_BUFFER_SIZE; i++)
  {
    if(AlarmWork[i].Callback == NULL)
    {
      break;
    }
      printc("\r # Registered Alarm number: %d\n", i + 1);
      printc("\r # date = %02u.%02u.%02u\n", AlarmWork[i].DateTime.Day,
                                             AlarmWork[i].DateTime.Month,
                                             AlarmWork[i].DateTime.Year);
      printc("\r # time = %02u:%02u:%02u\n", AlarmWork[i].DateTime.Hour,
                                             AlarmWork[i].DateTime.Minute,
                                             AlarmWork[i].DateTime.Second);
      printc("\r # AlarmID = %d\n",          AlarmWork[i].AlarmID);
      printc("\r # State = %d\n",            AlarmWork[i].State);
      printc("\r # Repeat = 0x%X\n",         AlarmWork[i].Repeat);
      printc("\r # Callback = 0x%X\n",       AlarmWork[i].Callback);
  }

  if (i == 0)
    printc("\r # Not Registered Alarm\n");

  if(i == ALARM_WORK_BUFFER_SIZE)
  {
    EXIT_FUNC(ALARM_QUEUE_FULL , TIME_ALARM_STATUS);
  }

  EXIT_SUCCESS_FUNC(TIME_ALARM_STATUS);
}
FUNC_REGISTER(TIME_ALARM_STATUS, Time_Alarm_Status);

/*******************************************************************************
*
*******************************************************************************/
Status_t Set_Time_Alarm(TimeAlarm_t *TimeAlarm_p)
{
  FuncIN(SET_TIME_ALARM);
  int i;
  Status_t Status;
  ASSERT(TimeAlarm_p -> AlarmID < NO_OF_TIME_ALARMS, -INVALID_INPUT_PARAMETER);

  for(i = 0; i < ALARM_WORK_BUFFER_SIZE; i++)
  {
    if(AlarmWork[i].AlarmID ==  TimeAlarm_p -> AlarmID)
      break;
  }
  if(i != ALARM_WORK_BUFFER_SIZE)
  {
    ALARM_DEBUG(printc("\r # Time Alarm set with parameters:\n"));
    ALARM_DEBUG(printc("\r # Alarm ID = %d\n", TimeAlarm_p -> AlarmID));

    if(TimeAlarm_p -> Callback != NULL)
    {
      AlarmWork[i].Callback = TimeAlarm_p -> Callback;
    }
    if(TimeAlarm_p -> State != 0)
    {
      AlarmWork[i].State = TimeAlarm_p -> State;
      ALARM_DEBUG(printc("\r # State = %d\n", TimeAlarm_p -> State));
    }
    if(TimeAlarm_p -> DateTime.Hour != 0 ||
       TimeAlarm_p -> DateTime.Minute != 0 ||
       TimeAlarm_p -> DateTime.Second != 0)
    {
      AlarmWork[i].DateTime = TimeAlarm_p -> DateTime;
      AlarmWork[i].Repeat = TimeAlarm_p -> Repeat;

      ALARM_DEBUG(
      printc("\r # date = %02u.%02u.%02u\n", TimeAlarm_p -> DateTime.Day,
                                             TimeAlarm_p -> DateTime.Month,
                                             TimeAlarm_p -> DateTime.Year);
      printc("\r # time = %02u:%02u:%02u\n", TimeAlarm_p -> DateTime.Hour,
                                             TimeAlarm_p -> DateTime.Minute,
                                             TimeAlarm_p -> DateTime.Second);)
    }

    Update_Repetitive_Alarms();
    qsort(AlarmWork, ALARM_WORK_BUFFER_SIZE, sizeof(TimeAlarm_t), Compare_AlarmWork);

    ALARM_DEBUG(printc("\r # (%s) input parameters for RTC_Enable_Alarm\n",__func__));
    ALARM_DEBUG(printc("\r # date = %02u.%02u.%02u\n",  AlarmWork[0].DateTime.Day,
                                                        AlarmWork[0].DateTime.Month,
                                                        AlarmWork[0].DateTime.Year));
    ALARM_DEBUG(printc("\r # time = %02u:%02u:%02u\n",  AlarmWork[0].DateTime.Hour,
                                                        AlarmWork[0].DateTime.Minute,
                                                        AlarmWork[0].DateTime.Second));
    ALARM_DEBUG(printc("\r # Callback = 0x%X\n",        AlarmWork[0].Callback));

    Status = RTC_Enable_Alarm(0xFF, &AlarmWork[0].DateTime, (void *)Execute_Time_Alarm);

    VERIFY(Status, Status);

  } else {
    EXIT_FUNC(TIME_ALARM_ID_MISSING_ERROR , SET_TIME_ALARM);
  }
  EXIT_SUCCESS_FUNC(SET_TIME_ALARM);
}
FUNC_REGISTER(SET_TIME_ALARM, Set_Time_Alarm);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Time_Alarm_Dummy_Handler(void *Ptr)
{
  ALARM_INFO(printc(" # Time alarm dummy handler executed!\n"));

  return SUCCESS;
}
