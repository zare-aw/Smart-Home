#include "Global_Defines.h"
#include "Includes.h"

#if (HD44780_BUS_WIDTH != 4) && (HD44780_BUS_WIDTH != 8)
#error The HD44780_BUS_WIDTH must be 8 or 4!
#endif

/* delay definition */
#define HD44780_POWER_UP_DLY          40000   // 40 ms
#define HD44780_FIRST_COMM_DLY        4100    // 4.1 ms
#define HD44780_SECOND_COMM_DLY       100     // 100 us
#define HD44780_MAX_COMM_DLY          3000    // 3ms

/* HD44780 command set */
#define HD44780_CLEAR                 0x01    /* Clear display */
#define HD44780_RETURN                0x02    /* Return display to home */

#define HD44780_ENTRY_MODE            0x04    /* Set Cursor, Display move and direction */
#define HD44780_ENTRY_MODE_CURSOR_S   0x00
#define HD44780_ENTRY_MODE_BOTH_S     0x01
#define HD44780_ENTRY_MODE_DEC        0x00
#define HD44780_ENTRY_MODE_INC        0x02

#define HD44780_DISPLAY_CTRL          0x08    /* Set display and cursor mode */
#define HD44780_DISPLAY_CTRL_C_NORM   0x00
#define HD44780_DISPLAY_CTRL_C_BLINK  0x01
#define HD44780_DISPLAY_CTRL_C_OFF    0x00
#define HD44780_DISPLAY_CTRL_C_ON     0x02
#define HD44780_DISPLAY_CTRL_D_OFF    0x00
#define HD44780_DISPLAY_CTRL_D_ON     0x04

#define HD44780_DISPLAY_MOVE          0x10    /* Display and cursor move */
#define HD44780_DISPLAY_MOVE_LEFT     0x00
#define HD44780_DISPLAY_MOVE_RIGHT    0x04
#define HD44780_DISPLAY_MOVE_C        0x00
#define HD44780_DISPLAY_MOVE_D        0x08

#define HD44780_FUNCTION_SET          0x20    /* Set display function */
#define HD44780_FUNCTION_SET_DOT_5_8  0x00
#define HD44780_FUNCTION_SET_DOT_5_10 0x04
#define HD44780_FUNCTION_SET_1_LINE   0x00
#define HD44780_FUNCTION_SET_2_LINE   0x08
#define HD44780_FUNCTION_SET_4_BIT    0x00
#define HD44780_FUNCTION_SET_8_BIT    0x10

#define HD44780_SET_CGRAM_ADD         0x40    /* Set AC point to CGRAM */
#define HD44780_SET_DDRAM_ADD         0x80    /* Set AC point to DDRAM */

// HD44780 Read Status
#define HD44780_STATUS_AC_MASK        0x7F    /* AC Mask */
#define HD44780_STATUS_BUSY_MASK      0x80    /* Busy Mask */

#define HD44780_BUSY_CHECK            TRUE
#define HD44780_NOT_BUSY_CHECK        FALSE

HD44780_CTRL_DEF HD4478_Ctrl =
{
  0,                    /* Display Position */
  HD44780_AC_DIR,       /* Address counter direction */
  HD44780_MOVE,         /* Cursor or display move */
  HD44780_LINE,         /* Number of line */
  HD44780_DOT_MATRIX,   /* Character Dot matrix */
  HD44780_DISPLAY_STATE,/* Display state On or Off */
  HD44780_CURSOR_STATE, /* Cursor state On or Off */
  HD44780_CURSOR_MODE,  /* Cursor mode Blink or not */
};

#if HD44780_WR == 0
sint8 DataRamAddHold = 0;
#endif

#if HD44780_BUS_WIDTH == 8
  #define HD44780_WRITE_COMMAND_HIGH(Data)  HD44780_Write_IO(Data)
#else
  #define HD44780_WRITE_COMMAND_HIGH(Data)  HD44780_Write_IO((Data >> 4))
#endif

