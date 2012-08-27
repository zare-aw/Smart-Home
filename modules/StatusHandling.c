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
    
    if(FunctionBuffer[Function] == (DS1820_INIT | FUNC_OUT_MASK))
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
    
    if(FunctionBuffer[Function] == (DS1820_INIT | FUNC_OUT_MASK))
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
    
    if(FunctionBuffer[Function] == (DS1820_INIT | FUNC_OUT_MASK))
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
      // System
    case (INITIALIZATION):
      printc(" - Initialization IN\n");
      break;
    case (INITIALIZATION | FUNC_OUT_MASK):
      printc(" - Initialization OUT\n");
      break;
    
      // Delay
    case (DLY):
      printc(" - Dly IN\n");
      break;
    case (DLY | FUNC_OUT_MASK):
      printc(" - Dly OUT\n");
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
    
      // IR Driver
    case (IR_INIT):
      printc(" - IR_Init IN\n");
      break;
    case (IR_INIT | FUNC_OUT_MASK):
      printc(" - IR_Init OUT\n");
      break;
    case (IR_COMMAND_INIT):
      printc(" - IR_Command_Init IN\n");
      break;
    case (IR_COMMAND_INIT | FUNC_OUT_MASK):
      printc(" - IR_Command_Init OUT\n");
      break;
	case (IR_SET_COMMAND):
      printc(" - IR_Set_Command IN\n");
      break;
    case (IR_SET_COMMAND | FUNC_OUT_MASK):
      printc(" - IR_Set_Command OUT\n");
      break;
    case (IR_GET_COMMAND):
      printc(" - IR_Get_Command IN\n");
      break;
    case (IR_GET_COMMAND | FUNC_OUT_MASK):
      printc(" - IR_Get_Command OUT\n");
      break;
    case (IR_TIMER_ISR):
      printc(" - IR_Timer_ISR IN\n");
      break;
    case (IR_TIMER_ISR | FUNC_OUT_MASK):
      printc(" - IR_Timer_ISR OUT\n");
      break;
    case (IR_INPUT_ISR):
      printc(" - IR_Input_ISR IN\n");
      break;
    case (IR_INPUT_ISR | FUNC_OUT_MASK):
      printc(" - IR_Input_ISR OUT\n");
      break;
    case (IR_EXT_INTERRUPT_ISR):
      printc(" - IR_Ext_Interrupt_ISR IN\n");
      break;
    case (IR_EXT_INTERRUPT_ISR | FUNC_OUT_MASK):
      printc(" - IR_Ext_Interrupt_ISR OUT\n");
      break;
    case (IR_EXT_INTERRUPT_INIT):
      printc(" - IR_Ext_Interrupt_Init IN\n");
      break;
    case (IR_EXT_INTERRUPT_INIT | FUNC_OUT_MASK):
      printc(" - IR_Ext_Interrupt_Init OUT\n");
      break;
    
      // Out Driver
    case (OUT_INIT):
      printc(" - Out_Init IN\n");
      break;
    case (OUT_INIT | FUNC_OUT_MASK):
      printc(" - Out_Init OUT\n");
      break;
    case (OUT_SYNC):
      printc(" - Out_Sync IN\n");
      break;
    case (OUT_SYNC | FUNC_OUT_MASK):
      printc(" - Out_Sync OUT\n");
      break;
    case (OUT_GET_STATE):
      printc(" - Out_Get_State IN\n");
      break;
    case (OUT_GET_STATE | FUNC_OUT_MASK):
      printc(" - Out_Get_State OUT\n");
      break;
    
      // Menu Callbacks
    case (MENU_CALLBACKS_INIT):
      printc(" - Menu_Callbacks_Init IN\n");
      break;
    case (MENU_CALLBACKS_INIT | FUNC_OUT_MASK):
      printc(" - Menu_Callbacks_Init OUT\n");
      break;
    case (POWER_KEY_CALLBACK):
      printc(" - Power_Key_Callback IN\n");
      break;
    case (POWER_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Power_Key_Callback OUT\n");
      break;
    case (UP_KEY_CALLBACK):
      printc(" - Up_Key_Callback IN\n");
      break;
    case (UP_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Up_Key_Callback OUT\n");
      break;
    case (DOWN_KEY_CALLBACK):
      printc(" - Down_Key_Callback IN\n");
      break;
    case (DOWN_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Down_Key_Callback OUT\n");
      break;
    case (LEFT_KEY_CALLBACK):
      printc(" - Left_Key_Callback IN\n");
      break;
    case (LEFT_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Left_Key_Callback OUT\n");
      break;
    case (RIGHT_KEY_CALLBACK):
      printc(" - Right_Key_Callback IN\n");
      break;
    case (RIGHT_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Right_Key_Callback OUT\n");
      break;
    case (ENTER_KEY_CALLBACK):
      printc(" - Enter_Key_Callback IN\n");
      break;
    case (ENTER_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Enter_Key_Callback OUT\n");
      break;
    case (CANCEL_KEY_CALLBACK):
      printc(" - Cancel_Key_Callback IN\n");
      break;
    case (CANCEL_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Cancel_Key_Callback OUT\n");
      break;
    case (MENU_KEY_CALLBACK):
      printc(" - Menu_Key_Callback IN\n");
      break;
    case (MENU_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Menu_Key_Callback OUT\n");
      break;
    case (EXIT_KEY_CALLBACK):
      printc(" - Exit_Key_Callback IN\n");
      break;
    case (EXIT_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Exit_Key_Callback OUT\n");
      break;
    case (NUM1_KEY_CALLBACK):
      printc(" - Num1_Key_Callback IN\n");
      break;
    case (NUM1_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Num1_Key_Callback OUT\n");
      break;
    case (NUM2_KEY_CALLBACK):
      printc(" - Num2_Key_Callback IN\n");
      break;
    case (NUM2_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Num2_Key_Callback OUT\n");
      break;
    case (NUM3_KEY_CALLBACK):
      printc(" - Num3_Key_Callback IN\n");
      break;
    case (NUM3_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Num3_Key_Callback OUT\n");
      break;
    case (NUM4_KEY_CALLBACK):
      printc(" - Num4_Key_Callback IN\n");
      break;
    case (NUM4_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Num4_Key_Callback OUT\n");
      break;
    case (NUM5_KEY_CALLBACK):
      printc(" - Num5_Key_Callback IN\n");
      break;
    case (NUM5_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Num5_Key_Callback OUT\n");
      break;
    case (NUM6_KEY_CALLBACK):
      printc(" - Num6_Key_Callback IN\n");
      break;
    case (NUM6_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Num6_Key_Callback OUT\n");
      break;
    case (NUM7_KEY_CALLBACK):
      printc(" - Num7_Key_Callback IN\n");
      break;
    case (NUM7_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Num7_Key_Callback OUT\n");
      break;
    case (NUM8_KEY_CALLBACK):
      printc(" - Num8_Key_Callback IN\n");
      break;
    case (NUM8_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Num8_Key_Callback OUT\n");
      break;
    case (NUM9_KEY_CALLBACK):
      printc(" - Num9_Key_Callback IN\n");
      break;
    case (NUM9_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Num9_Key_Callback OUT\n");
      break;
    case (NUM0_KEY_CALLBACK):
      printc(" - Num0_Key_Callback IN\n");
      break;
    case (NUM0_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Num0_Key_Callback OUT\n");
      break;
    case (VOL_UP_KEY_CALLBACK):
      printc(" - Vol_Up_Key_Callback IN\n");
      break;
    case (VOL_UP_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Vol_Up_Key_Callback OUT\n");
      break;
    case (VOL_DOWN_KEY_CALLBACK):
      printc(" - Vol_Down_Key_Callback IN\n");
      break;
    case (VOL_DOWN_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Vol_Down_Key_Callback OUT\n");
      break;
    case (CH_UP_KEY_CALLBACK):
      printc(" - Ch_Up_Key_Callback IN\n");
      break;
    case (CH_UP_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Ch_Up_Key_Callback OUT\n");
      break;
    case (CH_DOWN_KEY_CALLBACK):
      printc(" - Ch_Down_Key_Callback IN\n");
      break;
    case (CH_DOWN_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Ch_Down_Key_Callback OUT\n");
      break;
    case (MUTE_KEY_CALLBACK):
      printc(" - Mute_Key_Callback IN\n");
      break;
    case (MUTE_KEY_CALLBACK | FUNC_OUT_MASK):
      printc(" - Mute_Key_Callback OUT\n");
      break;
    
      // DS1820 Driver
    case (DS1820_INIT):
      printc(" - DS1820_Init IN\n");
      break;
    case (DS1820_INIT | FUNC_OUT_MASK):
      printc(" - DS1820_Init OUT\n");
      break;
    case (DS1820_START_CONVERSION):
      printc(" - DS1820_Start_Conversion IN\n");
      break;
    case (DS1820_START_CONVERSION | FUNC_OUT_MASK):
      printc(" - DS1820_Start_Conversion OUT\n");
      break;
    case (DS1820_READ_TEMP):
      printc(" - DS1820_Read_Temp IN\n");
      break;
    case (DS1820_READ_TEMP | FUNC_OUT_MASK):
      printc(" - DS1820_Read_Temp OUT\n");
      break;
    case (DS1820_READ_SN):
      printc(" - DS1820_Read_SN IN\n");
      break;
    case (DS1820_READ_SN | FUNC_OUT_MASK):
      printc(" - DS1820_Read_SN OUT\n");
      break;
    case (DS_RESET):
      printc(" - DS_Reset IN\n");
      break;
    case (DS_RESET | FUNC_OUT_MASK):
      printc(" - DS_Reset OUT\n");
      break;
    
      // Menu
    case (MENU_INIT):
      printc(" - Menu_Init IN\n");
      break;
    case (MENU_INIT | FUNC_OUT_MASK):
      printc(" - Menu_Init OUT\n");
      break;
    case (MENU):
      printc(" - Menu IN\n");
      break;
    case (MENU | FUNC_OUT_MASK):
      printc(" - Menu OUT\n");
      break;
    case (DISPLAY_MENU_UPDATE):
      printc(" - Display_Menu_Update IN\n");
      break;
    case (DISPLAY_MENU_UPDATE | FUNC_OUT_MASK):
      printc(" - Display_Menu_Update OUT\n");
      break;
    case (DISPLAY_DATE_TIME_UPDATE):
      printc(" - Display_Date_Time_Update IN\n");
      break;
    case (DISPLAY_DATE_TIME_UPDATE | FUNC_OUT_MASK):
      printc(" - Display_Date_Time_Update OUT\n");
      break;
    case (DISPLAY_TEMP_UPDATE):
      printc(" - Display_Temp_Update IN\n");
      break;
    case (DISPLAY_TEMP_UPDATE | FUNC_OUT_MASK):
      printc(" - Display_Temp_Update OUT\n");
      break;
    case (REGISTER_MENU_TEMP):
      printc(" - Register_Menu_Temp IN\n");
      break;
    case (REGISTER_MENU_TEMP | FUNC_OUT_MASK):
      printc(" - Register_Menu_Temp OUT\n");
      break;
    case (UNREGISTER_MENU_TEMP):
      printc(" - Unregister_Menu_Temp IN\n");
      break;
    case (UNREGISTER_MENU_TEMP | FUNC_OUT_MASK):
      printc(" - Unregister_Menu_Temp OUT\n");
      break;
    case (MENU_SEC_INT_CALLBACK):
      printc(" - Menu_Sec_Int_Callback IN\n");
      break;
    case (MENU_SEC_INT_CALLBACK | FUNC_OUT_MASK):
      printc(" - Menu_Sec_Int_Callback OUT\n");
      break;
    case (UPDATE_DISPLAY_PANEL):
      printc(" - Update_Display_Panel IN\n");
      break;
    case (UPDATE_DISPLAY_PANEL | FUNC_OUT_MASK):
      printc(" - Update_Display_Panel OUT\n");
      break;
    case (UPDATE_SURFACE_BUFFER):
      printc(" - Update_Surface_Buffer IN\n");
      break;
    case (UPDATE_SURFACE_BUFFER | FUNC_OUT_MASK):
      printc(" - Update_Surface_Buffer OUT\n");
      break;
    case (PRINTD):
      printc(" - printd IN\n");
      break;
    case (PRINTD | FUNC_OUT_MASK):
      printc(" - printd OUT\n");
      break;
    
      // Temperature
    case (REGISTER_TEMP_SENSOR):
      printc(" - Register_Temp_Sensor IN\n");
      break;
    case (REGISTER_TEMP_SENSOR | FUNC_OUT_MASK):
      printc(" - Register_Temp_Sensor OUT\n");
      break;
    case (UNREGISTER_TEMP_SENSOR):
      printc(" - Unregister_Temp_Sensor IN\n");
      break;
    case (UNREGISTER_TEMP_SENSOR | FUNC_OUT_MASK):
      printc(" - Unregister_Temp_Sensor OUT\n");
      break;
    case (REGISTER_TEMP_ALARM):
      printc(" - Register_Temp_Alarm IN\n");
      break;
    case (REGISTER_TEMP_ALARM | FUNC_OUT_MASK):
      printc(" - Register_Temp_Alarm OUT\n");
      break;
    case (SET_TEMP_ALARM):
      printc(" - Set_Temp_Alarm IN\n");
      break;
    case (SET_TEMP_ALARM | FUNC_OUT_MASK):
      printc(" - Set_Temp_Alarm OUT\n");
      break;
    case (UNREGISTER_TEMP_ALARM):
      printc(" - Unregister_Temp_Alarm IN\n");
      break;
    case (UNREGISTER_TEMP_ALARM | FUNC_OUT_MASK):
      printc(" - Unregister_Temp_Alarm OUT\n");
      break;
    case (SET_STATE_TEMP_ALARM):
      printc(" - Set_State_Temp_Alarm IN\n");
      break;
    case (SET_STATE_TEMP_ALARM | FUNC_OUT_MASK):
      printc(" - Set_State_Temp_Alarm OUT\n");
      break;
    case (READ_TEMP_ALARM):
      printc(" - Read_Temp_Alarm IN\n");
      break;
    case (READ_TEMP_ALARM | FUNC_OUT_MASK):
      printc(" - Read_Temp_Alarm OUT\n");
      break;
    case (TEMP_INIT):
      printc(" - Temp_Init IN\n");
      break;
    case (TEMP_INIT | FUNC_OUT_MASK):
      printc(" - Temp_Init OUT\n");
      break;
    case (TEMP_REINIT):
      printc(" - Temp_Reinit IN\n");
      break;
    case (TEMP_REINIT | FUNC_OUT_MASK):
      printc(" - Temp_Reinit OUT\n");
      break;
    case (TEMP_WORK):
      printc(" - Temp_Work IN\n");
      break;
    case (TEMP_WORK | FUNC_OUT_MASK):
      printc(" - Temp_Work OUT\n");
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
