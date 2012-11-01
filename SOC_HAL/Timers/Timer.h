#ifndef __Timer_h
#define __Timer_h

#include "StatusHandling.h"

#define DELAY_TIMER_RESET_VALUE     60000000

#define DELAY_TIMER_GET_COUNTER() T0TC

void Wait(uint32 Time_uSec);

Status_t Delay_Timer_Set_Match_0(uint32 Value, void (*Callback)(void *));
Status_t Delay_Timer_Set_Match_1(uint32 Value, void (*Callback)(void *));
Status_t Delay_Timer_Set_Match_2(uint32 Value, void (*Callback)(void *));

void Delay_Timer_Init(void);

void Timer_1_Init(void);

void Timer_1_Start(uint32 MatchValue);
void Timer_1_Stop(void);
void Timer_1_Update_Match_0_Value(uint32 MatchValue);

#endif
