/*******************************************************************************
 * Copyright:
 *    Zarko Kostadinovski
 *
 * Author Name:
 *    Zarko Kostadinovski
 *
 * Author e-mail:
 *    zare_aw@yahoo.com
 *
 * File:
 *    Func_Trace.c
 *
 * Description:
 *    Implements Function trace debug future. This is usefull for tracing
 *    function, and get the list of function which is called to specific point.
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Console.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define MAX_FUNCTION_IN_BECKUP_BUFFER  10
#define FUNC_OUT_MASK                  0x80000000

#define DIR_IN        0
#define DIR_OUT       1

#define FUNC_OUT_OF_RANGE     0x01

/*******************************************************************************
 * Global variables
 ******************************************************************************/
Func_t FunctionsBuffer[MAX_FUNCTION_IN_BECKUP_BUFFER] = {0};
uint8 FunctionsInBuffer = 0;

/*******************************************************************************
 * Function for get start address of functions section
 ******************************************************************************/
static inline Func_Tbl_t *Get_Func_Section_Begin(void)
{
  return __section_begin(".func");
}

/*******************************************************************************
 * Function for get end address of functions section
 ******************************************************************************/
static inline Func_Tbl_t *Get_Func_Section_End(void)
{
  return __section_end(".func");
}

/*******************************************************************************
 * FuncIN - Function to register function code in function buffer
 *          on input of function
 * @in Function - Function code
 * @out void
 ******************************************************************************/
void FuncIN(Func_t Function)
{
  if(FunctionsInBuffer >= MAX_FUNCTION_IN_BECKUP_BUFFER)
    FunctionsInBuffer = 0;
  
  FunctionsBuffer[FunctionsInBuffer] = Function;
  FunctionsInBuffer ++;
}

/*******************************************************************************
 * FuncOUT - Function to register function code in function buffer
 *          on exit of function
 * @in Function - Function code
 * @out void
 ******************************************************************************/
void FuncOUT(Func_t Function)
{
  if(FunctionsInBuffer >= MAX_FUNCTION_IN_BECKUP_BUFFER)
    FunctionsInBuffer = 0;
  
  FunctionsBuffer[FunctionsInBuffer] = Function;
  FunctionsBuffer[FunctionsInBuffer] |= FUNC_OUT_MASK;
  FunctionsInBuffer ++;
}

/*******************************************************************************
 * Get_Func - Function to get some function from function buffer.
 * @in NoOfFunc - Which function from function buffer to return
 *                -1 - return latest function
 *                -X - return X function previous in function buffer
 * @out Func_t - Return requested function
 ******************************************************************************/
static Func_t Get_Func(int NoOfFunc)
{
  if((-NoOfFunc) > MAX_FUNCTION_IN_BECKUP_BUFFER)
    return FUNC_OUT_OF_RANGE;
  
  int Func = FunctionsInBuffer + NoOfFunc;
  
  if(Func < 0)
    Func += MAX_FUNCTION_IN_BECKUP_BUFFER;
  
  return FunctionsBuffer[Func];
}

/*******************************************************************************
 * Function for find function table entry for a function flag
 * @in Func - Func_t function flag
 * @out **Func_Tbl_p - Double pointer for returning Func_Tbl structire
 *                      of the Func
 * @out Status_t - Status
 ******************************************************************************/
static Status_t Find_Func(const Func_t Func, Func_Tbl_t **Func_Tbl_p)
{
  Func_Tbl_t *Func_Section_Begin = Get_Func_Section_Begin();
  Func_Tbl_t *Func_Section_End = Get_Func_Section_End();
  Func_Tbl_t *Func_Tbl;
  
  if((Func == NULL) || (Func_Tbl_p == NULL))
  {
    // FATAL ERROR. TODO: Blink sime diode, do something :)
  }
  
  for(Func_Tbl = Func_Section_Begin; Func_Tbl != Func_Section_End; Func_Tbl++)
  {
    if(Func_Tbl -> Func == Func)
    {
      *Func_Tbl_p = Func_Tbl;   // Full match
      return SUCCESS;
    }
  } // for
  
  return FUNC_NOT_FOUND;
}

/*******************************************************************************
 * Function for print function history. It prints strings on all functions which
 *   function flag is in FunctionsBuffer.
 * @in void
 * @out void
 ******************************************************************************/
void Print_Func_History(void)
{
  uint16 i = 0;
  Func_t Func;
  Func_Tbl_t *Func_Tbl_p;
  uint8 DirFlag = DIR_IN;
  
  printc("\n # Function history:\n");
  
  for(i = MAX_FUNCTION_IN_BECKUP_BUFFER; i != 0 ; i--)
  {
    Func = Get_Func(-i);
    
    if(Func != FUNC_OUT_OF_RANGE)
    {
      if(Func == 0)
        continue;
      
      if(Func & FUNC_OUT_MASK)
        DirFlag = DIR_OUT;
      else
        DirFlag = DIR_IN;
      
      Func &= ~FUNC_OUT_MASK;
      
      if(Find_Func(Func, &Func_Tbl_p) == SUCCESS)
      {
        if(DirFlag == DIR_IN)
          printc(" - %s IN\n", Func_Tbl_p -> Name);
        else
          printc(" - %s OUT\n", Func_Tbl_p -> Name);
      }
      else
      {
        if(DirFlag == DIR_IN)
          printc(" - FunctionFlag = 0x%08X  IN\n", Func);
        else
          printc(" - FunctionFlag = 0x%08X  OUT\n", Func);
      }
    }
    else
      break;
  } // for(i = 1; i < MAX_FUNCTION_IN_BECKUP_BUFFER; i++)
}