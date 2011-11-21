#include "Includes.h"

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Status(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_STATUS);
  printc("\r # Status = Running\n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_List(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_LIST);
  
  printc("\r Console List executed\n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Info(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_INFO);
  printc("\r # Smart Home system\n");
  printc(" # HW Version 1.0\n");
  printc(" # SW Version 1.0\n");
  printc(" # Compile Date = %s\n", __DATE__);
  printc(" # Compiler version = %d\n", __VER__);
  printc(" # Target ID = %d\n", __TID__);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Time(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_TIME);
  
  Get_Time_Command(NoOfCommand);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Date(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_DATE);
  
  Get_Date_Command(NoOfCommand);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Set_Time(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SET_TIME);
  uint8 h, m, s;
      
  h = (QueueConsoleCommand[NoOfCommand][9] - 0x30) * 10;
  h += (QueueConsoleCommand[NoOfCommand][10] - 0x30);
  m = (QueueConsoleCommand[NoOfCommand][12] - 0x30) * 10;
  m += (QueueConsoleCommand[NoOfCommand][13] - 0x30);
  s = (QueueConsoleCommand[NoOfCommand][15] - 0x30) * 10;
  s += (QueueConsoleCommand[NoOfCommand][16] - 0x30);
      
  Set_Time_Command(NoOfCommand, h, m, s);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Set_Date(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SET_DATE);
  uint8 d, m;
  uint16 y;
      
  d = (QueueConsoleCommand[NoOfCommand][9] - 0x30) * 10;
  d += (QueueConsoleCommand[NoOfCommand][10] - 0x30);
  m = (QueueConsoleCommand[NoOfCommand][12] - 0x30) * 10;
  m += (QueueConsoleCommand[NoOfCommand][13] - 0x30);
  y = (QueueConsoleCommand[NoOfCommand][15] - 0x30) * 1000;
  y += (QueueConsoleCommand[NoOfCommand][16] - 0x30) * 100;
  y += (QueueConsoleCommand[NoOfCommand][17] - 0x30) * 10;
  y += (QueueConsoleCommand[NoOfCommand][18] - 0x30);
      
  Set_Date_Command(NoOfCommand, d, m, y);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Config(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_CONFIG);
  
  Get_Configuration_Command(NoOfCommand);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Set_Config(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SET_CONFIG);
  
  Set_Configurations_Command(NoOfCommand);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Ir(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_IR);
  
  Get_IR_Commands_Command(NoOfCommand);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Set_Ir(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SET_IR);
  uint16 NoOfIRCommand;
  uint8 CommandUpdate = 1;
  char *CommandString = NULL;
  ir_t  ir_s;
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = IR_DUMMY_ID;
  ir_s.Callback_p = IR_Dummy_Handler;
      
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "n=");
  if(CommandString != NULL)
  {
    NoOfIRCommand = atoi(CommandString + 2);
    if(NoOfIRCommand > (MAX_IR_COMMANDS - RESERVED_IR_COMMANDS))
    {
      printc("\r # Invalid command number\n");
      CommandUpdate = 0;
    }
    if(NoOfIRCommand == NULL)
    {
      CommandString += 2;
      if(!strncmp("power", CommandString, 5))
        NoOfIRCommand = POWER_KEY;
      else if(!strncmp("up", CommandString, 5))
        NoOfIRCommand = UP_KEY;
      else if(!strncmp("down", CommandString, 5))
        NoOfIRCommand = DOWN_KEY;
      else if(!strncmp("left", CommandString, 5))
        NoOfIRCommand = LEFT_KEY;
      else if(!strncmp("right", CommandString, 5))
        NoOfIRCommand = RIGHT_KEY;
      else if(!strncmp("enter", CommandString, 5))
        NoOfIRCommand = ENTER_KEY;
      else if(!strncmp("cancel", CommandString, 5))
        NoOfIRCommand = CANCEL_KEY;
      else if(!strncmp("menu", CommandString, 5))
        NoOfIRCommand = MENU_KEY;
      else if(!strncmp("exit", CommandString, 5))
        NoOfIRCommand = EXIT_KEY;
      else if(!strncmp("num1", CommandString, 5))
        NoOfIRCommand = NUM1_KEY;
      else if(!strncmp("num2", CommandString, 5))
        NoOfIRCommand = NUM2_KEY;
      else if(!strncmp("num3", CommandString, 5))
        NoOfIRCommand = NUM3_KEY;
      else if(!strncmp("num4", CommandString, 5))
        NoOfIRCommand = NUM4_KEY;
      else if(!strncmp("num5", CommandString, 5))
        NoOfIRCommand = NUM5_KEY;
      else if(!strncmp("num6", CommandString, 5))
        NoOfIRCommand = NUM6_KEY;
      else if(!strncmp("num7", CommandString, 5))
        NoOfIRCommand = NUM7_KEY;
      else if(!strncmp("num8", CommandString, 5))
        NoOfIRCommand = NUM8_KEY;
      else if(!strncmp("num9", CommandString, 5))
        NoOfIRCommand = NUM9_KEY;
      else if(!strncmp("num0", CommandString, 5))
        NoOfIRCommand = NUM0_KEY;
      else if(!strncmp("vol-up", CommandString, 5))
        NoOfIRCommand = VOL_UP_KEY;
      else if(!strncmp("vol-down", CommandString, 5))
        NoOfIRCommand = VOL_DOWN_KEY;
      else if(!strncmp("ch-up", CommandString, 5))
        NoOfIRCommand = CH_UP_KEY;
      else if(!strncmp("ch-down", CommandString, 5))
        NoOfIRCommand = CH_DOWN_KEY;
      else if(!strncmp("mute", CommandString, 5))
        NoOfIRCommand = MUTE_KEY;
      else
      {
        printc("\r # Invalid command number\n");
        CommandUpdate = 0;
      }
    } // if(NoOfIRCommand == NULL)
  } // if(CommandString != NULL)
  else
  {
    printc("\r # Command number mising\n");
    CommandUpdate = 0;
  }
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "a=");
  if(CommandString != NULL)
    ir_s.Address = atoi(CommandString + 2);
      
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "c=");
  if(CommandString != NULL)
    ir_s.Command = atoi(CommandString + 2);
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "m=");
  if(CommandString != NULL)
  {
    CommandString += 2;
    
    if(!strncmp("single", CommandString, 6))
      ir_s.CallMode = SINGLE_CALL;
    else if(!strncmp("repetitive", CommandString, 10))
      ir_s.CallMode = REPETITIVE_CALL;
    else
    {
      printc(" # Invalid input parameters!\n");
      printc(" # CallMode parametar is invalid, see help for this command\n");
      printc(" # IR Command not set!\n");
      RETURN_SUCCESS_FUNC(CONSOLE_SET_IR);
    }
  } //  if(NoOfIRCommand == NULL)
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "response=");
  if(CommandString != NULL)
  {
    CommandString += 9;
    
    if(!strncmp("out_1_ON", CommandString, 8))
    {
      ir_s.Callback_p = Out_1_Set;
      ir_s.Target = IR_OUT_1_SET;
    }
    else if(!strncmp("out_1_OFF", CommandString, 9))
    {
      ir_s.Callback_p = Out_1_Clr;
      ir_s.Target = IR_OUT_1_CLR;
    }
    else if(!strncmp("out_1_toggle", CommandString, 12))
    {
      ir_s.Callback_p = Out_1_Toggle;
      ir_s.Target = IR_OUT_1_TOGGLE;
    }
    else if(!strncmp("out_2_ON", CommandString, 8))
    {
      ir_s.Callback_p = Out_2_Set;
      ir_s.Target = IR_OUT_2_SET;
    }
    else if(!strncmp("out_2_OFF", CommandString, 9))
    {
      ir_s.Callback_p = Out_2_Clr;
      ir_s.Target = IR_OUT_2_CLR;
    }
    else if(!strncmp("out_2_toggle", CommandString, 12))
    {
      ir_s.Callback_p = Out_2_Toggle;
      ir_s.Target = IR_OUT_2_TOGGLE;
    }
    else if(!strncmp("out_3_ON", CommandString, 8))
    {
      ir_s.Callback_p = Out_3_Set;
      ir_s.Target = IR_OUT_3_SET;
    }
    else if(!strncmp("out_3_OFF", CommandString, 9))
    {
      ir_s.Callback_p = Out_3_Clr;
      ir_s.Target = IR_OUT_3_CLR;
    }
    else if(!strncmp("out_3_toggle", CommandString, 12))
    {
      ir_s.Callback_p = Out_3_Toggle;
      ir_s.Target = IR_OUT_3_TOGGLE;
    }
    else if(!strncmp("out_4_ON", CommandString, 8))
    {
      ir_s.Callback_p = Out_4_Set;
      ir_s.Target = IR_OUT_4_SET;
    }
    else if(!strncmp("out_4_OFF", CommandString, 9))
    {
      ir_s.Callback_p = Out_4_Clr;
      ir_s.Target = IR_OUT_4_CLR;
    }
    else if(!strncmp("out_4_toggle", CommandString, 12))
    {
      ir_s.Callback_p = Out_4_Toggle;
      ir_s.Target = IR_OUT_4_TOGGLE;
    }
    else if(!strncmp("out_5_ON", CommandString, 8))
    {
      ir_s.Callback_p = Out_5_Set;
      ir_s.Target = IR_OUT_5_SET;
    }
    else if(!strncmp("out_5_OFF", CommandString, 9))
    {
      ir_s.Callback_p = Out_5_Clr;
      ir_s.Target = IR_OUT_5_CLR;
    }
    else if(!strncmp("out_5_toggle", CommandString, 12))
    {
      ir_s.Callback_p = Out_5_Toggle;
      ir_s.Target = IR_OUT_5_TOGGLE;
    }
    else if(!strncmp("out_6_ON", CommandString, 8))
    {
      ir_s.Callback_p = Out_6_Set;
      ir_s.Target = IR_OUT_6_SET;
    }
    else if(!strncmp("out_6_OFF", CommandString, 9))
    {
      ir_s.Callback_p = Out_6_Clr;
      ir_s.Target = IR_OUT_6_CLR;
    }
    else if(!strncmp("out_6_toggle", CommandString, 12))
    {
      ir_s.Callback_p = Out_6_Toggle;
      ir_s.Target = IR_OUT_6_TOGGLE;
    }
    else if(!strncmp("sound_alarm", CommandString, 11))
    {
      ir_s.Callback_p = IR_Dummy_Handler;
      ir_s.Target = IR_DUMMY_ID;
    }
    else if(!strncmp("dummy", CommandString, 5))
    {
      ir_s.Callback_p = IR_Dummy_Handler;
      ir_s.Target = IR_DUMMY_ID;
    }
    else
    {
      printc(" # Invalid input parameters!\n");
      printc(" # response parametar is invalid, see help for this command\n");
      printc(" # IR Command not set!\n");
      RETURN_SUCCESS_FUNC(CONSOLE_SET_IR);
    }
    
  } //  if(NoOfIRCommand == NULL)
  
  if(CommandUpdate)
    Set_IR_Commands_Command(NoOfCommand, NoOfIRCommand, &ir_s);
  
  RETURN_SUCCESS_FUNC(CONSOLE_SET_IR);
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Backlight(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_BACKLIGHT);
  
  Get_Back_Light_Level_Command(NoOfCommand);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Set_Backlight(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SET_BACKLIGHT);  
  uint8 Level = 50;
      
  if(QueueConsoleCommand[NoOfCommand][15] == ' ' || QueueConsoleCommand[NoOfCommand][15] == 0)
  {
    Level = (QueueConsoleCommand[NoOfCommand][14] - 0x30);
  }
  else if(QueueConsoleCommand[NoOfCommand][16] == ' ' || QueueConsoleCommand[NoOfCommand][16] == 0)
  {
    Level =  (QueueConsoleCommand[NoOfCommand][14] - 0x30) * 10;
    Level += (QueueConsoleCommand[NoOfCommand][15] - 0x30);
  }
  else if(QueueConsoleCommand[NoOfCommand][17] == ' ' || QueueConsoleCommand[NoOfCommand][17] == 0)
  {
    Level =  (QueueConsoleCommand[NoOfCommand][14] - 0x30) * 100;
    Level += (QueueConsoleCommand[NoOfCommand][15] - 0x30) * 10;
    Level += (QueueConsoleCommand[NoOfCommand][16] - 0x30);
  }
      
  Set_Back_Light_Level_Command(NoOfCommand, Level);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Light_Switch(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_LIGHT_SWITCH);
  
  Get_Lignt_Switch_Level_Command(NoOfCommand);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Set_Light_Switch(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SET_LIGHT_SWITCH);
  uint8 Max = 10;
  uint8 Min = 5;
  
  if(QueueConsoleCommand[NoOfCommand][18] == ' ')
  {
    Min = (QueueConsoleCommand[NoOfCommand][17] - 0x30);
    if(QueueConsoleCommand[NoOfCommand][20] == ' ' || QueueConsoleCommand[NoOfCommand][20] == 0)
    {
      Max = (QueueConsoleCommand[NoOfCommand][19] - 0x30);
    }
    else if(QueueConsoleCommand[NoOfCommand][21] == ' ' || QueueConsoleCommand[NoOfCommand][21] == 0)
    {
      Max =  (QueueConsoleCommand[NoOfCommand][19] - 0x30) * 10;
      Max += (QueueConsoleCommand[NoOfCommand][20] - 0x30);
    }
    else if(QueueConsoleCommand[NoOfCommand][22] == ' ' || QueueConsoleCommand[NoOfCommand][22] == 0)
    {
      Max =  (QueueConsoleCommand[NoOfCommand][19] - 0x30) * 100;
      Max += (QueueConsoleCommand[NoOfCommand][20] - 0x30) * 10;
      Max += (QueueConsoleCommand[NoOfCommand][21] - 0x30);
    }
  }
  else if(QueueConsoleCommand[NoOfCommand][19] == ' ')
  {
    Min =  (QueueConsoleCommand[NoOfCommand][17] - 0x30) * 10;
    Min += (QueueConsoleCommand[NoOfCommand][18] - 0x30);
    if(QueueConsoleCommand[NoOfCommand][21] == ' ' || QueueConsoleCommand[NoOfCommand][21] == 0)
    {
      Max = (QueueConsoleCommand[NoOfCommand][20] - 0x30);
    }
    else if(QueueConsoleCommand[NoOfCommand][22] == ' ' || QueueConsoleCommand[NoOfCommand][22] == 0)
    {
      Max =  (QueueConsoleCommand[NoOfCommand][20] - 0x30) * 10;
      Max += (QueueConsoleCommand[NoOfCommand][21] - 0x30);
    }
    else if(QueueConsoleCommand[NoOfCommand][23] == ' ' || QueueConsoleCommand[NoOfCommand][23] == 0)
    {
      Max =  (QueueConsoleCommand[NoOfCommand][20] - 0x30) * 100;
      Max += (QueueConsoleCommand[NoOfCommand][21] - 0x30) * 10;
      Max += (QueueConsoleCommand[NoOfCommand][22] - 0x30);
    }
  }
  else if(QueueConsoleCommand[NoOfCommand][20] == ' ')
  {
    Min =  (QueueConsoleCommand[NoOfCommand][17] - 0x30) * 100;
    Min += (QueueConsoleCommand[NoOfCommand][18] - 0x30) * 10;
    Min += (QueueConsoleCommand[NoOfCommand][19] - 0x30);
    if(QueueConsoleCommand[NoOfCommand][22] == ' ' || QueueConsoleCommand[NoOfCommand][22] == 0)
    {
      Max = (QueueConsoleCommand[NoOfCommand][21] - 0x30);
    }
    else if(QueueConsoleCommand[NoOfCommand][23] == ' ' || QueueConsoleCommand[NoOfCommand][23] == 0)
    {
      Max =  (QueueConsoleCommand[NoOfCommand][21] - 0x30) * 10;
      Max += (QueueConsoleCommand[NoOfCommand][22] - 0x30);
    }
    else if(QueueConsoleCommand[NoOfCommand][24] == ' ' || QueueConsoleCommand[NoOfCommand][24] == 0)
    {
      Max =  (QueueConsoleCommand[NoOfCommand][21] - 0x30) * 100;
      Max += (QueueConsoleCommand[NoOfCommand][22] - 0x30) * 10;
      Max += (QueueConsoleCommand[NoOfCommand][23] - 0x30);
    }
  }
  
  Set_Lignt_Switch_Level_Command(NoOfCommand, Max, Min);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Out_Switch(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_OUT_SWITCH);
  
  Get_Out_Switch_Command(NoOfCommand);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Set_Out_Switch(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SET_OUT_SWITCH);
  char *CommandString;
  uint8 OutNumber;
  uint8 OutValue;
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "n=");
  if(CommandString != NULL)
    OutNumber = atoi(CommandString + 2);
  else
  {
    printc("\r # Missing 'n' input parameter!\n");
    RETURN_SUCCESS_FUNC(CONSOLE_SET_OUT_SWITCH);
  }
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "v=");
  if(CommandString != NULL)
    OutValue = atoi(CommandString + 2);
  else
  {
    printc("\r # Missing 'v' input parameter!\n");
    RETURN_SUCCESS_FUNC(CONSOLE_SET_OUT_SWITCH);
  }
  
  Set_Out_Switch_Command(NoOfCommand, OutNumber, OutValue);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Switch_Settings(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SWITCH_SETTINGS);
  
  uint8 Chanel = 0;
      
  //TODO: Dovrsi ja komandata.
      
  Get_Switch_Setings_Command(NoOfCommand, Chanel);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Set_Switch_Settings(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SET_SWITCH_SETTINGS);
  
  uint8 Chanel = 0;
      
  //TODO: Dovrsi ja komandata.
      
  Set_Switch_Setings_Command(NoOfCommand, Chanel);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Temp(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_TEMP);
  char *CommandString = NULL;
  
  if(strstr(QueueConsoleCommand[NoOfCommand], "all") != NULL)
    Get_Temp_Command(NoOfCommand, 0xFF);
  else if(strstr(QueueConsoleCommand[NoOfCommand], "id="))
  {
    CommandString = strstr(QueueConsoleCommand[NoOfCommand], "id=");
    if(CommandString != NULL)
      Get_Temp_Command(NoOfCommand, atoi(CommandString + 3));
  }
  else
    Get_Temp_Command(NoOfCommand, 0xFF);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Alarm(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_ALARM);
  
  Get_Alarm_Command(NoOfCommand);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Set_Alarm(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SET_ALARM);
  
  Set_Alarm_Command(NoOfCommand);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Get_Temp_Alarm(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_TEMP_ALARM);
  
  if(strstr(QueueConsoleCommand[NoOfCommand], "int") != NULL)
    Get_Temp_Alarm_Command(NoOfCommand, 1);
  else if(strstr(QueueConsoleCommand[NoOfCommand], "ext") != NULL)
    Get_Temp_Alarm_Command(NoOfCommand, 2);
  else
    Get_Temp_Alarm_Command(NoOfCommand, ALL_TEMP_ALARMS);     // Take all registered interrupts
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Set_Temp_Alarm(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_SET_TEMP_ALARM);
  TempAlarm_t TempAlarm_s = {NULL};
  char *CommandString = NULL;
  
  TempAlarm_s.Value = -255;
  TempAlarm_s.AlarmID = NO_ALARM_ID;
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "sensor=");
  if(CommandString != NULL)
  {
    if(!strncmp("int", CommandString + 7, 3))
    {
      if(Check_Sensor_Availability(0))
        TempAlarm_s.SensorID = 0;
      else
        printc("\r # Internal Sensor not available\n");
    }
    else if(!strncmp("ext", CommandString + 7, 3))
    {
      if(Check_Sensor_Availability(1))
        TempAlarm_s.SensorID = 1;
      else
        printc("\r # External Sensor not available\n");
    }
    else
    {
      printc(" # Invalid input parameters!\n");
      printc(" # Sensor parameters is: int, ext\n");
      printc(" # Alarm not set!\n");
      RETURN_SUCCESS_FUNC(CONSOLE_SET_TEMP_ALARM);
    }
  }
  else
  {
    printc(" # Missing input parameter! 'sensor' parametar must be specified!\n");
    RETURN_SUCCESS_FUNC(CONSOLE_SET_TEMP_ALARM);
  }
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "temp=");
  if(CommandString != NULL)
    TempAlarm_s.Value = atoi(CommandString + 5);
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "event=");
  if(CommandString != NULL)
  {
    if(!strncmp("above", CommandString + 6, 5))
      TempAlarm_s.Event = ABOVE;
    else if(!strncmp("bellow", CommandString + 6, 6))
      TempAlarm_s.Event = BELLOW;
    else if(!strncmp("equal", CommandString + 6, 5))
      TempAlarm_s.Event = EQUAL;
    else if(!strncmp("above_or_equal", CommandString + 6, 14))
      TempAlarm_s.Event = ABOVE_OR_EQUAL;
    else if(!strncmp("bellow_or_equal", CommandString + 6, 15))
      TempAlarm_s.Event = BELLOW_OR_EQUAL;
    else if(!strncmp("different", CommandString + 6, 9))
      TempAlarm_s.Event = DIFFERENT;
    else
    {
      printc(" # Invalid input parameters!\n");
      printc(" # event parameters is: above, bellow, equal, above_or_equal, bellow_or_equal, different\n");
      printc(" # Alarm not set!\n");
      RETURN_SUCCESS_FUNC(CONSOLE_SET_TEMP_ALARM);
    }
  }
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "state=");
  if(CommandString != NULL)
  {
    if(!strncmp("ON", CommandString + 6, 2))
      TempAlarm_s.State = ALARM_ON;
    else if(!strncmp("OFF", CommandString + 6, 3))
      TempAlarm_s.State = ALARM_OFF;
    else
    {
      printc(" # Invalid input parameters!\n");
      printc(" # state parameters is: ON, OFF\n");
      printc(" # Alarm not set!\n");
      RETURN_SUCCESS_FUNC(CONSOLE_SET_TEMP_ALARM);
    }
  }
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "alarmID=");
  if(CommandString != NULL)
    TempAlarm_s.AlarmID = atoi(CommandString + 8);
  
  CommandString = strstr(QueueConsoleCommand[NoOfCommand], "response=");
  if(CommandString != NULL)
  {
    if(!strncmp("out_1_ON", CommandString + 9, 8))
      TempAlarm_s.Callback = (void *)Out_1_Set;
    else if(!strncmp("out_1_OFF", CommandString + 9, 9))
      TempAlarm_s.Callback = (void *)Out_1_Clr;
    if(!strncmp("out_2_ON", CommandString + 9, 8))
      TempAlarm_s.Callback = (void *)Out_2_Set;
    else if(!strncmp("out_2_OFF", CommandString + 9, 9))
      TempAlarm_s.Callback = (void *)Out_2_Clr;
    if(!strncmp("out_3_ON", CommandString + 9, 8))
      TempAlarm_s.Callback = (void *)Out_3_Set;
    else if(!strncmp("out_3_OFF", CommandString + 9, 9))
      TempAlarm_s.Callback = (void *)Out_3_Clr;
    if(!strncmp("out_4_ON", CommandString + 9, 8))
      TempAlarm_s.Callback = (void *)Out_4_Set;
    else if(!strncmp("out_4_OFF", CommandString + 9, 9))
      TempAlarm_s.Callback = (void *)Out_4_Clr;
    if(!strncmp("out_5_ON", CommandString + 9, 8))
      TempAlarm_s.Callback = (void *)Out_5_Set;
    else if(!strncmp("out_5_OFF", CommandString + 9, 9))
      TempAlarm_s.Callback = (void *)Out_5_Clr;
    if(!strncmp("out_6_ON", CommandString + 9, 8))
      TempAlarm_s.Callback = (void *)Out_6_Set;
    else if(!strncmp("out_6_OFF", CommandString + 9, 9))
      TempAlarm_s.Callback = (void *)Out_6_Clr;
    if(!strncmp("sound_alarm", CommandString + 9, 11))
      TempAlarm_s.Callback = (void *)Temp_Alarm_Dummy_Handler;
    else if(!strncmp("dummy", CommandString + 9, 5))
      TempAlarm_s.Callback = (void *)Temp_Alarm_Dummy_Handler;
    else
    {
      printc(" # Invalid input parameters!\n");
      printc(" # response parametar is invalid, see help for this command\n");
      printc(" # Alarm not set!\n");
      RETURN_SUCCESS_FUNC(CONSOLE_SET_TEMP_ALARM);
    }
  }
  
  Set_Temp_Alarm_Command(NoOfCommand, &TempAlarm_s);
  
  RETURN_SUCCESS_FUNC(CONSOLE_SET_TEMP_ALARM);
}






// Debug commands
/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Dump_Display(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_DUMP_DISPLAY);
  
  Display_Dump_Command(NoOfCommand);
  
  RETURN_SUCCESS_FUNC(CONSOLE_DUMP_DISPLAY);
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Update_Display(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_UPDATE_DISPLAY);
  
  switch(atoi(QueueConsoleCommand[NoOfCommand] + 3))
  {
    case 0:
      Display_Update_Command(NoOfCommand, DISABLE);
      break;
    case 1:
      Display_Update_Command(NoOfCommand, ENABLE);
      break;
    default:
      Display_Update_Command(NoOfCommand, DISABLE);
      printc(" # Console display update disabled!\n");
      break;
  }
  
  RETURN_SUCCESS_FUNC(CONSOLE_UPDATE_DISPLAY);
}
