#ifndef _Delay_h
#define _Delay_h

#include "StatusHandling.h"

/**** Delay Global error state defines ****/
#define DELAY_QUEUE_FULL                    DELAY_OFFSET | 0x01

void uDelay(uint32 Delay);
void mDelay(uint32 Delay);
void sDelay(uint32 Delay);

Status_t Delay_Work(const uint32 Delay, void (*Callback)(void *));

void Delay_Timer_Init(void);

#endif
