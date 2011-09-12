#include "Includes.h"


/*******************************************************************************
* 
*******************************************************************************/
Status_t Menu_Callbacks_Init(uint8 DisplayType, uint16 Xres, uint16 Yres)
{
  Function_IN(MENU_CALLBACKS_INIT);
  
  CONTROL(!IR_Command_Init(POWER_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Power_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(UP_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Up_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(DOWN_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Down_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(LEFT_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Left_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(RIGHT_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Right_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(ENTER_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Enter_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(CANCEL_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Cancel_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(MENU_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Menu_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(EXIT_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Exit_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(NUM1_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Num1_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(NUM2_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Num2_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(NUM3_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Num3_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(NUM4_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Num4_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(NUM5_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Num5_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(NUM6_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Num6_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(NUM7_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Num7_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(NUM8_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Num8_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(NUM9_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Num9_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(NUM0_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Num0_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(VOL_UP_KEY, NULL, NULL, REPETITIVE_CALL, 0, (void*)Vol_Up_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(VOL_DOWN_KEY, NULL, NULL, REPETITIVE_CALL, 0, (void*)Vol_Down_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(CH_UP_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Ch_Up_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(CH_DOWN_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Ch_Down_Key_Callback), IR_COMMAND_INIT_ERROR);
  CONTROL(!IR_Command_Init(MUTE_KEY, NULL, NULL, SINGLE_CALL, 0, (void*)Mute_Key_Callback), IR_COMMAND_INIT_ERROR);
  
  
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Power_Key_Callback(void *p)
{
  Function_IN(POWER_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Power key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Up_Key_Callback(void *p)
{
  Function_IN(UP_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Up key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Down_Key_Callback(void *p)
{
  Function_IN(DOWN_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Down key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Left_Key_Callback(void *p)
{
  Function_IN(LEFT_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Left key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Right_Key_Callback(void *p)
{
  Function_IN(RIGHT_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Right key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Enter_Key_Callback(void *p)
{
  Function_IN(ENTER_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Enter key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Cancel_Key_Callback(void *p)
{
  Function_IN(CANCEL_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Cancel key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Menu_Key_Callback(void *p)
{
  Function_IN(MENU_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Menu key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Exit_Key_Callback(void *p)
{
  Function_IN(EXIT_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Exit key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num1_Key_Callback(void *p)
{
  Function_IN(NUM1_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num1 key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num2_Key_Callback(void *p)
{
  Function_IN(NUM2_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num2 key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num3_Key_Callback(void *p)
{
  Function_IN(NUM3_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num3 key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num4_Key_Callback(void *p)
{
  Function_IN(NUM4_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num4 key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num5_Key_Callback(void *p)
{
  Function_IN(NUM5_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num5 key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num6_Key_Callback(void *p)
{
  Function_IN(NUM6_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num6 key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num7_Key_Callback(void *p)
{
  Function_IN(NUM7_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num7 key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num8_Key_Callback(void *p)
{
  Function_IN(NUM8_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num8 key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num9_Key_Callback(void *p)
{
  Function_IN(NUM9_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num9 key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Num0_Key_Callback(void *p)
{
  Function_IN(NUM0_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Num0 key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Vol_Up_Key_Callback(void *p)
{
  Function_IN(VOL_UP_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Vol-Up key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Vol_Down_Key_Callback(void *p)
{
  Function_IN(VOL_DOWN_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Vol-Down key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Ch_Up_Key_Callback(void *p)
{
  Function_IN(CH_UP_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Ch-Up key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Ch_Down_Key_Callback(void *p)
{
  Function_IN(CH_DOWN_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Ch-Down key callback called !\n"));
  
  RETURN_SUCCESS();
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Mute_Key_Callback(void *p)
{
  Function_IN(MUTE_KEY_CALLBACK);
  MENU_DEBUG(printc("\r # Mute key callback called !\n"));
  
  RETURN_SUCCESS();
}