/*************************************************************************
* Function Name: HD44780_Write_Data
* @in: uint8 Data
* @out: None
* Description: Write data to HD44780
*************************************************************************/
void HD44780_Write_Data(uint8 Data)
{
  HD44780_Set_RS(1);
#if HD44780_BUS_WIDTH == 8
  HD44780_Write_IO(Data);
#else
  HD44780_Write_IO((Data >> 4) & 0xF);
  HD44780_Write_IO(Data & 0xF);
#endif
}

#if HD44780_WR > 0
/*************************************************************************
* Function Name: HD44780_Read_Data
* @in: None
* @out: uint8
* Description: Read data from HD44780
*************************************************************************/
uint8 HD44780_Read_Data(void)
{
  uint8 Data;
  HD44780_Set_RS(1);
#if HD44780_BUS_WIDTH == 8
  Data = HD44780_Read_IO();
#else
  Data = (HD44780_Read_IO() << 4) & 0xF0;
  Data |= HD44780_Read_IO()       & 0x0F;
#endif
  return Data;
}
#endif

/*************************************************************************
* Function Name: HD44780_Write_Command
* @in: uint8 Command
* @out: None
* Description: Send command to HD44780
*************************************************************************/
void HD44780_Write_Command(uint8 Command)
{
  HD44780_Set_RS(0);
#if HD44780_BUS_WIDTH == 8
  HD44780_Write_IO(Command);
#else
  HD44780_Write_IO((Command >> 4) & 0xF);
  HD44780_Write_IO(Command & 0xF);
#endif
}

#if HD44780_WR > 0
/*************************************************************************
* Function Name: HD44780_Read_Status
* @in: None
* @out: uint8
* Description: Read status of HD44780
*************************************************************************/
uint8 HD44780_Read_Status(void)
{
  uint8 Data;
  HD44780_Set_RS(0);
#if HD44780_BUS_WIDTH == 8
  Data = HD44780_Read_IO();
#else
  Data = (HD44780_Read_IO() << 4) & 0xF0;
  Data |= HD44780_Read_IO()       & 0x0F;
#endif
  return Data;
}
#endif

/*************************************************************************
 * Function Name: HD44780_GetDDRamAdd
 * Parameters: HD44780_XY_DEF X,
 *             HD44780_XY_DEF Y,
 *             Int8U * DDAdd
 * Return: HD44780_ERROR_CODE_DEF
 *         HD44780_OK  0: Pass
 *       HD44780_ERROR 2: Out of boundary
 * Description: Calculate DDRAM address by X,Y coordinate
 *
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_GetDDRamAdd(HD44780_XY_DEF X, HD44780_XY_DEF Y, uint8 * DDAdd)
{
  /* Find Address by coordinate */
  if (Y > 3)
  {
    return HD44780_ERROR;
  }
  if (X > HD44780_MAX_LINE1_ADD)
  {
    return HD44780_ERROR;
  }
  *DDAdd = X;
  if (Y > 0)
  {
    switch(Y){
      case 1:
        * DDAdd += HD44780_MIN_LINE2_ADD;
        break;
      case 2:
        * DDAdd += HD44780_MIN_LINE3_ADD;
        break;
      case 3:
        * DDAdd += HD44780_MIN_LINE4_ADD;
        break;
      default:
        break;
    }
  }
  return HD44780_OK;
}


