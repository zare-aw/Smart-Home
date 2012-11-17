#include <stdlib.h>
#include <string.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Out.h"

Status_t Do_Sw(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_SW);
  
  Out_t Out = {0};
  char *CommandString;
  int i, SwUpdate = 0;
  
  if(argc > 0)
  {
    for(i = 0; i < argc; i++)
    {
      CommandString = strstr(argv[i], "sw1=");
      if(CommandString != NULL)
      {
        if(atoi(CommandString + 4))
          Out_1_Set(NULL);
        else
          Out_1_Clr(NULL);
        
        SwUpdate = 1;
      }
      
      CommandString = strstr(argv[i], "sw2=");
      if(CommandString != NULL)
      {
        if(atoi(CommandString + 4))
          Out_2_Set(NULL);
        else
          Out_2_Clr(NULL);
        
        SwUpdate = 1;
      }
      
      CommandString = strstr(argv[i], "sw3=");
      if(CommandString != NULL)
      {
        if(atoi(CommandString + 4))
          Out_3_Set(NULL);
        else
          Out_3_Clr(NULL);
        
        SwUpdate = 1;
      }
      
      CommandString = strstr(argv[i], "sw4=");
      if(CommandString != NULL)
      {
        if(atoi(CommandString + 4))
          Out_4_Set(NULL);
        else
          Out_4_Clr(NULL);
        
        SwUpdate = 1;
      }
      
      CommandString = strstr(argv[i], "sw5=");
      if(CommandString != NULL)
      {
        if(atoi(CommandString + 4))
          Out_5_Set(NULL);
        else
          Out_5_Clr(NULL);
        
        SwUpdate = 1;
      }
      
      CommandString = strstr(argv[i], "sw6=");
      if(CommandString != NULL)
      {
        if(atoi(CommandString + 4))
          Out_6_Set(NULL);
        else
          Out_6_Clr(NULL);
        
        SwUpdate = 1;
      }
    } // for(i = 0; i < argc; i++)
    
    if(SwUpdate == 0)
      EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_SW);
  }
  else
  {
    Out_Get_State(OUTS_TO_SET, &Out);
    
    printcmd("\n # Out switches state:\n");
    printcmd(" # Sw_1 = %u\n", Out.S_1);
    printcmd(" # Sw_2 = %u\n", Out.S_2);
    printcmd(" # Sw_3 = %u\n", Out.S_3);
    printcmd(" # Sw_4 = %u\n", Out.S_4);
    printcmd(" # Sw_5 = %u\n", Out.S_5);
    printcmd(" # Sw_6 = %u\n", Out.S_6);
  }
  
  EXIT_SUCCESS_FUNC(DO_SW);
}
FUNC_REGISTER(DO_SW, Do_Sw);

CMD_CREATE(
  sw, NO_OF_OUTS, Do_Sw,
  "'sw' - Print switches state. 'sw swX=V' - Set switch, X - Number of switch, V - Value\n",
  "You can set multiple switches in one command call\n"
  "Example 'sw sw1=1 sw2=0 sw5=1'\n"
);
