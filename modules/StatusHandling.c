#include "Global_Defines.h"
#include "StatusHandling.h"
#include "Includes.h"

/*******************************************************************************
 * Function for handle Fatal Error. This function prints error and
 *   function history. There is no return from this function!
 * @in Status - Error which cause Fatal Abort!
 * @out void
 ******************************************************************************/
void Fatal_Abort(Status_t Status)
{
  printc("\n # ABORT !!!\n");
  if(Status < SUCCESS)
    printc(" # ERROR: -0x%08X\n", -Status);
  else
    printc(" # ERROR: 0x%08X\n", Status);
  
  Print_Func_History();
  
  __disable_interrupt();
  
  while(1)
  {
    Console_Print_Pull();
  } // while(1)
}
