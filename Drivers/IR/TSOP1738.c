#include "Global_Defines.h"
#include "Timer.h"
#include "Console.h"
#include "Delay.h"
#include "Debug_GPIO.h"

#include "TSOP1738.h"
#include "TSOP1738_Debug.h"
#include "TSOP1738_Func.h"
#include "TSOP1738_Pins.h"

uint8 Control_g = 0;
uint8 ControlBeckup = 0;
uint8 Address_g = 0;
uint8 AddressBeckup = 0;
uint8 Command_g = 0;
uint8 CommandBeckup = 0;
uint8 IrInputState = 0;
uint8 RepeatCommand = 0;
uint8 IR_SetCommand = 0;
uint16 Set_NoOfCommand;

uint8 WorkQueueHead = 0;
uint8 WorkQueueTail = 0;
uint8 WorkQueueCount = 0;

uint8 IR_Input_Debug_Flag = DISABLE;

Status_t (*WorkQueueCallback[IR_WORK_QUEUE_SIZE])(void * )  = {NULL};

ir_t IR_Commands[MAX_IR_COMMANDS] = {0};
ir_t IR_LastCommand = {0};

static Status_t IR_Ext_Interrupt_Init(void);
__arm static Status_t IR_Input_ISR(uint8 Control, uint8 Address, uint8 Command);

/*******************************************************************************
* 
*******************************************************************************/
Status_t IR_Received_Debug_Set_State(uint32 State)
{
  FuncIN(IR_RECEIVED_DEBUG_SET_STATE);
  
  switch(State)
  {
    case ENABLE:
      IR_Input_Debug_Flag = ENABLE;
      EXIT_SUCCESS_FUNC(IR_RECEIVED_DEBUG_SET_STATE);
    case DISABLE:
      IR_Input_Debug_Flag = DISABLE;
      EXIT_SUCCESS_FUNC(IR_RECEIVED_DEBUG_SET_STATE);
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }
  
  // This state should be never reached
  EXIT_SUCCESS_FUNC(IR_RECEIVED_DEBUG_SET_STATE);
}
FUNC_REGISTER(IR_RECEIVED_DEBUG_SET_STATE, IR_Received_Debug_Set_State);

/*******************************************************************************
* 
*******************************************************************************/
Status_t IR_Init(void)
{
  FuncIN(IR_INIT);
  
  Timer_1_Init();
  IR_Ext_Interrupt_Init();
  TSOP_PIN_INIT();
  
  EXIT_SUCCESS_FUNC(IR_INIT);
}
FUNC_REGISTER(IR_INIT, IR_Init);

/*******************************************************************************
* 
*******************************************************************************/
static Status_t IR_Ext_Interrupt_Init(void)
{
  FuncIN(IR_EXT_INTERRUPT_INIT);
  
  EXTINT_bit.EINT2 = 1;         // Clear INT Flag
  EXTWAKE_bit.EXTWAKE2 = 1;     // Enable Wake Up on Ext interrupt
  EXTMODE_bit.EXTMODE2 = 1;     // Edge senitive interrupt
  EXTPOLAR_bit.EXTPOLAR2 = 0;   // Falling-edge sensitive interrupt
  
  EXIT_SUCCESS_FUNC(IR_EXT_INTERRUPT_INIT);
}
FUNC_REGISTER(IR_EXT_INTERRUPT_INIT, IR_Ext_Interrupt_Init);

