#include <stdlib.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "PWM_Backlight.h"
#include "StatusHandling.h"

Status_t Do_Bl(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_BL);
  
  uint16 Intensity;
  
  if(argc > 0)
  {
    Intensity = atoi(argv[0]);
    if(Intensity > 1023)
      EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_BL);
    
    Set_PWM_Backlight_Intensity(Intensity);
  }
  else
  {
    Get_PWM_Backlight_Intensity(&Intensity);
    printcmd("\r # Backlight level = %d (0-1023)\n", Intensity);
  }
  
  EXIT_SUCCESS_FUNC(DO_BL);
}
FUNC_REGISTER(DO_BL, Do_Bl);

CMD_CREATE(
  bl, 1, Do_Bl,
  "'bl' - Print Backlight level. 'bl n' - Set Backlight level, 'n' is level number\n",
  "'bl' - Print Backlight level. From 0 to 1023.\n"
  "'bl n' - (with 'n' as argument) Set Backlight level to n value. 'n' range is from 0 to 1023\n"
);