/*************************************************************************
 * Function Name: HD44780_CheckVisual
 * Parameters: Int8U DDRamAdd
 * Return: HD44780_ERROR_CODE_DEF
 *         HD44780_OK           : Pass
 *         HD44780_ERROR        : Out of address boundary
 *         HD44780_OUT_OF_VISUAL: Out of visual boundary
 * Description: Whether current DDRAM address is into visual area
 *
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_CheckVisual(uint8 DDRamAdd)
{
  uint8 LastPos = 0;
  if (DDRamAdd > HD44780_MAX_LINE4_ADD)
  {
    return HD44780_ERROR;
  }
  if((DDRamAdd > HD44780_MAX_LINE3_ADD) && (DDRamAdd < HD44780_MIN_LINE2_ADD))
  {
    return HD44780_ERROR;
  }
  if (DDRamAdd >= HD44780_MIN_LINE2_ADD)
  {
    /* Convert address to line 1 address */
    DDRamAdd %= 0x40;
  }
  LastPos = HD4478_Ctrl.DisplayPos+HD44780_HORIZONTAL_SIZE;
  if(LastPos > HD44780_MAX_LINE1_ADD)
  {
    if((DDRamAdd > HD44780_MAX_LINE1_ADD - HD4478_Ctrl.DisplayPos) && (DDRamAdd < HD4478_Ctrl.DisplayPos))
    {
      return HD44780_OUT_OF_VISUAL;
    }
    LastPos = HD44780_MAX_LINE1_ADD;
  }
  if ((DDRamAdd < HD4478_Ctrl.DisplayPos) || (DDRamAdd > LastPos))
  {
    return HD44780_OUT_OF_VISUAL;
  }
  return HD44780_OK;
}

/*************************************************************************
 * Function Name: HD44780_BusyCheck
 * Parameters: Int8U * AddCount, Int32U MaxDly
 * Return: HD44780_ERROR_CODE_DEF
 *         HD44780_OK  0: Pass
 *     HD44780_ERROR 1: Busy check Time Out
 * Description: Wait MaxDly *100u or until the busy flag is clear
 *
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_BusyCheck(uint8 * AddCount, uint32 MaxDly)
{
#if HD44780_WR > 0
uint8 AddHold;
#endif
  for (;MaxDly;--MaxDly)
  {
#if HD44780_WR > 0
    AddHold = HD44780_Read_Status();
    if ((AddHold & HD44780_STATUS_BUSY_MASK) == 0)
    {
      /* Wait 1.5 * Tlcd */
      HD44780_BUS_DLY();
      HD44780_BUS_DLY();
      /* Get current AC */
      AddHold = HD44780_Read_Status();
      AddHold &= HD44780_STATUS_AC_MASK;
      if(AddCount != NULL)
      {
        *AddCount = AddHold;
      }
      return HD44780_OK;
    }
#endif
    Dly(100, 'u', NULL);
  }
#if HD44780_WR > 0
  return HD44780_BUSY_TO_ERROR;
#else
  if(AddCount != NULL)
  {
    *AddCount = DataRamAddHold;
  }
  return HD44780_OK;
#endif
}

/*************************************************************************
 * Function Name: HD44780_Init
 * Parameters: none
 * Return: HD44780_ERROR_CODE_DEF
 *         HD44780_OK  0: Pass
 *     HD44780_ERROR 1: Busy check Time Out
 * Description: Init HD44780 after power-up
 *
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_PowerUpInit(void)
{
  uint8 Command;
  HD4478_Ctrl.DisplayPos = 0;
  /* Init MCU IO */
  HD44780_IO_Init();
  /* Power up init sequence */
  Dly(HD44780_POWER_UP_DLY, 'u', NULL);
  HD44780_Set_RS(0);
  HD44780_WRITE_COMMAND_HIGH(HD44780_FUNCTION_SET+HD44780_FUNCTION_SET_8_BIT);
  Dly(HD44780_FIRST_COMM_DLY, 'u', NULL);
  HD44780_WRITE_COMMAND_HIGH(HD44780_FUNCTION_SET+HD44780_FUNCTION_SET_8_BIT);
  Dly(HD44780_SECOND_COMM_DLY, 'u', NULL);
  HD44780_WRITE_COMMAND_HIGH(HD44780_FUNCTION_SET+HD44780_FUNCTION_SET_8_BIT);
  Dly(HD44780_SECOND_COMM_DLY, 'u', NULL);
  /* Display Function set */
#if HD44780_BUS_WIDTH == 8
  Command = HD44780_FUNCTION_SET + HD44780_FUNCTION_SET_8_BIT;
