#ifndef _SurfaceFlinger_h
#define _SurfaceFlinger_h

#define Y_SIZE  4
#define X_SIZE  20

#define PULL    0
#define FORCE   1

// Function definitions
Status_t printd(uint8 line, const char *format, ...);
Status_t syncd(void);
void Console_Display_Dump(void);
void Update_Display_Panel(uint8 Mode);

#endif