/*******************************************************************************
* @in NoOfCommand - Broj na komanda koja sakame da ja promenime
* @in Address - Adresa koja sakame da ja zapiseme. Ako tuka preneseme NULL nema
*                da se promeni adresata, ke si ostane starata
* @in Command - Komanda koja sakame da ja zapiseme. Ako tuka preneseme NULL nema
*                da se promeni komandata, ke si ostane starata
* @in CallMode - SINGLE_CALL or REPETITIVE_CALL
* @in Callback - Adresa na Callback funkcija. Koga ke se povika ovaa komanda
*                preku IR, ke se povika taa funkcija. Funkcijata ke bide
*                od sledniot tip: Status_t (*Func_p)(void * );
* NOTE: Ako Address = 0, Command = 0, Callback = 0, CallMode = 0, Target = 0
*       togas taa komanda ke se resetira
*******************************************************************************/
Status_t IR_Command_Init(uint16 NoOfCommand, ir_t *ir_p)
{
  FuncIN(IR_COMMAND_INIT);
  
  ASSERT((NoOfCommand < MAX_IR_COMMANDS) && (NoOfCommand > 0), -IR_COMMAND_ERROR);
  
  if((ir_p -> Address == NULL) && (ir_p -> Command == NULL) && (ir_p -> Callback_p == NULL) && (ir_p -> CallMode == NULL) && (ir_p -> Target == NULL))
  {
    IR_Commands[NoOfCommand].Address = NULL;
    IR_Commands[NoOfCommand].Command = NULL;
    IR_Commands[NoOfCommand].CallMode = NULL;
    IR_Commands[NoOfCommand].Target = NULL;
    IR_Commands[NoOfCommand].Callback_p = NULL;
  }
  else
  {
    if(ir_p -> Address != NULL)
      IR_Commands[NoOfCommand].Address = ir_p -> Address;
    if(ir_p -> Command != NULL)
      IR_Commands[NoOfCommand].Command = ir_p -> Command;
    if(ir_p -> CallMode != NULL)
      IR_Commands[NoOfCommand].CallMode = ir_p -> CallMode;
    if(ir_p -> Target != NULL)
      IR_Commands[NoOfCommand].Target = ir_p -> Target;
    if(ir_p -> Callback_p != NULL)
      IR_Commands[NoOfCommand].Callback_p = ir_p -> Callback_p;
  }
  
  EXIT_SUCCESS_FUNC(IR_COMMAND_INIT);
}
FUNC_REGISTER(IR_COMMAND_INIT, IR_Command_Init);

/*******************************************************************************
* 
*******************************************************************************/
Status_t IR_Set_Command(uint16 NoOfCommand)
{
  FuncIN(IR_SET_COMMAND);
  
  IR_SetCommand = 1;
  Set_NoOfCommand = NoOfCommand;

  EXIT_SUCCESS_FUNC(IR_SET_COMMAND);
}
FUNC_REGISTER(IR_SET_COMMAND, IR_Set_Command);

/*******************************************************************************
* 
*******************************************************************************/
Status_t IR_Get_Command(uint16 NoOfCommand, ir_t * IR_Command)
{
  FuncIN(IR_GET_COMMAND);
  
  *IR_Command = IR_Commands[NoOfCommand];
  
  EXIT_SUCCESS_FUNC(IR_GET_COMMAND);
}
FUNC_REGISTER(IR_GET_COMMAND, IR_Get_Command);

/*******************************************************************************
* 
*******************************************************************************/
__arm static Status_t IR_Add_Delayed_Callback_In_Queue(Status_t (*Callback_p)(void * ))
{
  FuncIN(IR_ADD_DELAYED_CALLBACK_IN_QUEUE);
  
  ASSERT(Callback_p != NULL, -INVALID_INPUT_POINTER);
  
  if(WorkQueueHead >= IR_WORK_QUEUE_SIZE)
    WorkQueueHead = 0;
  
  if(WorkQueueCount >= IR_WORK_QUEUE_SIZE)
    EXIT_FUNC(IR_QUEUE_FULL, IR_ADD_DELAYED_CALLBACK_IN_QUEUE);
  
  WorkQueueCallback[WorkQueueHead++] = Callback_p;
  
  WorkQueueCount++;
  
  EXIT_SUCCESS_FUNC(IR_ADD_DELAYED_CALLBACK_IN_QUEUE);
}
FUNC_REGISTER(IR_ADD_DELAYED_CALLBACK_IN_QUEUE, IR_Add_Delayed_Callback_In_Queue);

