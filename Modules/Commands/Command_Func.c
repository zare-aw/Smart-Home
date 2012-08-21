#include <stdio.h>
#include <string.h>
#include "Global_Defines.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "StatusHandling.h"


Status_t Get_Func_String(Func_t Function, char *FuncString)
{
  if(COMMANDS_OFFSET != (Function & 0xFF000000))
    return -INVALID_INPUT_PARAMETER;
  
  if(FuncString == NULL)
    return -INVALID_INPUT_POINTER;
  
  // Remove function out flag (MSB)
  Function &= 0x7FFFFFFF;
  
  switch(Function)
  {
    // Command.c
    case FIND_CMD:
      strcpy(FuncString, "Find_Cmd");
      break;
    case RUN_COMMAND:
      strcpy(FuncString, "Run_Command");
      break;
    case PRINTCMD:
      strcpy(FuncString, "printcmd");
      break;
    case PARSE_LINE:
      strcpy(FuncString, "Parse_Line");
      break;
    case COMMANDS_INIT:
      strcpy(FuncString, "Commands_Init");
      break;
    
    // cmd_help.c
    case DO_HELP:
      strcpy(FuncString, "Do_Help");
      break;

    // cmd_info.c
    case DO_INFO:
      strcpy(FuncString, "Do_Info");
      break;

    // cmd_time.c
    case DO_TIME:
      strcpy(FuncString, "Do_Time");
      break;
    
   // cmd_set_time.c
    case DO_SET_TIME:
      strcpy(FuncString, "Do_Set_Time");
      break;
 
    default:
      sprintf(FuncString, "Function not found! Module Command. Function No = %X.", (Function & 0x00FFFFFF));
      break;
  }
  
  return SUCCESS;
}