#else
  HD44780_WRITE_COMMAND_HIGH(HD44780_FUNCTION_SET + HD44780_FUNCTION_SET_4_BIT);
  Dly(HD44780_SECOND_COMM_DLY, 'u', NULL);
  Command = HD44780_FUNCTION_SET + HD44780_FUNCTION_SET_4_BIT;
#endif
  if (HD4478_Ctrl.Line)
  {
    Command |= HD44780_FUNCTION_SET_2_LINE;
  }
  if (HD4478_Ctrl.DotMode)
  {
    Command |= HD44780_FUNCTION_SET_DOT_5_10;
  }
  HD44780_Write_Command(Command);
  if (HD44780_BusyCheck(NULL,HD44780_SECOND_COMM_DLY) != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  /* Display off */
  HD44780_Write_Command(HD44780_DISPLAY_CTRL);
  if (HD44780_BusyCheck(NULL,HD44780_MAX_COMM_DLY) != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  /* Display clear */
  if (HD44780_ClearDisplay() != HD44780_OK)
  {
    return HD44780_ERROR;
  }
#if HD44780_WR == 0
  DataRamAddHold = 0;
#endif
  /* Set entry mode */
  Command = HD44780_ENTRY_MODE;
  if (HD4478_Ctrl.AC_Direction)
  {
    Command |= HD44780_ENTRY_MODE_INC;
  }
  if (HD4478_Ctrl.DisplayShift)
  {
    Command |= HD44780_ENTRY_MODE_BOTH_S;
  }
  /* Set Display and cursor mode */
  if (HD44780_SetMode() != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  return HD44780_OK;
}

/*************************************************************************
 * Function Name: HD44780_GetSetting
 * Parameters: none
 * Return: HD44780_CTRL_DEF *
 * Description: Return pointer to Driver settings structure
 *
 *************************************************************************/
HD44780_CTRL_DEF * HD44780_GetSetting(void)
{
  return &HD4478_Ctrl;
}

/*************************************************************************
 * Function Name: HD44780_SetMode
 * Parameters: none
 * Return: HD44780_ERROR_CODE_DEF
 *         HD44780_OK  0: Pass
 *     HD44780_ERROR 1: Busy check Time Out
 * Description: Set display mode: Display On/Off; Cursor On/Off
 *  Cursor blink On/Off
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_SetMode(void)
{
  uint8 Command = HD44780_DISPLAY_CTRL;
  if (HD4478_Ctrl.DisplayOn)
  {
    Command |= HD44780_DISPLAY_CTRL_D_ON;
  }
  if (HD4478_Ctrl.CursorOn)
  {
    Command |= HD44780_DISPLAY_CTRL_C_ON;
  }
  if (HD4478_Ctrl.CursorBlink)
  {
    Command |= HD44780_DISPLAY_CTRL_C_BLINK;
  }
  HD44780_Write_Command(Command);
  return HD44780_BusyCheck(NULL,HD44780_FIRST_COMM_DLY);
}

/*************************************************************************
 * Function Name: HD44780_ClearDisplay
 * Parameters: none
 * Return: HD44780_ERROR_CODE_DEF
 *         HD44780_OK  0: Pass
 *     HD44780_ERROR 1: Busy check Time Out
 * Description: Clear display and set position to home
 *
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_ClearDisplay (void)
{
#if HD44780_WR == 0
  DataRamAddHold = 0;
#endif
  HD4478_Ctrl.DisplayPos = 0;
  HD44780_Write_Command(HD44780_CLEAR);
  return HD44780_BusyCheck(NULL,HD44780_MAX_COMM_DLY);
}

/*************************************************************************
 * Function Name: HD44780_ReturnToHome
 * Parameters: none
 * Return: HD44780_ERROR_CODE_DEF
 *         HD44780_OK  0: Pass
 *     HD44780_ERROR 1: Busy check Time Out
 * Description: Set display position to home
 *
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_ReturnToHome(void)
{
#if HD44780_WR == 0
  DataRamAddHold = 0;
#endif
  HD4478_Ctrl.DisplayPos = 0;
  HD44780_Write_Command(HD44780_RETURN);
  return HD44780_BusyCheck(NULL,HD44780_MAX_COMM_DLY);
}

/*************************************************************************
 * Function Name: HD44780_GetDisplayPosition
 * Parameters: none
 * Return: Int8U
 *
 * Description: Return X coordinate of visual part
 *
 *************************************************************************/
uint8 HD44780_GetDisplayPosition(void)
{
  return HD4478_Ctrl.DisplayPos;
}

/*************************************************************************
 * Function Name: HD44780_DisplayShift
 * Parameters: Boolean DisplayOn, Int8S DisplayShift
 * Return: HD44780_ERROR_CODE_DEF
 *         HD44780_OK  0: Pass
 *       HD44780_ERROR 1: Busy check Time Out
 * Description: Shift display
 *
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_DisplayShift(uint8 DisplayOn, sint8 DisplayShift)
{
  uint8 ShiftDir;
  if (DisplayShift >= 0)
  {
    if(DisplayShift > HD44780_MAX_LINE1_ADD)
    {
      return HD44780_ERROR;
    }
    ShiftDir = HD44780_DISPLAY_MOVE_RIGHT;
  }
  else
  {
    if(DisplayShift < -HD44780_MAX_LINE2_ADD)
    {
      return HD44780_ERROR;
    }
    ShiftDir = HD44780_DISPLAY_MOVE_LEFT;
    DisplayShift = 0 - DisplayShift;  /* DisplayShift = -DisplayShift */
  }
  for (int i = 0; i < DisplayShift; ++i)
  {
    HD44780_Write_Command(HD44780_DISPLAY_MOVE + HD44780_DISPLAY_MOVE_D + ShiftDir);
    if (HD44780_BusyCheck(NULL,HD44780_SECOND_COMM_DLY) != HD44780_OK)
    {
      return HD44780_ERROR;
    }
    if (ShiftDir == HD44780_DISPLAY_MOVE_LEFT)
    {
      if(++HD4478_Ctrl.DisplayPos > HD44780_MAX_LINE1_ADD)
      {
        HD4478_Ctrl.DisplayPos = 0;
      }
    }
    else
    {
      if(--HD4478_Ctrl.DisplayPos > HD44780_MAX_LINE1_ADD) /* --0 = 0xFF > 39 */
      {
        HD4478_Ctrl.DisplayPos = HD44780_MAX_LINE1_ADD;
      }
    }
  }
  return HD44780_OK;
}

