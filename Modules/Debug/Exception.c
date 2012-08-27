#include "Global_Defines.h"
#include "Includes.h"

__arm __noreturn void Undefined_Instructions_Handler(uint32 Address, uint32 Instruction)
{
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Undefined Instruction ABORT !!!\n");
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Undefined Instruction Address = %X\n", Address);
  printc("\r>>> Undefined Instruction = %X\n", Instruction);
  Abort(UNDEFINED_INSTRUCTIONS_EXCEPTION);
  while(1);
}

__arm __noreturn void Software_Interrupt_Handler(uint32 Address, uint32 Instruction)
{
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Software Interrupt ABORT !!!\n");
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Software Interrupt Address = %X\n", Address);
  printc("\r>>> Software Interrupt Instruction = %X\n", Instruction);
  Abort(SOFTWARE_INTERRUPT_EXCEPTION);
  while(1);
}

__arm __noreturn void Prefetch_Abort_Handler(uint32 Address)
{
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Prefetch Abort ABORT !!!\n");
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Prefetch Abort Address = %X\n", Address);
  Abort(PREFETCH_ABORT_EXCEPTION);
  while(1);
}

__arm __noreturn void Data_Abort_Handler(uint32 Address, uint32 Instruction)
{
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Data Abort ABORT !!!\n");
  printc("\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  printc("\r>>> Data Abort Address = %X\n", Address);
  printc("\r>>> Data Abort Instruction = %X\n", Instruction);
  Abort(DATA_ABORT_EXCEPTION);
  while(1);
}

