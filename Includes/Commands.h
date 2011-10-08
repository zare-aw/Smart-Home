#ifndef _Commands_h
#define _Commands_h

#define IR              10
#define INPUT           11
#define CONSOLE_INPUT   20
#define IR_INPUT        21

//#define _COMMAND_DEBUG

#ifdef _COMMAND_DEBUG
#define COMMAND_DEBUG(a) a
#else
#define COMMAND_DEBUG(a)
#endif

Status_t Get_Time_Command(uint8 NoOfCommand);
Status_t Set_Time_Command(uint8 NoOfCommand, uint8 h, uint8 m, uint8 s);
Status_t Get_Date_Command(uint8 NoOfCommand);
Status_t Set_Date_Command(uint8 NoOfCommand, uint8 d, uint8 m, uint16 y);
Status_t Get_Configuration_Command(uint8 NoOfCommand);
Status_t Set_Configurations_Command(uint8 NoOfCommand);
Status_t Get_IR_Commands_Command(uint8 NoOfCommand);
Status_t Set_IR_Commands_Command(uint8 NoOfCommand, uint16 NoOfIRCommand, uint8 Address, uint8 Command);
Status_t Get_Back_Light_Level_Command(uint8 NoOfCommand);
Status_t Set_Back_Light_Level_Command(uint8 NoOfCommand, uint8 Level);
Status_t Get_Lignt_Switch_Level_Command(uint8 NoOfCommand);
Status_t Set_Lignt_Switch_Level_Command(uint8 NoOfCommand, uint8 Max, uint8 Min);
Status_t Get_Out_Switch_Command(uint8 NoOfCommand);
Status_t Set_Out_Switch_Command(uint8 NoOfCommand);
Status_t Get_Switch_Setings_Command(uint8 NoOfCommand, uint8 Chanel);
Status_t Set_Switch_Setings_Command(uint8 NoOfCommand, uint8 Chanel);
Status_t Get_Temp_Command(uint8 NoOfCommand, uint8 SensorID);
Status_t Get_Alarm_Command(uint8 NoOfCommand);
Status_t Set_Alarm_Command(uint8 NoOfCommand);
Status_t Get_Temp_Alarm_Command(uint8 NoOfCommand, uint8 ID);
Status_t Set_Temp_Alarm_Command(uint8 NoOfCommand, TempAlarm_t *TempAlarm_p);

// Debug Commands
Status_t Display_Dump_Command(uint8 NoOfCommand);
Status_t Display_Update_Command(uint8 NoOfCommand, uint8 UpdateFlag);


#endif