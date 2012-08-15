/******************************************************************************
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
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "Global_Defines.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define MAX_FUNCTION_IN_BECKUP_BUFFER  10
#define FUNC_OUT_MASK                  0x80000000

/******************************************************************************
 * Typedefs
 *****************************************************************************/
typedef unsigned long Function_t;

/******************************************************************************
 * Global variables
 *****************************************************************************/
Function_t FunctionsBuffer[MAX_FUNCTION_IN_BECKUP_BUFFER] = {0};
uint8 FunctionsInBuffer = 0;

/*******************************************************************************
 * FuncIN - Function to register function code in function buffer
 *          on input of function
 * @in Function - Function code
 * @out void
 ******************************************************************************/
void FuncIN(Function_t Function)
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
void FuncOUT(Function_t Function)
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
 * @out Function_t - Return requested function
 ******************************************************************************/
Function_t Get_Func(int NoOfFunc)
{
  if((-NoOfFunc) > MAX_FUNCTION_IN_BECKUP_BUFFER)
    return NULL;

  int Func = FunctionsInBuffer + NoOfFunc;
  
  if(Func < 0)
    Func += MAX_FUNCTION_IN_BECKUP_BUFFER;
  
  return FunctionsBuffer[Func];
}

