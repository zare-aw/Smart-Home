#ifndef _SurfaceFlinger_h
#define _SurfaceFlinger_h

#define Y_SIZE  4
#define X_SIZE  20

#define PULL    0
#define FORCE   1

#define _SF_DEBUG

#ifdef _SF_DEBUG
#define SF_DEBUG(a) a
#else
#define SF_DEBUG(a)
#endif

// Function definitions
Status_t printd(uint8 line, const char *format, ...);
void clrd(void);
Status_t syncd(void);
void Console_Display_Dump(void);
void Console_Display_Update_Set(uint8 UpdateFlag);
Status_t Update_Display_Panel(uint8 Mode);

#endif