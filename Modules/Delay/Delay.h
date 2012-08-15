#ifndef _Delay_h
#define _Delay_h

#define FREE    1
#define BUSY    2

extern uint8 DlyStatus;

__arm void Dly_ISR(void);
Status_t Dly(unsigned int a, char c, void *DlyCallback_p);
void DlyStop(void);

#endif
