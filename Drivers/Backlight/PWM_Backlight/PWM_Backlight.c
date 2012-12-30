#include "Global_Defines.h"
#include "StatusHandling.h"
#include "Console.h"

#include "PWM.h"
#include "PWM_Backlight.h"
#include "PWM_Backlight_Defconfig.h"
#include "PWM_Backlight_Debug.h"
#include "PWM_Backlight_Func.h"

#include "TSOP1738.h"

/**** Function definitions ****/
static Status_t Ch_Up_Key_Callback(void *p);
static Status_t Ch_Down_Key_Callback(void *p);

/*******************************************************************************
 * Function Name: PWM_Backlight_Init
 * @in: uint16 StartIntensity - Backlight Intensity upon initialization
 * @out: Status_t
 * Description: Set default backlight
 ******************************************************************************/
Status_t PWM_Backlight_Init(uint16 StartIntensity)
{
  FuncIN(PWM_BACKLIGHT_INIT);

  PwmOutD_t BacklightStartIntensity = {0};
  ir_t ir_s;

  BacklightStartIntensity.Out5D = StartIntensity;

  Pwm_Init(SINGLE_EDGE_CONTROL, BACKLIGHT_FREQ, BACKLIGHT_OUT, &BacklightStartIntensity);

  BL_DEBUG(printc("\r # Backlight Initialized with Initial Intensity = %d\n", StartIntensity));
  
  ir_s.Address = CH_UP_KEY_ADDRESS;
  ir_s.Command = CH_UP_KEY_COMMAND;
  ir_s.CallMode = REPETITIVE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Ch_Up_Key_Callback;
  VERIFY(IR_Command_Init(CH_UP_KEY, &ir_s), IR_COMMAND_INIT_ERROR);
  
  ir_s.Address = CH_DOWN_KEY_ADDRESS;
  ir_s.Command = CH_DOWN_KEY_COMMAND;
  ir_s.CallMode = REPETITIVE_CALL;
  ir_s.Target = 0;
  ir_s.Callback_p = Ch_Down_Key_Callback;
  VERIFY(IR_Command_Init(CH_DOWN_KEY, &ir_s), IR_COMMAND_INIT_ERROR);

  EXIT_SUCCESS_FUNC(PWM_BACKLIGHT_INIT);
}
FUNC_REGISTER(PWM_BACKLIGHT_INIT, Backlight_Init);

/*******************************************************************************
 * Function Name: Set_PWM_Backlight_Intensity
 * @in: uint16 SetIntensity - Set the desired Intensity
 * @out: Status_t
 * Description: Set Intensity
 ******************************************************************************/
Status_t Set_PWM_Backlight_Intensity(uint16 Intensity)
{
  FuncIN(SET_PWM_BACKLIGHT_INTENSITY);

  Pwm_Set_Duty_Cycle(BACKLIGHT_OUT_NUMBER, Intensity);

  BL_DEBUG(printc("\r # Backlight: Set new Intensity = %d\n", Intensity));

  EXIT_SUCCESS_FUNC(SET_PWM_BACKLIGHT_INTENSITY);
}
FUNC_REGISTER(SET_PWM_BACKLIGHT_INTENSITY, Set_Backlight_Intensity);

/*******************************************************************************
 * Function Name: Get_PWM_Backlight_Intensity
 * @out: uint16 *Intensity - Get the desired Intensity
 * @out: Status_t
 * Description: Get Intensity
 ******************************************************************************/
Status_t Get_PWM_Backlight_Intensity(uint16 *Intensity)
{
  FuncIN(GET_PWM_BACKLIGHT_INTENSITY);
  
  Pwm_Get_Duty_Cycle(BACKLIGHT_OUT_NUMBER, Intensity);
  
  EXIT_SUCCESS_FUNC(GET_PWM_BACKLIGHT_INTENSITY);
}
FUNC_REGISTER(GET_PWM_BACKLIGHT_INTENSITY, Get_Backlight_Intensity);

/*******************************************************************************
 * Function Name: Change_PWM_Backlight_Intensity
 * @in: Direction - BL_INCREASE or BL_DECREASE
 * @in: Value - Change Value
 * @out: Status_t
 * Description: Change the backlight intensity (increase or decrease)
 *              for input Value
 ******************************************************************************/
static Status_t Change_PWM_Backlight_Intensity(uint8 Direction, uint16 Value)
{
  FuncIN(CHANGE_PWM_BACKLIGHT_INTENSITY);
  uint16 Intensity;
  sint16 SetIntensity;
  
  Pwm_Get_Duty_Cycle(BACKLIGHT_OUT_NUMBER, &Intensity);
  
  switch(Direction)
  {
    case BL_INCREASE:
      SetIntensity = Intensity + Value;
      if(SetIntensity < 1020)
        Set_PWM_Backlight_Intensity(SetIntensity);
      else
        Set_PWM_Backlight_Intensity(1020);
      break;
    case BL_DECREASE:
      SetIntensity = Intensity - Value;
      if(SetIntensity > 0)
        Set_PWM_Backlight_Intensity(SetIntensity);
      else
        Set_PWM_Backlight_Intensity(0);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  EXIT_SUCCESS_FUNC(CHANGE_PWM_BACKLIGHT_INTENSITY);
}
FUNC_REGISTER(CHANGE_PWM_BACKLIGHT_INTENSITY, Change_PWM_Backlight_Intensity);

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Ch_Up_Key_Callback(void *p)
{
  FuncIN(CH_UP_KEY_CALLBACK);
  
  BL_DEBUG_L1(printc("\r # Ch-Up key callback called !\n"));
  
  Change_PWM_Backlight_Intensity(BL_INCREASE, BACKLIGHT_CHANGE_JUMP_VALUE);
  
  EXIT_SUCCESS_FUNC(CH_UP_KEY_CALLBACK);
}
FUNC_REGISTER(CH_UP_KEY_CALLBACK, Ch_Up_Key_Callback);

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Ch_Down_Key_Callback(void *p)
{
  FuncIN(CH_DOWN_KEY_CALLBACK);
  
  BL_DEBUG_L1(printc("\r # Ch-Down key callback called !\n"));
  
  Change_PWM_Backlight_Intensity(BL_DECREASE, BACKLIGHT_CHANGE_JUMP_VALUE);
  
  EXIT_SUCCESS_FUNC(CH_DOWN_KEY_CALLBACK);
}
FUNC_REGISTER(CH_DOWN_KEY_CALLBACK, Ch_Down_Key_Callback);