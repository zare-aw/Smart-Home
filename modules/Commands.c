#include "Global_Defines.h"
#include "Includes.h"

/*******************************************************************************
* Final
*******************************************************************************/
Status_t Get_Time_Command(uint8 NoOfCommand)
{
  Function_IN(GET_TIME_COMMAND);
  char String[32] = {0};
  RtcTime_t Time;
  
  RTC_Get_Time(&Time);
  
  if(strstr(QueueConsoleCommand[NoOfCommand], "-a") != NULL)
    CONTROL(!Format_Time(2, &Time, String), RTC_GENERAL_ERROR);
  else
    CONTROL(!Format_Time(1, &Time, String), RTC_GENERAL_ERROR);
  
  printc("\r # %s\n", String);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* Final
*******************************************************************************/
Status_t Set_Time_Command(uint8 NoOfCommand, uint8 h, uint8 m, uint8 s)
{
  Function_IN(SET_TIME_COMMAND);
  
  RtcTime_t Time;
  
  Time.Hour = h;
  Time.Minute = m;
  Time.Second = s;
  
  if(RTC_Set_Time(&Time) == RTC_INVALID_TIME_ERROR)
    printc("\r # Invalid Time!\n");
  else
    printc("\r # Time Set!\n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* Final
*******************************************************************************/
Status_t Get_Date_Command(uint8 NoOfCommand)
{
  Function_IN(GET_DATE_COMMAND);
  RtcDate_t Date;
  char String[32] = {0};
  
  RTC_Get_Date(&Date);
  
  if(strstr(QueueConsoleCommand[NoOfCommand], "-l") != NULL)
    CONTROL(!Format_Date(2, &Date, String), RTC_GENERAL_ERROR);
  else
    CONTROL(!Format_Date(1, &Date, String), RTC_GENERAL_ERROR);
  
  printc("\r # %s\n", String);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* Final
*******************************************************************************/
Status_t Set_Date_Command(uint8 NoOfCommand, uint8 d, uint8 m, uint16 y)
{
  Function_IN(SET_DATE_COMMAND);
  
  RtcDate_t Date;
  Date.Day = d;
  Date.Month = m;
  Date.Year = y;
  
  if(RTC_Set_Date(&Date) == RTC_INVALID_DATE_ERROR)
    printc("\r # Invalid Date!\n");
  else
    printc("\r # Date Set\n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Get_Configuration_Command(uint8 NoOfCommand)
{
  Function_IN(GET_CONFIGURATION_COMMAND);
  
  printc(" # Get Configuration Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_Configurations_Command(uint8 NoOfCommand)
{
  Function_IN(SET_CONFIGURATIONS_COMMAND);
  
  printc(" # Set Configurations Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Get_IR_Commands_Command(uint8 NoOfCommand)
{
  Function_IN(GET_IR_COMMANDS_COMMAND);
  ir_t IR_Command = {0};
  uint16 i;
  
  printc("\r # Maximum supported general IR commands: %u\n", MAX_IR_COMMANDS - RESERVED_IR_COMMANDS);
  printc("\r # IR Commands:\n");
  
  for(i = 0; i < MAX_IR_COMMANDS; i++)
  {
    CONTROL(!IR_Get_Command(i, &IR_Command), IR_COMMAND_GET_ERROR);
    if((IR_Command.Address != NULL) || (IR_Command.Command != NULL) || (IR_Command.CallMode != NULL) || (IR_Command.Target != NULL))
      printc("\r # IR_Command_Number = %u\tAddress = %u\tCommand = %u\tCallMode = %u\tTarget = %u\n", i, IR_Command.Address, IR_Command.Command, IR_Command.CallMode, IR_Command.Target);
  }
  
  printc("\r # Other IR Commands are empty \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* @in NoOfCommand - Broj na komanda vo Queue
* @in NoOfIRCommand - Broj na komanda sto treba da se postavi
* @in Address - Adresa na IR komandata
* @in Command - Broj na IR komandata
                Dokolku i Address i Command se NULL, togas input e IR
*******************************************************************************/
Status_t Set_IR_Commands_Command(uint8 NoOfCommand, uint16 NoOfIRCommand, ir_t *ir_p)
{
  Function_IN(SET_IR_COMMANDS_COMMAND);

  if((ir_p -> Address == NULL) && (ir_p -> Command == NULL))
  {
    CONTROL(!IR_Command_Init(NoOfIRCommand, ir_p), IR_COMMAND_SET_ERROR);
    CONTROL(!IR_Set_Command(NoOfIRCommand), IR_COMMAND_SET_ERROR);
    printc("\r # Waiting for Command from IR\n");
  }
  else
  {
    CONTROL(!IR_Command_Init(NoOfIRCommand, ir_p), IR_COMMAND_SET_ERROR);
    printc("\r # IR Command Set with parameters:\n");
    printc(" # NoOfCommand = %u\n", NoOfIRCommand);
    printc(" # Address = %u\n", ir_p -> Address);
    printc(" # Command = %u\n", ir_p -> Command);
    printc(" # CallMode = %u\n", ir_p -> CallMode);
    printc(" # Target = %u\n", ir_p -> Target);
    printc(" # Callback = %u\n", ir_p -> Callback_p);
    
  }
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Get_Back_Light_Level_Command(uint8 NoOfCommand)
{
  Function_IN(GET_BACK_LIGHT_LEVEL_COMMAND);
  
  printc(" # Get Back Light Level Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_Back_Light_Level_Command(uint8 NoOfCommand, uint8 Level)
{
  Function_IN(SET_BACK_LIGHT_LEVEL_COMMAND);
  
  printc(" # Set Back Light Level Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Get_Lignt_Switch_Level_Command(uint8 NoOfCommand)
{
  Function_IN(GET_LIGHT_SWITCH_LEVEL_COMMAND);
  
  printc(" # Get Light Switch Level Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* @in NoOfCommand - Broj na komanda vo Queue
* @in Max - Vrednost na jacina na svetlina pri koja displejot ke sveti maksimum
* @in Min - Vrednost na jacina na svetlina pri koja displejot ke sveti minimum
*******************************************************************************/
Status_t Set_Lignt_Switch_Level_Command(uint8 NoOfCommand, uint8 Max, uint8 Min)
{
  Function_IN(SET_LIGHT_SWITCH_LEVEL_COMMAND);
  
  printc(" # Set Light Switch Level Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Get_Out_Switch_Command(uint8 NoOfCommand)
{
  Function_IN(GET_OUT_SWITCH_COMMAND);
  
  Out_t Out;
  
  Out_Get_State(OUTS_TO_SET, &Out);
  
  printc("\r # Out_1 = %u\n", Out.S_1);
  printc("\r # Out_2 = %u\n", Out.S_2);
  printc("\r # Out_3 = %u\n", Out.S_3);
  printc("\r # Out_4 = %u\n", Out.S_4);
  printc("\r # Out_5 = %u\n", Out.S_5);
  printc("\r # Out_6 = %u\n", Out.S_6);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_Out_Switch_Command(uint8 NoOfCommand, uint8 OutNumber, uint8 OutValue)
{
  Function_IN(SET_OUT_SWITCH_COMMAND);
  
  switch(OutNumber)
  {
    case 1:
      if(OutValue == 1)
        Out_1_Set(NULL);
      else if(OutValue == 0)
        Out_1_Clr(NULL);
      else
      {
        printc("\r # Invalid value for Out_1\n");
        RETURN_SUCCESS_FUNC(SET_OUT_SWITCH_COMMAND);
      }
      break;
    case 2:
      if(OutValue == 1)
        Out_2_Set(NULL);
      else if(OutValue == 0)
        Out_2_Clr(NULL);
      else
      {
        printc("\r # Invalid value for Out_2\n");
        RETURN_SUCCESS_FUNC(SET_OUT_SWITCH_COMMAND);
      }
      break;
    case 3:
      if(OutValue == 1)
        Out_3_Set(NULL);
      else if(OutValue == 0)
        Out_3_Clr(NULL);
      else
      {
        printc("\r # Invalid value for Out_3\n");
        RETURN_SUCCESS_FUNC(SET_OUT_SWITCH_COMMAND);
      }
      break;
    case 4:
      if(OutValue == 1)
        Out_4_Set(NULL);
      else if(OutValue == 0)
        Out_4_Clr(NULL);
      else
      {
        printc("\r # Invalid value for Out_4\n");
        RETURN_SUCCESS_FUNC(SET_OUT_SWITCH_COMMAND);
      }
      break;
    case 5:
      if(OutValue == 1)
        Out_5_Set(NULL);
      else if(OutValue == 0)
        Out_5_Clr(NULL);
      else
      {
        printc("\r # Invalid value for Out_5\n");
        RETURN_SUCCESS_FUNC(SET_OUT_SWITCH_COMMAND);
      }
      break;
    case 6:
      if(OutValue == 1)
        Out_6_Set(NULL);
      else if(OutValue == 0)
        Out_6_Clr(NULL);
      else
      {
        printc("\r # Invalid value for Out_6\n");
        RETURN_SUCCESS_FUNC(SET_OUT_SWITCH_COMMAND);
      }
      break;
    default:
      printc("\r # Invalid Switch number!\n");
      RETURN_SUCCESS_FUNC(SET_OUT_SWITCH_COMMAND);
  }
  
  RETURN_SUCCESS_FUNC(SET_OUT_SWITCH_COMMAND);
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Get_Switch_Setings_Command(uint8 NoOfCommand, uint8 Chanel)
{
  Function_IN(GET_SWITCH_SETINGS_COMMAND);
  
  printc(" # Get Switch Setings Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_Switch_Setings_Command(uint8 NoOfCommand, uint8 Chanel)
{
  Function_IN(SET_SWITCH_SETINGS_COMMAND);
  
  printc(" # Set Switch Setings Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* @in NoOfCommand - Broj na komanda vo Queue
* @in SensorID - Sensor od koj ja sakame temperaturata, 0xFF za site kanali
*******************************************************************************/
Status_t Get_Temp_Command(uint8 NoOfCommand, uint8 SensorID)
{
  Function_IN(GET_TEMP_COMMAND);
  int Temp;
  
  if(SensorID == 0xFF)
  {
    for(int i = 0; i < NO_OF_TEMP_SENSORS; i++)
    {
      Temp = ReadTemp(i);
      if(Temp > -250)
        printc("\r # Temp%d = %d\n", i, Temp);
    }
  }
  else
    printc("\r # Temp = %d\n", ReadTemp(SensorID));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Get_Alarm_Command(uint8 NoOfCommand)
{
  Function_IN(GET_ALARM_COMMAND);
  
  printc(" # Get Alarm Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_Alarm_Command(uint8 NoOfCommand)
{
  Function_IN(SET_ALARM_COMMAND);
  
  printc(" # Set Alarm Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Get_Temp_Alarm_Command(uint8 NoOfCommand, uint8 SensorID)
{
  Function_IN(GET_TEMP_ALARM_COMMAND);
  TempAlarm_t TempAlarm_s;
  
  if(SensorID == ALL_TEMP_ALARMS)
  {
    for(uint8 i = 0; i < NO_OF_TEMP_SENSORS; i++)
      for(uint8 j = 0; j < NO_OF_ALARMS; j++)
        if(Read_Temp_Alarm(i, j, &TempAlarm_s) == SUCCESS)
        {
          printc(" # TempSensor %d, AlarmID %d, State = ", i, j);
          switch(TempAlarm_s.State)
          {
            case ALARM_OFF:
              printc("OFF");
              break;
            case ALARM_ON:
              printc("ON");
              break;
            default:
              printc("UNKNOWN");
              break;
          }
          printc(", Event = ");
          switch(TempAlarm_s.Event)
          {
            case ABOVE:
              printc("ABOVE");
              break;
            case BELLOW:
              printc("BELLOW");
              break;
            case EQUAL:
              printc("EQUAL");
              break;
            case ABOVE_OR_EQUAL:
              printc("ABOVE_OR_EQUAL");
              break;
            case BELLOW_OR_EQUAL:
              printc("BELLOW_OR_EQUAL");
              break;
            case DIFFERENT:
              printc("DIFFERENT");
              break;
            default:
              printc("UNKNOWN");
              break;
          }
          printc(", Value = %d", TempAlarm_s.Value);
          TEMP_DEBUG(printc(", CallbackAddress = %X", (uint32)TempAlarm_s.Callback));
          printc("\n");
        }
  }
  else
  {
    for(uint8 j = 0; j < NO_OF_ALARMS; j++)
        if(Read_Temp_Alarm_Wrap(SensorID, j, &TempAlarm_s) == SUCCESS)
        {
          printc(" # TempSensor %d, AlarmID %d, State = ", SensorID, j);
          switch(TempAlarm_s.State)
          {
            case ALARM_OFF:
              printc("OFF");
              break;
            case ALARM_ON:
              printc("ON");
              break;
            default:
              printc("UNKNOWN");
              break;
          }
          printc(", Event = ");
          switch(TempAlarm_s.Event)
          {
            case ABOVE:
              printc("ABOVE");
              break;
            case BELLOW:
              printc("BELLOW");
              break;
            case EQUAL:
              printc("EQUAL");
              break;
            case ABOVE_OR_EQUAL:
              printc("ABOVE_OR_EQUAL");
              break;
            case BELLOW_OR_EQUAL:
              printc("BELLOW_OR_EQUAL");
              break;
            case DIFFERENT:
              printc("DIFFERENT");
              break;
            default:
              printc("UNKNOWN");
              break;
          }
          printc(", Value = %d", TempAlarm_s.Value);
          TEMP_DEBUG(printc(", CallbackAddress = %X", (uint32)TempAlarm_s.Callback));
          printc("\n");
        }
  }
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_Temp_Alarm_Command(uint8 NoOfCommand, TempAlarm_t *TempAlarm_p)
{
  Function_IN(SET_TEMP_ALARM_COMMAND);
  
  COMMAND_DEBUG(printc("\r # Set_Temp_Alarm_Command() input parameters\n"));
  COMMAND_DEBUG(printc("\r # SensorID = %u\n", TempAlarm_p -> SensorID));
  COMMAND_DEBUG(printc("\r # AlarmID = %u\n", TempAlarm_p -> AlarmID));
  COMMAND_DEBUG(printc("\r # Event = %u\n", TempAlarm_p -> Event));
  COMMAND_DEBUG(printc("\r # State = %u\n", TempAlarm_p -> State));
  COMMAND_DEBUG(printc("\r # Value = %d\n", TempAlarm_p -> Value));
  COMMAND_DEBUG(printc("\r # Callback = %u\n", TempAlarm_p -> Callback));
  
  if(TempAlarm_p -> AlarmID != NO_ALARM_ID)
  {
    CONTROL(!Set_Temp_Alarm(TempAlarm_p), TEMP_SET_ALARM_ERROR);
    printc(" # Temp Alarm set\n");
  }
  else
  {
    if((TempAlarm_p -> Event != NO_ALARM) &&
       (TempAlarm_p -> Value != -255) &&
       (TempAlarm_p -> Callback != NULL) &&
       (TempAlarm_p -> SensorID < NO_OF_TEMP_SENSORS))
    {
      CONTROL(!Register_Temp_Alarm(TempAlarm_p -> SensorID, TempAlarm_p -> Event, TempAlarm_p -> Value,
                                  TempAlarm_p -> Callback, &(TempAlarm_p -> AlarmID)), TEMP_ALARM_REGISTER_ERROR);
      printc("\r # Temp Alarm Registered\n");
    }
    else
    {
      printc("\r # Temp Alarm Not Register\n");
    }
    
    if((TempAlarm_p -> State != 0) && (TempAlarm_p -> SensorID < NO_OF_TEMP_SENSORS) && (TempAlarm_p -> AlarmID != NO_ALARM_ID))
    {
      CONTROL(!Set_State_Temp_Alarm(TempAlarm_p -> SensorID, TempAlarm_p -> AlarmID, TempAlarm_p -> State), TEMP_ALARM_SET_STATE_ERROR);
      printc("\r # Temp Alarm state set\n");
    }
    else
    {
      printc("\r # Temp Alarm state not set\n");
    }
  }
  
  RETURN_SUCCESS();
}


// Debug Commands
/*******************************************************************************
* 
*******************************************************************************/
Status_t Display_Dump_Command(uint8 NoOfCommand)
{
  Function_IN(DISPLAY_DUMP_COMMAND);
  
  Console_Display_Dump();
  
  RETURN_SUCCESS_FUNC(DISPLAY_DUMP_COMMAND);
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Display_Update_Command(uint8 NoOfCommand, uint8 UpdateFlag)
{
  Function_IN(DISPLAY_UPDATE_COMMAND);
  
  Console_Display_Update_Set(UpdateFlag);
  
  RETURN_SUCCESS_FUNC(DISPLAY_UPDATE_COMMAND);
}
