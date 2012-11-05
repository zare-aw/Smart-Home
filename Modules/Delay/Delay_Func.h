#ifndef _Delay_Func_h
#define _Delay_Func_h

// Delay
#define UDELAY        DELAY_OFFSET | 0x01
#define MDELAY        DELAY_OFFSET | 0x02
#define SDELAY        DELAY_OFFSET | 0x03

#define DELAY_WORK    DELAY_OFFSET | 0x11
#define DELAY_ISR     DELAY_OFFSET | 0x12

#endif
