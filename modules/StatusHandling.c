#include "Includes.h"


Function_t FunctionBuffer[MAX_FUNCTION_IN_BECKUP_BUFFER] = {0};
uint8 FunctionInBeckupBuffer = 0;

void Function_IN(Function_t Function)
{
  FunctionBuffer[FunctionInBeckupBuffer] = Function;
  FunctionInBeckupBuffer ++;
  if(FunctionInBeckupBuffer >= MAX_FUNCTION_IN_BECKUP_BUFFER)
    FunctionInBeckupBuffer = 0;
}

void Function_OUT(Function_t Function)
{
  FunctionBuffer[FunctionInBeckupBuffer] = Function;
  FunctionBuffer[FunctionInBeckupBuffer] |= 800000;
  FunctionInBeckupBuffer ++;
  if(FunctionInBeckupBuffer >= MAX_FUNCTION_IN_BECKUP_BUFFER)
    FunctionInBeckupBuffer = 0;
}

void This_Function_OUT(void)
{
  if(FunctionInBeckupBuffer == 0)
    Function_OUT(FunctionBuffer[MAX_FUNCTION_IN_BECKUP_BUFFER - 1]);
  else
    Function_OUT(FunctionBuffer[FunctionInBeckupBuffer - 1]);
}    

uint8 Abort(Status_t Status)
{
  Function_t Function;
  
  switch(Status)
  {
  case INFO:
    printc("\n ##### Error: INFO, Non fatal error, program continue\n");
    return 1;
  case RTC_INVALID_DATE_ERROR:
    if(FunctionBuffer[FunctionInBeckupBuffer - 2] == SET_DATE_COMMAND)
      return 1;
    break;
  case RTC_INVALID_TIME_ERROR:
    if(FunctionBuffer[FunctionInBeckupBuffer - 2] == SET_TIME_COMMAND)
      return 1;
    break;
  case DLY_TIMER_UNAVAILABLE_ERROR:
    if(FunctionInBeckupBuffer == 0)
      Function = MAX_FUNCTION_IN_BECKUP_BUFFER - 1;
    else
      Function = FunctionInBeckupBuffer - 1;
    
    if(FunctionBuffer[Function] == (DS1820_INIT | 800000))
    {
      printc("\r # Unable to initialize DS1820. Error: DLY_TIMER_UNAVAILABLE_ERROR\n");
      return 0;
    }
    break;
  case DS1820_NO_PRESENCE_ERROR:
    if(FunctionInBeckupBuffer == 0)
      Function = MAX_FUNCTION_IN_BECKUP_BUFFER - 1;
    else
      Function = FunctionInBeckupBuffer - 1;
    
    if(FunctionBuffer[Function] == (DS1820_INIT | 800000))
    {
      printc("\r # Unable to initialize DS1820. Error: DS1820_NO_PRESENCE_ERROR\n");
      return 0;
    }
    break;
  case DS1820_SHORT_CIRCUIT_ERROR:
    if(FunctionInBeckupBuffer == 0)
      Function = MAX_FUNCTION_IN_BECKUP_BUFFER - 1;
    else
      Function = FunctionInBeckupBuffer - 1;
    
    if(FunctionBuffer[Function] == (DS1820_INIT | 800000))
    {
      printc("\r # Unable to initialize DS1820. Error: DS1820_SHORT_CIRCUIT_ERROR\n");
      return 0;
    }
    break;
  
  default:
    break;
  }
  
  printc("ABORT !!!\nERROR: %u\n", Status);  
  Print_Function_History();
  
  __disable_interrupt();
  
  while(1)
  {
    Console_Print_Pull();
  } // while(1)
}

