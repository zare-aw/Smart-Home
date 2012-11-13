#include "Global_Defines.h"
#include "Timer.h"
#include "Includes.h"
#include <NXP/iolpc2148.h>
#include "StatusHandling.h"

void (*Match_0_Callback)(void *);
void (*Match_1_Callback)(void *);
void (*Match_2_Callback)(void *);

/*******************************************************************************
 *
 ******************************************************************************/
void Wait(uint32 Time_uSec)
{
  uint32 Time;
  
  if((Time = T0TC + Time_uSec) > DELAY_TIMER_RESET_VALUE)
  {
    Time -= DELAY_TIMER_RESET_VALUE;
    while(T0TC > Time);
    while(T0TC < Time);
  }
  else
    while(T0TC < Time);
}

/*******************************************************************************
 * Funtion for set match 0 value and callback
 * @uint32 Value: Value to set for match 0
 * @void (*)(void *) Callback: Callback function pointer. This function is
 *                             called in interrupt context.
 *                             This function must have '__arm' flag!
 ******************************************************************************/
Status_t Delay_Timer_Set_Match_0(uint32 Value, void (*Callback)(void *))
{
  ASSERT(Callback != NULL, -INVALID_INPUT_POINTER);
  
  Match_0_Callback = Callback;
  T0MCR_bit.MR0INT = 1;             // Enable interrupt on match 0
  T0MR0 = Value;                    // Set match 0 value
  
  return SUCCESS;
}

/*******************************************************************************
 * Funtion for set match 1 value and callback
 * @uint32 Value: Value to set for match 1
 * @void (*)(void *) Callback: Callback function pointer. This function is
 *                             called in interrupt context.
 *                             This function must have '__arm' flag!
 ******************************************************************************/
Status_t Delay_Timer_Set_Match_1(uint32 Value, void (*Callback)(void *))
{
  ASSERT(Callback != NULL, -INVALID_INPUT_POINTER);
  
  Match_1_Callback = Callback;
  T0MCR_bit.MR1INT = 1;             // Enable interrupt on match 1
  T0MR1 = Value;                    // Set match 1 value
  
  return SUCCESS;
}

/*******************************************************************************
 * Funtion for set match 2 value and callback
 * @uint32 Value: Value to set for match 2
 * @void (*)(void *) Callback: Callback function pointer. This function is
 *                             called in interrupt context.
 *                             This function must have '__arm' flag!
 ******************************************************************************/
Status_t Delay_Timer_Set_Match_2(uint32 Value, void (*Callback)(void *))
{
  ASSERT(Callback != NULL, -INVALID_INPUT_POINTER);
  
  Match_2_Callback = Callback;
  T0MCR_bit.MR2INT = 1;             // Enable interrupt on match 2
  T0MR2 = Value;                    // Set match 2 value
  
  return SUCCESS;
}

/*******************************************************************************
 *
 ******************************************************************************/
void Delay_Timer_Init(void)
{
  uint32 PerCLK;
  
  T0TCR_bit.CE = 0;     // Timer count disable
  T0IR = 0xFF;          // Clear INTERRUPT FLAGS
  T0TCR_bit.CR = 1;     // Timer reset
  T0CTCR = 0;           // Increment on PCLK
  
  PerCLK = Read_PER_CLK();
  
  T0PR = (PerCLK / 1000000) - 1;    // Set prescale for 1 TIC on 1us
  T0PC = 0;                         // Clear prescale
  
  T0MCR = 0;                        // Clear all EVENT on match
  
  T0MR3 = DELAY_TIMER_RESET_VALUE;  // Set match 3 value
  T0MCR_bit.MR3RES = 1;             // On match, reset the timer
  
  T0CCR = 0;            // Disable Capture
  T0EMR = 0;            // Disable EXTERNAL MATCH
  
  T0TCR = 1;            // Remove reset and enable counter
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
  T1MCR_bit.MR0STOP = 0;// Koga ke ima match neka ne zapira tajmerot
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

__arm __irq void Timer_0_ISR(void)    // Interrupt function for TIMER0 
{
  uint8 IRQ_Serviced = 0;
  
  if(T0IR_bit.MR0INT == 1)
  {
    T0IR_bit.MR0INT = 1;        // Clear match 0 interrupt
    T0MCR_bit.MR0INT = 0;       // Disable interrupt on match 0
    Match_0_Callback(NULL);     // Call match 0 callback
    IRQ_Serviced = 1;           // Set IRQ_Serviced flag
  }
  
  if(T0IR_bit.MR1INT == 1)
  {
    T0IR_bit.MR1INT = 1;        // Clear match 1 interrupt
    T0MCR_bit.MR1INT = 0;       // Disable interrupt on match 1
    Match_1_Callback(NULL);     // Call match 1 callback
    IRQ_Serviced = 1;           // Set IRQ_Serviced flag
  }
  
  if(T0IR_bit.MR2INT == 1)
  {
    T0IR_bit.MR2INT = 1;        // Clear match 2 interrupt
    T0MCR_bit.MR2INT = 0;       // Disable interrupt on match 2
    Match_2_Callback(NULL);     // Call match 2 callback
    IRQ_Serviced = 1;           // Set IRQ_Serviced flag
  }
  
  if(IRQ_Serviced == 0)
    T0IR = 0xFF;
  
  VICVectAddr = 0;
}

__irq void Timer_1_ISR(void)    // Interrupt servisna rutina za TIMER1
{
  T1IR = 0xFF;

  (void)IR_Timer_ISR();

  VICVectAddr = 0;
}
