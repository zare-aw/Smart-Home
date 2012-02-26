#ifndef _Command_h
#define _Command_h

#include "Command_Defines.h"

#define CFG_HELP

typedef unsigned int Status_t;

#pragma section=".cmd"

typedef struct CmdTbl_s
{
  char *Name;         // Command name
  uint8 MaxArgs;      // Maximum number of arguments
  Status_t (*Cmd)(struct CmdTbl_s *, uint32, uint32, char *[]);  // Implementation function
  char *Usage;        // Usage message
#ifdef CFG_HELP
  char *Help;         // Help message
#endif
} CmdTbl_t;

#define CMD_CREATE(Name, MaxArgs, Cmd, Usage, Help) \
__root __packed CmdTbl_t Cmd_##Name @ ".cmd" = {#Name, MaxArgs, Cmd, Usage, Help}


#endif