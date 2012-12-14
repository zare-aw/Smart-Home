#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "Global_Defines.h"
#include "Func_Trace.h"
#include "StatusHandling.h"
#include "Console.h"
#include "HD44780.h"

#include "SurfaceFlinger.h"
#include "SurfaceFlinger_Func.h"

char SurfaceBuffer_1[Y_SIZE][X_SIZE] = {0};
char SurfaceBuffer_2[Y_SIZE][X_SIZE] = {0};
uint8 WorkingSurface = 1;
uint8 BeckupSurface = 2;
uint8 DisplaySync = 0;
uint8 ConsoleDisplayPrint = DISABLE;
uint8 UpdateDisplay_State = 0;

static Status_t Update_Surface_Buffer(char InputChar, uint8 line, uint8 column);
static void Swap_Surface_Buffer(void);
static Status_t Fill_Row(uint8 * const Row_p, const char *Buf_p);
static void Display_Update_Reset(void);

/*******************************************************************************
* Standardna funkcija za pisuvanje po display.
* @in line - Broj na linija vo koja treba da se pisuva stringot
* @in format - string koj sakame da go pecatime zaedno so formatirackite znaci
* @in ... - dopolnitelni parametri koi sakame da gi pecatime
* @out Status_t
*******************************************************************************/
Status_t printd(uint8 line, const char *format, ...)
{
  FuncIN(PRINTD);
  uint32 i = 0;
  uint32 column = 1;
  char VsBuffer[(Y_SIZE * X_SIZE) + 4] = {0};
  va_list args;
  
  ASSERT(line <= Y_SIZE, -INVALID_INPUT_PARAMETER);
  ASSERT(format != NULL, -INVALID_INPUT_POINTER);
  
  va_start(args, format);
  
  VERIFY(vsprintf(VsBuffer, format, args), -INVALID_INPUT_PARAMETER);
  
  while(VsBuffer[i])
  {
    Update_Surface_Buffer(VsBuffer[i], line, column);
    if(VsBuffer[i] == 0x0A)
    {
      line++;
      column = 1;
      if(line > Y_SIZE)
        Fatal_Abort(-INVALID_INPUT_PARAMETER);
    }
    column++;
    i++;
  }
  va_end(args);
  
  EXIT_SUCCESS_FUNC(PRINTD);
}
FUNC_REGISTER(PRINTD, printd);

