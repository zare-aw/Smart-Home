#ifndef _Configs_h
#define _Configs_h

#include "SW_Management.h"

/**** Exported Functions ****/
Status_t Config_SW_M_Write(SW_M_Event_t __packed *SW_M_Event_p, uint32 NoOfSW, uint32 NoOfEventsPerSW);
Status_t Config_SW_M_Read(SW_M_Event_t __packed *SW_M_Event_p, uint32 NoOfSW, uint32 NoOfEventsPerSW);
Status_t Config_SW_M_Init(void);

#endif // _Configs_h