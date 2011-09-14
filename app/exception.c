#include "Includes.h"

void Undefined_Instructions_Handler(void)
{
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Undefined Instruction ABORT !!!\n");
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  Abort(UNDEFINED_INSTRUCTIONS_EXCEPTION);
  while(1);
}

void Software_Interrupt_Handler(void)
{
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Software Interrupt ABORT !!!\n");
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  Abort(SOFTWARE_INTERRUPT_EXCEPTION);
  while(1);
}

void Prefetch_Abort_Handler(void)
{
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Prefetch Abort ABORT !!!\n");
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  Abort(PREFETCH_ABORT_EXCEPTION);
  while(1);
}

void Data_Abort_Handler(void)
{
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Data Abort ABORT !!!\n");
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  Abort(DATA_ABORT_EXCEPTION);
  while(1);
}

