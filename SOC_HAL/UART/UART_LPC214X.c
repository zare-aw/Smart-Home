#include <NXP/iolpc2148.h>
#include "Global_Defines.h"
#include "Func_Trace.h"
#include "Console.h"

#include "UART_LPC214X.h"
#include "UART_LPC214X_Func.h"

unsigned int UART_Flag1 = 0;
unsigned int UART_Flag2 = 0;

uint8 Old_Receive_INT_State_UART_0 = 0;
uint8 Old_Transmit_INT_State_UART_0 = 0;
uint8 Old_Receive_INT_State_UART_1 = 0;
uint8 Old_Transmit_INT_State_UART_1 = 0;

/*******************************************************************************
* Initialization function for UART 0.
* @IN baudrate, support 9600, 115200, 230400, 448000, 1000000, 2000000
*******************************************************************************/
Status_t UART_0_Init(unsigned int baud)
{
  FuncIN(UART_0_INIT);
  
  unsigned int PCLK_temp;
  
  PINSEL0_bit.P0_0 = 1;       // Dodeli gi soodvetnite pinovi na UART 0
  PINSEL0_bit.P0_1 = 1;
 
  if(PLLSTAT_bit.PLLE)        // So sledniov kod odreduvame kolku e PCLK
  {
    switch (VPBDIV)
    {
      case 0:
        PCLK_temp = ((PLLSTAT_bit.MSEL+1)*12000000)/4;  
        break;
      case 1:
        PCLK_temp = ((PLLSTAT_bit.MSEL+1)*12000000);
        break;
      case 2:
        PCLK_temp = ((PLLSTAT_bit.MSEL+1)*12000000)/2;
        break;
      default:
        Fatal_Abort(-PCLKSEL_ERROR);
    }
  }
  else
  {
    switch (VPBDIV)
    {
      case 0:
        PCLK_temp = 12000000/4;  
        break;
      case 1:
        PCLK_temp = 12000000;
        break;
      case 2:
        PCLK_temp = 12000000/2;
        break;
      default:
        break;
    }
  }
  
  U0LCR_bit.DLAB = 1;         // Ovozmozi pristap do Divisor registrite
  
  switch (PCLK_temp)
  {
    case 60000000:
      switch (baud)
      {
        case 600:
          U0DLL = 106;
          U0DLM = 24;
          U0FDR_bit.DIVADDVAL = 0;
          U0FDR_bit.MULVAL = 15;
          break;
        case 2400:
          U0DLL = 226;
          U0DLM = 4;
          U0FDR_bit.DIVADDVAL = 3;
          U0FDR_bit.MULVAL = 12;
          break;
        case 9600:
          U0DLL = 23;
          U0DLM = 1;
          U0FDR_bit.DIVADDVAL = 6;
          U0FDR_bit.MULVAL = 15;
          break;
        case 38400:
          U0DLL = 71;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 3;
          U0FDR_bit.MULVAL = 8;
          break;
        case 115200:
          U0DLL = 24;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 5;
          U0FDR_bit.MULVAL = 14;
          break;
        default:
          Fatal_Abort(-INVALID_INPUT_PARAMETER);
      }
    break;
    case 30000000:
      switch (baud)
      {
        case 600:
          U0DLL = 53;
          U0DLM = 12;
          U0FDR_bit.DIVADDVAL = 0;
          U0FDR_bit.MULVAL = 15;
          break;
        case 2400:
          U0DLL = 113;
          U0DLM = 2;
          U0FDR_bit.DIVADDVAL = 3;
          U0FDR_bit.MULVAL = 12;
          break;
        case 9600:
          U0DLL = 93;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 11;
          U0FDR_bit.MULVAL = 10;
          break;
        case 38400:
          U0DLL = 38;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 4;
          U0FDR_bit.MULVAL = 14;
          break;
        case 115200:
          U0DLL = 12;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 5;
          U0FDR_bit.MULVAL = 14;
          break;
        default:
          Fatal_Abort(-INVALID_INPUT_PARAMETER);
      }
    break;
    case 15000000:
      switch (baud)
      {
        case 600:
          U0DLL = 226;
          U0DLM = 4;
          U0FDR_bit.DIVADDVAL = 3;
          U0FDR_bit.MULVAL = 12;
          break;
        case 2400:
          U0DLL = 23;
          U0DLM = 1;
          U0FDR_bit.DIVADDVAL = 6;
          U0FDR_bit.MULVAL = 15;
          break;
        case 9600:
          U0DLL = 71;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 3;
          U0FDR_bit.MULVAL = 8;
          break;
        case 38400:
          U0DLL = 19;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 4;
          U0FDR_bit.MULVAL = 14;
          break;
        case 115200:
          U0DLL = 6;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 5;
          U0FDR_bit.MULVAL = 14;
          break;
        default:
          Fatal_Abort(-INVALID_INPUT_PARAMETER);
      }
    break;
    case 12000000:
      switch (baud)
      {
        case 600:
          U0DLL = 226;
          U0DLM = 4;
          U0FDR_bit.DIVADDVAL = 0;
          U0FDR_bit.MULVAL = 15;
          break;
        case 2400:
          U0DLL = 250;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 3;
          U0FDR_bit.MULVAL = 12;
          break;
        case 9600:
          U0DLL = 37;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 10;
          U0FDR_bit.MULVAL = 9;
          break;
        case 38400:
          U0DLL = 16;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 2;
          U0FDR_bit.MULVAL = 9;
          break;
        case 115200:
          U0DLL = 6;
          U0DLM = 0;
          U0FDR_bit.DIVADDVAL = 1;
          U0FDR_bit.MULVAL = 12;
          break;
        default:
          Fatal_Abort(-INVALID_INPUT_PARAMETER);
      }
    break;
    default:
      Fatal_Abort(-PCLKSEL_ERROR);
  }
  
    
  U0LCR_bit.DLAB = 0;     // Ovozmozi pristap do RBR i THR
  
  U0LCR_bit.WLS = 3;      // 8-bit Data
  U0LCR_bit.SBS = 0;      // 1 Stop bit
  U0LCR_bit.PE = 0;       // Disable parity
  U0LCR_bit.BC = 0;       // Iskluci BREAK
  
  U0FCR_bit.FCRFE = 1;    // Enable FIFO
  U0FCR_bit.RFR = 1;      // Rx FIFO Reset
  U0FCR_bit.TFR = 1;      // Tx FIFO Reset
  U0FCR_bit.RTLS = 0;     // TRIGGER na sekoj stasan bajt

  U0IER = 0;  
  U0IER_bit.RDAIE = 0;    // Onevozmozi prekin pri primen podatok
  U0IER_bit.THREIE = 0;   // Onevozmozi prekin pri prazen THR
  U0IER_bit.RXLSIE = 0;   // Onevozmozi prekin pri promena na linijata na Rx
  U0IER_bit.ABTOINTEN = 0;// Onevozmozi prekin pri auto-baud time out
  U0IER_bit.ABEOINTEN = 0;// Onevozmozi prekin pri kraj na auto-baud

  EXIT_SUCCESS_FUNC(UART_0_INIT);
}
FUNC_REGISTER(UART_0_INIT, UART_0_Init);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_Interrupt_State_UART_0(uint8 Received, uint8 THREmpty)
{
  FuncIN(SET_INTERRUPT_STATE_UART_0);

  Old_Receive_INT_State_UART_0 = U0IER_bit.RDAIE;
  Old_Transmit_INT_State_UART_0 = U0IER_bit.THREIE;
  
  switch(Received)
  {
    case ENABLE:
      U0IER_bit.RDAIE = 1;
      break;
    case DISABLE:
      U0IER_bit.RDAIE = 0;
      break;
    case NO_CHANGE:
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  switch(THREmpty)
  {
  case ENABLE:
    U0IER_bit.THREIE = 1;
    break;
  case DISABLE:
    U0IER_bit.THREIE = 0;
    break;
  case NO_CHANGE:
    break;
  default:
    Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  EXIT_SUCCESS_FUNC(SET_INTERRUPT_STATE_UART_0);
}
FUNC_REGISTER(SET_INTERRUPT_STATE_UART_0, Set_Interrupt_State_UART_0);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_Interrupt_State_UART_1(uint8 Received, uint8 THREmpty)
{
  FuncIN(SET_INTERRUPT_STATE_UART_1);
  
  Old_Receive_INT_State_UART_1 = U1IER_bit.RDAIE;
  Old_Transmit_INT_State_UART_1 = U1IER_bit.THREIE;
  
  switch(Received)
  {
  case ENABLE:
    U1IER_bit.RDAIE = 1;
    break;
  case DISABLE:
    U1IER_bit.RDAIE = 0;
    break;
  case NO_CHANGE:
    break;
  default:
    Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  switch(THREmpty)
  {
  case ENABLE:
    U1IER_bit.THREIE = 1;
    break;
  case DISABLE:
    U1IER_bit.THREIE = 0;
    break;
  case NO_CHANGE:
    break;
  default:
    Fatal_Abort(-INVALID_INPUT_PARAMETER);
  } 
  
  EXIT_SUCCESS_FUNC(SET_INTERRUPT_STATE_UART_1);
}
FUNC_REGISTER(SET_INTERRUPT_STATE_UART_1, Set_Interrupt_State_UART_1);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Return_Old_Interrupt_State_UART_0(void)
{
  U0IER_bit.RDAIE = Old_Receive_INT_State_UART_0;
  U0IER_bit.THREIE = Old_Transmit_INT_State_UART_0;
  return SUCCESS;
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Return_Old_Interrupt_State_UART_1(void)
{
  U1IER_bit.RDAIE = Old_Receive_INT_State_UART_1;
  U1IER_bit.THREIE = Old_Transmit_INT_State_UART_1;
  return SUCCESS;
}

/*******************************************************************************
* Postavuva broj na stasani bajti vo RX FIFO na UART0
* za koi ke se pojavi ineterrupt
*******************************************************************************/
Status_t Set_Trigger_UART_0(uint8 Trigger)
{
  FuncIN(SET_TRIGGER_UART_0);
  
  switch(Trigger)
  {
    case BYTE_1:
      U0FCR_bit.RTLS = 0;     // TRIGGER na sekoj stasan bajt
      break;
    case BYTE_4:
      U0FCR_bit.RTLS = 1;     // TRIGGER na sekoi 4 bajti
      break;
    case BYTE_8:
      U0FCR_bit.RTLS = 2;     // TRIGGER na sekoi 8 bajti
      break;
    case BYTE_14:
      U0FCR_bit.RTLS = 3;     // TRIGGER na sekoi 14 bajti
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  EXIT_SUCCESS_FUNC(SET_TRIGGER_UART_0);
}
FUNC_REGISTER(SET_TRIGGER_UART_0, Set_Trigger_UART_0);

/*******************************************************************************
* Postavuva broj na stasani bajti vo RX FIFO na UART1
* za koi ke se pojavi ineterrupt
*******************************************************************************/
Status_t Set_Trigger_UART_1(uint8 Trigger)
{
  FuncIN(SET_TRIGGER_UART_1);

  switch(Trigger)
  {
    case BYTE_1:
      U1FCR_bit.RTLS = 0;     // TRIGGER na sekoj stasan bajt
      break;
    case BYTE_4:
      U1FCR_bit.RTLS = 1;     // TRIGGER na sekoi 4 bajti
      break;
    case BYTE_8:
      U1FCR_bit.RTLS = 2;     // TRIGGER na sekoi 8 bajti
      break;
    case BYTE_14:
      U1FCR_bit.RTLS = 3;     // TRIGGER na sekoi 14 bajti
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  EXIT_SUCCESS_FUNC(SET_TRIGGER_UART_1);
}
FUNC_REGISTER(SET_TRIGGER_UART_1, Set_Trigger_UART_1);

/*******************************************************************************
* Function for write 1 byte UART 0 transmit FIFO
*******************************************************************************/
void Write_Char_UART_0(unsigned char ch)
{
  U0THR = ch;
}

/*******************************************************************************
* Function for write 1 byte UART 1 transmit FIFO
*******************************************************************************/
void Write_Char_UART_1(unsigned char ch)
{
  U1THR = ch;
}

/*******************************************************************************
* Function for sending 1 byte on UART 0
*******************************************************************************/
Status_t Put_Char_UART_0(unsigned char ch, unsigned int TimeOut)      // Praka int promenliva preku UART 0
{
  int i = 0;
  
  while(!U0LSR_bit.THRE)
  {
    i++;
    if(i == TimeOut)
      return UART0_SEND_ERROR;
  }
  
  U0THR = ch;
  
  return SUCCESS;
}

/*******************************************************************************
* Function for sending 1 byte on UART 1
*******************************************************************************/
Status_t Put_Char_UART_1(unsigned char ch, unsigned int TimeOut)      // Praka int promenliva preku UART 1
{
  int i = 0;
  
  while(!U1LSR_bit.THRE)
  {
    i++;
    if(i == TimeOut)
      return UART0_SEND_ERROR;
  }
  
  U1THR = ch;
  
  return SUCCESS;
}

/*******************************************************************************
* Function for reading 1 byte from UART 0 receive register
*******************************************************************************/
Status_t Get_Char_UART_0(unsigned char *ReceiveByte, unsigned int TimeOut)         // Ceka podatok od UART 0 i koga ke go dobie go vraka
{
  int i = 0;
  
  while (!U0LSR_bit.DR)
  {
    i++;
    if(i == TimeOut)
      return UART0_RECEIVE_ERROR;
  }
  
  *ReceiveByte = U0RBR;
  
  return SUCCESS;
}

/*******************************************************************************
* Function for reading 1 byte from UART 1 receive register
*******************************************************************************/
Status_t Get_Char_UART_1(unsigned char *ReceiveByte, unsigned int TimeOut)         // Ceka podatok od UART 1 i koga ke go dobie go vraka
{
  int i = 0;
  
  while (!U1LSR_bit.DR)
  {
    i++;
    if(i == TimeOut)
      return UART1_RECEIVE_ERROR;
  }
  
  *ReceiveByte = U1RBR;
  
  return SUCCESS;
}

/*******************************************************************************
* Clear RX FIFO Register on UART 0
*******************************************************************************/
Status_t Clear_RX_FIFO_UART_0(const unsigned int TimeOut)
{
  volatile uint8 Temp;
  unsigned int i = 0;
  
  while (U0LSR_bit.DR)
  {
    Temp = U0RBR;
    i++;
    if(i == TimeOut)
      return UART_0_RX_FIFO_ERROR;
  }
  
  return SUCCESS;
}

/*******************************************************************************
* Clear RX FIFO Register on UART 1
*******************************************************************************/
Status_t Clear_RX_FIFO_UART_1(const unsigned int TimeOut)
{
  volatile uint8 Temp;
  unsigned int i = 0;
  
  while (U1LSR_bit.DR)
  {
    Temp = U1RBR;
    i++;
    if(i == TimeOut)
      return UART_1_RX_FIFO_ERROR;
  }
  
  return SUCCESS;
}

/*******************************************************************************
* Check TX FIFO on UART 0. 0 for empty FIFO, 1 for full FIFO
*******************************************************************************/
Status_t Check_TX_Status_UART_0(uint8 * Status)
{
  *Status = (uint8)U0LSR_bit.THRE;
  
  return SUCCESS;
}

/*******************************************************************************
* Check TX FIFO on UART 1. 0 for empty FIFO, 1 for full FIFO
*******************************************************************************/
Status_t Check_TX_Status_UART_1(uint8 * Status)
{
  *Status = (uint8)U1LSR_bit.THRE;
  
  return SUCCESS;
}

/*******************************************************************************
* Sending String on UART 0
*******************************************************************************/
Status_t Put_String_UART_0(char *Buf)
{
  Status_t Status = GENERAL_ERROR;
  char *pBuf = Buf;
  
  while (*pBuf)
  {
    Status = Put_Char_UART_0(*pBuf++, 0xFFFFFFF);
    if(Status != SUCCESS)
      return Status;
  }
  
  return Status;
}

/*******************************************************************************
* Sending String on UART 1
*******************************************************************************/
Status_t Put_String_UART_1(char *Buf)
{
  Status_t Status = GENERAL_ERROR;
  char *pBuf = Buf;
  
  while (*pBuf)
  {
    Status = Put_Char_UART_1(*pBuf++, 0xFFFFFFF);
    if(Status != SUCCESS)
      return Status;
  }
  
  return Status;
}

/*******************************************************************************
* Interrupt Rutini
*******************************************************************************/

__irq void UART0_ISR(void)    // Interrupt servisna rutina na UART 0
{
  (void)Console_ISR();
  
  VICVectAddr = 0;
}


__irq void UART1_ISR(void)    // Interrupt servisna rutina na UART 1
{
  VICVectAddr = 0; 
}
