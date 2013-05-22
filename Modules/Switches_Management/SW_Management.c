#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"

#include "SW_Management.h"
#include "SW_Management_Debug.h"
#include "SW_Management_Func.h"
#include "Console.h"

#include "Configs.h"
#include "Temperature.h"
#include "Alarm.h"

static Status_t TempReg11(void * Ptr);
static Status_t TempUnreg11(void * Ptr);

static Status_t TempReg12(void * Ptr);
static Status_t TempReg13(void * Ptr);
static Status_t TempReg14(void * Ptr);
static Status_t TempReg21(void * Ptr);
static Status_t TempReg22(void * Ptr);
static Status_t TempReg23(void * Ptr);
static Status_t TempReg24(void * Ptr);
static Status_t TempReg31(void * Ptr);
static Status_t TempReg32(void * Ptr);
static Status_t TempReg33(void * Ptr);
static Status_t TempReg34(void * Ptr);
static Status_t TempReg41(void * Ptr);
static Status_t TempReg42(void * Ptr);
static Status_t TempReg43(void * Ptr);
static Status_t TempReg44(void * Ptr);
static Status_t TempReg51(void * Ptr);
static Status_t TempReg52(void * Ptr);
static Status_t TempReg53(void * Ptr);
static Status_t TempReg54(void * Ptr);
static Status_t TempReg61(void * Ptr);
static Status_t TempReg62(void * Ptr);
static Status_t TempReg63(void * Ptr);
static Status_t TempReg64(void * Ptr);


static Status_t TempUnreg12(void * Ptr);
static Status_t TempUnreg13(void * Ptr);
static Status_t TempUnreg14(void * Ptr);
static Status_t TempUnreg21(void * Ptr);
static Status_t TempUnreg22(void * Ptr);
static Status_t TempUnreg23(void * Ptr);
static Status_t TempUnreg24(void * Ptr);
static Status_t TempUnreg31(void * Ptr);
static Status_t TempUnreg32(void * Ptr);
static Status_t TempUnreg33(void * Ptr);
static Status_t TempUnreg34(void * Ptr);
static Status_t TempUnreg41(void * Ptr);
static Status_t TempUnreg42(void * Ptr);
static Status_t TempUnreg43(void * Ptr);
static Status_t TempUnreg44(void * Ptr);
static Status_t TempUnreg51(void * Ptr);
static Status_t TempUnreg52(void * Ptr);
static Status_t TempUnreg53(void * Ptr);
static Status_t TempUnreg54(void * Ptr);
static Status_t TempUnreg61(void * Ptr);
static Status_t TempUnreg62(void * Ptr);
static Status_t TempUnreg63(void * Ptr);
static Status_t TempUnreg64(void * Ptr);

static Status_t SW_M_Temp_Reg_Event(uint32 NoOfSwitch, uint32 NoOfEvent);
static Status_t SW_M_Temp_Unreg_Event(uint32 NoOfSwitch, uint32 NoOfEvent);

__packed SW_M_Event_t SW_M_Event[NO_OF_SWITCHES][NO_OF_EVENTS_PER_SWITCH] = {0};

SW_M_Event_t SW_M_Event_ = {0};

void *CallbackON[]      = {(void *)Out_1_Set,
                           (void *)Out_2_Set,
                           (void *)Out_3_Set,
                           (void *)Out_4_Set,
                           (void *)Out_5_Set,
                           (void *)Out_6_Set};
void *CallbackOFF[]     = {(void *)Out_1_Clr,
                           (void *)Out_2_Clr,
                           (void *)Out_3_Clr,
                           (void *)Out_4_Clr,
                           (void *)Out_5_Clr,
                           (void *)Out_6_Clr};
void *CallbackToggle[]  = {(void *)Out_1_Toggle,
                           (void *)Out_2_Toggle,
                           (void *)Out_3_Toggle,
                           (void *)Out_4_Toggle,
                           (void *)Out_5_Toggle,
                           (void *)Out_6_Toggle};

void *CallbackTempReg[]  = {(void *)TempReg11,
                            (void *)TempReg12,
                            (void *)TempReg13,
                            (void *)TempReg14,
                            (void *)TempReg21,
                            (void *)TempReg22,
                            (void *)TempReg23,
                            (void *)TempReg24,
                            (void *)TempReg31,
                            (void *)TempReg32,
                            (void *)TempReg33,
                            (void *)TempReg34,
                            (void *)TempReg41,
                            (void *)TempReg42,
                            (void *)TempReg43,
                            (void *)TempReg44,
                            (void *)TempReg51,
                            (void *)TempReg52,
                            (void *)TempReg53,
                            (void *)TempReg54,
                            (void *)TempReg61,
                            (void *)TempReg62,
                            (void *)TempReg63,
                            (void *)TempReg64};

