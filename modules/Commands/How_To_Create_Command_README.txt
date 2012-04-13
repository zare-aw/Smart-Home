Commands are added by creating a new command structure.
This is done by first including Command.h

Then using the CMD_CREATE() macro to fill in a Cmd_Tbl_t struct.

CMD_CREATE(Name, MaxArgs, Cmd, Usage, Help)

Name:	 Is the name of the commad. THIS IS NOT a string.
MaxArgs: The maximumn numbers of arguments this function takes
Cmd: 	 Function pointer Status_t (*Cmd)(struct Cmd_Tbl_s *, uint32, uint32, char *[]);
Usage:	 Short description. This is a string
Help:	 Long description. This is a string


**** Behinde the scene ******

The structure created is named with a special prefix (Cmd_)
and placed by the linker in a special section (.cmd).

This makes it possible for the final link to extract all commands
compiled into any object code and construct a static array so the
command can be found in an array starting at __section_begin(".cmd").

Created by Zarko Kostadinovski