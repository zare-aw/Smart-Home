#ifndef _Menu_SW_Time_Dep_h
#define _Menu_SW_Time_Dep_h

Status_t Menu_Time_Dep_Set_Time_Name(void);
Status_t Menu_Time_Dep_Set_Time_Response_Name(void);
Status_t Menu_Time_Dep_Set_Time_State_Name(void);
Status_t Menu_Time_Dep_Setting_Time_Name(void);
Status_t Menu_Time_Dep_Set_Time_1(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Time_Dep_Set_Time_2(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Time_Dep_Date(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Time_Dep_Time_Response(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Time_Dep_Time_State(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Time_Dep_Set_Time(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Time_Dep_Date_Set_Date(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);
Status_t Menu_Time_Dep_Date_Set_Repeat(struct Menu_State_s *Menu_State_p, const uint32 Key, void *Ptr);

extern uint8 SetTimeFlag;
extern char Time_1_Name[SWITCHES_SET_STRING_LENGTH];
extern char Time_2_Name[SWITCHES_SET_STRING_LENGTH];
extern char Time_Response_Name[SWITCHES_SET_STRING_LENGTH];
extern char Time_State_Name[SWITCHES_SET_STRING_LENGTH];
extern char Set_Time_Name[SWITCHES_SET_STRING_LENGTH];
extern char Set_Date_Name[SWITCHES_SET_STRING_LENGTH];
extern char Set_Repeat_Name[SWITCHES_SET_STRING_LENGTH];

#endif // _Menu_SW_Time_Dep_h