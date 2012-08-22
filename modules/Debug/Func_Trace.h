#ifndef _Func_Trace_h
#define _Func_Trace_h

typedef unsigned long Func_t;

/*******************************************************************************
* Macros
*******************************************************************************/

/*******************************************************************************
* Modules offsets
*******************************************************************************/
#define CONSOLE_OFFSET          0x04000000
#define COMMANDS_OFFSET         0x05000000

/*******************************************************************************
* 
*******************************************************************************/
typedef struct Func_Tbl_s
{
  Func_t Func;        // Function flag
  char *Name;         // Function name
} Func_Tbl_t;

#pragma section=".func"

#define FUNC_REGISTER(Func, Name) \
__root __packed Func_Tbl_t Func_##Name @ ".Func" = {Func, #Name}

/*******************************************************************************
* Functions
*******************************************************************************/
void FuncIN(Func_t Function);
void FuncOUT(Func_t Function);

#endif
