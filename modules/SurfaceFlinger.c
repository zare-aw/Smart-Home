#include "Includes.h"

char SurfaceBuffer_1[Y_SIZE][X_SIZE] = {0};
char SurfaceBuffer_2[Y_SIZE][X_SIZE] = {0};
uint8 WorkingSurface = 1;
uint8 BeckupSurface = 2;
uint8 DisplaySync = 0;
uint8 ConsoleDisplayPrint = DISABLE;

static Status_t Update_Surface_Buffer(char InputChar, uint8 line, uint8 column);
static void Swap_Surface_Buffer(void);

/*******************************************************************************
* Standardna funkcija za pisuvanje po display.
* @in line - Broj na linija vo koja treba da se pisuva stringot
* @in format - string koj sakame da go pecatime zaedno so formatirackite znaci
* @in ... - dopolnitelni parametri koi sakame da gi pecatime
* @out Status_t
*******************************************************************************/
Status_t printd(uint8 line, const char *format, ...)
{
  Function_IN(PRINTD);
  uint32 i = 0;
  uint32 column = 1;
  char VsBuffer[(Y_SIZE * X_SIZE) + 4] = {0};
  va_list args;
  
  EXIT(line <= Y_SIZE, INVALID_INPUT_PARAMETER);
  EXIT(format != NULL, INVALID_INPUT_POINTER);
  
  va_start(args, format);
  
  EXIT(vsprintf(VsBuffer, format, args) >= 0, INVALID_INPUT_PARAMETER);
  
  while(VsBuffer[i])
  {
    Update_Surface_Buffer(VsBuffer[i], line, column);
    if(VsBuffer[i] == 0x0A)
    {
      line++;
      column = 1;
      if(line > Y_SIZE)
        return INVALID_INPUT_PARAMETER;
    }
    column++;
    i++;
  }
  va_end(args);
  RETURN_SUCCESS_FUNC(PRINTD);
}

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
    return ERROR;
  
  return SUCCESS;
}

/*******************************************************************************
* 
*******************************************************************************/
static Status_t Update_Surface_Buffer(char InputChar, uint8 Line, uint8 Column)
{
  Function_IN(UPDATE_SURFACE_BUFFER);
  
  CONTROL((Line <= Y_SIZE) && (Column <= X_SIZE), INVALID_INPUT_PARAMETER);
  switch(BeckupSurface)
  {
    case 1:
      SurfaceBuffer_1[Line - 1][Column - 1] = InputChar;
      break;
    case 2:
      SurfaceBuffer_2[Line - 1][Column - 1] = InputChar;
      break;
    default:
      return GENERAL_ERROR;
  }
  
  RETURN_SUCCESS_FUNC(UPDATE_SURFACE_BUFFER);
}

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
void Console_Display_Update_Set(uint8 UpdateFlag)
{
  ConsoleDisplayPrint = UpdateFlag;
}

/*******************************************************************************
* 
*******************************************************************************/
void Console_Display_Dump(void)
{
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
}

/*******************************************************************************
* 
*******************************************************************************/
Status_t Update_Display_Panel(uint8 Mode)
{
  Function_IN(UPDATE_DISPLAY_PANEL);
  
  switch(Mode)
  {
    case PULL:
      if(DisplaySync == 1)
      {
        if(ConsoleDisplayPrint == ENABLE)
          Console_Display_Dump();
        // Dovrsi
        DisplaySync = 0;
      }
      break;
    case FORCE:
      if(ConsoleDisplayPrint == ENABLE)
        Console_Display_Dump();
      // Dovrsi
      DisplaySync = 0;
      break;
    default:
      CONTROL(0, INVALID_INPUT_PARAMETER);
      break;
  }
  
  RETURN_SUCCESS_FUNC(UPDATE_DISPLAY_PANEL);
}