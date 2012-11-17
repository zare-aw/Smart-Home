#include "Global_Defines.h"
#include "StatusHandling.h"
#include "Includes.h"

Function_t FunctionBuffer[MAX_FUNCTION_IN_BECKUP_BUFFER] = {0};
uint8 FunctionInBeckupBuffer = 0;

void Function_IN(Function_t Function)
{
  if(FunctionInBeckupBuffer >= MAX_FUNCTION_IN_BECKUP_BUFFER)
  {
    STATUS_DEBUG(printc(">>> WARNING: Invalid FunctionInBeckupBuffer Value, %d\n", FunctionInBeckupBuffer));
    FunctionInBeckupBuffer = 0;
    // TODO: Sometime FunctionInBeckupBuffer = 10. See what causing that.
  }
  FunctionBuffer[FunctionInBeckupBuffer] = Function;
  FunctionInBeckupBuffer ++;
  if(FunctionInBeckupBuffer >= MAX_FUNCTION_IN_BECKUP_BUFFER)
    FunctionInBeckupBuffer = 0;
}

void Function_OUT(Function_t Function)
{
  FunctionBuffer[FunctionInBeckupBuffer] = Function;
  FunctionBuffer[FunctionInBeckupBuffer] |= FUNC_OUT_MASK;
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

/*******************************************************************************
 * Function for handle Fatal Error. This function prints error and
 *   function history. There is no return from this function!
 * @in Status - Error which cause Fatal Abort!
 * @out void
 ******************************************************************************/
void Fatal_Abort(Status_t Status)
{
  printc("\n # ABORT !!!\n");
  if(Status < SUCCESS)
    printc(" # ERROR: -0x%08X\n", -Status);
  else
    printc(" # ERROR: 0x%08X\n", Status);
  
  Print_Func_History();
  
  __disable_interrupt();
  
  while(1)
  {
    Console_Print_Pull();
  } // while(1)
}

/*******************************************************************************
* 
*******************************************************************************/
uint8 Abort(Status_t Status)
{  
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
      // System
    case (INITIALIZATION):
      printc(" - Initialization IN\n");
      break;
    case (INITIALIZATION | FUNC_OUT_MASK):
      printc(" - Initialization OUT\n");
      break;
    
      // ConsoleHelp
    case (CONSOLE_HELP):
      printc(" - Console_Help IN\n");
      break;
    case (CONSOLE_HELP | FUNC_OUT_MASK):
      printc(" - Console_Help OUT\n");
      break;
    case (CONSOLE_STATUS):
      printc(" - Console_Status IN\n");
      break;
    case (CONSOLE_STATUS | FUNC_OUT_MASK):
      printc(" - Console_Status OUT\n");
      break;
    case (CONSOLE_LIST):
      printc(" - Console_List IN\n");
      break;
    case (CONSOLE_LIST | FUNC_OUT_MASK):
      printc(" - Console_List OUT\n");
      break;
    case (CONSOLE_INFO):
      printc(" - Console_Info IN\n");
      break;
    case (CONSOLE_INFO | FUNC_OUT_MASK):
      printc(" - Console_Info OUT\n");
      break;
    case (CONSOLE_TIME):
      printc(" - Console_Time IN\n");
      break;
    case (CONSOLE_TIME | FUNC_OUT_MASK):
      printc(" - Console_Time OUT\n");
      break;
    case (CONSOLE_DATE):
      printc(" - Console_Date IN\n");
      break;
    case (CONSOLE_DATE | FUNC_OUT_MASK):
      printc(" - Console_Date OUT\n");
      break;
    case (CONSOLE_SET_TIME):
      printc(" - Console_Set_Time IN\n");
      break;
    case (CONSOLE_SET_TIME | FUNC_OUT_MASK):
      printc(" - Console_Set_Time OUT\n");
      break;
    case (CONSOLE_SET_DATE):
      printc(" - Console_Set_Date IN\n");
      break;
    case (CONSOLE_SET_DATE | FUNC_OUT_MASK):
      printc(" - Console_Set_Date OUT\n");
      break;
    case (CONSOLE_CONFIG):
      printc(" - Console_Config IN\n");
      break;
    case (CONSOLE_CONFIG | FUNC_OUT_MASK):
      printc(" - Console_Config OUT\n");
      break;
    case (CONSOLE_SET_CONFIG):
      printc(" - Console_Set_Config IN\n");
      break;
    case (CONSOLE_SET_CONFIG | FUNC_OUT_MASK):
      printc(" - Console_Set_Config OUT\n");
      break;
    case (CONSOLE_IR):
      printc(" - Console_Ir IN\n");
      break;
    case (CONSOLE_IR | FUNC_OUT_MASK):
      printc(" - Console_Ir OUT\n");
      break;
    case (CONSOLE_SET_IR):
      printc(" - Console_Set_Ir IN\n");
      break;
    case (CONSOLE_SET_IR | FUNC_OUT_MASK):
      printc(" - Console_Set_Ir OUT\n");
      break;
    case (CONSOLE_BACKLIGHT):
      printc(" - Console_Backlight IN\n");
      break;
    case (CONSOLE_BACKLIGHT | FUNC_OUT_MASK):
      printc(" - Console_Backlight OUT\n");
      break;
    case (CONSOLE_SET_BACKLIGHT):
      printc(" - Console_Set_Backlight IN\n");
      break;
    case (CONSOLE_SET_BACKLIGHT | FUNC_OUT_MASK):
      printc(" - Console_Set_Backlight OUT\n");
      break;
    case (CONSOLE_LIGHT_SWITCH):
      printc(" - Console_Light_Switch IN\n");
      break;
    case (CONSOLE_LIGHT_SWITCH | FUNC_OUT_MASK):
      printc(" - Console_Light_Switch OUT\n");
      break;
    case (CONSOLE_SET_LIGHT_SWITCH):
      printc(" - Console_Set_Light_Switch IN\n");
      break;
    case (CONSOLE_SET_LIGHT_SWITCH | FUNC_OUT_MASK):
      printc(" - Console_Set_Light_Switch OUT\n");
      break;
    case (CONSOLE_OUT_SWITCH):
      printc(" - Console_Out_Switch IN\n");
      break;
    case (CONSOLE_OUT_SWITCH | FUNC_OUT_MASK):
      printc(" - Console_Out_Switch OUT\n");
      break;
    case (CONSOLE_SET_OUT_SWITCH):
      printc(" - Console_Set_Out_Switch IN\n");
      break;
    case (CONSOLE_SET_OUT_SWITCH | FUNC_OUT_MASK):
      printc(" - Console_Set_Out_Switch OUT\n");
      break;
    case (CONSOLE_SWITCH_SETTINGS):
      printc(" - Console_Switch_Settings IN\n");
      break;
    case (CONSOLE_SWITCH_SETTINGS | FUNC_OUT_MASK):
      printc(" - Console_Switch_Settings OUT\n");
      break;
    case (CONSOLE_SET_SWITCH_SETTINGS):
      printc(" - Console_Set_Switch_Settings IN\n");
      break;
    case (CONSOLE_SET_SWITCH_SETTINGS | FUNC_OUT_MASK):
      printc(" - Console_Set_Switch_Settings OUT\n");
      break;
    case (CONSOLE_TEMP):
      printc(" - Console_Temp IN\n");
      break;
    case (CONSOLE_TEMP | FUNC_OUT_MASK):
      printc(" - Console_Temp OUT\n");
      break;
    case (CONSOLE_ALARM):
      printc(" - Console_Alarm IN\n");
      break;
    case (CONSOLE_ALARM | FUNC_OUT_MASK):
      printc(" - Console_Alarm OUT\n");
      break;
    case (CONSOLE_SET_ALARM):
      printc(" - Console_Set_Alarm IN\n");
      break;
    case (CONSOLE_SET_ALARM | FUNC_OUT_MASK):
      printc(" - Console_Set_Alarm OUT\n");
      break;
    case (CONSOLE_TEMP_ALARM):
      printc(" - Console_Temp_Alarm IN\n");
      break;
    case (CONSOLE_TEMP_ALARM | FUNC_OUT_MASK):
      printc(" - Console_Temp_Alarm OUT\n");
      break;
    case (CONSOLE_SET_TEMP_ALARM):
      printc(" - Console_Set_Temp_Alarm IN\n");
      break;
    case (CONSOLE_SET_TEMP_ALARM | FUNC_OUT_MASK):
      printc(" - Console_Set_Temp_Alarm OUT\n");
      break;
    
      // Debug Commands help
    case (CONSOLE_DUMP_DISPLAY):
      printc(" - Console_Dump_Display IN\n");
      break;
    case (CONSOLE_DUMP_DISPLAY | FUNC_OUT_MASK):
      printc(" - Console_Dump_Display OUT\n");
      break;
    case (CONSOLE_UPDATE_DISPLAY):
      printc(" - Console_Update_Display IN\n");
      break;
    case (CONSOLE_UPDATE_DISPLAY | FUNC_OUT_MASK):
      printc(" - Console_Update_Display OUT\n");
      break;
    
      // Console Commands
    case (GET_TIME_COMMAND):
      printc(" - Get_Time_Command IN\n");
      break;
    case (GET_TIME_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_Time_Command OUT\n");
      break;
    case (SET_TIME_COMMAND):
      printc(" - Set_Time_Command IN\n");
      break;
    case (SET_TIME_COMMAND | FUNC_OUT_MASK):
      printc(" - Set_Time_Command OUT\n");
      break;
    case (GET_DATE_COMMAND):
      printc(" - Get_Date_Command IN\n");
      break;
    case (GET_DATE_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_Date_Command OUT\n");
      break;
    case (SET_DATE_COMMAND):
      printc(" - Set_Date_Command IN\n");
      break;
    case (SET_DATE_COMMAND | FUNC_OUT_MASK):
      printc(" - Set_Date_Command OUT\n");
      break;
    case (GET_CONFIGURATION_COMMAND):
      printc(" - Get_Configuration_Command IN\n");
      break;
    case (GET_CONFIGURATION_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_Configuration_Command OUT\n");
      break;
    case (SET_CONFIGURATIONS_COMMAND):
      printc(" - Set_Configuration_Command IN\n");
      break;
    case (SET_CONFIGURATIONS_COMMAND | FUNC_OUT_MASK):
      printc(" - Set_Configuration_Command OUT\n");
      break;
    case (GET_IR_COMMANDS_COMMAND):
      printc(" - Get_IR_Commands_Command IN\n");
      break;
    case (GET_IR_COMMANDS_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_IR_Commands_Command OUT\n");
      break;
    case (SET_IR_COMMANDS_COMMAND):
      printc(" - Set_IR_Commands_Command IN\n");
      break;
    case (SET_IR_COMMANDS_COMMAND | FUNC_OUT_MASK):
      printc(" - Set_IR_Commands_Command OUT\n");
      break;
    case (GET_BACK_LIGHT_LEVEL_COMMAND):
      printc(" - Get_Beck_Light_Level_Command IN\n");
      break;
    case (GET_BACK_LIGHT_LEVEL_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_Beck_Light_Level_Command OUT\n");
      break;
    case (SET_BACK_LIGHT_LEVEL_COMMAND):
      printc(" - Set_Beck_Light_Level_Command IN\n");
      break;
    case (SET_BACK_LIGHT_LEVEL_COMMAND | FUNC_OUT_MASK):
      printc(" - Set_Beck_Light_Level_Command OUT\n");
      break;
    case (GET_LIGHT_SWITCH_LEVEL_COMMAND):
      printc(" - Get_Lignt_Switch_Level_Command IN\n");
      break;
    case (GET_LIGHT_SWITCH_LEVEL_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_Lignt_Switch_Level_Command OUT\n");
      break;
    case (SET_LIGHT_SWITCH_LEVEL_COMMAND):
      printc(" - Set_Lignt_Switch_Level_Command IN\n");
      break;
    case (SET_LIGHT_SWITCH_LEVEL_COMMAND | FUNC_OUT_MASK):
      printc(" - Set_Lignt_Switch_Level_Command OUT\n");
      break;
    case (GET_OUT_SWITCH_COMMAND):
      printc(" - Get_Out_Switch_Command IN\n");
      break;
    case (GET_OUT_SWITCH_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_Out_Switch_Command OUT\n");
      break;
    case (SET_OUT_SWITCH_COMMAND):
      printc(" - Set_Out_Switch_Command IN\n");
      break;
    case (SET_OUT_SWITCH_COMMAND | FUNC_OUT_MASK):
      printc(" - Set_Out_Switch_Command OUT\n");
      break;
    case (GET_TEMP_COMMAND):
      printc(" - Get_Temp_Command IN\n");
      break;
    case (GET_TEMP_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_Temp_Command OUT\n");
      break;
    case (GET_SWITCH_SETINGS_COMMAND):
      printc(" - Get_Switch_Setings_Command IN\n");
      break;
    case (GET_SWITCH_SETINGS_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_Switch_Setings_Command OUT\n");
      break;
    case (SET_SWITCH_SETINGS_COMMAND):
      printc(" - Set_Switch_Setings_Command IN\n");
      break;
    case (SET_SWITCH_SETINGS_COMMAND | FUNC_OUT_MASK):
      printc(" - Set_Switch_Setings_Command OUT\n");
      break;
    case (GET_ALARM_COMMAND):
      printc(" - Get_Alarm_Command IN\n");
      break;
    case (GET_ALARM_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_Alarm_Command OUT\n");
      break;
    case (SET_ALARM_COMMAND):
      printc(" - Set_Alarm_Command IN\n");
      break;
    case (SET_ALARM_COMMAND | FUNC_OUT_MASK):
      printc(" - Set_Alarm_Command OUT\n");
      break;
    case (GET_TEMP_ALARM_COMMAND):
      printc(" - Get_Temp_Alarm_Command IN\n");
      break;
    case (GET_TEMP_ALARM_COMMAND | FUNC_OUT_MASK):
      printc(" - Get_Temp_Alarm_Command OUT\n");
      break;
    case (SET_TEMP_ALARM_COMMAND):
      printc(" - Set_Temp_Alarm_Command IN\n");
      break;
    case (SET_TEMP_ALARM_COMMAND | FUNC_OUT_MASK):
      printc(" - Set_Temp_Alarm_Command OUT\n");
      break;
    
      // Debug Commands
    case (DISPLAY_DUMP_COMMAND):
      printc(" - Display_Dump_Command IN\n");
      break;
    case (DISPLAY_DUMP_COMMAND | FUNC_OUT_MASK):
      printc(" - Display_Dump_Command OUT\n");
      break;
    case (DISPLAY_UPDATE_COMMAND):
      printc(" - Display_Update_Command IN\n");
      break;
    case (DISPLAY_UPDATE_COMMAND | FUNC_OUT_MASK):
      printc(" - Display_Update_Command OUT\n");
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
