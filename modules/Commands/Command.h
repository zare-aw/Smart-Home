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
#define CMD_INVALID_FUNCTION_POINTER            COMMANDS_OFFSET | 0x08
// Find_Cmd()
#define CMD_POSSIBLE_CMD                        COMMANDS_OFFSET | 0x10
#define CMD_NOT_FOUND                           COMMANDS_OFFSET | 0x11
// Run_Command()
#define CMD_EMPTY_COMMAND                       COMMANDS_OFFSET | 0x12
#define CMD_NOT_EXECUTED                        COMMANDS_OFFSET | 0x13
// Parse_Line()
#define CMD_TOO_MANY_ARGUMENTS                  COMMANDS_OFFSET | 0x15
#define CMD_ILEGAL_COMMAND_PARAMETER            COMMANDS_OFFSET | 0x16

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
Status_t Run_Command(const char *Cmd);

#endif
