#include "Global_Defines.h"
#include "Includes.h"
#include "Func_Trace.h"
#include "Console_Defconfig.h"
#include "Console_Func.h"
#include "ConsoleHelp.h"
#include "ConsoleCommands.h"
#include "Command.h"

char InputString[MAX_CONSOLE_COMMAND_LENGTH] = {0};
char Console_Queue[CONSOLE_QUEUE_SIZE] = {0};
char QueueConsoleCommand[MAX_CONSOLE_COMMAND_IN_QUEUE][MAX_CONSOLE_COMMAND_LENGTH] = {0};
char ConsoleCommandHistory[MAX_CONSOLE_COMMAND_HISTORY][MAX_CONSOLE_COMMAND_LENGTH] = {0};

uint32 Console_Queue_Cnt = 0;
uint32 Console_Queue_Add_Cnt = 0;
uint32 Console_Queue_Print_Cnt = 0;
uint8 InputCharCnt = 0;
uint8 ConsoleCommandsInQueue = 0;
uint8 ConsoleCommandsInHistory = 0;
uint8 Console_Mode = MODE_POOLING;
uint8 ConsoleChanel = UART_0;
uint8 ConsoleHistoryCnt = 0;

static Status_t Add_Console_Command_In_History(char *InputString);
static Status_t Get_Console_Command_From_History(uint8 NoOfPreviousCommand, char *CommandString);

/*******************************************************************************
* Definicija na funkciski pokazuvaci
*******************************************************************************/
Status_t (*Console_Chanell_Init)(unsigned int ) = NULL;
Status_t (*Console_Get_Char)(unsigned char *, unsigned int ) = NULL;
void     (*Console_Write_Char)(unsigned char ) = NULL;
Status_t (*Console_Put_Char)(unsigned char , unsigned int ) = NULL;
Status_t (*Console_Clear_RX_FIFO)(const unsigned int ) = NULL;
Status_t (*Console_Set_RX_Trigger)(uint8 ) = NULL;
Status_t (*Console_Set_Interrupt_State)(uint8 , uint8 ) = NULL;
Status_t (*Console_Put_String)(char *) = NULL;
Status_t (*Console_Check_TX_FIFO)(uint8 *) = NULL;
Status_t (*Console_Return_Old_Interrupt_State)() = NULL;

/*******************************************************************************
* Standardna funkcija za pisuvanje po konzola.
* @in format - string koj sakame da go pecatime zaedno so formatirackite znaci
* @in ... - dopolnitelni parametri koi sakame da gi pecatime
* @out NONE
*******************************************************************************/
void printc(const char *format, ...)
{
  uint32 i = 0;
  char VsBuffer[VS_BUFFER_SIZE] = {0};
  va_list args;
  
  va_start(args, format);
  
  vsprintf (VsBuffer, format, args);
  while(VsBuffer[i])
  {
    Add_Char_In_Console_Queue(VsBuffer[i]);
    if(VsBuffer[i] == 0x0A)
      Add_Char_In_Console_Queue(0x0D);
    i++;
  }
  va_end(args);
}

/*******************************************************************************
* Funkcija za prakanje na string na konzola.
* @in Line - string koj sakame da go pecatime
* @out Status
*******************************************************************************/
Status_t puts(const char *Line)
{
  uint32 i;
  
  for(i = 0; Line[i]; i++)
  {
    Add_Char_In_Console_Queue(Line[i]);
    if(Line[i] == 0x0A)
      Add_Char_In_Console_Queue(0x0D);
  }
  
  return SUCCESS;
}

/*******************************************************************************
* Dodava karakter vo console queue
* @in Input - Karakter koj ke se dodade vo Queue
* @out NONE
*******************************************************************************/
void Add_Char_In_Console_Queue(char Input)
{
  if(Console_Queue_Cnt < CONSOLE_QUEUE_SIZE)
  {
     Console_Queue[Console_Queue_Add_Cnt] = Input;
     Console_Queue_Add_Cnt ++;
     if(Console_Queue_Add_Cnt == CONSOLE_QUEUE_SIZE)
       Console_Queue_Add_Cnt = 0;
     Console_Queue_Cnt ++;
  }
}

