#include <intrinsics.h>
#include "Global_Defines.h"
#include "StatusHandling.h"
#include "Initialization.h"
#include "Console.h"
#include "SurfaceFlinger.h"
#include "Temperature.h"
#include "Out.h"

void main()
{
  (void)Initialization();
  __enable_interrupt();
  
  printc("\n********************************\n");
  printc("\r****** Device Started !!! ******\n");
  printc("\r********************************\n");
  
  printd(1, "Display Test");
  printd(2, "Smart Home system");
  syncd();
  
  while(1)
  {
    (void)Console_Print_Pull();
    Console_Command_Execute(0);
    Temp_Work();
    Update_Display_Panel(PULL);
    (void)Out_Sync();
  } // while(1)
}   // main()


