#include "Global_Defines.h"
#include "Includes.h"



void Timer_0_Init(void)
{
  T0TCR_bit.CE = 0;     // Iskluci go tajmerot
  T0IR = 0xFF;          // Cistime INTERRUPT FLAGS
  T0TCR_bit.CR = 1;     // Resetiraj go tajmerot
  T0CTCR = 0;           // Increment na PCLK
  T0PR = 30000;         // 30000 na preskalerot za da dobieme 1 TIC na 1ms
  T0PC = 0;             // Se cisti preskalerot
  T0MCR = 0;            // Se zabranuvaat site EVENT od match
  T0MCR_bit.MR0INT = 1; // Ovozmozuva prekin na match 0
  T0MCR_bit.MR0RES = 1; // Koga ke ima match neka se resetira tajmerot
  T0CCR = 0;            // Isklucuvame Capture
  T0EMR = 0;            // Onevozmozuvame EXTERNAL MATCH
}

void Timer_0_Start(unsigned int a, unsigned int b)
{
  T0PR = b;             // Postavi vrednost vo preskalerot
  T0MR0 = a;            // Postavi na koja vrednost na match da ima event (prekin)
  T0TCR_bit.CR = 1;     // Resetiraj go tajmerot
  T0TCR = 1;            // Vkluci go tajmerot da broi i trgni go resetot ( da ne stoi na 0 tajmerot )
}

void Timer_0_Stop(void)
{
  T0TCR_bit.CE = 0;     // Iskluci go tajmerot
}

void Timer_1_Init(void)
{
  T1TCR_bit.CE = 0;     // Iskluci go tajmerot
  T1IR = 0xFF;          // Cistime INTERRUPT FLAGS
  T1TCR_bit.CR = 1;     // Resetiraj go tajmerot
  T1CTCR = 0;           // Increment na PCLK
  T1PR = 30;            // 30 na preskalerot za da dobieme 1 TIC na 1us
  T1PC = 0;             // Se cisti preskalerot
  T1MCR = 0;            // Se zabranuvaat site EVENT od match
  T1MCR_bit.MR0INT = 1; // Ovozmozuva prekin na match 0
  T1MCR_bit.MR0RES = 1; // Koga ke ima match neka se resetira tajmerot
  T1MCR_bit.MR0STOP = 0; // Koga ke ima match neka ne zapira tajmerot
  T1CCR = 0;            // Isklucuvame Capture
  T1EMR = 0;            // Onevozmozuvame EXTERNAL MATCH
}

void Timer_1_Start(uint32 MatchValue)
{
  T1MR0 = MatchValue;   // Postavi na koja vrednost na match da ima event (prekin)
  T1TCR_bit.CR = 1;     // Resetiraj go tajmerot
  T1TCR = 1;            // Vkluci go tajmerot da broi i trgni go resetot ( da ne stoi na 0 tajmerot )
}

void Timer_1_Stop(void)
{
  T1TCR_bit.CE = 0;     // Iskluci go tajmerot
}

void Timer_1_Update_Match_0_Value(uint32 MatchValue)
{
  T1MR0 = MatchValue;   // Postavi na koja vrednost na match 0 da ima event (prekin)
}



__irq void Timer_0_ISR(void)    // Interrupt servisna rutina za TIMER0 
{
  T0IR = 0xFF;
  
  Dly_ISR();
  
  VICVectAddr = 0;
}

__irq void Timer_1_ISR(void)    // Interrupt servisna rutina za TIMER1
{
  T1IR = 0xFF;

  (void)IR_Timer_ISR();

  VICVectAddr = 0;
}
