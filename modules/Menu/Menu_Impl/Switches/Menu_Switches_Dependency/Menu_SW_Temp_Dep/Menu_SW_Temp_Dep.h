#ifndef _Menu_SW_Temp_Dep_h
#define _Menu_SW_Temp_Dep_h

Status_t Menu_Temp_Dep_Set_Temp_Name(void);
Status_t Menu_Temp_Dep_Set_Temp_1(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Temp_Dep_Set_Temp_2(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Temp_Dep_Temp_State(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Temp_Dep_Temp_Response(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Temp_Dep_Set_Temp(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Temp_Dep_Set_Sensor(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Temp_Dep_Set_Event(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);

extern uint8 SetTempFlag;
extern char Temp_1_Name[SWITCHES_SET_STRING_LENGTH];
extern char Temp_2_Name[SWITCHES_SET_STRING_LENGTH];
extern char Temp_State_Name[SWITCHES_SET_STRING_LENGTH];
extern char Temp_Response_Name[SWITCHES_SET_STRING_LENGTH];
extern char Set_Temp_Name[SWITCHES_SET_STRING_LENGTH];
extern char Set_Sensor_Name[SWITCHES_SET_STRING_LENGTH];
#endif // _Menu_SW_Temp_Dep_h