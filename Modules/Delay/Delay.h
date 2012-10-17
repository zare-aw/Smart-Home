#ifndef _Delay_h
#define _Delay_h

#include "StatusHandling.h"

#define FREE    1
#define BUSY    2

#define DLY_BUSY_ERROR                      DELAY_OFFSET | 0x01
#define DLY_TIMER_UNAVAILABLE_ERROR         DELAY_OFFSET | 0x02

extern uint8 DlyStatus;

Status_t uDelay(uint32 Delay);
Status_t mDelay(uint32 Delay);
Status_t sDelay(uint32 Delay);

__arm void Dly_ISR(void);
Status_t Dly(unsigned int a, char c, void *DlyCallback_p);
void Dly_Stop(void);

#endif
