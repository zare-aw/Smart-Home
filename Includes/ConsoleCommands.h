#ifndef _ConsoleCommands_h
#define _ConsoleCommands_h

#define ALL_TEMP_ALARMS     255

#define IR_DUMMY_ID         1
#define IR_OUT_1_SET        2
#define IR_OUT_2_SET        3
#define IR_OUT_3_SET        4
#define IR_OUT_4_SET        5
#define IR_OUT_5_SET        6
#define IR_OUT_6_SET        7
#define IR_OUT_1_CLR        8
#define IR_OUT_2_CLR        9
#define IR_OUT_3_CLR        10
#define IR_OUT_4_CLR        11
#define IR_OUT_5_CLR        12
#define IR_OUT_6_CLR        13
#define IR_OUT_1_TOGGLE     14
#define IR_OUT_2_TOGGLE     15
#define IR_OUT_3_TOGGLE     16
#define IR_OUT_4_TOGGLE     17
#define IR_OUT_5_TOGGLE     18
#define IR_OUT_6_TOGGLE     19
#define IR_SOUND_ALARM_ID   20


// Function
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
Status_t Console_Update_Display(uint8 NoOfCommand);
#endif