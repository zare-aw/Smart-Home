#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"

#include "SW_Management.h"
#include "SW_Management_Debug.h"
#include "SW_Management_Func.h"

__packed SW_M_Event_t SW_M_Event[NO_OF_SWITCHES][NO_OF_EVENTS_PER_SWITCH] = {0};

/*******************************************************************************
 *
 ******************************************************************************/
Status_t SW_M_Set_Event(uint32 NoOfSwitch, uint32 NoOfEvent, SW_M_Event_t *SW_M_Event_p)
{
  FuncIN(SW_M_SET_EVENT);
  
  
  
  EXIT_SUCCESS_FUNC(SW_M_SET_EVENT);
}
SW_M_FUNC_REGISTER(SW_M_SET_EVENT, SW_M_Set_Event);