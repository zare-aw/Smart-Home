#ifndef _Command_h
#define _Command_h

#include "Command_Defines.h"
#include "Command_Debug.h"

#define CFG_HELP

#pragma section=".cmd"


// State defines
// Find_Cmd()
#define POSSIBLE_CMD                0x05000001
#define CMD_NOT_FOUND               0x05000002

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


// Functions
Cmd_Tbl_t *Get_Cmd_Section_Begin(void);
Cmd_Tbl_t *Get_Cmd_Section_End(void);
uint32 Get_Cmd_Section_Size(void);
Status_t Find_Cmd(const char *Cmd, Cmd_Tbl_t **Cmd_Tbl_p);

#endif