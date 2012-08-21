#ifndef _Func_Trace_h
#define _Func_Trace_h

typedef unsigned long Func_t;

/*******************************************************************************
* Modules offsets
*******************************************************************************/
#define COMMANDS_OFFSET         0x05000000

/*******************************************************************************
* Functions
*******************************************************************************/
void FuncIN(Func_t Function);
void FuncOUT(Func_t Function);

#endif
