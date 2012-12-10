#ifndef __Alarm_h
#define __Alarm_h

#include <NXP/iolpc2148.h>
#include "StatusHandling.h"
#include "RTC.h"
#include "Out.h"


#define ALARM_WORK_BUFFER_SIZE    10

/**** Delay Global error state defines ****/
#define ALARM_QUEUE_FULL                    ALARM_TIME_OFFSET | 0x01

typedef struct TimeAlarm_s
{
  RtcDateTime_t DateTime;
  void *Callback;
} TimeAlarm_t;

typedef struct TimeAlarmResponse_s
{
  char *String;
  void *Callback;
} TimeAlarmResponse_t;



//functions
Status_t Register_Time_Alarm(TimeAlarm_t *TimeAlarm_p);
Status_t Unregister_Time_Alarm(void *Ptr);
Status_t Time_Alarm_Status(void *Ptr);
Status_t Time_Alarm_Dummy_Handler(void *Ptr);

static TimeAlarmResponse_t AlarmResponse[] =
{
  {
    .String = "out_1_ON",
    .Callback = (void *)Out_1_Set
  },
  {
    .String = "out_1_OFF",
    .Callback = (void *)Out_1_Clr
  },
  {
    .String = "out_2_ON",
    .Callback = (void *)Out_2_Set
  },
  {
    .String = "out_2_OFF",
    .Callback = (void *)Out_2_Clr
  },
  {
    .String = "out_3_ON",
    .Callback = (void *)Out_3_Set
  },
  {
    .String = "out_3_OFF",
    .Callback = (void *)Out_3_Clr
  },
  {
    .String = "out_4_ON",
    .Callback = (void *)Out_4_Set
  },
  {
    .String = "out_4_OFF",
    .Callback = (void *)Out_4_Clr
  },
  {
    .String = "out_5_ON",
    .Callback = (void *)Out_5_Set
  },
  {
    .String = "out_5_OFF",
    .Callback = (void *)Out_5_Clr
  },
  {
    .String = "out_6_ON",
    .Callback = (void *)Out_6_Set
  },
  {
    .String = "out_6_OFF",
    .Callback = (void *)Out_6_Clr
  },
  {
    .String = "sound_alarm",
    .Callback = (void *)Time_Alarm_Dummy_Handler
  },
  {
    .String = "dummy",
    .Callback = (void *)Time_Alarm_Dummy_Handler
  },
  {0} // Terminator
};
#endif
