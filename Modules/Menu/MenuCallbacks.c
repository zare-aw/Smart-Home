#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Menu_Func.h"
#include "Menu_Debug.h"
#include "TSOP1738.h"
#include "Console.h"
#include "Menu.h"
#include "Menu_KeyMap.h"

#include "Out.h"


/*******************************************************************************
* 
*******************************************************************************/
Status_t Power_Key_Callback(void *p)
{
  FuncIN(POWER_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Power key callback called !\n"));
  
  VERIFY(Menu(POWER_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(POWER_KEY_CALLBACK);
}
FUNC_REGISTER(POWER_KEY_CALLBACK, Power_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Up_Key_Callback(void *p)
{
  FuncIN(UP_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Up key callback called !\n"));
  
  VERIFY(Menu(UP_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(UP_KEY_CALLBACK);
}
FUNC_REGISTER(UP_KEY_CALLBACK, Up_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Down_Key_Callback(void *p)
{
  FuncIN(DOWN_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Down key callback called !\n"));
  
  VERIFY(Menu(DOWN_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(DOWN_KEY_CALLBACK);
}
FUNC_REGISTER(DOWN_KEY_CALLBACK, Down_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Left_Key_Callback(void *p)
{
  FuncIN(LEFT_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Left key callback called !\n"));
  
  VERIFY(Menu(LEFT_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(LEFT_KEY_CALLBACK);
}
FUNC_REGISTER(LEFT_KEY_CALLBACK, Left_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Right_Key_Callback(void *p)
{
  FuncIN(RIGHT_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Right key callback called !\n"));
  
  VERIFY(Menu(RIGHT_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(RIGHT_KEY_CALLBACK);
}
FUNC_REGISTER(RIGHT_KEY_CALLBACK, Right_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Enter_Key_Callback(void *p)
{
  FuncIN(ENTER_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Enter key callback called !\n"));
  
  VERIFY(Menu(ENTER_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(ENTER_KEY_CALLBACK);
}
FUNC_REGISTER(ENTER_KEY_CALLBACK, Enter_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Cancel_Key_Callback(void *p)
{
  FuncIN(CANCEL_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Cancel key callback called !\n"));
  
  VERIFY(Menu(CANCEL_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(CANCEL_KEY_CALLBACK);
}
FUNC_REGISTER(CANCEL_KEY_CALLBACK, Cancel_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Menu_Key_Callback(void *p)
{
  FuncIN(MENU_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Menu key callback called !\n"));
  
  VERIFY(Menu(MENU_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(MENU_KEY_CALLBACK);
}
FUNC_REGISTER(MENU_KEY_CALLBACK, Menu_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Exit_Key_Callback(void *p)
{
  FuncIN(EXIT_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Exit key callback called !\n"));
  
  VERIFY(Menu(EXIT_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(EXIT_KEY_CALLBACK);
}
FUNC_REGISTER(EXIT_KEY_CALLBACK, Exit_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num1_Key_Callback(void *p)
{
  FuncIN(NUM1_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Num1 key callback called !\n"));
  
  VERIFY(Menu(NUM1_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(NUM1_KEY_CALLBACK);
}
FUNC_REGISTER(NUM1_KEY_CALLBACK, Num1_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num2_Key_Callback(void *p)
{
  FuncIN(NUM2_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Num2 key callback called !\n"));
  
  VERIFY(Menu(NUM2_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(NUM2_KEY_CALLBACK);
}
FUNC_REGISTER(NUM2_KEY_CALLBACK, Num2_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num3_Key_Callback(void *p)
{
  FuncIN(NUM3_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Num3 key callback called !\n"));
  
  VERIFY(Menu(NUM3_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(NUM3_KEY_CALLBACK);
}
FUNC_REGISTER(NUM3_KEY_CALLBACK, Num3_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num4_Key_Callback(void *p)
{
  FuncIN(NUM4_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Num4 key callback called !\n"));
  
  VERIFY(Menu(NUM4_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(NUM4_KEY_CALLBACK);
}
FUNC_REGISTER(NUM4_KEY_CALLBACK, Num4_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num5_Key_Callback(void *p)
{
  FuncIN(NUM5_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Num5 key callback called !\n"));
  
  VERIFY(Menu(NUM5_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(NUM5_KEY_CALLBACK);
}
FUNC_REGISTER(NUM5_KEY_CALLBACK, Num5_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num6_Key_Callback(void *p)
{
  FuncIN(NUM6_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Num6 key callback called !\n"));
  
  VERIFY(Menu(NUM6_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(NUM6_KEY_CALLBACK);
}
FUNC_REGISTER(NUM6_KEY_CALLBACK, Num6_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num7_Key_Callback(void *p)
{
  FuncIN(NUM7_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Num7 key callback called !\n"));
  
  VERIFY(Menu(NUM7_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(NUM7_KEY_CALLBACK);
}
FUNC_REGISTER(NUM7_KEY_CALLBACK, Num7_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num8_Key_Callback(void *p)
{
  FuncIN(NUM8_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Num8 key callback called !\n"));
  
  VERIFY(Menu(NUM8_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(NUM8_KEY_CALLBACK);
}
FUNC_REGISTER(NUM8_KEY_CALLBACK, Num8_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num9_Key_Callback(void *p)
{
  FuncIN(NUM9_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Num9 key callback called !\n"));
  
  VERIFY(Menu(NUM9_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(NUM9_KEY_CALLBACK);
}
FUNC_REGISTER(NUM9_KEY_CALLBACK, Num9_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num0_Key_Callback(void *p)
{
  FuncIN(NUM0_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Num0 key callback called !\n"));
  
  VERIFY(Menu(NUM0_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(NUM0_KEY_CALLBACK);
}
FUNC_REGISTER(NUM0_KEY_CALLBACK, Num0_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Vol_Up_Key_Callback(void *p)
{
  FuncIN(VOL_UP_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Vol-Up key callback called !\n"));
  
  VERIFY(Menu(VOL_UP_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(VOL_UP_KEY_CALLBACK);
}
FUNC_REGISTER(VOL_UP_KEY_CALLBACK, Vol_Up_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Vol_Down_Key_Callback(void *p)
{
  FuncIN(VOL_DOWN_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Vol-Down key callback called !\n"));
  
  VERIFY(Menu(VOL_DOWN_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(VOL_DOWN_KEY_CALLBACK);
}
FUNC_REGISTER(VOL_DOWN_KEY_CALLBACK, Vol_Down_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Ch_Up_Key_Callback(void *p)
{
  FuncIN(CH_UP_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Ch-Up key callback called !\n"));
  
  VERIFY(Menu(CH_UP_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(CH_UP_KEY_CALLBACK);
}
FUNC_REGISTER(CH_UP_KEY_CALLBACK, Ch_Up_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Ch_Down_Key_Callback(void *p)
{
  FuncIN(CH_DOWN_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Ch-Down key callback called !\n"));
  
  VERIFY(Menu(CH_DOWN_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(CH_DOWN_KEY_CALLBACK);
}
FUNC_REGISTER(CH_DOWN_KEY_CALLBACK, Ch_Down_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Mute_Key_Callback(void *p)
{
  FuncIN(MUTE_KEY_CALLBACK);
  
  MENU_DEBUG(printc("\r # Mute key callback called !\n"));
  
  VERIFY(Menu(MUTE_KEY_EVENT), -MENU_ERROR);
  
  EXIT_SUCCESS_FUNC(MUTE_KEY_CALLBACK);
}
FUNC_REGISTER(MUTE_KEY_CALLBACK, Mute_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
Status_t Menu_Callbacks_Init(uint8 DisplayType, uint16 Xres, uint16 Yres)
{
  FuncIN(MENU_CALLBACKS_INIT);
  
  ir_t ir_s;
  
  ir_s.Address = POWER_KEY_ADDRESS;
  ir_s.Command = POWER_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Power_Key_Callback;
  VERIFY(IR_Command_Init(POWER_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = UP_KEY_ADDRESS;
  ir_s.Command = UP_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Up_Key_Callback;
  VERIFY(IR_Command_Init(UP_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = DOWN_KEY_ADDRESS;
  ir_s.Command = DOWN_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Down_Key_Callback;
  VERIFY(IR_Command_Init(DOWN_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = LEFT_KEY_ADDRESS;
  ir_s.Command = LEFT_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Left_Key_Callback;
  VERIFY(IR_Command_Init(LEFT_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = RIGHT_KEY_ADDRESS;
  ir_s.Command = RIGHT_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Right_Key_Callback;
  VERIFY(IR_Command_Init(RIGHT_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = ENTER_KEY_ADDRESS;
  ir_s.Command = ENTER_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Enter_Key_Callback;
  VERIFY(IR_Command_Init(ENTER_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = CANCEL_KEY_ADDRESS;
  ir_s.Command = CANCEL_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Cancel_Key_Callback;
  VERIFY(IR_Command_Init(CANCEL_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = MENU_KEY_ADDRESS;
  ir_s.Command = MENU_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Menu_Key_Callback;
  VERIFY(IR_Command_Init(MENU_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = EXIT_KEY_ADDRESS;
  ir_s.Command = EXIT_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Exit_Key_Callback;
  VERIFY(IR_Command_Init(EXIT_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NUM_1_KEY_ADDRESS;
  ir_s.Command = NUM_1_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num1_Key_Callback;
  VERIFY(IR_Command_Init(NUM1_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NUM_2_KEY_ADDRESS;
  ir_s.Command = NUM_2_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num2_Key_Callback;
  VERIFY(IR_Command_Init(NUM2_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NUM_3_KEY_ADDRESS;
  ir_s.Command = NUM_3_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num3_Key_Callback;
  VERIFY(IR_Command_Init(NUM3_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NUM_4_KEY_ADDRESS;
  ir_s.Command = NUM_4_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num4_Key_Callback;
  VERIFY(IR_Command_Init(NUM4_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NUM_5_KEY_ADDRESS;
  ir_s.Command = NUM_5_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num5_Key_Callback;
  VERIFY(IR_Command_Init(NUM5_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NUM_6_KEY_ADDRESS;
  ir_s.Command = NUM_6_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num6_Key_Callback;
  VERIFY(IR_Command_Init(NUM6_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NUM_7_KEY_ADDRESS;
  ir_s.Command = NUM_7_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num7_Key_Callback;
  VERIFY(IR_Command_Init(NUM7_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NUM_8_KEY_ADDRESS;
  ir_s.Command = NUM_8_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num8_Key_Callback;
  VERIFY(IR_Command_Init(NUM8_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NUM_9_KEY_ADDRESS;
  ir_s.Command = NUM_9_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num9_Key_Callback;
  VERIFY(IR_Command_Init(NUM9_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NUM_0_KEY_ADDRESS;
  ir_s.Command = NUM_0_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num0_Key_Callback;
  VERIFY(IR_Command_Init(NUM0_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = VOL_UP_KEY_ADDRESS;
  ir_s.Command = VOL_UP_KEY_COMMAND;
  ir_s.CallMode = REPETITIVE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Vol_Up_Key_Callback;
  VERIFY(IR_Command_Init(VOL_UP_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = VOL_DOWN_KEY_ADDRESS;
  ir_s.Command = VOL_DOWN_KEY_COMMAND;
  ir_s.CallMode = REPETITIVE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Vol_Down_Key_Callback;
  VERIFY(IR_Command_Init(VOL_DOWN_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = CH_UP_KEY_ADDRESS;
  ir_s.Command = CH_UP_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Ch_Up_Key_Callback;
  VERIFY(IR_Command_Init(CH_UP_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = CH_DOWN_KEY_ADDRESS;
  ir_s.Command = CH_DOWN_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Ch_Down_Key_Callback;
  VERIFY(IR_Command_Init(CH_DOWN_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = MUTE_KEY_ADDRESS;
  ir_s.Command = MUTE_KEY_COMMAND;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Mute_Key_Callback;
  VERIFY(IR_Command_Init(MUTE_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = 8;
  ir_s.Command = 43;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Out_1_Toggle;
  VERIFY(IR_Command_Init(51, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = 8;
  ir_s.Command = 44;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Out_2_Toggle;
  VERIFY(IR_Command_Init(52, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = 8;
  ir_s.Command = 45;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Out_3_Toggle;
  VERIFY(IR_Command_Init(53, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = 8;
  ir_s.Command = 46;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Out_4_Toggle;
  VERIFY(IR_Command_Init(54, &ir_s), IR_COMMAND_INIT_ERROR);
  
  EXIT_SUCCESS_FUNC(MENU_CALLBACKS_INIT);
}
FUNC_REGISTER(MENU_CALLBACKS_INIT, Menu_Callbacks_Init);
