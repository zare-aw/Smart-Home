#include <stdio.h>
#include <string.h>
#include "Global_Defines.h"
#include "Console_Func.h"
#include "Func_Trace.h"
#include "StatusHandling.h"


Status_t Get_Console_Func_String(Func_t Function, char *FuncString)
{
  if(CONSOLE_OFFSET != (Function & 0xFF000000))
    return -INVALID_INPUT_PARAMETER;
  
  if(FuncString == NULL)
    return -INVALID_INPUT_POINTER;
  
  // Remove function out flag (MSB)
  Function &= 0x7FFFFFFF;
  
  switch(Function)
  {
    // Console.c
    case ADD_STRING_IN_CONSOLE_QUEUE:
      strcpy(FuncString, "Add_String_In_Console_Queue");
      break;
    case CONSOLE_PRINT_PULL:
      strcpy(FuncString, "Console_Print_Pull");
      break;
    case CONSOLE_ISR:
      strcpy(FuncString, "Console_ISR");
      break;
    case CONSOLE_SERVER_INIT:
      strcpy(FuncString, "Console_Server_Init");
      break;
    case ADD_CONSOLE_COMMAND_IN_QUEUE:
      strcpy(FuncString, "Add_Console_Command_In_Queue");
      break;
    case ADD_CONSOLE_COMMAND_IN_HISTORY:
      strcpy(FuncString, "Add_Console_Command_In_History");
      break;
    case GET_CONSOLE_COMMAND_FROM_HISTORY:
      strcpy(FuncString, "Get_Console_Command_From_History");
      break;
    case REMOVE_CONSOLE_COMMAND_FROM_QUEUE:
      strcpy(FuncString, "Remove_Console_Command_From_Queue");
      break;
    case CONSOLE_COMMAND_EXECUTE:
      strcpy(FuncString, "Console_Command_Execute");
      break;
    
    default:
      sprintf(FuncString, "Function not found! Module Console. Function No = %X.", (Function & 0x00FFFFFF));
      break;
  }
  
  return SUCCESS;
}
