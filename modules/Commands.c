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
Status_t Set_IR_Commands_Command(uint8 NoOfCommand, uint16 NoOfIRCommand, uint8 Address, uint8 Command)
{
  Function_IN(SET_IR_COMMANDS_COMMAND);

  if((Address == NULL) && (Command == NULL))
  {
    CONTROL(!IR_Set_Command(NoOfIRCommand), IR_COMMAND_SET_ERROR);
    printc("\r # Waiting for Command from IR\n");
  }
  else
  {
    CONTROL(!IR_Command_Init(NoOfIRCommand, Address, Command, NULL, NULL, NULL), IR_COMMAND_SET_ERROR);
    printc("\r # IR Command Set with parameters:\n");
    printc(" # NoOfCommand = %u\tAddress = %u\tCommand = %u\n", NoOfIRCommand, Address, Command);
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
  
  printc(" # Get Out Switch Command Executed \n");
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Set_Out_Switch_Command(uint8 NoOfCommand)
{
  Function_IN(SET_OUT_SWITCH_COMMAND);
  
  printc(" # Set Out Switch Command Executed \n");
  
  RETURN_SUCCESS();
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
* @in Chanel - Broj na kanal od koj ja sakame temperaturata
*******************************************************************************/
Status_t Get_Temp_Command(uint8 NoOfCommand, uint8 Chanel)
{
  Function_IN(GET_TEMP_COMMAND);
  
  int Temp;
  Status_t StatusReturn = GENERAL_ERROR;
  
  StatusReturn = DS1820_Start_Conversion(1, NULL);
  CONTROL(StatusReturn == SUCCESS, StatusReturn);
  Dly(750, 'm', NULL);
  StatusReturn = DS1820_Read_Temp(&Temp, 1, NULL);
  CONTROL(StatusReturn == SUCCESS, StatusReturn);
  printc("\r # Temp = %d\n", Temp);
  
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
