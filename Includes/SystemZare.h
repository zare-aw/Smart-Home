#ifndef _SystemZare_h
#define _SystemZare_h

#define OSC_12MHz   12000000

#define OSC_CLK   OSC_12MHz

Status_t MAM_Init (unsigned int a);
Status_t PLL_Init(uint8 a);
uint32 Read_CPU_CLK(void);
void PCLK_Init(uint8 a);
uint32 Read_PER_CLK(void);
void Print_Reset_Source(void);

#endif