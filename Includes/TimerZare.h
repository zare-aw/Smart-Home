#ifndef __TimerZare_h
#define __TimerZare_h

void Timer_0_Init(void);
void Timer_1_Init(void);

void Timer_0_Start (unsigned int a, unsigned int b);
void Timer_0_Stop(void);

void Timer_1_Start(uint32 MatchValue);
void Timer_1_Stop(void);
void Timer_1_Update_Match_0_Value(uint32 MatchValue);


#endif