/*******************************************************************************
* 
*******************************************************************************/
void clrd(void)
{
  switch(BeckupSurface)
  {
    case 1:
      for(int i = 0; i < Y_SIZE; i++)
        memset(SurfaceBuffer_1[i], 0, X_SIZE);
      break;
    case 2:
      for(int i = 0; i < Y_SIZE; i++)
        memset(SurfaceBuffer_2[i], 0, X_SIZE);
      break;
    default:
      break;
  }
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t syncd(void)
{
  if(DisplaySync == 0)
  {
    DisplaySync = 1;
    Swap_Surface_Buffer();
  }
  else
  {
    Swap_Surface_Buffer();
    Display_Update_Reset();
  }
  
  return SUCCESS;
}

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Update_Surface_Buffer(char InputChar, uint8 Line, uint8 Column)
{
  FuncIN(UPDATE_SURFACE_BUFFER);
  
  ASSERT((Line <= Y_SIZE) && (Column <= X_SIZE), -INVALID_INPUT_PARAMETER);
  
  switch(BeckupSurface)
  {
    case 1:
      SurfaceBuffer_1[Line - 1][Column - 1] = InputChar;
      break;
    case 2:
      SurfaceBuffer_2[Line - 1][Column - 1] = InputChar;
      break;
    default:
      Fatal_Abort(-GENERAL_ERROR);
  }
  
  EXIT_SUCCESS_FUNC(UPDATE_SURFACE_BUFFER);
}
FUNC_REGISTER(UPDATE_SURFACE_BUFFER, Update_Surface_Buffer);

/*******************************************************************************
* 
*******************************************************************************/
static void Swap_Surface_Buffer(void)
{
  if(WorkingSurface == 1)
    WorkingSurface = 2;
  else
    WorkingSurface = 1;
  
  if(BeckupSurface == 2)
    BeckupSurface = 1;
  else
    BeckupSurface = 2;
}

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Fill_Row(uint8 * const Row_p, const char *Buf_p)
{
  FuncIN(FILL_ROW);
  
  ASSERT(Row_p != NULL, -INVALID_INPUT_POINTER);
  ASSERT(Buf_p != NULL, -INVALID_INPUT_POINTER);
  
  uint8 *Buff_p = (uint8 *)Buf_p;
  uint8 *Index_p = Buff_p;
  uint8 *End_p = Buff_p + X_SIZE;
  uint8 len = 0;
  
  while(*Index_p != 0x0A && *Index_p != 0 && Index_p < End_p)
    Index_p++;
  
  len = Index_p - Buff_p;
  memset((void *)Row_p, 0x20, X_SIZE);
  memcpy((void *)Row_p, (void *)Buff_p, len);

  *(Row_p + X_SIZE) = 0;
  
  EXIT_SUCCESS_FUNC(FILL_ROW);
}
FUNC_REGISTER(FILL_ROW, Fill_Row);

/*******************************************************************************
* 
*******************************************************************************/
void Console_Display_Update_Set(uint8 UpdateFlag)
{
  ConsoleDisplayPrint = UpdateFlag;
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Console_Display_Dump(void)
{
  FuncIN(CONSOLE_DISPLAY_DUMP);
  
  printc("\n**");
  for(int i = 0; i < X_SIZE; i++)
    printc("*");
  printc("**\n");
  
  for(int i = 0; i < Y_SIZE; i++)
  {
    printc("**");
    
    for(int j = 0; j < X_SIZE; j++)
    {
      switch(WorkingSurface)
      {
        case 1:
          if(SurfaceBuffer_1[i][j] == 0)
            printc(" ");
          else
            printc("%c", SurfaceBuffer_1[i][j]);
          break;
        case 2:
          if(SurfaceBuffer_2[i][j] == 0)
            printc(" ");
          else
            printc("%c", SurfaceBuffer_2[i][j]);
          break;
        default:
          printc("X");
          break;
      }
    }
    
    printc("**\n");
  }
  
  printc("**");
  for(int i = 0; i < X_SIZE; i++)
    printc("*");
  printc("**\n");
  
  EXIT_SUCCESS_FUNC(CONSOLE_DISPLAY_DUMP);
}
FUNC_REGISTER(CONSOLE_DISPLAY_DUMP, Console_Display_Dump);

/*******************************************************************************
* 
*******************************************************************************/
static void Display_Update_Reset(void)
{
  UpdateDisplay_State = 0;
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Update_Display_Panel(uint8 Mode)
{
  FuncIN(UPDATE_DISPLAY_PANEL);
  
  HD44780_STRING_DEF *Row;
  
  switch(Mode)
  {
    case PULL:
      if(DisplaySync == 1)
      {
        if((ConsoleDisplayPrint == ENABLE) && (UpdateDisplay_State == 0))
          Console_Display_Dump();
        
        Row = (uint8 *)malloc(X_SIZE + 1);
        ASSERT(Row != 0, -HEAP_ALLOCATION_ERROR);
        
        switch(WorkingSurface)
        {
          case 1:
            Fill_Row(Row, SurfaceBuffer_1[UpdateDisplay_State]);
            break;
          case 2:
            Fill_Row(Row, SurfaceBuffer_2[UpdateDisplay_State]);
            break;
        }
        
        switch(UpdateDisplay_State)
        {
          case 0:
            if(HD44780_OK !=  HD44780_StrShow(0, 0, Row))
              EXIT_FUNC(MENU_DISPLAY_ERROR, UPDATE_DISPLAY_PANEL);
            
            // Next State
            UpdateDisplay_State = 1;
            break;
          case 1:
            if(HD44780_OK !=  HD44780_StrShow(0, 1, Row))
              EXIT_FUNC(MENU_DISPLAY_ERROR, UPDATE_DISPLAY_PANEL);
            
            // Next State
#if Y_SIZE == 2
            UpdateDisplay_State = 0;
            DisplaySync = 0;
            break;
#else
            UpdateDisplay_State = 2;
            break;
          case 2:
            if(HD44780_OK !=  HD44780_StrShow(0, 2, Row))
              EXIT_FUNC(MENU_DISPLAY_ERROR, UPDATE_DISPLAY_PANEL);
            
            // Next State
            UpdateDisplay_State = 3;
            break;
          case 3:
            if(HD44780_OK !=  HD44780_StrShow(0, 3, Row))
              EXIT_FUNC(MENU_DISPLAY_ERROR, UPDATE_DISPLAY_PANEL);
            
            // Next State
            UpdateDisplay_State = 0;
            DisplaySync = 0;
            break;
#endif
          default:
            UpdateDisplay_State = 0;
            DisplaySync = 0;
            break;
        } // switch(UpdateDisplay_State)
        
        free(Row);
      } // if(DisplaySync == 1)
      break;
    case FORCE:
      if(ConsoleDisplayPrint == ENABLE)
        Console_Display_Dump();
        
      Row = (uint8 *)malloc(X_SIZE + 1);
      ASSERT(Row != 0, -HEAP_ALLOCATION_ERROR);
      
      for(uint32 i = 0; i < Y_SIZE; i++)
      {
        switch(WorkingSurface)
        {
          case 1:
            Fill_Row(Row, SurfaceBuffer_1[i]);
            break;
          case 2:
            Fill_Row(Row, SurfaceBuffer_2[i]);
            break;
          default:
            Fatal_Abort(-UNKNOWN_ERROR);
        }

        if(HD44780_OK !=  HD44780_StrShow(0, i,  Row))
          EXIT_FUNC(MENU_DISPLAY_ERROR, UPDATE_DISPLAY_PANEL);
      } // for(uint32 i = 0; i < Y_SIZE; i++)
      
      free(Row);
      break;
    default:
      Fatal_Abort(-INVALID_INPUT_PARAMETER);
      break;
  } // switch(Mode)
  
  EXIT_SUCCESS_FUNC(UPDATE_DISPLAY_PANEL);
}
FUNC_REGISTER(UPDATE_DISPLAY_PANEL, Update_Display_Panel);
