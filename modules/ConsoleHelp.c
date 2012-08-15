#include "Global_Defines.h"
#include "Includes.h"


/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Help(uint8 NoOfCommand)
{
  Function_IN(CONSOLE_HELP);
  uint8 i;
  
  if(QueueConsoleCommand[NoOfCommand][4] == '\0' || QueueConsoleCommand[NoOfCommand][5] == '\0')
  {
    printc("\r # Smart Home system console\n");
    printc(" # Supported commands:\n");
    printc(" - help\n");
    printc(" - status\n");
    printc(" - list\n");
    printc(" - info\n");
    printc(" - time\n");
    printc(" - date\n");
    printc(" - set-time\n");
    printc(" - set-date\n");
    printc(" - config\n");
    printc(" - set-config\n");
    printc(" - ir\n");
    printc(" - set-ir\n");
    printc(" - becklight\n");
    printc(" - set-becklight\n");
    printc(" - light-switch\n");
    printc(" - set-light-switch\n");
    printc(" - out-switch\n");
    printc(" - set-out-switch\n");
    printc(" - switch-settings\n");
    printc(" - set-switch-settings\n");
    printc(" - temp\n");
    printc(" - alarm\n");
    printc(" - set-alarm\n");
    printc(" - get-temp-alarm\n");
    printc(" - set-temp-alarm\n");
  }
  else
  {
    for(i = 0; i < (MAX_CONSOLE_COMMAND_LENGTH - 5); i++)
      QueueConsoleCommand[NoOfCommand][i] = QueueConsoleCommand[NoOfCommand][i+5];
    
    if(!strncmp("help", QueueConsoleCommand[NoOfCommand], 4))
    {
      printc("\r This is a help menu\n");
    }
    else if(!strncmp("status", QueueConsoleCommand[NoOfCommand], 6))
    {
      printc("\r # status - Print status of device\n");
    }
    else if(!strncmp("list", QueueConsoleCommand[NoOfCommand], 4))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("info", QueueConsoleCommand[NoOfCommand], 4))
    {
      printc("\r # 'info' - Print information about Hardware and Software\n");
    }
    else if(!strncmp("time", QueueConsoleCommand[NoOfCommand], 4))
    {
      printc("\r # 'time' - Print current time\n");
      printc("\r # 'time -a' - Print current time in 12h format\n");
    }
    else if(!strncmp("date", QueueConsoleCommand[NoOfCommand], 4))
    {
      printc("\r # 'date' - Print current date\n");
      printc("\r # 'date -l' - Print current date in extended format\n");
    }
    else if(!strncmp("set-time", QueueConsoleCommand[NoOfCommand], 8))
    {
      printc("\r # 'set-time hh:mm:ss' - Set time in 24h format\n");
      printc("\r # example: 'set-time 14:02:55'\n");
    }
    else if(!strncmp("set-date", QueueConsoleCommand[NoOfCommand], 8))
    {
      printc("\r # 'set-date dd.mm.yyyy' - Set date\n");
      printc("\r # example: 'set-date 25.05.2011'\n");
    }
    else if(!strncmp("config", QueueConsoleCommand[NoOfCommand], 6))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-config", QueueConsoleCommand[NoOfCommand], 10))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("ir", QueueConsoleCommand[NoOfCommand], 2))
    {
      printc("\r # ir - Get saved IR commands\n");
    }
    else if(!strncmp("set-ir", QueueConsoleCommand[NoOfCommand], 6))
    {
      printc("\r # 'set-ir n=X' - Set IR command, X - number of command, command are get from IR receiver\n");
      printc("\r # 'set-ir n=X a=Y c=Z m=U response=V' - Set IR command, X - number of command, Y - Address of command, Z - Command of command\n");
      printc("\r # U - CallMode, single or repetitive, V - what to do on this IR command, out_1_ON, out_3_OFF, dummy, ...\n");
      printc("\r # Address and Command (Y and Z) are from RC5 protocol\n");
      printc("\r # If Address and Command from RC5 are NULL, command are get from IR receiver, all other parameters are optional\n");
    }
    else if(!strncmp("becklight", QueueConsoleCommand[NoOfCommand], 9))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-becklight", QueueConsoleCommand[NoOfCommand], 13))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("light-switch", QueueConsoleCommand[NoOfCommand], 12))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-light-switch", QueueConsoleCommand[NoOfCommand], 16))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("out-switch", QueueConsoleCommand[NoOfCommand], 10))
    {
      printc("\r # Print out switch state\n");
    }
    else if(!strncmp("set-out-switch", QueueConsoleCommand[NoOfCommand], 14))
    {
      printc("\r # For set out switch\n");
      printc("\r # set-out-switch n=X v=Y, X - number of switch, 1, 2, ... , 6, Y - Value, 1 or 0\n");
    }
    else if(!strncmp("switch-setings", QueueConsoleCommand[NoOfCommand], 14))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-switch-setings", QueueConsoleCommand[NoOfCommand], 18))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("temp", QueueConsoleCommand[NoOfCommand], 4))
    {
      printc("\r # 'temp X' - X = all, id=.\n");
      printc("\r # all - get temperature from all sensors.\n");
      printc("\r # id= - set sensor ID.\n");
      printc("\r # if X parameter is missing, temp is printing from all sensors\n");
      printc("\r # example: 'temp id=2'\n");
    }
    else if(!strncmp("alarm", QueueConsoleCommand[NoOfCommand], 5))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-alarm", QueueConsoleCommand[NoOfCommand], 9))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("get-temp-alarm", QueueConsoleCommand[NoOfCommand], 14))
    {
      printc("\r # 'get-temp-alarm X' - X=int or X=ext\n");
      printc("\r # int - temp alarm on internal temperature sensor\n");
      printc("\r # ext - temp alarm on external temperature sensor\n");
      printc("\r # 'get-temp-alarm' - (without parameter) get temp alarms on all sensors\n");
      printc("\r # example: 'get-temp-alarm ext'\n");
    }
    else if(!strncmp("set-temp-alarm", QueueConsoleCommand[NoOfCommand], 14))
    {
      printc("\r # 'set-temp-alarm sensor=A temp=B event=C state=D alarmID=E response=F' - Set temperature alarm\n");
      printc("\r # sensor   A = int, ext. int - internal sensor, ext - external sensor\n");
      printc("\r # temp     B = temperature in celsius\n");
      printc("\r # event    C = above, bellow, equal, above_or_equal, bellow_or_equal, different\n");
      printc("\r # state    D = ON, OFF\n");
      printc("\r # alarmID  E = number, alarm ID\n");
      printc("\r # response F = out_1_ON, out_1_OFF, ... , out_6_ON, out_6_OFF, sound_alarm, dummy\n");
      printc("\r # If you set 'alarmID' all other parameters is updated on that alarm. Other parameters is no necessary to set\n");
      printc("\r # If you not set 'alarmID' you must set: sensor, temp, event, response. You can set and 'state' if you like\n");
      printc("\r # example 1: 'set-temp-alarm alarmID=2 temp=26 state=ON'\n");
      printc("\r # example 2: 'set-temp-alarm sensor=int temp=26 state=ON event=equal response=out_1_OFF'\n");
    }
    
  }
  
  RETURN_SUCCESS();
}
