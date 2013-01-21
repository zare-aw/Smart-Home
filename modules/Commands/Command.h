#ifndef _Command_h
#define _Command_h

#include "Command_Defconfig.h"
#include "Func_Trace.h"
#include "StatusHandling.h"

/**** Cmd Global error state defines ****/
#define CMD_SUCCESS                             0x00
#define CMD_ERROR                               COMMANDS_OFFSET | 0x01
#define CMD_GENERAL_ERROR                       COMMANDS_OFFSET | 0x02
#define CMD_FATAL_ERROR                         COMMANDS_OFFSET | 0x03
#define	CMD_UNKNOWN_ERROR		        COMMANDS_OFFSET | 0x04
#define CMD_INVALID_INPUT_PARAMETER             COMMANDS_OFFSET | 0x05
#define CMD_INVALID_INIT_INPUT_PARAMETER        COMMANDS_OFFSET | 0x06
#define CMD_INVALID_INPUT_POINTER               COMMANDS_OFFSET | 0x07
#define CMD_INVALID_FUNCTION_POINTER            COMMANDS_OFFSET | 0x08

#define CMD_POSSIBLE_CMD                        COMMANDS_OFFSET | 0x10
#define CMD_NOT_FOUND                           COMMANDS_OFFSET | 0x11

#define CMD_EMPTY_COMMAND                       COMMANDS_OFFSET | 0x12
#define CMD_NOT_EXECUTED                        COMMANDS_OFFSET | 0x13

#define CMD_INVALID_ARGUMENT                    COMMANDS_OFFSET | 0x14
#define CMD_MISSING_ARGUMENT                    COMMANDS_OFFSET | 0x15
#define CMD_TOO_MANY_ARGUMENTS                  COMMANDS_OFFSET | 0x16
#define CMD_ILEGAL_COMMAND_PARAMETER            COMMANDS_OFFSET | 0x17

typedef struct Cmd_Init_Parameters_s
{
  Status_t (*putscmd)(const char *);  // Function pointer for return string
} Cmd_Init_Parameters_t;

typedef struct Cmd_Tbl_s
{
  const char *Name;         // Command name
  const uint8 MaxArgs;      // Maximum number of arguments
  Status_t (*Cmd)(struct Cmd_Tbl_s *, uint32, uint32, char *[]);  // Implementation function
  const char *Usage;        // Usage message
#ifdef CFG_HELP
  const char *Help;         // Help message
#endif
} Cmd_Tbl_t;

#pragma section=".cmd"

#define CMD_CREATE(Name, MaxArgs, Cmd, Usage, Help) \
__root __packed const Cmd_Tbl_t Cmd_##Name @ ".cmd" = {#Name, MaxArgs, Cmd, Usage, Help}

// Functions
inline Cmd_Tbl_t *Get_Cmd_Section_Begin(void);
inline Cmd_Tbl_t *Get_Cmd_Section_End(void);
uint32 Get_Cmd_Section_Size(void);
Status_t Find_Cmd(const char *Cmd, Cmd_Tbl_t **Cmd_Tbl_p);
Status_t Run_Command(const char *Cmd);
Status_t printcmd(const char *format, ...);
Status_t Commands_Init(Cmd_Init_Parameters_t *Cmd_Init_Parameters_p);

#endif
