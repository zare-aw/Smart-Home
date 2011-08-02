#include "Includes.h"

#ifndef  __DRV_HD44780_H
#define  __DRV_HD44780_H

typedef uint8 HD44780_XY_DEF;
typedef uint8 HD44780_STRING_DEF;

/* Display address range definition */
#define HD44780_MIN_LINE1_ADD     0x00
#define HD44780_MAX_LINE1_ADD     0x27
#define HD44780_MIN_LINE2_ADD     0x40
#define HD44780_MAX_LINE2_ADD     0x67
/* Max DDRAM Address */
#define HD44780_MAX_DDRAM         0x67
/* Max CGRAM Address */
#define HD44780_MAX_CGRAM         0x3F
/* Address counter auto increment/decrement definition */
#define HD44780_AC_DECREMENT      0
#define HD44780_AC_INCREMENT      1
/* Auto Display shift or cursor move definition */
#define HD44780_CURSOR_MOVE       0
#define HD44780_DISPLAY_SHIFT     1
/* Number of line 1/2 definition */
#define HD44780_1_LINE            0
#define HD44780_2_LINE            1
/* Dot 5x8 or 5x10 definition */
#define HD44780_DOT_5_8           0
#define HD44780_DOT_5_10          1
/* Display On/Off definition */
#define HD44780_DISPLAY_OFF       0
#define HD44780_DISPLAY_ON        1
/* Cursor On/Off definition */
#define HD44780_CURSOR_OFF        0
#define HD44780_CURSOR_ON         1
/* Cursor Blink definition */
#define HD44780_CURSOR_NORM       0
#define HD44780_CURSOR_BLINK      1

typedef struct _HD44780_CTRL_DEF
{
  uint8  DisplayPos;
  uint16 AC_Direction  : 1;
  uint16 DisplayShift  : 1;
  uint16 Line          : 1;
  uint16 DotMode       : 1;
  uint16 DisplayOn     : 1;
  uint16 CursorOn      : 1;
  uint16 CursorBlink   : 1;
} HD44780_CTRL_DEF;

typedef enum _HD44780_ERROR_CODE_DEF
{
  HD44780_OK = 0,
  HD44780_BUSY_TO_ERROR,
  HD44780_ERROR,
  HD44780_OUT_OF_VISUAL,
} HD44780_ERROR_CODE_DEF;

HD44780_ERROR_CODE_DEF HD44780_PowerUpInit (void);
HD44780_CTRL_DEF * HD44780_GetSetting(void);
HD44780_ERROR_CODE_DEF HD44780_SetMode (void);
HD44780_ERROR_CODE_DEF HD44780_ClearDisplay (void);
HD44780_ERROR_CODE_DEF HD44780_ReturnToHome (void);
HD44780_ERROR_CODE_DEF HD44780_DisplayShift(uint8 DisplayOn, sint8 DisplayShift);
HD44780_ERROR_CODE_DEF HD44780_CursorPosSet (uint8 CursorOn, uint8 CursorBlink, HD44780_XY_DEF X, HD44780_XY_DEF Y);
HD44780_ERROR_CODE_DEF HD44780_RdCGRAM(HD44780_STRING_DEF * CG_Data, uint8 CGRAM_Add);
HD44780_ERROR_CODE_DEF HD44780_WrCGRAM (HD44780_STRING_DEF * CG_Data, uint8 CGRAM_Add);
HD44780_ERROR_CODE_DEF HD44780_StrShow(HD44780_XY_DEF X, HD44780_XY_DEF Y,  HD44780_STRING_DEF * DataStr);
uint8 HD44780_GetDisplayPosition(void);

#endif  /* __DRV_HD44780_H */
