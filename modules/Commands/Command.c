#include "Command.h"


/*******************************************************************************
* Function for get start address of command section
*******************************************************************************/
Cmd_Tbl_t *Get_Cmd_Section_Begin(void)
{
  return __section_begin(".cmd");
}

/*******************************************************************************
* Function for get end address of command section
*******************************************************************************/
Cmd_Tbl_t *Get_Cmd_Section_End(void)
{
  return __section_end(".cmd");
}

/*******************************************************************************
* Function for get size on command section
*******************************************************************************/
uint32 Get_Cmd_Section_Size(void)
{
  return __section_size(".cmd");
}
