#ifndef _ConsoleCommands_h
#define _ConsoleCommands_h

#define ALL_TEMP_ALARMS     255

Status_t Console_Status(uint8 NoOfCommand);
Status_t Console_List(uint8 NoOfCommand);
Status_t Console_Info(uint8 NoOfCommand);
Status_t Console_Time(uint8 NoOfCommand);
Status_t Console_Date(uint8 NoOfCommand);
Status_t Console_Set_Time(uint8 NoOfCommand);
Status_t Console_Set_Date(uint8 NoOfCommand);
Status_t Console_Config(uint8 NoOfCommand);
Status_t Console_Set_Config(uint8 NoOfCommand);
Status_t Console_Ir(uint8 NoOfCommand);
Status_t Console_Set_Ir(uint8 NoOfCommand);
Status_t Console_Becklight(uint8 NoOfCommand);
Status_t Console_Set_Becklight(uint8 NoOfCommand);
Status_t Console_Light_Switch(uint8 NoOfCommand);
Status_t Console_Set_Light_Switch(uint8 NoOfCommand);
Status_t Console_Out_Switch(uint8 NoOfCommand);
Status_t Console_Set_Out_Switch(uint8 NoOfCommand);
Status_t Console_Switch_Settings(uint8 NoOfCommand);
Status_t Console_Set_Switch_Settings(uint8 NoOfCommand);
Status_t Console_Temp(uint8 NoOfCommand);
Status_t Console_Alarm(uint8 NoOfCommand);
Status_t Console_Set_Alarm(uint8 NoOfCommand);
Status_t Console_Get_Temp_Alarm(uint8 NoOfCommand);
Status_t Console_Set_Temp_Alarm(uint8 NoOfCommand);

// Debug commands
Status_t Console_Dump_Display(uint8 NoOfCommand);
#endif