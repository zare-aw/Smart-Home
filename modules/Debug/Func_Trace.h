#ifndef _Func_Trace_h
#define _Func_Trace_h

/*******************************************************************************
* Macros
*******************************************************************************/

/*******************************************************************************
* Modules offsets
*******************************************************************************/
#define FUNC_TRACE_OFFSET       0x01000000
#define CONSOLE_OFFSET          0x04000000
#define COMMANDS_OFFSET         0x05000000

/*******************************************************************************
* Func_Trace status
*******************************************************************************/
#define FUNC_NOT_FOUND      FUNC_TRACE_OFFSET | 0x01

/*******************************************************************************
* Typedefs
*******************************************************************************/
typedef unsigned long Func_t;

typedef struct Func_Tbl_s
{
  Func_t Func;        // Function flag
  char *Name;         // Function name
} Func_Tbl_t;

#pragma section=".func"

#define FUNC_REGISTER(Func, Name) \
__root __packed Func_Tbl_t Func_##Name @ ".func" = {Func, #Name}

/*******************************************************************************
* Functions
*******************************************************************************/
void FuncIN(Func_t Function);
void FuncOUT(Func_t Function);
void Print_Func_History(void);

#endif