/*******************************************************************************
* 
*******************************************************************************/
__arm static Status_t IR_Get_Delayed_Callback_From_Queue(Status_t (**Callback_pp)(void * ))
{
  FuncIN(IR_GET_DELAYED_CALLBACK_FROM_QUEUE);
  
  ASSERT(Callback_pp != NULL, -INVALID_INPUT_POINTER);
  
  if(WorkQueueCount == 0)
    EXIT_FUNC(IR_QUEUE_EMPTY, IR_GET_DELAYED_CALLBACK_FROM_QUEUE);
  
  if(WorkQueueTail >= IR_WORK_QUEUE_SIZE)
    WorkQueueTail = 0;
  
  *Callback_pp = WorkQueueCallback[WorkQueueTail++];
  
  WorkQueueCount--;
  
  EXIT_SUCCESS_FUNC(IR_GET_DELAYED_CALLBACK_FROM_QUEUE);
}
FUNC_REGISTER(IR_GET_DELAYED_CALLBACK_FROM_QUEUE, IR_Get_Delayed_Callback_From_Queue);

/*******************************************************************************
* 
*******************************************************************************/
Status_t IR_Delayed_Work(void)
{
  FuncIN(IR_DELAYED_WORK);
  
  if(WorkQueueCount != 0)
  {
    Status_t (*Callback_p)(void * ) = NULL;
    
    ASSERT(IR_Get_Delayed_Callback_From_Queue(&Callback_p) == SUCCESS, -UNKNOWN_ERROR);
    ASSERT(Callback_p != NULL, -UNKNOWN_ERROR);
    
    ASSERT(!Callback_p(NULL), -IR_CALLBACK_ERROR);
  }
  
  EXIT_SUCCESS_FUNC(IR_DELAYED_WORK);
}
FUNC_REGISTER(IR_DELAYED_WORK, IR_Delayed_Work);

/*******************************************************************************
* 
*******************************************************************************/
__arm Status_t IR_Timer_ISR(void)
{
  uint8 Input = 0;
  Input = TSOP_PIN_READ();    // Ova mora da se zavrsi najbrzo sto moze
  
  if(IR_Input_Debug_Flag == ENABLE)
  {
    DBG_PIN_1_SET();
    uDelay(5);
    DBG_PIN_1_CLR();
  }
  
  FuncIN(IR_TIMER_ISR);
    
  switch (IrInputState)
  {
    case 0:
      Control_g = !Input;
      IrInputState++;
      Timer_1_Update_Match_0_Value(IR_BURST_T * 2);
      break;
    case 1:
      Address_g |= ((!Input) & 0x01) << 4;
      IrInputState++;
      break;
    case 2:
      Address_g |= ((!Input) & 0x01) << 3;
      IrInputState++;
      break;
    case 3:
      Address_g |= ((!Input) & 0x01) << 2;
      IrInputState++;
      break;
    case 4:
      Address_g |= ((!Input) & 0x01) << 1;
      IrInputState++;
      break;
    case 5:
      Address_g |= ((!Input) & 0x01);
      IrInputState++;
      break;
    case 6:
      Command_g |= ((!Input) & 0x01) << 5;
      IrInputState++;
      break;
    case 7:
      Command_g |= ((!Input) & 0x01) << 4;
      IrInputState++;
      break;
    case 8:
      Command_g |= ((!Input) & 0x01) << 3;
      IrInputState++;
      break;
    case 9:
      Command_g |= ((!Input) & 0x01) << 2;
      IrInputState++;
      break;
    case 10:
      Command_g |= ((!Input) & 0x01) << 1;
      IrInputState++;
      break;
    case 11:
      Command_g |= ((!Input) & 0x01);
      TSOP_DEBUG(printc("\nAddress = %u\tCommand = %u\n", Address_g, Command_g));
      TSOP_INT_ENABLE();
      Timer_1_Stop();
      IrInputState = 0;
      
      if((Address_g == 0) && (Command_g == 0))
        break;
      
      if(IR_SetCommand == 1)
      {
        IR_Commands[Set_NoOfCommand].Address = Address_g;
        IR_Commands[Set_NoOfCommand].Command = Command_g;
        IR_SetCommand = 0;
        printc("\r # IR Command Set with parameters:\n");
        printc(" # NoOfCommand = %u\tAddress = %u\tCommand = %u\n", Set_NoOfCommand, Address_g, Command_g);
      }
      else
      {
        if(IR_Input_Debug_Flag == ENABLE)
          printc("\r # IR_DEBUG: Received: Address = %u\tCommand = %u\n", Address_g, Command_g);
        
        if((Control_g == ControlBeckup) && (Address_g == AddressBeckup) && (Command_g == CommandBeckup))
        {
          IR_Input_ISR(REPEAT_COMMAND, Address_g, Command_g);
          TSOP_DEBUG(printc("\r # IR Repeat command received\n"));
        }
        else
        {
          IR_Input_ISR(NEW_COMMAND, Address_g, Command_g);
          TSOP_DEBUG(printc("\r # IR New command received\n"));
        }
      
        ControlBeckup = Control_g;
        AddressBeckup = Address_g;
        CommandBeckup = Command_g;
      }
      break;
    default:
      Fatal_Abort(-IR_READ_ERROR);
      break;
  } // switch
  
  EXIT_SUCCESS_FUNC(IR_TIMER_ISR);
}
FUNC_REGISTER(IR_TIMER_ISR, IR_Timer_ISR);

