#include "Includes.h"

void main()
{
  (void)Initialization();
  __enable_interrupt();
  
  printc("\n********************************\n");
  printc("\r****** Device Started !!! ******\n");
  printc("\r********************************\n");
  
  while(1)
  {
    (void)Console_Print_Pull();
    Console_Command_Execute(0);
//    (void)Out_Sync();
  } // while(1)
}   // main()


