#ifndef _Console_h
#define _Console_h

#include "StatusHandling.h"
#include "Console_Defconfig.h"

/*******************************************************************************
* Function flags for console module
*******************************************************************************/
#define CONSOLE_COMMANDS_OVERFLOW           CONSOLE_OFFSET | 0x01
#define CONSOLE_COMMAND_ERROR               CONSOLE_OFFSET | 0x02
#define CONSOLE_COMMAND_EXECUTE_ERROR       CONSOLE_OFFSET | 0x03
#define CONSOLE_CHANNEL_INIT_ERROR          CONSOLE_OFFSET | 0x04

extern char InputString[MAX_CONSOLE_COMMAND_LENGTH];
extern char QueueConsoleCommand[MAX_CONSOLE_COMMAND_IN_QUEUE][MAX_CONSOLE_COMMAND_LENGTH];

extern uint8 ConsoleCommandsInQueue;
extern uint8 ConsoleChanel;
extern unsigned int Console_Queue_Cnt;

void printc(const char *format, ...);
Status_t puts(const char *Line);
void Add_Char_In_Console_Queue(char Input);
Status_t Console_Print_Pull(void);
Status_t Console_Server_Init(uint8 Chanell, unsigned int Speed, uint8 Mode);

Status_t Add_Console_Command_In_Queue(char *InputString);
Status_t Remove_Console_Command_From_Queue(uint8 NoOfCommand);

Status_t Console_Command_Execute(uint8 NoOfCommand);

Status_t Console_ISR(void);

#endif
