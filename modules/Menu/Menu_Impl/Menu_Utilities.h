#ifndef _Menu_Utilities_h
#define _Menu_Utilities_h

#define NO_OF_DAYS 7
#define MAX_DAY_STRING_LENGTH 10

extern uint16 Year;
extern uint8 Month;
extern uint8 Day;
extern uint8 Hour;
extern uint8 Minute;
extern uint8 Second;

extern uint8 PointerPosition;

Status_t Menu_Time_Update_Disp_Ptr_Pos(void);
Status_t Menu_Update_Disp_Ptr_Pos(void);
Status_t Menu_Time_Increment_Ptr_Pos_Number(void);
Status_t Menu_Time_Decrement_Ptr_Pos_Number(void);
Status_t Menu_Time_Set_Ptr_Pos_Number(uint32 Number);
Status_t Menu_Date_Update_Disp_Ptr_Pos(void);
Status_t Menu_Date_Increment_Ptr_Pos_Number(void);
Status_t Menu_Date_Decrement_Ptr_Pos_Number(void);
Status_t Menu_Date_Set_Ptr_Pos_Number(uint32 Number);
Status_t Menu_Repeat_Update_Display(uint8 Offset, const uint32 Menu_Ptr_Pos, uint8 Repeat);

#endif // _Menu_Utilities_h