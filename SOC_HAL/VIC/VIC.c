#include "Global_Defines.h"
#include    "Includes.h"

/*******************************************************************************
* Intrrupt rutini. Se naogaat vo soodvetnite moduli
*******************************************************************************/
__irq void UART0_ISR(void);
__irq void UART1_ISR(void);
__irq void Timer_0_ISR(void);
__irq void Timer_1_ISR(void);
__irq void Ext_Int_0_ISR(void);
__irq void Ext_Int_1_ISR(void);
__irq void Ext_Int_2_ISR(void);
__irq void Ext_Int_3_ISR(void);
__irq void I2C0_ISR(void);
__irq void RTC_Isr(void);


/*******************************************************************************
* Funkcija za inicijalizacija na VIC
* @in NONE
* @out NONE
* @in-out NONE
*******************************************************************************/
void VICInit(void)
{
  VICIntEnable = 0;                           // Onevozmozi gi site prekini
  VICIntSelect = 0;                           // Site prekini ke bidat IRQ
  VICIntEnClear = 0xFFFFFFFF;                 // Iscisti gi flegovite za site prekini
  VICProtection = 0;                          // Ovozmozi generalen pristap do VIC
  VICVectAddr = 0;                             // Iscisti go baferot za adresa na rutinata
  VICProtection = 0;                          // Ovozmozi generalen pristap do VIC
  
  VICVectAddr2 = (unsigned int)Timer_0_ISR;   // Stavi ja adresata na servisnata rutina na slot 2
  VICVectCntl2_bit.NUMBER = 4;                // Postavi go Timer0 na slot 2 (Timer0 ima adresa 4)
  VICVectCntl2_bit.ENABLED = 1;               // Ovozmozi go INTERRUPT-ot od slot 2
  VICIntEnable_bit.INT4 = 1;                  // Vkluci go Timer0 Interrupt
  
  VICVectAddr3 = (unsigned int)Timer_1_ISR;   // Stavi ja adresata na servisnata rutina na slot 3
  VICVectCntl3_bit.NUMBER = 5;                // Postavi go Timer1 na slot 3
  VICVectCntl3_bit.ENABLED = 1;               // Ovozmozi go INTERRUPT-ot od slot 3
  VICIntEnable_bit.INT5 = 1;                  // Vkluci go Timer1 Interrupt
    
  VICVectAddr0  = (unsigned int)UART0_ISR;    // Stavi ja adresata na servisnata rutina na slot 0
  VICVectCntl0_bit.NUMBER = 6;                // Postavi go UART0 na slot 0
  VICVectCntl0_bit.ENABLED = 1;               // Ovozmozi go INTERRUPT-ot od slot 0
  VICIntEnable_bit.INT6 = 1;                  // Vkluci go UART0 Interrupt
  
  VICVectAddr1 = (unsigned int)UART1_ISR;     // Stavi ja adresata na servisnata rutina na slot 1
  VICVectCntl1_bit.NUMBER = 7;                // Postavi go UART1 na slot 1
  VICVectCntl1_bit.ENABLED = 1;               // Ovozmozi go INTERRUPT-ot od slot 1
  VICIntEnable_bit.INT7 = 1;                  // Vkluci go UART1 Interrupt
  
  VICVectAddr4 = (unsigned int)Ext_Int_0_ISR; // Stavi ja adresata na servisnata rutina na slot 4
  VICVectCntl4_bit.NUMBER = 14;               // Postavi go ExtInt0 na slot 4
  VICVectCntl4_bit.ENABLED = 1;               // Ovozmozi go INTERRUPT-ot od slot 4
  VICIntEnable_bit.INT14 = 1;                 // Vkluci go ExtInt0 Interrupt
  
  VICVectAddr5 = (unsigned int)Ext_Int_1_ISR; // Stavi ja adresata na servisnata rutina na slot 5
  VICVectCntl5_bit.NUMBER = 15;               // Postavi go ExtInt1 na slot 5
  VICVectCntl5_bit.ENABLED = 1;               // Ovozmozi go INTERRUPT-ot od slot 5
  VICIntEnable_bit.INT15 = 1;                 // Vkluci go ExtInt1 Interrupt
  
  VICVectAddr6 = (unsigned int)Ext_Int_2_ISR; // Stavi ja adresata na servisnata rutina na slot 6
  VICVectCntl6_bit.NUMBER = 16;               // Postavi go ExtInt2 na slot 6
  VICVectCntl6_bit.ENABLED = 1;               // Ovozmozi go INTERRUPT-ot od slot 6
  VICIntEnable_bit.INT16 = 1;                 // Vkluci go ExtInt2 Interrupt
  
  VICVectAddr7 = (unsigned int)Ext_Int_3_ISR; // Stavi ja adresata na servisnata rutina na slot 7
  VICVectCntl7_bit.NUMBER = 17;               // Postavi go ExtInt3 na slot 7
  VICVectCntl7_bit.ENABLED = 1;               // Ovozmozi go INTERRUPT-ot od slot 7
  VICIntEnable_bit.INT17 = 1;                 // Vkluci go ExtInt3 Interrupt
  
  VICVectAddr8 = (unsigned int)I2C0_ISR;      // Stavi ja adresata na servisnata rutina na slot 8
  VICVectCntl8_bit.NUMBER = 9;                // Postavi go I2C0 na slot 8
  VICVectCntl8_bit.ENABLED = 1;               // Ovozmozi go INTERRUPT-ot od slot 8
  VICIntEnable_bit.INT9 = 1;                  // Vkluci go I2C0 Interrupt
  
  VICVectAddr9 = (unsigned int)RTC_Isr;       // Stavi ja adresata na servisnata rutina na slot 9
  VICVectCntl9_bit.NUMBER = 13;               // Postavi go RTC na slot 9
  VICVectCntl9_bit.ENABLED = 1;               // Ovozmozi go INTERRUPT-ot od slot 9
  VICIntEnable_bit.INT13 = 1;                 // Vkluci go RTC Interrupt
  
}



__irq void Ext_Int_0_ISR(void)
{
  VICVectAddr = 0;
}
__irq void Ext_Int_1_ISR(void)
{
  VICVectAddr = 0;
}
__irq void Ext_Int_3_ISR(void)
{
  VICVectAddr = 0;
}
__irq void I2C0_ISR(void)
{
  VICVectAddr = 0;
}