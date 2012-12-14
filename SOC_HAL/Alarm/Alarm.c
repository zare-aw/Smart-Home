#include <NXP/iolpc2148.h>
#include <stdlib.h>
#include "Global_Defines.h"
#include "StatusHandling.h"
#include "Func_Trace.h"
#include "Console.h"
#include "RTC.h"
#include "Command.h"

#include "Alarm.h"
#include "Alarm_Func.h"
#include "Alarm_Debug.h"


TimeAlarm_t AlarmWork[ALARM_WORK_BUFFER_SIZE] = {0};

/*******************************************************************************
 *
 ******************************************************************************/
static int Compare_AlarmWork(const void *A, const void *B)
{
  RtcDateTime_t DateTime_A = ((TimeAlarm_t *)A) -> DateTime;
  RtcDateTime_t DateTime_B = ((TimeAlarm_t *)B) -> DateTime;
  void *Callback_A = (void *)((TimeAlarm_t *)A) -> Callback;
  void *Callback_B = (void *)((TimeAlarm_t *)B) -> Callback;
  
  if((Callback_A == NULL) || (Callback_B == NULL))
  {
    if((Callback_A == NULL) && (Callback_B == NULL))
      return 0;
    else
    {
      if(Callback_A == NULL)
        return 1;
      else
        return -1;
    }
  }
  
  if(DateTime_A.Year != DateTime_B.Year)
    return DateTime_A.Year -DateTime_B.Year;
  
  
  if(DateTime_A.Month != DateTime_B.Month)
    return DateTime_A.Month -DateTime_B.Month;
  
  
  if(DateTime_A.Day != DateTime_B.Day)
    return DateTime_A.Day -DateTime_B.Day;
  
  
  if(DateTime_A.Hour != DateTime_B.Hour)
    return DateTime_A.Hour -DateTime_B.Hour;
  
  
  if(DateTime_A.Minute != DateTime_B.Minute)
    return DateTime_A.Minute -DateTime_B.Minute;
  
  
  if(DateTime_A.Second != DateTime_B.Second)
    return DateTime_A.Second -DateTime_B.Second;
  
  return 0;
}
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
  
  for(i = 0; i < ALARM_WORK_BUFFER_SIZE; i++)
  {
    if(AlarmWork[i].Callback == NULL)
    {
      AlarmWork[i].DateTime = TimeAlarm_p -> DateTime;
      AlarmWork[i].Callback = TimeAlarm_p -> Callback;
      break;
    }
  }

  if(i == ALARM_WORK_BUFFER_SIZE)
  {
    EXIT_FUNC(ALARM_QUEUE_FULL , REGISTER_TIME_ALARM);
  }
   
  qsort(AlarmWork, ALARM_WORK_BUFFER_SIZE, sizeof(TimeAlarm_t), Compare_AlarmWork);

  TIME_DEBUG(printcmd("\r # (%s) input parameters for RTC_Enable_Alarm\n",__func__));
  TIME_DEBUG(printcmd("\r # date = %02u.%02u.%02u\n", AlarmWork[0].DateTime.Day,
                                                      AlarmWork[0].DateTime.Month,
                                                      AlarmWork[0].DateTime.Year));
  TIME_DEBUG(printcmd("\r # time = %02u:%02u:%02u\n", AlarmWork[0].DateTime.Hour,
                                                      AlarmWork[0].DateTime.Minute,
                                                      AlarmWork[0].DateTime.Second));
  TIME_DEBUG(printcmd("\r # Callback = 0x%X\n",       AlarmWork[0].Callback));

  Status = RTC_Enable_Alarm(0xFF, &AlarmWork[0].DateTime, (void *)Unregister_Time_Alarm);
  
  VERIFY(Status, Status);
  
  EXIT_SUCCESS_FUNC(REGISTER_TIME_ALARM);
}
FUNC_REGISTER(REGISTER_TIME_ALARM, Register_Time_Alarm);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Unregister_Time_Alarm(void *Ptr)
{
  FuncIN(UNREGISTER_TIME_ALARM);
  Status_t Status;
  int i;
  
  if(AlarmWork[1].Callback != NULL)
  {
    Status = RTC_Enable_Alarm(NULL, &AlarmWork[1].DateTime, (void *)Unregister_Time_Alarm);
  
    VERIFY(Status, Status);
  }
  
  ASSERT(AlarmWork[0].Callback != NULL, -NOT_REGISTERED_ERROR);
  ((void(*)(void *))(AlarmWork[0].Callback))(NULL);
    
  for(i = 0; i < (ALARM_WORK_BUFFER_SIZE - 1); i++)
  {
    AlarmWork[i] = AlarmWork[i + 1];
    if(AlarmWork[i].Callback == NULL)
    break;
  }


  EXIT_SUCCESS_FUNC(UNREGISTER_TIME_ALARM);
}
FUNC_REGISTER(UNREGISTER_TIME_ALARM, Unregister_Time_Alarm);
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
      printcmd("\r # Registered Alarm number: %d\n", i);
      printcmd("\r # date = %02u.%02u.%02u\n", AlarmWork[i].DateTime.Day,
                                               AlarmWork[i].DateTime.Month,
                                               AlarmWork[i].DateTime.Year);
      printcmd("\r # time = %02u:%02u:%02u\n", AlarmWork[i].DateTime.Hour,
                                               AlarmWork[i].DateTime.Minute,
                                               AlarmWork[i].DateTime.Second);
      printcmd("\r # Callback = 0x%X\n\n",     AlarmWork[i].Callback);

  }

  if(i == ALARM_WORK_BUFFER_SIZE)
  {
    EXIT_FUNC(ALARM_QUEUE_FULL , TIME_ALARM_STATUS);
  }
  
  EXIT_SUCCESS_FUNC(TIME_ALARM_STATUS);
}
FUNC_REGISTER(TIME_ALARM_STATUS, Time_Alarm_Status);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Time_Alarm_Dummy_Handler(void *Ptr)
{
  TIME_INFO(printc(" # Time alarm dummy handler executed!\n"));
  
  return SUCCESS;
}
