#include "Includes.h"


/*******************************************************************************
* 
*******************************************************************************/
Status_t Menu_Callbacks_Init(uint8 DisplayType, uint16 Xres, uint16 Yres)
{
  Function_IN(MENU_CALLBACKS_INIT);
  
  ir_t ir_s;
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Power_Key_Callback;
  CONTROL(!IR_Command_Init(POWER_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Up_Key_Callback;
  CONTROL(!IR_Command_Init(UP_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Down_Key_Callback;
  CONTROL(!IR_Command_Init(DOWN_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Left_Key_Callback;
  CONTROL(!IR_Command_Init(LEFT_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Right_Key_Callback;
  CONTROL(!IR_Command_Init(RIGHT_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Enter_Key_Callback;
  CONTROL(!IR_Command_Init(ENTER_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Cancel_Key_Callback;
  CONTROL(!IR_Command_Init(CANCEL_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Menu_Key_Callback;
  CONTROL(!IR_Command_Init(MENU_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Exit_Key_Callback;
  CONTROL(!IR_Command_Init(EXIT_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num1_Key_Callback;
  CONTROL(!IR_Command_Init(NUM1_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num2_Key_Callback;
  CONTROL(!IR_Command_Init(NUM2_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num3_Key_Callback;
  CONTROL(!IR_Command_Init(NUM3_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num4_Key_Callback;
  CONTROL(!IR_Command_Init(NUM4_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num5_Key_Callback;
  CONTROL(!IR_Command_Init(NUM5_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num6_Key_Callback;
  CONTROL(!IR_Command_Init(NUM6_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num7_Key_Callback;
  CONTROL(!IR_Command_Init(NUM7_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num8_Key_Callback;
  CONTROL(!IR_Command_Init(NUM8_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num9_Key_Callback;
  CONTROL(!IR_Command_Init(NUM9_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Num0_Key_Callback;
  CONTROL(!IR_Command_Init(NUM0_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = REPETITIVE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Vol_Up_Key_Callback;
  CONTROL(!IR_Command_Init(VOL_UP_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = REPETITIVE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Vol_Down_Key_Callback;
  CONTROL(!IR_Command_Init(VOL_DOWN_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Ch_Up_Key_Callback;
  CONTROL(!IR_Command_Init(CH_UP_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Ch_Down_Key_Callback;
  CONTROL(!IR_Command_Init(CH_DOWN_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Mute_Key_Callback;
  CONTROL(!IR_Command_Init(MUTE_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Power_Key_Callback(void *p)
{
  Function_IN(POWER_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Power key callback called !\n"));
  
  CONTROL(Menu(POWER_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Up_Key_Callback(void *p)
{
  Function_IN(UP_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Up key callback called !\n"));
  
  CONTROL(Menu(UP_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Down_Key_Callback(void *p)
{
  Function_IN(DOWN_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Down key callback called !\n"));
  
  CONTROL(Menu(DOWN_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Left_Key_Callback(void *p)
{
  Function_IN(LEFT_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Left key callback called !\n"));
  
  CONTROL(Menu(LEFT_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Right_Key_Callback(void *p)
{
  Function_IN(RIGHT_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Right key callback called !\n"));
  
  CONTROL(Menu(RIGHT_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Enter_Key_Callback(void *p)
{
  Function_IN(ENTER_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Enter key callback called !\n"));
  
  CONTROL(Menu(ENTER_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Cancel_Key_Callback(void *p)
{
  Function_IN(CANCEL_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Cancel key callback called !\n"));
  
  CONTROL(Menu(CANCEL_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Menu_Key_Callback(void *p)
{
  Function_IN(MENU_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Menu key callback called !\n"));
  
  CONTROL(Menu(MENU_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Exit_Key_Callback(void *p)
{
  Function_IN(EXIT_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Exit key callback called !\n"));
  
  CONTROL(Menu(EXIT_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num1_Key_Callback(void *p)
{
  Function_IN(NUM1_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num1 key callback called !\n"));
  
  CONTROL(Menu(NUM1_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num2_Key_Callback(void *p)
{
  Function_IN(NUM2_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num2 key callback called !\n"));
  
  CONTROL(Menu(NUM2_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num3_Key_Callback(void *p)
{
  Function_IN(NUM3_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num3 key callback called !\n"));
  
  CONTROL(Menu(NUM3_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num4_Key_Callback(void *p)
{
  Function_IN(NUM4_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num4 key callback called !\n"));
  
  CONTROL(Menu(NUM4_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num5_Key_Callback(void *p)
{
  Function_IN(NUM5_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num5 key callback called !\n"));
  
  CONTROL(Menu(NUM5_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num6_Key_Callback(void *p)
{
  Function_IN(NUM6_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num6 key callback called !\n"));
  
  CONTROL(Menu(NUM6_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num7_Key_Callback(void *p)
{
  Function_IN(NUM7_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num7 key callback called !\n"));
  
  CONTROL(Menu(NUM7_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num8_Key_Callback(void *p)
{
  Function_IN(NUM8_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num8 key callback called !\n"));
  
  CONTROL(Menu(NUM8_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num9_Key_Callback(void *p)
{
  Function_IN(NUM9_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num9 key callback called !\n"));
  
  CONTROL(Menu(NUM9_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num0_Key_Callback(void *p)
{
  Function_IN(NUM0_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num0 key callback called !\n"));
  
  CONTROL(Menu(NUM0_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Vol_Up_Key_Callback(void *p)
{
  Function_IN(VOL_UP_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Vol-Up key callback called !\n"));
  
  CONTROL(Menu(VOL_UP_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Vol_Down_Key_Callback(void *p)
{
  Function_IN(VOL_DOWN_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Vol-Down key callback called !\n"));
  
  CONTROL(Menu(VOL_DOWN_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Ch_Up_Key_Callback(void *p)
{
  Function_IN(CH_UP_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Ch-Up key callback called !\n"));
  
  CONTROL(Menu(CH_UP_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Ch_Down_Key_Callback(void *p)
{
  Function_IN(CH_DOWN_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Ch-Down key callback called !\n"));
  
  CONTROL(Menu(CH_DOWN_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Mute_Key_Callback(void *p)
{
  Function_IN(MUTE_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Mute key callback called !\n"));
  
  CONTROL(Menu(MUTE_KEY_EVENT), MENU_ERROR);
  
  RETURN_SUCCESS();
}
