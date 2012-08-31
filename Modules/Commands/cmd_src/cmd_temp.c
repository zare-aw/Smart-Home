#include <stdlib.h>
#include "Global_Defines.h"
#include "Command.h"
#include "Command_Func.h"
#include "Func_Trace.h"
#include "Temperature.h"
#include "StatusHandling.h"

Status_t Do_Temp(Cmd_Tbl_t *Cmd_Tbl, uint32 flag, uint32 argc, char *argv[])
{
  FuncIN(DO_TEMP);
  
  int Temp, i;
  uint16 SensorID;
  
  if(argc > 0)
  {
    SensorID = atoi(argv[0]);
    Temp = ReadTemp(SensorID);
    
    if(Temp == TEMP_EMPTY_SLOT)
    {
      printcmd("\r # Invalid SensorID! Sensor with ID = %d is not registered!\n", SensorID);
      EXIT_FUNC(CMD_INVALID_ARGUMENT, DO_TEMP);
    }
    
    printcmd("\r # SensorID = %d, Temperature = %d\n", SensorID, Temp);
  }
  else
  {
    for(i = 0; i < NO_OF_TEMP_SENSORS; i++)
    {
      Temp = ReadTemp(i);
      if(Temp != TEMP_EMPTY_SLOT)
        printcmd("\r # SensorID = %d, Temperature = %d\n", i, Temp);
    }
  }
  
  EXIT_SUCCESS_FUNC(DO_TEMP);
}
FUNC_REGISTER(DO_TEMP, Do_Temp);

CMD_CREATE(
  temp, 1, Do_Temp,
  "'temp' - Print temperature of all sensors. 'temp n' - Print temperature of specified sensor, 'n' is temp sensor ID\n",
  "'temp' - Print temperature of all available temperature sensors.\n"
  "'temp n' - (with 'n' as argument) Print temperature of specified sensor. 'n' is temperature sensor ID number.\n"
);

