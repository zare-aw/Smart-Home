#include "Command.h"
#include "Command_Func.h"
#include <string.h>


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

/*******************************************************************************
* Function for find command table entry for a command
*******************************************************************************/
Status_t Find_Cmd(const char *Cmd, Cmd_Tbl_t **Cmd_Tbl_p)
{
  FUNCTION_IN(FIND_CMD);
  Cmd_Tbl_t *Cmd_Section_Begin = Get_Cmd_Section_Begin();
  Cmd_Tbl_t *Cmd_Section_End = Get_Cmd_Section_End();
  Cmd_Tbl_t *Cmd_Tbl;
  Cmd_Tbl_t *Cmd_Tbl_Temp;
  int Len;
  int N_Found = 0;
  
  if((Cmd == NULL) || (Cmd_Tbl_p == NULL))
    FATAL_ABORT(CMD_INVALID_INPUT_POINTER, FIND_CMD);
  
  Len = strlen(Cmd);
  
  for(Cmd_Tbl = Cmd_Section_Begin; Cmd_Tbl != Cmd_Section_End; Cmd_Tbl++)
  {
    if(strncmp(Cmd, Cmd_Tbl -> Name, Len) == 0)
    {
      if (Len == strlen(Cmd_Tbl -> Name))
      {
        *Cmd_Tbl_p = Cmd_Tbl;   // Full match
        FUNC_EXIT(CMD_SUCCESS, FIND_CMD);
      }
      
      Cmd_Tbl_Temp = Cmd_Tbl;
      N_Found++;
    }
  } // for
  
  if(N_Found == 1)
  {
    *Cmd_Tbl_p = Cmd_Tbl_Temp;
    FUNC_EXIT(POSSIBLE_CMD, FIND_CMD);
  }
  
  FUNC_EXIT(CMD_NOT_FOUND, FIND_CMD);
}