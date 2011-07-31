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
      printc("\r # info - Print information about Hardware and Software\n");
    }
    else if(!strncmp("time", QueueConsoleCommand[NoOfCommand], 4))
    {
      printc("\r # time - Print current time\n");
      printc("\r # time -a - Print current time in 12h format\n");
    }
    else if(!strncmp("date", QueueConsoleCommand[NoOfCommand], 4))
    {
      printc("\r # date - Print current date\n");
      printc("\r # date -l - Print current date in extended format\n");
    }
    else if(!strncmp("set-time", QueueConsoleCommand[NoOfCommand], 8))
    {
      printc("\r # set-time hh:mm:ss - Set time in 24h format\n");
      printc("\r # ex: set-time 14:02:55\n");
    }
    else if(!strncmp("set-date", QueueConsoleCommand[NoOfCommand], 8))
    {
      printc("\r # set-date dd.mm.yyyy - Set date\n");
      printc("\r # ex: set-date 25.05.2011\n");
    }
    else if(!strncmp("config", QueueConsoleCommand[NoOfCommand], 10))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-config", QueueConsoleCommand[NoOfCommand], 10))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("ir", QueueConsoleCommand[NoOfCommand], 6))
    {
      printc("\r # ir - Get saved IR commands\n");
    }
    else if(!strncmp("set-ir", QueueConsoleCommand[NoOfCommand], 6))
    {
      printc("\r # set-ir n=X - Set IR command, X - number of command, command are get from IR receiver\n");
      printc("\r # set-ir n=X a=Y c=Z - Set IR command, X - number of command, Y - Address of command, Z - Command of command\n");
      printc("\r # Address and Command (X and Y) are from RC5 protocol\n");
    }
    else if(!strncmp("becklight", QueueConsoleCommand[NoOfCommand], 13))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-becklight", QueueConsoleCommand[NoOfCommand], 13))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("light-switch", QueueConsoleCommand[NoOfCommand], 16))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-light-switch", QueueConsoleCommand[NoOfCommand], 16))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("out-switch", QueueConsoleCommand[NoOfCommand], 14))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-out-switch", QueueConsoleCommand[NoOfCommand], 14))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("switch-setings", QueueConsoleCommand[NoOfCommand], 18))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-switch-setings", QueueConsoleCommand[NoOfCommand], 18))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("temp", QueueConsoleCommand[NoOfCommand], 4))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("alarm", QueueConsoleCommand[NoOfCommand], 5))
    {
      printc("\r # Not implemented\n");
    }
    else if(!strncmp("set-alarm", QueueConsoleCommand[NoOfCommand], 9))
    {
      printc("\r # Not implemented\n");
    }
    
  }
  
  RETURN_SUCCESS();
}