void *CallbackTempUnreg[]  = {(void *)TempUnreg11,
                            (void *)TempUnreg12,
                            (void *)TempUnreg13,
                            (void *)TempUnreg14,
                            (void *)TempUnreg21,
                            (void *)TempUnreg22,
                            (void *)TempUnreg23,
                            (void *)TempUnreg24,
                            (void *)TempUnreg31,
                            (void *)TempUnreg32,
                            (void *)TempUnreg33,
                            (void *)TempUnreg34,
                            (void *)TempUnreg41,
                            (void *)TempUnreg42,
                            (void *)TempUnreg43,
                            (void *)TempUnreg44,
                            (void *)TempUnreg51,
                            (void *)TempUnreg52,
                            (void *)TempUnreg53,
                            (void *)TempUnreg54,
                            (void *)TempUnreg61,
                            (void *)TempUnreg62,
                            (void *)TempUnreg63,
                            (void *)TempUnreg64};

/*******************************************************************************
 * Temp event register functions
 ******************************************************************************/
static Status_t TempReg11(void * Ptr)
{
  printc("(%s): Register Temp Alarm 11!\n", __func__);
  SW_M_Temp_Reg_Event(1, 1);

  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg12(void * Ptr)
{
  SW_M_Temp_Reg_Event(1, 2);
  printc("(%s): Register Temp Alarm 12!\n", __func__);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg13(void * Ptr)
{
  SW_M_Temp_Reg_Event(1, 3);
  printc("(%s): Register Temp Alarm 13!\n", __func__);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg14(void * Ptr)
{
  SW_M_Temp_Reg_Event(1, 4);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg21(void * Ptr)
{
  SW_M_Temp_Reg_Event(2, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg22(void * Ptr)
{
  SW_M_Temp_Reg_Event(2, 2);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg23(void * Ptr)
{
  SW_M_Temp_Reg_Event(2, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg24(void * Ptr)
{
  SW_M_Temp_Reg_Event(2, 4);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg31(void * Ptr)
{
  SW_M_Temp_Reg_Event(3, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg32(void * Ptr)
{
  SW_M_Temp_Reg_Event(3, 2);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg33(void * Ptr)
{
  SW_M_Temp_Reg_Event(3, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg34(void * Ptr)
{
  SW_M_Temp_Reg_Event(3, 4);
  return SUCCESS;
}

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg41(void * Ptr)
{
  SW_M_Temp_Reg_Event(4, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg42(void * Ptr)
{
  SW_M_Temp_Reg_Event(4, 2);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg43(void * Ptr)
{
  SW_M_Temp_Reg_Event(4, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg44(void * Ptr)
{
  SW_M_Temp_Reg_Event(4, 4);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg51(void * Ptr)
{
  SW_M_Temp_Reg_Event(5, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg52(void * Ptr)
{
  SW_M_Temp_Reg_Event(5, 2);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg53(void * Ptr)
{
  SW_M_Temp_Reg_Event(5, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg54(void * Ptr)
{
  SW_M_Temp_Reg_Event(5, 4);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg61(void * Ptr)
{
  SW_M_Temp_Reg_Event(6, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg62(void * Ptr)
{
  SW_M_Temp_Reg_Event(6, 2);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg63(void * Ptr)
{
  SW_M_Temp_Reg_Event(6, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempReg64(void * Ptr)
{
  SW_M_Temp_Reg_Event(6, 4);
  return SUCCESS;
}

/*******************************************************************************
 * Temp event unregister functions
 ******************************************************************************/
static Status_t TempUnreg11(void * Ptr)
{

  printc("(%s): Unregister Temp Alarm 11 ID1 = %d ID2 = %d!\n", __func__, SW_M_Event_.Temp_1.AlarmID,  SW_M_Event_.Temp_2.AlarmID);
  printc("(%s): Unregister Temp Alarm 11 Temp1 = %d Temp2 = %d!\n", __func__, SW_M_Event_.Temp_1.Temp,  SW_M_Event_.Temp_2.Temp);
  SW_M_Temp_Unreg_Event(1, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg12(void * Ptr)
{
  printc("(%s): Unregister Temp Alarm 12!\n", __func__);
  SW_M_Temp_Unreg_Event(1, 2);

  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg13(void * Ptr)
{
  SW_M_Temp_Unreg_Event(1, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg14(void * Ptr)
{
  SW_M_Temp_Unreg_Event(1, 4);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg21(void * Ptr)
{
  SW_M_Temp_Unreg_Event(2, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg22(void * Ptr)
{
  SW_M_Temp_Unreg_Event(2, 2);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg23(void * Ptr)
{
  SW_M_Temp_Unreg_Event(2, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg24(void * Ptr)
{
  SW_M_Temp_Unreg_Event(2, 4);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg31(void * Ptr)
{
  SW_M_Temp_Unreg_Event(3, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg32(void * Ptr)
{
  SW_M_Temp_Unreg_Event(3, 2);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg33(void * Ptr)
{
  SW_M_Temp_Unreg_Event(3, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg34(void * Ptr)
{
  SW_M_Temp_Unreg_Event(3, 4);
  return SUCCESS;
}

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg41(void * Ptr)
{
  SW_M_Temp_Unreg_Event(4, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg42(void * Ptr)
{
  SW_M_Temp_Unreg_Event(4, 2);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg43(void * Ptr)
{
  SW_M_Temp_Unreg_Event(4, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg44(void * Ptr)
{
  SW_M_Temp_Unreg_Event(4, 4);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg51(void * Ptr)
{
  SW_M_Temp_Unreg_Event(5, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg52(void * Ptr)
{
  SW_M_Temp_Unreg_Event(5, 2);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg53(void * Ptr)
{
  SW_M_Temp_Unreg_Event(5, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg54(void * Ptr)
{
  SW_M_Temp_Unreg_Event(5, 4);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg61(void * Ptr)
{
  SW_M_Temp_Unreg_Event(6, 1);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg62(void * Ptr)
{
  SW_M_Temp_Unreg_Event(6, 2);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg63(void * Ptr)
{
  SW_M_Temp_Unreg_Event(6, 3);
  return SUCCESS;
}
/*******************************************************************************
 *
 ******************************************************************************/
static Status_t TempUnreg64(void * Ptr)
{
  SW_M_Temp_Unreg_Event(6, 4);
  return SUCCESS;
}

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t SW_M_Get_Callback(uint32 NoOfSwitch, uint32 Type, void **Callback)
{
  FuncIN(SW_M_GET_CALLBACK);

  switch(Type)
  {
    case SW_CALLBACK_TYPE_ON:
      *Callback = CallbackON[NoOfSwitch - 1];
      break;
    case SW_CALLBACK_TYPE_OFF:
      *Callback = CallbackOFF[NoOfSwitch - 1];
      break;
    case SW_CALLBACK_TYPE_TOGGLE:
      *Callback = CallbackToggle[NoOfSwitch - 1];
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
  }

  EXIT_SUCCESS_FUNC(SW_M_GET_CALLBACK);
}
SW_M_FUNC_REGISTER(SW_M_GET_CALLBACK, SW_M_Get_Callback);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t SW_M_Temp_Reg_Event(uint32 NoOfSwitch, uint32 NoOfEvent)
{
  FuncIN(SW_M_TEMP_REG_EVENT);

  void *Callback;
  TempAlarm_t TempAlarm;
  SW_M_Event_ = SW_M_Event[NoOfSwitch - 1][NoOfEvent - 1];
  SW_M_Event_t *SW_M_Event_p = &SW_M_Event_;

  if(0 != (SW_M_Event_p -> Config & SW_EVENT_ON) &&
     0 != (SW_M_Event_p -> Config & SW_EVENT_TIME_TEMP_DEP))
  {
    /**** Config Temp_1 ****/
    if(SW_M_Event_p -> Temp_1.State == SW_TEMP_ALARM_ON)
    {
      if(0 != (SW_M_Event_p -> Config & SW_EVENT_RESPONSE_1_ON))
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_ON, &Callback);
      else
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_OFF, &Callback);

      if(SW_M_Event_p -> Temp_1.AlarmID == SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Register Start Time Temp Event!\n", __func__);
        Register_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor,
                            SW_M_Event_p -> Temp_1.Event,
                            SW_M_Event_p -> Temp_1.Temp,
                            Callback,
                            &(SW_M_Event_p -> Temp_1.AlarmID));

        Set_State_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor,
                             SW_M_Event_p -> Temp_1.AlarmID,
                             SW_M_Event_p -> Temp_1.State);

      }
      else
      {
        TempAlarm.Event = SW_M_Event_p -> Temp_1.Event;
        TempAlarm.State = SW_M_Event_p -> Temp_1.State;
        TempAlarm.SensorID = SW_M_Event_p -> Temp_1.Sensor;
        TempAlarm.AlarmID = SW_M_Event_p -> Temp_1.AlarmID;
        TempAlarm.Value = SW_M_Event_p -> Temp_1.Temp;
        TempAlarm.Callback = Callback;

        printc("(%s): Set Start Time Temp Event!\n", __func__);
        Set_Temp_Alarm(&TempAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Temp_1.AlarmID != SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Unregister Start Time Temp Event!\n", __func__);
        Unregister_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor, SW_M_Event_p -> Temp_1.AlarmID);
        SW_M_Event_p -> Temp_1.AlarmID = SW_TEMP_NO_ALARM_ID;
      }
    }

    /**** Config Temp_2 ****/
    if(SW_M_Event_p -> Temp_2.State == SW_TEMP_ALARM_ON)
    {
      if(0 != (SW_M_Event_p -> Config & SW_EVENT_RESPONSE_2_ON))
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_ON, &Callback);
      else
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_OFF, &Callback);

      if(SW_M_Event_p -> Temp_2.AlarmID == SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Register Stop Time Temp Event!\n", __func__);
        Register_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor,
                            SW_M_Event_p -> Temp_2.Event,
                            SW_M_Event_p -> Temp_2.Temp,
                            Callback,
                            &(SW_M_Event_p -> Temp_2.AlarmID));

        Set_State_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor,
                             SW_M_Event_p -> Temp_2.AlarmID,
                             SW_M_Event_p -> Temp_2.State);
      }
      else
      {
        TempAlarm.Event = SW_M_Event_p -> Temp_2.Event;
        TempAlarm.State = SW_M_Event_p -> Temp_2.State;
        TempAlarm.SensorID = SW_M_Event_p -> Temp_2.Sensor;
        TempAlarm.AlarmID = SW_M_Event_p -> Temp_2.AlarmID;
        TempAlarm.Value = SW_M_Event_p -> Temp_2.Temp;
        TempAlarm.Callback = Callback;

        printc("(%s): Set Stop Time Temp Event!\n", __func__);
        Set_Temp_Alarm(&TempAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Temp_2.AlarmID != SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Unregister Stop Time Temp Event!\n", __func__);
        Unregister_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor, SW_M_Event_p -> Temp_2.AlarmID);
        SW_M_Event_p -> Temp_2.AlarmID = SW_TEMP_NO_ALARM_ID;
      }
    }
  }
  else
  {
    if(SW_M_Event_p -> Temp_1.AlarmID != SW_TEMP_NO_ALARM_ID)
    {
      printc("(%s): Unregister Start Time Temp Event!\n", __func__);
      Unregister_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor, SW_M_Event_p -> Temp_1.AlarmID);
      SW_M_Event_p -> Temp_1.AlarmID = SW_TEMP_NO_ALARM_ID;
    }

    if(SW_M_Event_p -> Temp_2.AlarmID != SW_TEMP_NO_ALARM_ID)
    {
      printc("(%s): Unregister Stop Time Temp Event!\n", __func__);
      Unregister_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor, SW_M_Event_p -> Temp_2.AlarmID);
      SW_M_Event_p -> Temp_2.AlarmID = SW_TEMP_NO_ALARM_ID;
    }
  }
  SW_M_Event[NoOfSwitch - 1][NoOfEvent - 1] = *SW_M_Event_p;

  EXIT_SUCCESS_FUNC(SW_M_TEMP_REG_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_TEMP_REG_EVENT, SW_M_Temp_Reg_Event);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t SW_M_Temp_Unreg_Event(uint32 NoOfSwitch, uint32 NoOfEvent)
{
  FuncIN(SW_M_TEMP_UNREG_EVENT);

  SW_M_Event_ = SW_M_Event[NoOfSwitch - 1][NoOfEvent - 1];
  SW_M_Event_t *SW_M_Event_p = &SW_M_Event_;

  printc("(%s): Unregister Stop Time Temp Event ID1 = %d !\n", __func__,SW_M_Event_p -> Temp_1.AlarmID);
  printc("(%s): Unregister Stop Time Temp Event ID2 = %d !\n", __func__,SW_M_Event_p -> Temp_2.AlarmID);

  if(0 != (SW_M_Event_p -> Config & SW_EVENT_ON) &&
     0 != (SW_M_Event_p -> Config & SW_EVENT_TIME_TEMP_DEP))
  {
    if(SW_M_Event_p -> Temp_1.AlarmID != SW_TEMP_NO_ALARM_ID)
    {
      printc("(%s): Unregister Start Time Temp Event!\n", __func__);
      Unregister_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor, SW_M_Event_p -> Temp_1.AlarmID);
      SW_M_Event_p -> Temp_1.AlarmID = SW_TEMP_NO_ALARM_ID;
    }

    if(SW_M_Event_p -> Temp_2.AlarmID != SW_TEMP_NO_ALARM_ID)
    {
      printc("(%s): Unregister Stop Time Temp Event!\n", __func__);
      Unregister_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor, SW_M_Event_p -> Temp_2.AlarmID);
      SW_M_Event_p -> Temp_2.AlarmID = SW_TEMP_NO_ALARM_ID;
    }
  }
  printc("(%s): Unregister Time Temp Event DONE!\n", __func__);

  EXIT_SUCCESS_FUNC(SW_M_TEMP_UNREG_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_TEMP_UNREG_EVENT, SW_M_Temp_Unreg_Event);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t SW_M_Config_Temp_Event(uint32 NoOfSwitch, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_CONFIG_TEMP_EVENT);

  void *Callback;
  TempAlarm_t TempAlarm;

  if(0 != (SW_M_Event_p -> Config & SW_EVENT_ON) &&
     0 != (SW_M_Event_p -> Config & SW_EVENT_TEMP_DEP))
  {
    /**** Config Temp_1 ****/
    if(SW_M_Event_p -> Temp_1.State == SW_TEMP_ALARM_ON)
    {
      if((SW_M_Event_p -> Config & SW_EVENT_RESPONSE_1_ON) == SW_EVENT_RESPONSE_1_ON)
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_ON, &Callback);
      else
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_OFF, &Callback);

      if(SW_M_Event_p -> Temp_1.AlarmID == SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Register Temp 1 Event!\n", __func__);
        Register_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor,
                            SW_M_Event_p -> Temp_1.Event,
                            SW_M_Event_p -> Temp_1.Temp,
                            Callback,
                            &(SW_M_Event_p -> Temp_1.AlarmID));

        Set_State_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor,
                             SW_M_Event_p -> Temp_1.AlarmID,
                             SW_M_Event_p -> Temp_1.State);
      }
      else
      {
        TempAlarm.Event = SW_M_Event_p -> Temp_1.Event;
        TempAlarm.State = SW_M_Event_p -> Temp_1.State;
        TempAlarm.SensorID = SW_M_Event_p -> Temp_1.Sensor;
        TempAlarm.AlarmID = SW_M_Event_p -> Temp_1.AlarmID;
        TempAlarm.Value = SW_M_Event_p -> Temp_1.Temp;
        TempAlarm.Callback = Callback;

        printc("(%s): Set Temp 1 Event!\n", __func__);
        Set_Temp_Alarm(&TempAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Temp_1.AlarmID != SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Unregister Temp 1 Event!\n", __func__);
        Unregister_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor, SW_M_Event_p -> Temp_1.AlarmID);
        SW_M_Event_p -> Temp_1.AlarmID = SW_TEMP_NO_ALARM_ID;
      }
    }

    /**** Config Temp_2 ****/
    if(SW_M_Event_p -> Temp_2.State == SW_TEMP_ALARM_ON)
    {
      if(0 != (SW_M_Event_p -> Config & SW_EVENT_RESPONSE_2_ON))
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_ON, &Callback);
      else
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_OFF, &Callback);

      if(SW_M_Event_p -> Temp_2.AlarmID == SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Register Temp 2 Event!\n", __func__);
        Register_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor,
                            SW_M_Event_p -> Temp_2.Event,
                            SW_M_Event_p -> Temp_2.Temp,
                            Callback,
                            &(SW_M_Event_p -> Temp_2.AlarmID));

        Set_State_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor,
                             SW_M_Event_p -> Temp_2.AlarmID,
                             SW_M_Event_p -> Temp_2.State);
      }
      else
      {
        TempAlarm.Event = SW_M_Event_p -> Temp_2.Event;
        TempAlarm.State = SW_M_Event_p -> Temp_2.State;
        TempAlarm.SensorID = SW_M_Event_p -> Temp_2.Sensor;
        TempAlarm.AlarmID = SW_M_Event_p -> Temp_2.AlarmID;
        TempAlarm.Value = SW_M_Event_p -> Temp_2.Temp;
        TempAlarm.Callback = Callback;

        printc("(%s): Set Temp 2 Event!\n", __func__);
        Set_Temp_Alarm(&TempAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Temp_2.AlarmID != SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Unregister Temp 2 Event!\n", __func__);
        Unregister_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor, SW_M_Event_p -> Temp_2.AlarmID);
        SW_M_Event_p -> Temp_2.AlarmID = SW_TEMP_NO_ALARM_ID;
      }
    }
  }
  else
  {
    if (0 == (SW_M_Event_p -> Config & SW_EVENT_TIME_TEMP_DEP))
    {
      if(SW_M_Event_p -> Temp_1.AlarmID != SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Unregister Temp 1 Event!\n", __func__);
        Unregister_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor, SW_M_Event_p -> Temp_1.AlarmID);
        SW_M_Event_p -> Temp_1.AlarmID = SW_TEMP_NO_ALARM_ID;
      }

      if(SW_M_Event_p -> Temp_2.AlarmID != SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Unregister Temp 2 Event!\n", __func__);
        Unregister_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor, SW_M_Event_p -> Temp_2.AlarmID);
        SW_M_Event_p -> Temp_2.AlarmID = SW_TEMP_NO_ALARM_ID;
      }
    }
  }

  EXIT_SUCCESS_FUNC(SW_M_CONFIG_TEMP_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_CONFIG_TEMP_EVENT, SW_M_Config_Temp_Event);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t SW_M_Config_Time_Event(uint32 NoOfSwitch, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_CONFIG_TIME_EVENT);

  TimeAlarm_t TimeAlarm;

  if(0 != (SW_M_Event_p -> Config & SW_EVENT_ON) &&
     0 != (SW_M_Event_p -> Config & SW_EVENT_TIME_DEP))
  {
    /**** Config Time_Start ****/
    if(SW_M_Event_p -> Time_Start.State == SW_TIME_ALARM_ON)
    {
      if((SW_M_Event_p -> Config & SW_EVENT_RESPONSE_1_ON) == SW_EVENT_RESPONSE_1_ON)
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_ON, &TimeAlarm.Callback);
      else
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_OFF, &TimeAlarm.Callback);

      if(SW_M_Event_p -> Time_Start.AlarmID == SW_TIME_NO_ALARM_ID)
      {
        TimeAlarm.State = SW_M_Event_p -> Time_Start.State;
        TimeAlarm.AlarmID = SW_TIME_NO_ALARM_ID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Start.Hour,
                                             SW_M_Event_p -> Time_Start.Minute,
                                             SW_M_Event_p -> Time_Start.Second};

        Register_Time_Alarm(&TimeAlarm);
        SW_M_Event_p -> Time_Start.AlarmID = TimeAlarm.AlarmID;

        printc("(%s): Register Start Time Event Rep:0x%x!\n", __func__, TimeAlarm.Repeat);
      }
      else
      {
        TimeAlarm.State = SW_M_Event_p -> Time_Start.State;
        TimeAlarm.AlarmID = SW_M_Event_p -> Time_Start.AlarmID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Start.Hour,
                                             SW_M_Event_p -> Time_Start.Minute,
                                             SW_M_Event_p -> Time_Start.Second};
        printc("(%s): Set Start Time Event Rep:0x%x!\n", __func__, TimeAlarm.Repeat);
        Set_Time_Alarm(&TimeAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Time_Start.AlarmID != SW_TIME_NO_ALARM_ID)
      {
        printc("(%s): Unregister Start Time Event!\n", __func__);
        Unregister_Time_Alarm(SW_M_Event_p -> Time_Start.AlarmID);
        SW_M_Event_p -> Time_Start.AlarmID = SW_TIME_NO_ALARM_ID;
      }
    }

    /**** Config Time_Stop ****/
    if(SW_M_Event_p -> Time_Stop.State == SW_TIME_ALARM_ON)
    {
      if((SW_M_Event_p -> Config & SW_EVENT_RESPONSE_2_ON) == SW_EVENT_RESPONSE_2_ON)
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_ON, &TimeAlarm.Callback);
      else
        SW_M_Get_Callback(NoOfSwitch, SW_CALLBACK_TYPE_OFF, &TimeAlarm.Callback);

      if(SW_M_Event_p -> Time_Stop.AlarmID == SW_TIME_NO_ALARM_ID)
      {
        TimeAlarm.State = SW_M_Event_p -> Time_Stop.State;
        TimeAlarm.AlarmID = SW_TIME_NO_ALARM_ID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Stop.Hour,
                                             SW_M_Event_p -> Time_Stop.Minute,
                                             SW_M_Event_p -> Time_Stop.Second};

        Register_Time_Alarm(&TimeAlarm);
        SW_M_Event_p -> Time_Stop.AlarmID = TimeAlarm.AlarmID;

        printc("(%s): Register Stop Time Event Rep:0x%x!\n", __func__, TimeAlarm.Repeat);
      }
      else
      {
        TimeAlarm.State = SW_M_Event_p -> Time_Stop.State;
        TimeAlarm.AlarmID = SW_M_Event_p -> Time_Stop.AlarmID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Stop.Hour,
                                             SW_M_Event_p -> Time_Stop.Minute,
                                             SW_M_Event_p -> Time_Stop.Second};
        printc("(%s): Set Stop Time Event Rep:0x%x!\n", __func__, TimeAlarm.Repeat);
        Set_Time_Alarm(&TimeAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Time_Stop.AlarmID != SW_TIME_NO_ALARM_ID)
      {
        printc("(%s): Unregister Stop Time Event!\n", __func__);
        Unregister_Time_Alarm(SW_M_Event_p -> Time_Stop.AlarmID);
        SW_M_Event_p -> Time_Stop.AlarmID = SW_TIME_NO_ALARM_ID;
      }
    }
  }
  else
  {
    if (0 == (SW_M_Event_p -> Config & SW_EVENT_TIME_TEMP_DEP))
    {
      if(SW_M_Event_p -> Time_Start.AlarmID != SW_TIME_NO_ALARM_ID)
      {
        printc("(%s): Unregister Start Time Event!\n", __func__);
        Unregister_Time_Alarm(SW_M_Event_p -> Time_Start.AlarmID);
        SW_M_Event_p -> Time_Start.AlarmID = SW_TIME_NO_ALARM_ID;
      }

      if(SW_M_Event_p -> Time_Stop.AlarmID != SW_TIME_NO_ALARM_ID)
      {
        printc("(%s): Unregister Stop Time Event!\n", __func__);
        Unregister_Time_Alarm(SW_M_Event_p -> Time_Stop.AlarmID);
        SW_M_Event_p -> Time_Stop.AlarmID = SW_TIME_NO_ALARM_ID;
      }
    }
  }

  EXIT_SUCCESS_FUNC(SW_M_CONFIG_TIME_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_CONFIG_TIME_EVENT, SW_M_Config_Time_Event);

/*******************************************************************************
 *
 ******************************************************************************/
static Status_t SW_M_Config_Time_Temp_Event(uint32 NoOfSwitch, uint32 NoOfEvent, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_CONFIG_TIME_TEMP_EVENT);

  TimeAlarm_t TimeAlarm;

  if(0 != (SW_M_Event_p -> Config & SW_EVENT_ON) &&
     0 != (SW_M_Event_p -> Config & SW_EVENT_TIME_TEMP_DEP))
  {
    /**** Config Time_Start ****/
    if(SW_M_Event_p -> Time_Start.State == SW_TIME_ALARM_ON)
    {
      if(SW_M_Event_p -> Time_Start.AlarmID == SW_TIME_NO_ALARM_ID)
      {
        TimeAlarm.Callback = CallbackTempReg[(NoOfSwitch - 1) * NO_OF_EVENTS_PER_SWITCH + NoOfEvent - 1];
        TimeAlarm.State = SW_TIME_ALARM_ON;
        TimeAlarm.AlarmID = SW_TIME_NO_ALARM_ID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Start.Hour,
                                             SW_M_Event_p -> Time_Start.Minute,
                                             SW_M_Event_p -> Time_Start.Second};

        Register_Time_Alarm(&TimeAlarm);
        SW_M_Event_p -> Time_Start.AlarmID = TimeAlarm.AlarmID;

        printc("(%s):(%d)*** Register Start Time Temp Event! ID = %d***\n", __func__,__LINE__, TimeAlarm.AlarmID);
      }
      else
      {
        TimeAlarm.Callback = CallbackTempReg[(NoOfSwitch - 1) * NO_OF_EVENTS_PER_SWITCH + NoOfEvent - 1];;
        TimeAlarm.State = SW_TIME_ALARM_ON;
        TimeAlarm.AlarmID = SW_M_Event_p -> Time_Start.AlarmID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Start.Hour,
                                             SW_M_Event_p -> Time_Start.Minute,
                                             SW_M_Event_p -> Time_Start.Second};
        printc("(%s):(%d)*** Set Start Time Temp Event! %x ***\n", __func__,__LINE__, TimeAlarm.Repeat);
        Set_Time_Alarm(&TimeAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Time_Start.AlarmID != SW_TIME_NO_ALARM_ID)
      {
        printc("(%s):(%d)*** Unregister Start Time Temp Event! ***\n", __func__,__LINE__);
        Unregister_Time_Alarm(SW_M_Event_p -> Time_Start.AlarmID);
        SW_M_Event_p -> Time_Start.AlarmID = SW_TIME_NO_ALARM_ID;
      }
    }

    /**** Config Time_Stop ****/
    if(SW_M_Event_p -> Time_Stop.State == SW_TIME_ALARM_ON)
    {
      if(SW_M_Event_p -> Time_Stop.AlarmID == SW_TIME_NO_ALARM_ID)
      {
        TimeAlarm.Callback = CallbackTempUnreg[(NoOfSwitch - 1) * NO_OF_EVENTS_PER_SWITCH + NoOfEvent - 1];
        TimeAlarm.State = SW_TIME_ALARM_ON;
        TimeAlarm.AlarmID = SW_TIME_NO_ALARM_ID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Stop.Hour,
                                             SW_M_Event_p -> Time_Stop.Minute,
                                             SW_M_Event_p -> Time_Stop.Second};

        Register_Time_Alarm(&TimeAlarm);
        SW_M_Event_p -> Time_Stop.AlarmID = TimeAlarm.AlarmID;

        printc("(%s):(%d)*** Register Stop Time Temp Event! ID = %d***\n", __func__, __LINE__, TimeAlarm.AlarmID);
      }
      else
      {
        TimeAlarm.Callback = CallbackTempUnreg[(NoOfSwitch - 1) * NO_OF_EVENTS_PER_SWITCH + NoOfEvent - 1];;
        TimeAlarm.State = SW_TIME_ALARM_ON;
        TimeAlarm.AlarmID = SW_M_Event_p -> Time_Stop.AlarmID;
        TimeAlarm.Repeat = SW_M_Event_p -> Date.Repeat;
        TimeAlarm.DateTime = (RtcDateTime_t){SW_M_Event_p -> Date.Year,
                                             SW_M_Event_p -> Date.Month,
                                             SW_M_Event_p -> Date.Day,
                                             SW_M_Event_p -> Time_Stop.Hour,
                                             SW_M_Event_p -> Time_Stop.Minute,
                                             SW_M_Event_p -> Time_Stop.Second};
        printc("(%s):(%d)*** Set Stop Time Temp Event! ***\n", __func__,__LINE__);
        Set_Time_Alarm(&TimeAlarm);
      }
    }
    else
    {
      if(SW_M_Event_p -> Time_Stop.AlarmID != SW_TIME_NO_ALARM_ID)
      {
        printc("(%s):(%d)*** Unregister Stop Time Temp Event! ***\n", __func__,__LINE__);
        Unregister_Time_Alarm(SW_M_Event_p -> Time_Stop.AlarmID);
        SW_M_Event_p -> Time_Stop.AlarmID = SW_TIME_NO_ALARM_ID;
      }
    }
  }
  else
  {
    if (0 == (SW_M_Event_p -> Config & SW_EVENT_TIME_DEP))
    {
      if(SW_M_Event_p -> Time_Start.AlarmID != SW_TIME_NO_ALARM_ID)
      {
        printc("(%s):(%d)*** Unregister Start Time Temp Event! ***\n", __func__,__LINE__);
        Unregister_Time_Alarm(SW_M_Event_p -> Time_Start.AlarmID);
        SW_M_Event_p -> Time_Start.AlarmID = SW_TIME_NO_ALARM_ID;
      }

      if(SW_M_Event_p -> Time_Stop.AlarmID != SW_TIME_NO_ALARM_ID)
      {
        printc("(%s):(%d)*** Unregister Stop Time Temp Event! ***\n", __func__,__LINE__);
        Unregister_Time_Alarm(SW_M_Event_p -> Time_Stop.AlarmID);
        SW_M_Event_p -> Time_Stop.AlarmID = SW_TIME_NO_ALARM_ID;
      }
    }

    if (0 == (SW_M_Event_p -> Config & SW_EVENT_TEMP_DEP))
    {
      if(SW_M_Event_p -> Temp_1.AlarmID != SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Unregister Time Temp 1 Event!\n", __func__);
        Unregister_Temp_Alarm(SW_M_Event_p -> Temp_1.Sensor, SW_M_Event_p -> Temp_1.AlarmID);
        SW_M_Event_p -> Temp_1.AlarmID = SW_TEMP_NO_ALARM_ID;
      }

      if(SW_M_Event_p -> Temp_2.AlarmID != SW_TEMP_NO_ALARM_ID)
      {
        printc("(%s): Unregister Time Temp 2 Event!\n", __func__);
        Unregister_Temp_Alarm(SW_M_Event_p -> Temp_2.Sensor, SW_M_Event_p -> Temp_2.AlarmID);
        SW_M_Event_p -> Temp_2.AlarmID = SW_TEMP_NO_ALARM_ID;
      }
    }
  }


  EXIT_SUCCESS_FUNC(SW_M_CONFIG_TIME_TEMP_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_CONFIG_TIME_TEMP_EVENT, SW_M_Config_Time_Temp_Event);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t SW_M_Set_Event(uint32 NoOfSwitch, uint32 NoOfEvent, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_SET_EVENT);

  SW_M_Config_Temp_Event(NoOfSwitch, SW_M_Event_p);

  SW_M_Config_Time_Event(NoOfSwitch, SW_M_Event_p);

  SW_M_Config_Time_Temp_Event(NoOfSwitch, NoOfEvent, SW_M_Event_p);

  SW_M_Event[NoOfSwitch - 1][NoOfEvent - 1] = *SW_M_Event_p;

  Config_SW_M_Write(SW_M_Event[0], NO_OF_SWITCHES, NO_OF_EVENTS_PER_SWITCH);

  EXIT_SUCCESS_FUNC(SW_M_SET_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_SET_EVENT, SW_M_Set_Event);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t SW_M_Get_Event(uint32 NoOfSwitch, uint32 NoOfEvent, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_GET_EVENT);

  *SW_M_Event_p = SW_M_Event[NoOfSwitch - 1][NoOfEvent - 1];

  EXIT_SUCCESS_FUNC(SW_M_GET_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_GET_EVENT, SW_M_Get_Event);

/*******************************************************************************
 *
 ******************************************************************************/
Status_t SW_M_Init(void)
{
  FuncIN(SW_M_INIT);

  Config_SW_M_Init(NO_OF_SWITCHES, NO_OF_EVENTS_PER_SWITCH);

  Config_SW_M_Read(SW_M_Event[0], NO_OF_SWITCHES, NO_OF_EVENTS_PER_SWITCH);

  EXIT_SUCCESS_FUNC(SW_M_INIT);
}
SW_M_FUNC_REGISTER(SW_M_INIT, SW_M_Init);
