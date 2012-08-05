#ifndef _Command_h
#define _Command_h

#include "Command_Defines.h"
#include "Command_Debug.h"
#include "StatusHandling.h"

#define CFG_HELP

#pragma section=".cmd"

/**** Cmd Global error state defines ****/
#define CMD_SUCCESS                             COMMANDS_OFFSET | 0x00
#define CMD_ERROR                               COMMANDS_OFFSET | 0x01
#define CMD_GENERAL_ERROR                       COMMANDS_OFFSET | 0x02
#define CMD_FATAL_ERROR                         COMMANDS_OFFSET | 0x03
#define	CMD_UNKNOWN_ERROR		        COMMANDS_OFFSET | 0x04
#define CMD_INVALID_INPUT_PARAMETER             COMMANDS_OFFSET | 0x05
#define CMD_INVALID_INIT_INPUT_PARAMETER        COMMANDS_OFFSET | 0x06
#define CMD_INVALID_INPUT_POINTER               COMMANDS_OFFSET | 0x07

/**** State defines *****/
// Find_Cmd()
#define POSSIBLE_CMD                COMMANDS_OFFSET | 0x01
#define CMD_NOT_FOUND               COMMANDS_OFFSET | 0x02

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