/*******************************************************************************
* Dodava string vo console queue
* @in: char *Input - Pinter kon string koj ke se dodade vo Queue
* @out Status_t
*******************************************************************************/
Status_t Add_String_In_Console_Queue(char *Input)
{
  FuncIN(ADD_STRING_IN_CONSOLE_QUEUE);
  
  uint16 Cnt = 0;
  ASSERT(Input != NULL, -INVALID_INPUT_POINTER);
  
  while(Input[Cnt] != '\0')
  {
    Add_Char_In_Console_Queue(Input[Cnt]);
    Cnt++;
    
    ASSERT(Cnt < MAX_CONSOLE_COMMAND_LENGTH, -INVALID_INPUT_PARAMETER);
  }
  
  EXIT_SUCCESS_FUNC(ADD_STRING_IN_CONSOLE_QUEUE);
}
FUNC_REGISTER(ADD_STRING_IN_CONSOLE_QUEUE, Add_String_In_Console_Queue);

/*******************************************************************************
* Funkcija koja se povikuva periodicno vo glavna jamka
* i pecati toa sto ima vo queue
* @in NONE
* @out Status_t - Status so koj e izvrsena funkcijata
*******************************************************************************/
Status_t Console_Print_Pull(void)
{
  FuncIN(CONSOLE_PRINT_PULL);
  
  uint8 Status = 0;
  uint8 i;
  
  if(Console_Mode == MODE_INTERRUPT)
    EXIT_SUCCESS_FUNC(CONSOLE_PRINT_PULL);
  
  if(Console_Queue_Cnt == 0)   // Nema karakteri za pecatenje
    EXIT_SUCCESS_FUNC(CONSOLE_PRINT_PULL);
  
  Console_Check_TX_FIFO(&Status);
  
  if(Status == 1)
  {
    for(i = 0; i < 16; i++)
    {
      Console_Write_Char(Console_Queue[Console_Queue_Print_Cnt]);
      Console_Queue_Print_Cnt ++;
      if(Console_Queue_Print_Cnt == CONSOLE_QUEUE_SIZE)
        Console_Queue_Print_Cnt = 0;
      Console_Queue_Cnt --;
      if(Console_Queue_Cnt == 0)
        goto Exit;
    }
  }
  else
    goto Exit;

Exit:
  EXIT_SUCCESS_FUNC(CONSOLE_PRINT_PULL);
}
FUNC_REGISTER(CONSOLE_PRINT_PULL, Console_Print_Pull);

/*******************************************************************************
* ISR rutina za Console
*******************************************************************************/
__arm Status_t Console_ISR(void)
{
  FuncIN(CONSOLE_ISR);

  uint8 Ch = NULL;
  
  Console_Get_Char(&Ch, 0x05);
  
  switch(Ch)
  {
  case 0x0D:  // Enter
    Add_Char_In_Console_Queue(Ch);
    Add_Char_In_Console_Queue(0x0A);   // LF
    Add_Char_In_Console_Queue(0x7E);   // '~'
    Add_Char_In_Console_Queue(0x24);   // '$'
    Add_Char_In_Console_Queue(0x20);   // SPACE
    InputString[InputCharCnt] = '\0';
    
    if(strlen(InputString) != 0)
    {
      Add_Console_Command_In_Queue(InputString);
      Add_Console_Command_In_History(InputString);
    }
    
    InputCharCnt = 0;
    break;
  case 0x08:  // Backspace
    if(InputCharCnt > 0)
    {
      InputCharCnt --;
      Add_Char_In_Console_Queue(Ch);
    }
    break;
  case 0x7F:  // Delete
    if(InputCharCnt > 0)
    {
      InputCharCnt --;
      Add_Char_In_Console_Queue(Ch);
    }
    break;
  case '8':  // Up    TODO: Check the value
    if(ConsoleHistoryCnt <= MAX_CONSOLE_COMMAND_HISTORY)
      ConsoleHistoryCnt++;
	Get_Console_Command_From_History(ConsoleHistoryCnt, InputString);
	InputCharCnt = strlen(InputString);
	Add_String_In_Console_Queue("\r~$ ");
	Add_String_In_Console_Queue(InputString);
    break;
  case '2':  // Down    TODO: Check the value
    if(ConsoleHistoryCnt >= 1)
      ConsoleHistoryCnt--;
	
	if((ConsoleHistoryCnt > 0) && (ConsoleHistoryCnt <= MAX_CONSOLE_COMMAND_HISTORY))
	{
	  Get_Console_Command_From_History(ConsoleHistoryCnt, InputString);
	  InputCharCnt = strlen(InputString);
	  Add_String_In_Console_Queue("\r~$ ");
	  Add_String_In_Console_Queue(InputString);
	}
	else
	{
	  InputString[0] = '\0';
	  InputCharCnt = 0;
	  Add_String_In_Console_Queue("\r~$ ");
	}
	
    break;
  default:
    Add_Char_In_Console_Queue(Ch);
    InputString[InputCharCnt] = Ch;
    InputCharCnt ++;
    break;
  }
  
  EXIT_SUCCESS_FUNC(CONSOLE_ISR);
}
FUNC_REGISTER(CONSOLE_ISR, Console_ISR);