/*******************************************************************************
* 
*******************************************************************************/
void Print_Function_History(void)
{
  unsigned int i = 0;
  printc("Function history:\n");
  for(i = 0; i < MAX_FUNCTION_IN_BECKUP_BUFFER; i++)
  {
    switch(FunctionBuffer[FunctionInBeckupBuffer])
    {
    case (INITIALIZATION):
      printc(" - Initialization IN\n");
      break;
    case (INITIALIZATION | 800000):
      printc(" - Initialization OUT\n");
      break;
    case (PLL_INIT):
      printc(" - PLL_Init IN\n");
      break;
    case (PLL_INIT | 800000):
      printc(" - PLL_Init OUT\n");
      break;
    case (MAM_INIT):
      printc(" - MAM_Init IN\n");
      break;
    case (MAM_INIT | 800000):
      printc(" - MAM_Init OUT\n");
      break;
      
    case (UART_0_INIT):
      printc(" - UART_0_Init IN\n");
      break;
    case (UART_0_INIT | 800000):
      printc(" - UART_0_Init OUT\n");
      break;
    case (UART_1_INIT):
      printc(" - UART_1_Init IN\n");
      break;
    case (UART_1_INIT | 800000):
      printc(" - UART_1_Init OUT\n");
      break;
    case (SET_INTERRUPT_STATE_UART_0):
      printc(" - Set_Interrupt_State_UART_0 IN\n");
      break;
    case (SET_INTERRUPT_STATE_UART_0 | 800000):
      printc(" - Set_Interrupt_State_UART_0 OUT\n");
      break;
    case (SET_INTERRUPT_STATE_UART_1):
      printc(" - Set_Interrupt_State_UART_1 IN\n");
      break;
    case (SET_INTERRUPT_STATE_UART_1 | 800000):
      printc(" - Set_Interrupt_State_UART_1 OUT\n");
      break;
    case (SET_TRIGGER_UART_0):
      printc(" - Set_Trigger_UART_0 IN\n");
      break;
    case (SET_TRIGGER_UART_0 | 800000):
      printc(" - Set_Trigger_UART_0 OUT\n");
      break;
    case (SET_TRIGGER_UART_1):
      printc(" - Set_Trigger_UART_1 IN\n");
      break;
    case (SET_TRIGGER_UART_1 | 800000):
      printc(" - Set_Trigger_UART_1 OUT\n");
      break;
     
    case (CONSOLE_COMMAND_EXECUTE):
      printc(" - Console_Command_Execute IN\n");
      break;
    case (CONSOLE_COMMAND_EXECUTE | 800000):
      printc(" - Console_Command_Execute OUT\n");
      break;
    case (CONSOLE_SERVER_INIT):
      printc(" - Console_Server_Init IN\n");
      break;
    case (CONSOLE_SERVER_INIT | 800000):
      printc(" - Console_Server_Init OUT\n");
      break;
    case (CONSOLE_PRINT_PULL):
      printc(" - Console_Print_Pull IN\n");
      break;
    case (CONSOLE_PRINT_PULL | 800000):
      printc(" - Console_Print_Pull OUT\n");
      break;
    case (CONSOLE_ISR):
      printc(" - Console_ISR IN\n");
      break;
    case (CONSOLE_ISR | 800000):
      printc(" - Console_ISR OUT\n");
      break;
      
      
    case (DLY):
      printc(" - Dly IN\n");
      break;
    case (DLY | 800000):
      printc(" - Dly OUT\n");
      break;
          
    case (CONSOLE_HELP):
      printc(" - Console_Help IN\n");
      break;
    case (CONSOLE_HELP | 800000):
      printc(" - Console_Help OUT\n");
      break;
    case (CONSOLE_STATUS):
      printc(" - Console_Status IN\n");
      break;
    case (CONSOLE_STATUS | 800000):
      printc(" - Console_Status OUT\n");
      break;
    case (CONSOLE_LIST):
      printc(" - Console_List IN\n");
      break;
    case (CONSOLE_LIST | 800000):
      printc(" - Console_List OUT\n");
      break;
    case (CONSOLE_INFO):
      printc(" - Console_Info IN\n");
      break;
    case (CONSOLE_INFO | 800000):
      printc(" - Console_Info OUT\n");
      break;
    
    case (GET_TIME_COMMAND):
      printc(" - Get_Time_Command IN\n");
      break;
    case (GET_TIME_COMMAND | 800000):
      printc(" - Get_Time_Command OUT\n");
      break;
    case (SET_TIME_COMMAND):
      printc(" - Set_Time_Command IN\n");
      break;
    case (SET_TIME_COMMAND | 800000):
      printc(" - Set_Time_Command OUT\n");
      break;
    case (GET_DATE_COMMAND):
      printc(" - Get_Date_Command IN\n");
      break;
    case (GET_DATE_COMMAND | 800000):
      printc(" - Get_Date_Command OUT\n");
      break;
    case (SET_DATE_COMMAND):
      printc(" - Set_Date_Command IN\n");
      break;
    case (SET_DATE_COMMAND | 800000):
      printc(" - Set_Date_Command OUT\n");
      break;
    case (GET_CONFIGURATION_COMMAND):
      printc(" - Get_Configuration_Command IN\n");
      break;
    case (GET_CONFIGURATION_COMMAND | 800000):
      printc(" - Get_Configuration_Command OUT\n");
      break;
    case (SET_CONFIGURATIONS_COMMAND):
      printc(" - Set_Configuration_Command IN\n");
      break;
    case (SET_CONFIGURATIONS_COMMAND | 800000):
      printc(" - Set_Configuration_Command OUT\n");
      break;
    case (GET_IR_COMMANDS_COMMAND):
      printc(" - Get_IR_Commands_Command IN\n");
      break;
    case (GET_IR_COMMANDS_COMMAND | 800000):
      printc(" - Get_IR_Commands_Command OUT\n");
      break;
    case (SET_IR_COMMANDS_COMMAND):
      printc(" - Set_IR_Commands_Command IN\n");
      break;
    case (SET_IR_COMMANDS_COMMAND | 800000):
      printc(" - Set_IR_Commands_Command OUT\n");
      break;
    case (GET_BACK_LIGHT_LEVEL_COMMAND):
      printc(" - Get_Beck_Light_Level_Command IN\n");
      break;
    case (GET_BACK_LIGHT_LEVEL_COMMAND | 800000):
      printc(" - Get_Beck_Light_Level_Command OUT\n");
      break;
    case (SET_BACK_LIGHT_LEVEL_COMMAND):
      printc(" - Set_Beck_Light_Level_Command IN\n");
      break;
    case (SET_BACK_LIGHT_LEVEL_COMMAND | 800000):
      printc(" - Set_Beck_Light_Level_Command OUT\n");
      break;
    case (GET_LIGHT_SWITCH_LEVEL_COMMAND):
      printc(" - Get_Lignt_Switch_Level_Command IN\n");
      break;
    case (GET_LIGHT_SWITCH_LEVEL_COMMAND | 800000):
      printc(" - Get_Lignt_Switch_Level_Command OUT\n");
      break;
    case (SET_LIGHT_SWITCH_LEVEL_COMMAND):
      printc(" - Set_Lignt_Switch_Level_Command IN\n");
      break;
    case (SET_LIGHT_SWITCH_LEVEL_COMMAND | 800000):
      printc(" - Set_Lignt_Switch_Level_Command OUT\n");
      break;
    case (GET_OUT_SWITCH_COMMAND):
      printc(" - Get_Out_Switch_Command IN\n");
      break;
    case (GET_OUT_SWITCH_COMMAND | 800000):
      printc(" - Get_Out_Switch_Command OUT\n");
      break;
    case (SET_OUT_SWITCH_COMMAND):
      printc(" - Set_Out_Switch_Command IN\n");
      break;
    case (SET_OUT_SWITCH_COMMAND | 800000):
      printc(" - Set_Out_Switch_Command OUT\n");
      break;
    case (GET_TEMP_COMMAND):
      printc(" - Get_Temp_Command IN\n");
      break;
    case (GET_TEMP_COMMAND | 800000):
      printc(" - Get_Temp_Command OUT\n");
      break;
    case (GET_SWITCH_SETINGS_COMMAND):
      printc(" - Get_Switch_Setings_Command IN\n");
      break;
    case (GET_SWITCH_SETINGS_COMMAND | 800000):
      printc(" - Get_Switch_Setings_Command OUT\n");
      break;
    case (SET_SWITCH_SETINGS_COMMAND):
      printc(" - Set_Switch_Setings_Command IN\n");
      break;
    case (SET_SWITCH_SETINGS_COMMAND | 800000):
      printc(" - Set_Switch_Setings_Command OUT\n");
      break;
    case (GET_ALARM_COMMAND):
      printc(" - Get_Alarm_Command IN\n");
      break;
    case (GET_ALARM_COMMAND | 800000):
      printc(" - Get_Alarm_Command OUT\n");
      break;
    case (SET_ALARM_COMMAND):
      printc(" - Set_Alarm_Command IN\n");
      break;
    case (SET_ALARM_COMMAND | 800000):
      printc(" - Set_Alarm_Command OUT\n");
      break;
    
    case (IR_COMMAND_INIT):
      printc(" - IR_Command_Init IN\n");
      break;
    case (IR_COMMAND_INIT | 800000):
      printc(" - IR_Command_Init OUT\n");
      break;
      
    case (OUT_INIT):
      printc(" - Out_Init IN\n");
      break;
    case (OUT_INIT | 800000):
      printc(" - Out_Init OUT\n");
      break;
    case (OUT_SYNC):
      printc(" - Out_Sync IN\n");
      break;
    case (OUT_SYNC | 800000):
      printc(" - Out_Sync OUT\n");
      break;
    
      
    default:
      printc("\r - ??? Function ID = %u\n", FunctionBuffer[FunctionInBeckupBuffer]);
      break;
    } // switch
    
    FunctionInBeckupBuffer ++;
    if(FunctionInBeckupBuffer >= MAX_FUNCTION_IN_BECKUP_BUFFER)
      FunctionInBeckupBuffer = 0;
  } // for
} // Print_Function_History()
