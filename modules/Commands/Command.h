#ifndef _Command_h
#define _Command_h

#include "Command_Defines.h"
#include "Command_Debug.h"

#define CFG_HELP

#pragma section=".cmd"



typedef struct Cmd_Tbl_s
{
  char *Name;         // Command name
  uint8 MaxArgs;      // Maximum number of arguments
  Status_t (*Cmd)(struct Cmd_Tbl_s *, uint32, uint32, char *[]);  // Implementation function
  char *Usage;        // Usage message
#ifdef CFG_HELP
  char *Help;         // Help message
#endif
} Cmd_Tbl_t;

#define CMD_CREATE(Name, MaxArgs, Cmd, Usage, Help) \
__root __packed Cmd_Tbl_t Cmd_##Name @ ".cmd" = {#Name, MaxArgs, Cmd, Usage, Help}


#endif