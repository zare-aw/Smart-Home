#ifndef _Alarm_Func_h
#define _Alarm_Func_h

#define REGISTER_TIME_ALARM          ALARM_TIME_OFFSET | 0x01
#define EXECUTE_TIME_ALARM           ALARM_TIME_OFFSET | 0x02
#define UNREGISTER_TIME_ALARM        ALARM_TIME_OFFSET | 0x03
#define TIME_ALARM_STATUS            ALARM_TIME_OFFSET | 0x04
#define SET_TIME_ALARM               ALARM_TIME_OFFSET | 0x05
#define GET_ALARM_ID                 ALARM_TIME_OFFSET | 0x06
#define REMOVE_TIME_ALARM            ALARM_TIME_OFFSET | 0x07
#define UPDATE_REPETITIVE_ALARMS     ALARM_TIME_OFFSET | 0x08

#endif
