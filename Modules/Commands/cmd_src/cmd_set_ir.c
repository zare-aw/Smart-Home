#include <stdlib.h>
#include <string.h>
#include "Global_Defines.h"
#include "StatusHandling.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "TSOP1738.h"
#include "Out.h"

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

/*******************************************************************************
 *
 ******************************************************************************/
Status_t Do_Set_IR(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_SET_IR);

  uint16 NoOfIRCommand = NULL;
  char *CommandString = NULL;
  ir_t  ir_s;
  int i;
  
  ir_s.Address = NULL;
  ir_s.Command = NULL;
  ir_s.CallMode = SINGLE_CALL;
  ir_s.Target = IR_DUMMY_ID;
  ir_s.Callback_p = IR_Dummy_Handler;
  
  for(i = 0; i < argc; i++)
  {
    CommandString = strstr(argv[i], "n=");
    
    if(CommandString != NULL)
    {
      NoOfIRCommand = atoi(CommandString + 2);
      if(NoOfIRCommand > (MAX_IR_COMMANDS - RESERVED_IR_COMMANDS))
      {
        printcmd("\r # Invalid command number\n");
        EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SET_IR);
      }
      if(NoOfIRCommand == NULL)
      {
        CommandString += 2;
        if(!strncmp("power", CommandString, 5))
          NoOfIRCommand = POWER_KEY;
        else if(!strncmp("up", CommandString, 5))
          NoOfIRCommand = UP_KEY;
        else if(!strncmp("down", CommandString, 5))
          NoOfIRCommand = DOWN_KEY;
        else if(!strncmp("left", CommandString, 5))
          NoOfIRCommand = LEFT_KEY;
        else if(!strncmp("right", CommandString, 5))
          NoOfIRCommand = RIGHT_KEY;
        else if(!strncmp("enter", CommandString, 5))
          NoOfIRCommand = ENTER_KEY;
        else if(!strncmp("cancel", CommandString, 5))
          NoOfIRCommand = CANCEL_KEY;
        else if(!strncmp("menu", CommandString, 5))
          NoOfIRCommand = MENU_KEY;
        else if(!strncmp("exit", CommandString, 5))
          NoOfIRCommand = EXIT_KEY;
        else if(!strncmp("num1", CommandString, 5))
          NoOfIRCommand = NUM1_KEY;
        else if(!strncmp("num2", CommandString, 5))
          NoOfIRCommand = NUM2_KEY;
        else if(!strncmp("num3", CommandString, 5))
          NoOfIRCommand = NUM3_KEY;
        else if(!strncmp("num4", CommandString, 5))
          NoOfIRCommand = NUM4_KEY;
        else if(!strncmp("num5", CommandString, 5))
          NoOfIRCommand = NUM5_KEY;
        else if(!strncmp("num6", CommandString, 5))
          NoOfIRCommand = NUM6_KEY;
        else if(!strncmp("num7", CommandString, 5))
          NoOfIRCommand = NUM7_KEY;
        else if(!strncmp("num8", CommandString, 5))
          NoOfIRCommand = NUM8_KEY;
        else if(!strncmp("num9", CommandString, 5))
          NoOfIRCommand = NUM9_KEY;
        else if(!strncmp("num0", CommandString, 5))
          NoOfIRCommand = NUM0_KEY;
        else if(!strncmp("vol-up", CommandString, 5))
          NoOfIRCommand = VOL_UP_KEY;
        else if(!strncmp("vol-down", CommandString, 5))
          NoOfIRCommand = VOL_DOWN_KEY;
        else if(!strncmp("ch-up", CommandString, 5))
          NoOfIRCommand = CH_UP_KEY;
        else if(!strncmp("ch-down", CommandString, 5))
          NoOfIRCommand = CH_DOWN_KEY;
        else if(!strncmp("mute", CommandString, 5))
          NoOfIRCommand = MUTE_KEY;
        else
        {
          printcmd("\r # Invalid command number\n");
          EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SET_IR);
        }
      } // if(NoOfIRCommand == NULL)
    } // if(CommandString != NULL)
    
    CommandString = strstr(argv[i], "a=");
    if(CommandString != NULL)
      ir_s.Address = atoi(CommandString + 2);
    
    CommandString = strstr(argv[i], "c=");
    if(CommandString != NULL)
      ir_s.Command = atoi(CommandString + 2);
    
    CommandString = strstr(argv[i], "m=");
    if(CommandString != NULL)
    {
      CommandString += 2;
      
      if(!strncmp("single", CommandString, 6))
        ir_s.CallMode = SINGLE_CALL;
      else if(!strncmp("repetitive", CommandString, 10))
        ir_s.CallMode = REPETITIVE_CALL;
      else
      {
        printcmd(" # CallMode parametar is invalid\n");
        EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SET_IR);
      }
    } //  if(CommandString != NULL)
    
    CommandString = strstr(argv[i], "response=");
    if(CommandString != NULL)
    {
      CommandString += 9;
      
      if(!strncmp("out_1_ON", CommandString, 8))
      {
        ir_s.Callback_p = Out_1_Set;
        ir_s.Target = IR_OUT_1_SET;
      }
      else if(!strncmp("out_1_OFF", CommandString, 9))
      {
        ir_s.Callback_p = Out_1_Clr;
        ir_s.Target = IR_OUT_1_CLR;
      }
      else if(!strncmp("out_1_toggle", CommandString, 12))
      {
        ir_s.Callback_p = Out_1_Toggle;
        ir_s.Target = IR_OUT_1_TOGGLE;
      }
      else if(!strncmp("out_2_ON", CommandString, 8))
      {
        ir_s.Callback_p = Out_2_Set;
        ir_s.Target = IR_OUT_2_SET;
      }
      else if(!strncmp("out_2_OFF", CommandString, 9))
      {
        ir_s.Callback_p = Out_2_Clr;
        ir_s.Target = IR_OUT_2_CLR;
      }
      else if(!strncmp("out_2_toggle", CommandString, 12))
      {
        ir_s.Callback_p = Out_2_Toggle;
        ir_s.Target = IR_OUT_2_TOGGLE;
      }
      else if(!strncmp("out_3_ON", CommandString, 8))
      {
        ir_s.Callback_p = Out_3_Set;
        ir_s.Target = IR_OUT_3_SET;
      }
      else if(!strncmp("out_3_OFF", CommandString, 9))
      {
        ir_s.Callback_p = Out_3_Clr;
        ir_s.Target = IR_OUT_3_CLR;
      }
      else if(!strncmp("out_3_toggle", CommandString, 12))
      {
        ir_s.Callback_p = Out_3_Toggle;
        ir_s.Target = IR_OUT_3_TOGGLE;
      }
      else if(!strncmp("out_4_ON", CommandString, 8))
      {
        ir_s.Callback_p = Out_4_Set;
        ir_s.Target = IR_OUT_4_SET;
      }
      else if(!strncmp("out_4_OFF", CommandString, 9))
      {
        ir_s.Callback_p = Out_4_Clr;
        ir_s.Target = IR_OUT_4_CLR;
      }
      else if(!strncmp("out_4_toggle", CommandString, 12))
      {
        ir_s.Callback_p = Out_4_Toggle;
        ir_s.Target = IR_OUT_4_TOGGLE;
      }
      else if(!strncmp("out_5_ON", CommandString, 8))
      {
        ir_s.Callback_p = Out_5_Set;
        ir_s.Target = IR_OUT_5_SET;
      }
      else if(!strncmp("out_5_OFF", CommandString, 9))
      {
        ir_s.Callback_p = Out_5_Clr;
        ir_s.Target = IR_OUT_5_CLR;
      }
      else if(!strncmp("out_5_toggle", CommandString, 12))
      {
        ir_s.Callback_p = Out_5_Toggle;
        ir_s.Target = IR_OUT_5_TOGGLE;
      }
      else if(!strncmp("out_6_ON", CommandString, 8))
      {
        ir_s.Callback_p = Out_6_Set;
        ir_s.Target = IR_OUT_6_SET;
      }
      else if(!strncmp("out_6_OFF", CommandString, 9))
      {
        ir_s.Callback_p = Out_6_Clr;
        ir_s.Target = IR_OUT_6_CLR;
      }
      else if(!strncmp("out_6_toggle", CommandString, 12))
      {
        ir_s.Callback_p = Out_6_Toggle;
        ir_s.Target = IR_OUT_6_TOGGLE;
      }
      else if(!strncmp("sound_alarm", CommandString, 11))
      {
        ir_s.Callback_p = IR_Dummy_Handler;
        ir_s.Target = IR_DUMMY_ID;
      }
      else if(!strncmp("dummy", CommandString, 5))
      {
        ir_s.Callback_p = IR_Dummy_Handler;
        ir_s.Target = IR_DUMMY_ID;
      }
      else
      {
        printcmd(" # 'response' parametar is invalid\n");
        EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SET_IR);
      }
    } //  if(CommandString != NULL)
    
  } // for(i = 0; i < argc; i++)
  
  if(NoOfIRCommand == NULL)
  {
    printcmd("\r # Command number mising\n");
    EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SET_IR);
  }

  if((ir_s.Address == NULL) && (ir_s.Command == NULL))
  {
    VERIFY(IR_Command_Init(NoOfIRCommand, &ir_s), -IR_COMMAND_SET_ERROR);
    VERIFY(IR_Set_Command(NoOfIRCommand), -IR_COMMAND_SET_ERROR);
    printcmd("\r # Waiting for Command from IR\n");
  }
  else
  {
    VERIFY(IR_Command_Init(NoOfIRCommand, &ir_s), -IR_COMMAND_SET_ERROR);
    printcmd("\r # IR Command Set with parameters:\n");
    printcmd(" # NoOfCommand = %u\n", NoOfIRCommand);
    printcmd(" # Address = %u\n", ir_s.Address);
    printcmd(" # Command = %u\n", ir_s.Command);
    printcmd(" # CallMode = %u\n", ir_s.CallMode);
    printcmd(" # Target = %u\n", ir_s.Target);
    printcmd(" # Callback = %u\n", ir_s.Callback_p);
  }
  
  EXIT_SUCCESS_FUNC(DO_SET_IR);
}
FUNC_REGISTER(DO_SET_IR, Do_Set_IR);

CMD_CREATE(
  set_ir, 5, Do_Set_IR,
  "'set_ir' - Set IR command. 'set_ir n=number a=address c=command m=mode response=what_to_do'\n",
  "'n' - Command number. This is command number in the list. This parameter must be set!\n"
  "'a' - Address from RC5 protocol. Optional parameter\n"
  "'c' - Command from RC5 protocol. Optional parameter\n"
  "'m' - Mode.\n"
  "       - 'single' - One action on each press.\n"
  "       - 'repetitive' - Multiple action on hold.\n"
  "       If is not specified default is 'single'. Optional parameter.\n"
  "'response' - Response is action which should be executed.\n"
  "       Available options:\n"
  "       - 'out_1_ON' to 'out_6_ON'\n"
  "       - 'out_1_OFF' to 'out_6_OFF'\n"
  "       - 'out_1_toggle' to 'out_6_toggle'\n"
  "       - 'sound_alarm'\n"
  "       - 'dummy'\n"
  "       If is not specified default is 'dummy'. Optional parameter.\n"
);

