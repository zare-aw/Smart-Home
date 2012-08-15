#ifndef _Global_Defines_h
#define _Global_Defines_h

typedef unsigned char       uint8;
typedef signed char         sint8;
typedef unsigned short      uint16;
typedef signed short        sint16;
typedef unsigned int        uint32;
typedef signed int          sint32;
typedef unsigned long long  uint64;
typedef signed long long    sint64;

/*******************************************************************************
* Global Defines
*******************************************************************************/
#ifndef DISABLE
#define DISABLE   0
#endif

#ifndef ENABLE
#define ENABLE    1
#endif

#ifndef OFF
#define OFF       0
#endif

#ifndef ON
#define ON        1
#endif

#ifndef FALSE
#define FALSE     0
#endif

#ifndef TRUE
#define TRUE      !FALSE
#endif

#endif