/*******************************************************************************
* Funkcija za inicijalizacija na Console server
* @in Chanell - komunikaciski kanal na koj ke raboti console
* @in Speed - brzina so koja ke raboti console na soodvetniot kanal
* @in Mode - "MODE_POOLING" ili "MODE_INTERRUPT"
* @out Status_t - Status so koj e izvrsena funcijata
*******************************************************************************/
Status_t Console_Server_Init(uint8 Chanell, unsigned int Speed, uint8 Mode)
{
  FuncIN(CONSOLE_SERVER_INIT);
  
  Status_t Status = GENERAL_ERROR;
  
  switch(Chanell)
  {
    case UART_0:
      Console_Chanell_Init = UART_0_Init;
      Console_Get_Char = Get_Char_UART_0;
      Console_Write_Char = Write_Char_UART_0;
      Console_Put_Char = Put_Char_UART_0;
      Console_Clear_RX_FIFO = Clear_RX_FIFO_UART_0;
      Console_Set_RX_Trigger = Set_Trigger_UART_0;
      Console_Set_Interrupt_State = Set_Interrupt_State_UART_0;
      Console_Put_String = Put_String_UART_0;
      Console_Check_TX_FIFO = Check_TX_Status_UART_0;
      Console_Return_Old_Interrupt_State = Return_Old_Interrupt_State_UART_0;
      ConsoleChanel = UART_0;
      break;
    case UART_1:
//      Console_Chanell_Init = UART_1_Init;
      Console_Get_Char = Get_Char_UART_1;
      Console_Put_Char = Put_Char_UART_1;
      Console_Write_Char = Write_Char_UART_1;
      Console_Clear_RX_FIFO = Clear_RX_FIFO_UART_1;
      Console_Set_RX_Trigger = Set_Trigger_UART_1;
      Console_Set_Interrupt_State = Set_Interrupt_State_UART_1;
      Console_Put_String = Put_String_UART_1;
      Console_Check_TX_FIFO = Check_TX_Status_UART_1;
      Console_Return_Old_Interrupt_State = Return_Old_Interrupt_State_UART_1;
      ConsoleChanel = UART_1;
      break;
    default:
      Console_Chanell_Init = NULL;
      Console_Get_Char = NULL;
      Console_Write_Char = NULL;
      Console_Put_Char = NULL;
      Console_Clear_RX_FIFO = NULL;
      Console_Set_RX_Trigger = NULL;
      Console_Set_Interrupt_State = NULL;
      Console_Put_String = NULL;
      Console_Check_TX_FIFO = NULL;
      Console_Return_Old_Interrupt_State = NULL;
      ASSERT(0, -INVALID_INIT_INPUT_PARAMETER);
      break;
  }
  
  Status = Console_Chanell_Init(Speed);
  VERIFY(Status, -CONSOLE_CHANNEL_INIT_ERROR);
  if(Status > SUCCESS)
    EXIT_FUNC(CONSOLE_CHANNEL_INIT_ERROR, CONSOLE_SERVER_INIT);
  
  Status = Console_Set_Interrupt_State(ENABLE, DISABLE);
  VERIFY(Status, -CONSOLE_CHANNEL_INIT_ERROR);
  if(Status > SUCCESS)
    EXIT_FUNC(CONSOLE_CHANNEL_INIT_ERROR, CONSOLE_SERVER_INIT);
  
  Status = Console_Set_RX_Trigger(BYTE_1);
  VERIFY(Status, -CONSOLE_CHANNEL_INIT_ERROR);
  if(Status > SUCCESS)
    EXIT_FUNC(CONSOLE_CHANNEL_INIT_ERROR, CONSOLE_SERVER_INIT);
  
  switch(Mode)
  {
    case MODE_POOLING:
      Console_Mode = MODE_POOLING;
      break;
    case MODE_INTERRUPT:
      Console_Mode = MODE_INTERRUPT;
      break;
    default:
      Fatal_Abort(-INVALID_INIT_INPUT_PARAMETER);
      break;
  }
  
  EXIT_SUCCESS_FUNC(CONSOLE_SERVER_INIT);
}
FUNC_REGISTER(CONSOLE_SERVER_INIT, Console_Server_Init);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Add_Console_Command_In_Queue(char *InputString)
{
  FuncIN(ADD_CONSOLE_COMMAND_IN_QUEUE);
  
  ASSERT(InputString != NULL, -INVALID_INPUT_POINTER);
  ASSERT(ConsoleCommandsInQueue <= MAX_CONSOLE_COMMAND_IN_QUEUE, -CONSOLE_COMMANDS_OVERFLOW);
  
  strcpy(QueueConsoleCommand[ConsoleCommandsInQueue], InputString);
  ConsoleCommandsInQueue++;

  EXIT_SUCCESS_FUNC(ADD_CONSOLE_COMMAND_IN_QUEUE);
}
FUNC_REGISTER(ADD_CONSOLE_COMMAND_IN_QUEUE, Add_Console_Command_In_Queue);

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Add_Console_Command_In_History(char *InputString)
{
  FuncIN(ADD_CONSOLE_COMMAND_IN_HISTORY);
  ASSERT(InputString != NULL, -INVALID_INPUT_POINTER);
  
  if(ConsoleCommandsInHistory >= MAX_CONSOLE_COMMAND_HISTORY)
    ConsoleCommandsInHistory = 0;
  
  strcpy(ConsoleCommandHistory[ConsoleCommandsInHistory], InputString);
  
  ConsoleCommandsInHistory ++;
  
  EXIT_SUCCESS_FUNC(ADD_CONSOLE_COMMAND_IN_HISTORY);
}
FUNC_REGISTER(ADD_CONSOLE_COMMAND_IN_HISTORY, Add_Console_Command_In_History);

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Get_Console_Command_From_History(uint8 NoOfPreviousCommand, char *CommandString)
{
  FuncIN(GET_CONSOLE_COMMAND_FROM_HISTORY);
  ASSERT(CommandString != NULL, -INVALID_INPUT_POINTER);
  
  int Command = (int)(ConsoleCommandsInHistory - 1);
  
  Command -= NoOfPreviousCommand;
  
  if(Command < 0)
    Command = MAX_CONSOLE_COMMAND_HISTORY + Command;
  
  strcpy(InputString, ConsoleCommandHistory[Command]);

  EXIT_SUCCESS_FUNC(GET_CONSOLE_COMMAND_FROM_HISTORY);
}
FUNC_REGISTER(GET_CONSOLE_COMMAND_FROM_HISTORY, Get_Console_Command_From_History);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Remove_Console_Command_From_Queue(uint8 NoOfCommand)
{
  FuncIN(REMOVE_CONSOLE_COMMAND_FROM_QUEUE);
  ASSERT(NoOfCommand < ConsoleCommandsInQueue, -INVALID_INPUT_PARAMETER);
  
  Console_Set_Interrupt_State(DISABLE, NO_CHANGE);
  
  for(int i = NoOfCommand; i < (ConsoleCommandsInQueue - 1); i++)
    strcpy(QueueConsoleCommand[i],QueueConsoleCommand[i+1]);

  ConsoleCommandsInQueue--;
  Console_Return_Old_Interrupt_State();
  
  EXIT_SUCCESS_FUNC(REMOVE_CONSOLE_COMMAND_FROM_QUEUE);
}
FUNC_REGISTER(REMOVE_CONSOLE_COMMAND_FROM_QUEUE, Remove_Console_Command_From_Queue);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Command_Execute(uint8 NoOfCommand)
{     
  FuncIN(CONSOLE_COMMAND_EXECUTE);
  
  Status_t Status = GENERAL_ERROR;
  
  if(NoOfCommand >= ConsoleCommandsInQueue)
    EXIT_SUCCESS_FUNC(CONSOLE_COMMAND_EXECUTE);   // No Console Commands in Queue
  
  ASSERT(CMD_SUCCESS == Run_Command(QueueConsoleCommand[NoOfCommand]), -CONSOLE_COMMAND_EXECUTE_ERROR);

#if 0
  if(!strncmp("help", QueueConsoleCommand[NoOfCommand], 4))
       CONTROL(!Console_Help(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "status", QueueConsoleCommand[NoOfCommand], 6))
       CONTROL(!Console_Status(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "list", QueueConsoleCommand[NoOfCommand], 4))
       CONTROL(!Console_List(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "info", QueueConsoleCommand[NoOfCommand], 4))
       CONTROL(!Console_Info(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "time", QueueConsoleCommand[NoOfCommand], 4))
       CONTROL(!Console_Time(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "date", QueueConsoleCommand[NoOfCommand], 4))
       CONTROL(!Console_Date(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "set-time", QueueConsoleCommand[NoOfCommand], 8))
       CONTROL(!Console_Set_Time(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "set-date", QueueConsoleCommand[NoOfCommand], 8))
       CONTROL(!Console_Set_Date(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "config", QueueConsoleCommand[NoOfCommand], 6))
       CONTROL(!Console_Config(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "set-config", QueueConsoleCommand[NoOfCommand], 10))
       CONTROL(!Console_Set_Config(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "ir", QueueConsoleCommand[NoOfCommand], 2))
       CONTROL(!Console_Ir(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "set-ir", QueueConsoleCommand[NoOfCommand], 6))
       CONTROL(!Console_Set_Ir(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "backlight", QueueConsoleCommand[NoOfCommand], 9))
       CONTROL(!Console_Backlight(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "set-backlight", QueueConsoleCommand[NoOfCommand], 13))
       CONTROL(!Console_Set_Backlight(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "light-switch", QueueConsoleCommand[NoOfCommand], 12))
       CONTROL(!Console_Light_Switch(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "set-light-switch", QueueConsoleCommand[NoOfCommand], 16))
       CONTROL(!Console_Set_Light_Switch(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "out-switch", QueueConsoleCommand[NoOfCommand], 10))
       CONTROL(!Console_Out_Switch(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "set-out-switch", QueueConsoleCommand[NoOfCommand], 14))
       CONTROL(!Console_Set_Out_Switch(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "switch-settings", QueueConsoleCommand[NoOfCommand], 15))
       CONTROL(!Console_Switch_Settings(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "set-switch-settings", QueueConsoleCommand[NoOfCommand], 19))
       CONTROL(!Console_Set_Switch_Settings(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "temp", QueueConsoleCommand[NoOfCommand], 4))
       CONTROL(!Console_Temp(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "alarm", QueueConsoleCommand[NoOfCommand], 5))
       CONTROL(!Console_Alarm(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "set-alarm", QueueConsoleCommand[NoOfCommand], 9))
       CONTROL(!Console_Set_Alarm(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "get-temp-alarm", QueueConsoleCommand[NoOfCommand], 14))
       CONTROL(!Console_Get_Temp_Alarm(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "set-temp-alarm", QueueConsoleCommand[NoOfCommand], 14))
       CONTROL(!Console_Set_Temp_Alarm(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  
  // Debug commands
  else if(!strncmp( "dd", QueueConsoleCommand[NoOfCommand], 2))
       CONTROL(!Console_Dump_Display(NoOfCommand), CONSOLE_COMMAND_EXECUTE_ERROR);
  else if(!strncmp( "du", QueueConsoleCommand[NoOfCommand], 2))
#endif
  
  Status = Console_Update_Display(NoOfCommand);
  VERIFY(Status, -CONSOLE_COMMAND_EXECUTE_ERROR);
  if(Status > SUCCESS)
    EXIT_FUNC(CONSOLE_COMMAND_EXECUTE_ERROR, CONSOLE_COMMAND_EXECUTE);
  
  Status = Remove_Console_Command_From_Queue(NoOfCommand);
  VERIFY(Status, -CONSOLE_COMMAND_ERROR);
  if(Status > SUCCESS)
    EXIT_FUNC(CONSOLE_COMMAND_ERROR, CONSOLE_COMMAND_EXECUTE);
  
  EXIT_SUCCESS_FUNC(CONSOLE_COMMAND_EXECUTE);
}
FUNC_REGISTER(CONSOLE_COMMAND_EXECUTE, Console_Command_Execute);