/*************************************************************************
 * Function Name: HD44780_CursorPosSet
 * Parameters: Boolean CursorOn,Boolean CursorBlink,
 *             HD44780_XY_DEF X, HD44780_XY_DEF Y
 * Return: HD44780_ERROR_CODE_DEF
 *         HD44780_OK  0: Pass
 *       HD44780_ERROR 1: Busy check Time Out
 * Description: Set position of cursor
 *
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_CursorPosSet (uint8 CursorOn, uint8 CursorBlink, HD44780_XY_DEF X, HD44780_XY_DEF Y)
{
  uint8 CursorPos;
  /* Find Address by coordinate */
  if (HD44780_GetDDRamAdd(X,Y,&CursorPos) != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  /* Cursor off */
  HD4478_Ctrl.CursorOn = HD44780_CURSOR_OFF;
  if (HD44780_SetMode() != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  /* Set Address to DDRAM */
  HD44780_Write_Command(HD44780_SET_DDRAM_ADD + CursorPos);
#if HD44780_WR == 0
  DataRamAddHold = CursorPos;
#endif
  if (HD44780_BusyCheck(NULL,HD44780_SECOND_COMM_DLY) != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  /* Set Cursor dependence of CursorOn */
  HD4478_Ctrl.CursorOn = CursorOn;
  HD4478_Ctrl.CursorBlink = CursorBlink;
  return HD44780_SetMode();
}

#if HD44780_WR > 0
/*************************************************************************
 * Function Name: HD44780_RdCGRAM
 * Parameters: HD44780_STRING_DEF * CG_Data,
 *             Int8U CGRAM_Add
 * Return: HD44780_ERROR_CODE_DEF
 *        HD44780_OK   0: Pass
 *      HD44780_ERROR  1: Busy check Time Out
 * Description: Read Character pattern from CGRAM
 *
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_RdCGRAM(HD44780_STRING_DEF * CG_Data, uint8 CGRAM_Add)
{
  uint8 Counter = 8;
  uint8 DDRAM_AddHold;
  if (CGRAM_Add > HD44780_MAX_CGRAM)
  {
    return HD44780_ERROR;
  }
  /* Get current DDRAM address */
  if (HD44780_BusyCheck(&DDRAM_AddHold,HD44780_SECOND_COMM_DLY) != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  if (HD4478_Ctrl.DotMode)
  {
    Counter = 10;
    /* Address align to characters space */
    CGRAM_Add &= 0xF;
  }
  else
  {
    Counter = 8;
    /* Address align to characters space */
    CGRAM_Add &= 0x7;
  }
  /* Set CGRAM Address */
  HD44780_Write_Command(HD44780_SET_CGRAM_ADD + CGRAM_Add);
  if (HD44780_BusyCheck(NULL,HD44780_SECOND_COMM_DLY) != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  for ( ;Counter; --Counter)
  {
    *CG_Data = HD44780_Read_Data();
    if (HD44780_BusyCheck(NULL,HD44780_SECOND_COMM_DLY) != HD44780_OK)
    {
      break;
    }
    ++CG_Data;
  }
  HD44780_Write_Command(HD44780_SET_DDRAM_ADD + DDRAM_AddHold);
  return((HD44780_ERROR_CODE_DEF)(HD44780_BusyCheck(NULL,HD44780_SECOND_COMM_DLY) || (Counter?HD44780_ERROR:HD44780_OK)));
}
#endif

/*************************************************************************
 * Function Name: HD44780_WrCGRAM
 * Parameters: const HD44780_STRING_DEF * CG_Data,
 *             Int8U CGRAM_Add
 * Return: HD44780_ERROR_CODE_DEF
 *        HD44780_OK   0: Pass
 *      HD44780_ERROR  1: Busy check Time Out
 * Description: Write Character pattern into CGRAM
 *
HD44780_ERROR_CODE_DEF HD44780_WrCGRAM (const HD44780_STRING_DEF * CG_Data, Int8U CGRAM_Add)
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_WrCGRAM (HD44780_STRING_DEF * CG_Data, uint8 CGRAM_Add)
{
  uint8 Counter = 8;
  uint8 DDRAM_AddHold;
  /* Get current DDRAM address */
  if (HD44780_BusyCheck(&DDRAM_AddHold,HD44780_SECOND_COMM_DLY) != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  if (HD4478_Ctrl.DotMode)
  {
    Counter = 10;
    /* Address align to characters space */
    CGRAM_Add &= 0xF;
  }
  else
  {
    Counter = 8;
    /* Address align to characters space */
    CGRAM_Add &= 0x7;
  }
  CGRAM_Add *= Counter;
  if (CGRAM_Add > HD44780_MAX_CGRAM)
  {
    return HD44780_ERROR;
  }
  /* Set CGRAM Address */
  HD44780_Write_Command(HD44780_SET_CGRAM_ADD + CGRAM_Add);
  if (HD44780_BusyCheck(NULL,HD44780_SECOND_COMM_DLY) != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  for ( ;Counter; --Counter)
  {
    HD44780_Write_Data(*CG_Data);
    if (HD44780_BusyCheck(NULL,HD44780_SECOND_COMM_DLY) != HD44780_OK)
    {
      break;
    }
    ++CG_Data;
  }
  HD44780_Write_Command(HD44780_SET_DDRAM_ADD + DDRAM_AddHold);
  return((HD44780_ERROR_CODE_DEF)(HD44780_BusyCheck(NULL,HD44780_SECOND_COMM_DLY) || (Counter?HD44780_ERROR:HD44780_OK)));
}

/*************************************************************************
 * Function Name: HD44780_StrShow
 * Parameters: none
 * Return: MENU_ERROR_CODE_DEF
 *        HD44780_OK   0: Pass
 *      HD44780_ERROR  1: Busy check TimeOut
 * Description: Show zero terminate string into LCD
 *HD44780_ERROR_CODE_DEF HD44780_StrShow(HD44780_XY_DEF X, HD44780_XY_DEF Y, const HD44780_STRING_DEF * DataStr)
 *************************************************************************/
HD44780_ERROR_CODE_DEF HD44780_StrShow(HD44780_XY_DEF X, HD44780_XY_DEF Y,  HD44780_STRING_DEF * DataStr)
{
  uint8 DDRamAdd;
  HD44780_ERROR_CODE_DEF ErrorRes = HD44780_OK;
  if(HD44780_GetDDRamAdd(X,Y,&DDRamAdd) != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  /* Set Address to DDRAM */
  HD44780_Write_Command(HD44780_SET_DDRAM_ADD + DDRamAdd);
#if HD44780_WR == 0
  DataRamAddHold = DDRamAdd;
#endif
  if (HD44780_BusyCheck(&DDRamAdd,HD44780_SECOND_COMM_DLY) != HD44780_OK)
  {
    return HD44780_ERROR;
  }
  /* Write zero terminate string int LCD */
  while (*DataStr)
  {
//    ErrorRes |= HD44780_CheckVisual(DDRamAdd);
    HD44780_Write_Data(*DataStr);
#if HD44780_WR == 0
    if(HD4478_Ctrl.AC_Direction)
    {
      if((++DataRamAddHold > HD44780_MAX_LINE1_ADD) && (Y == 0))
      {
        DataRamAddHold = HD44780_MIN_LINE2_ADD;
      }
      else if ((Y == 1) && (DataRamAddHold > HD44780_MAX_LINE2_ADD))
      {
        DataRamAddHold = HD44780_MIN_LINE1_ADD;
      }
    }
    else
    {
      if((--DataRamAddHold < 0) && (Y == 0))
      {
        DataRamAddHold = HD44780_MAX_LINE2_ADD;
      }
      else if ((Y == 1) && (DataRamAddHold < HD44780_MIN_LINE2_ADD))
      {
        DataRamAddHold = HD44780_MAX_LINE1_ADD;
      }
    }
#endif
    if (HD44780_BusyCheck(&DDRamAdd,HD44780_SECOND_COMM_DLY) != HD44780_OK)
    {
      return HD44780_ERROR;
    }
    ++DataStr;
    if((Y == 0) && DDRamAdd > HD44780_MAX_LINE1_ADD)
    {
      HD44780_Write_Command(HD44780_SET_DDRAM_ADD+HD44780_MIN_LINE1_ADD);
    #if HD44780_WR == 0
      DataRamAddHold = HD44780_MIN_LINE1_ADD;
    #endif
      if (HD44780_BusyCheck(&DDRamAdd,HD44780_SECOND_COMM_DLY) != HD44780_OK)
      {
        return HD44780_ERROR;
      }
    }
    else if ((Y == 1) && DDRamAdd < HD44780_MIN_LINE2_ADD)
    {
      HD44780_Write_Command(HD44780_SET_DDRAM_ADD+HD44780_MIN_LINE2_ADD);
    #if HD44780_WR == 0
      DataRamAddHold = HD44780_MIN_LINE2_ADD;
    #endif
      if (HD44780_BusyCheck(&DDRamAdd,HD44780_SECOND_COMM_DLY) != HD44780_OK)
      {
        return HD44780_ERROR;
      }
    }
  }
  return ErrorRes;
}
