#ifndef _Menu_Switches_h
#define _Menu_Switches_h

#include "Out.h"

#define NO_OF_SWITCHES                NO_OF_OUTS
#define SWITCHES_STRING_LENGTH        8

#define SWITCHES_SET_STRING_LENGTH    X_SIZE

#define SW_1_SET_STR    0x00000001
#define SW_2_SET_STR    0x00000002
#define SW_3_SET_STR    0x00000004
#define SW_4_SET_STR    0x00000008
#define SW_5_SET_STR    0x00000010
#define SW_6_SET_STR    0x00000020

extern char SW_Name[NO_OF_SWITCHES][SWITCHES_STRING_LENGTH];

#endif // _Menu_Switches_h