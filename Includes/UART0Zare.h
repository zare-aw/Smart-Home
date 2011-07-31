#ifndef _UART0Zare_h
#define _UART0Zare_h

extern unsigned int UART_Flag1;
extern unsigned int UART_Flag2;

// broj na bajti na koi ke se pojavi interapt od RX na UART
#define BYTE_1    0
#define BYTE_4    1
#define BYTE_8    2
#define BYTE_14   3

#define UART_0    1
#define UART_1    2

#define NO_CHANGE 9

Status_t UART_0_Init(unsigned int baud);

Status_t Get_Char_UART_0(unsigned char *ReceiveByte, unsigned int TimeOut);
Status_t Get_Char_UART_1(unsigned char *ReceiveByte, unsigned int TimeOut);

void Write_Char_UART_0(unsigned char ch);
void Write_Char_UART_1(unsigned char ch);

Status_t Put_Char_UART_0(unsigned char ch, unsigned int TimeOut);
Status_t Put_Char_UART_1(unsigned char ch, unsigned int TimeOut);

Status_t Clear_RX_FIFO_UART_0(const unsigned int TimeOut);
Status_t Clear_RX_FIFO_UART_1(const unsigned int TimeOut);

Status_t Set_Trigger_UART_0(uint8 Trigger);
Status_t Set_Trigger_UART_1(uint8 Trigger);

Status_t Set_Interrupt_State_UART_0(uint8 Received, uint8 THREmpty);
Status_t Set_Interrupt_State_UART_1(uint8 Received, uint8 THREmpty);

Status_t Return_Old_Interrupt_State_UART_0(void);
Status_t Return_Old_Interrupt_State_UART_1(void);

Status_t Check_TX_Status_UART_0(uint8 * Status);
Status_t Check_TX_Status_UART_1(uint8 * Status);

Status_t Put_String_UART_0(char *Buf);
Status_t Put_String_UART_1(char *Buf);

#endif