/*******************************************************************************
* 
*******************************************************************************/
__arm static Status_t IR_Input_ISR(uint8 Control, uint8 Address, uint8 Command)
{
  FuncIN(IR_INPUT_ISR);
  uint32 i;
  
  if(Control == REPEAT_COMMAND)
  {
    if((IR_LastCommand.CallMode == REPETITIVE_CALL) &&
       (IR_LastCommand.Address == Address) &&
       (IR_LastCommand.Command == Command))
    {
      if(IR_LastCommand.IRQ_Callback_p != NULL)
        ASSERT(!IR_LastCommand.IRQ_Callback_p(NULL), -IR_CALLBACK_ERROR);
      
      IR_Add_Delayed_Callback_In_Queue(IR_LastCommand.Callback_p);
    }
  }
  else
  {
    for(i = 0; i < MAX_IR_COMMANDS; i++)
    {
      if((IR_Commands[i].Address == Address) && (IR_Commands[i].Command == Command))
      {
        IR_LastCommand = IR_Commands[i];
        
        if(IR_LastCommand.IRQ_Callback_p != NULL)
          ASSERT(!IR_LastCommand.IRQ_Callback_p(NULL), -IR_CALLBACK_ERROR);
        
        IR_Add_Delayed_Callback_In_Queue(IR_LastCommand.Callback_p);
      }
    }
  }
    
  EXIT_SUCCESS_FUNC(IR_INPUT_ISR);
}
FUNC_REGISTER(IR_INPUT_ISR, IR_Input_ISR);

/*******************************************************************************
* 
*******************************************************************************/
__arm static Status_t IR_Ext_Interrupt_ISR(void)
{
  FuncIN(IR_EXT_INTERRUPT_ISR);
  
  Timer_1_Start( (IR_BURST_T * 4) + ((IR_BURST_T / 8) * 3) );
  
  IrInputState = 0;
  
  TSOP_INT_DISABLE();
  
  Control_g = 0;
  Address_g = 0;
  Command_g = 0;
  
  EXIT_SUCCESS_FUNC(IR_EXT_INTERRUPT_ISR);
}
FUNC_REGISTER(IR_EXT_INTERRUPT_ISR, IR_Ext_Interrupt_ISR);

/*******************************************************************************
* 
*******************************************************************************/
__irq void Ext_Int_2_ISR(void)
{
  IR_Ext_Interrupt_ISR();
  EXTINT_bit.EINT2 = 1;   // Clear INT Flag
  VICVectAddr = 0;
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t IR_Dummy_Handler(void *Ptr)
{
  TSOP_INFO(printc(" # IR dummy handler executed!\n"));
  
  return SUCCESS;
}