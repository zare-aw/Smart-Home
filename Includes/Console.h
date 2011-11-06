#ifndef _Console_h
#define _Console_h

#include "StatusHandling.h"

#define MAX_CONSOLE_COMMAND_LENGTH         256
#define CONSOLE_QUEUE_SIZE                 4096
#define MAX_CONSOLE_COMMAND_IN_QUEUE       4
#define VS_BUFFER_SIZE                     256

#define CONSOLE_CHANELL     UART_0
#define CONSOLE_SPEED       115200
#define CONSOLE_MODE        MODE_POOLING

#ifndef MODE_INTERRUPT
#define MODE_INTERRUPT      1
#endif
#ifndef MODE_POOLING
#define MODE_POOLING        0
#endif

extern char InputString[MAX_CONSOLE_COMMAND_LENGTH];
extern char QueueConsoleCommand[MAX_CONSOLE_COMMAND_IN_QUEUE][MAX_CONSOLE_COMMAND_LENGTH];

extern uint8 ConsoleCommandsInQueue;
extern uint8 ConsoleChanel;
extern unsigned int Console_Queue_Cnt;

void printc(const char *format, ...);
void Add_Char_In_Console_Queue(char Input);
Status_t Console_Print_Pull(void);
Status_t Console_Server_Init(uint8 Chanell, unsigned int Speed, uint8 Mode);

Status_t Add_Console_Command_In_Queue(char *InputString);
Status_t Remove_Console_Command_From_Queue(uint8 NoOfCommand);

Status_t Console_Command_Execute(uint8 NoOfCommand);

Status_t Console_ISR(void);

#endif
