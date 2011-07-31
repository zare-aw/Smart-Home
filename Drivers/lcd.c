#include "Includes.h"

uint8 display = DISPLAY;
uint8 cursor = CURSOR;
uint8 blink = BLINK;

/*************************************************************************
 * Description: Init Direction Pins for LCD
 * @IN NONE
 * @OUT: NONE
 *************************************************************************/
void Init_Direction_Pins_Lcd(void)
{
   CIP_ENABLE_DIRECTION = DIRECTION_IZLEZ ;
   RS_DIRECTION = DIRECTION_IZLEZ ;
   RW_DIRECTION = DIRECTION_IZLEZ ;
   BACK_LIGHT_DIRECTION = DIRECTION_IZLEZ ;
   D0_DIRECTION = DIRECTION_IZLEZ ;
   D1_DIRECTION = DIRECTION_IZLEZ ;
   D2_DIRECTION = DIRECTION_IZLEZ ;
   D3_DIRECTION = DIRECTION_IZLEZ ;
   D4_DIRECTION = DIRECTION_IZLEZ ;
   D5_DIRECTION = DIRECTION_IZLEZ ;
   D6_DIRECTION = DIRECTION_IZLEZ ;
   D7_DIRECTION = DIRECTION_IZLEZ ; 
}

void Cip_Enable(void)
{
  CIP_ENABLE_CLEAR = CLEAR ;
  CIP_ENABLE_SET = SET   ;
  CIP_ENABLE_CLEAR = CLEAR ;
}

/*************************************************************************
 * Description: Write “20H” to DDRAM and set DDRAM address to “00H” from AC
 * @IN NONE
 * @OUT: NONE
 *************************************************************************/
void Clear_Display(void)
{
   RS_CLEAR = CLEAR;
   RW_CLEAR = CLEAR;
   D0_SET = SET;
   D1_CLEAR = CLEAR;
   D2_CLEAR = CLEAR;
   D3_CLEAR = CLEAR;
   D4_CLEAR = CLEAR;
   D5_CLEAR = CLEAR;
   D6_CLEAR = CLEAR;
   D7_CLEAR = CLEAR;
   Cip_Enable();
}

/*************************************************************************
 * Description: Set DDRAM address to “00H” from AC and return cursor 
   to its original position if shifted.
 * @IN NONE
 * @OUT: NONE
 *************************************************************************/
void Return_Home(void)
{
   RS_CLEAR = CLEAR;
   RW_CLEAR = CLEAR;
   D1_SET = SET;
   D2_CLEAR = CLEAR;
   D3_CLEAR = CLEAR;
   D4_CLEAR = CLEAR;
   D5_CLEAR = CLEAR;
   D6_CLEAR = CLEAR;
   D7_CLEAR = CLEAR;
   Cip_Enable();
}

/*************************************************************************
 * Description: Assign cursor moving direction and enable the shift 
   of entire display
 * @IN increment_decrement_DDRAM_adress 
   Description: When I/D = “1”, cursor/blink moves to right and DDRAM 
   address is increased by 1
 * @IN shift_display 
   Description: If SH = “1” and in DDRAM write operation, shift of entire 
   display is performed according to I/D value (I/D = “1” : shift left, 
   I/D = “0” : shift right).
 * @OUT: NONE
 *************************************************************************/
void Entry_Mode_Set(uint8 increment_decrement_DDRAM_adress, uint8 shift_display)
{
   RS_CLEAR = CLEAR;
   RW_CLEAR = CLEAR;
   D2_SET = SET;
   D3_CLEAR = CLEAR;
   D4_CLEAR = CLEAR;
   D5_CLEAR = CLEAR;
   D6_CLEAR = CLEAR;
   D7_CLEAR = CLEAR;
   
   if(increment_decrement_DDRAM_adress)
     D1_INCREMENT = INCREMENT;
   else
     D1_DECREMENT = DECREMENT;
 
   if (shift_display)
     D1_SHIFT = SHIFT_SPORED_ID;
   else
     D1_NOT_SHIFT    =  NOT_SHIFT;
}

/*************************************************************************
 * Description: Set display (D), cursor (C), and blinking of cursor (B) 
   on/off control bit.
 * 3 variables control display, cursor and blink: 
 * @IN NONE
 * @OUT: NONE
 *************************************************************************/
void Display_Cursos_Blink_ONN_OFF()
{
   RS_CLEAR = CLEAR ;
   RW_CLEAR = CLEAR ;
   D4_CLEAR = CLEAR ;
   D5_CLEAR = CLEAR ;
   D6_CLEAR = CLEAR ;
   D7_CLEAR = CLEAR ;
   
   if(DISPLAY)
     D2_DISPLAY_ON = DISPLAY_ON;
   else
     D2_DISPLAY_OFF = DISPLAY_OFF;

   if(CURSOR)
     D1_CURSOR_ON = CURSOR_ON ;
   else
     D1_CURSOR_OFF = CURSOR_OFF ;

   if(BLINK)
     D0_BLINK_ON = BLINK_ON ;
   else
     D0_BLINK_OFF = BLINK_OFF ;
}


void Mode_8( unsigned char linii, unsigned char font )
{
  
   RS_CLEAR          =  CLEAR ;
   
   RW_CLEAR          =  CLEAR ;
   
   D5_SET            =  SET   ;
   
   D6_CLEAR          =  CLEAR ;
   
   D7_CLEAR          =  CLEAR ;
     
   D4_MOD_8_BITEN    =  MOD_8_BITEN  ;
     
   if( linii )
   {
     
     D3_EDNA_LINIJA    =  ONE_LINE ;
     
   }
   
   else
   {
     
     D3_DVE_LINII      =  TWO_LINE ;
     
   }
   
   if( font )
   {
     
     D2_FONT_5x7       =  FONT_5x7 ;
     
   }
   
   else
   {
     
     D2_FONT_5x10      =  FONT_5x10 ;
     
   }
   

}


void Init_Lcd_Mode_8( uint8 linii, uint8 font )
{
  
  Init_Direction_Pins_Lcd ();
  
  Mode_8( linii, font );
  
  Display_Cursos_Blink_ONN_OFF ();
  
  Clear_Display ();
  
  //Entry_Mode_Set ();
  
  Delay_Lcd();
  
}


void Delay_Lcd(void)
{
  
  int i;
  
  for( i = 0; i < DELAY_LCD; i++ )  ;
  
}

void Write_Display( uint8 bukva )
{
  
  RS_SET = SET;
  RW_CLEAR = CLEAR;
  
  if ( bukva % 2 )
  {
    D0_SET = SET;
  }
  else
  {
    D0_CLEAR = CLEAR;
  }
  
  bukva = bukva >> 1;
  
  if ( bukva % 2 )
  {
    D1_SET = SET;
  }
  else
  {
    D1_CLEAR = CLEAR;
  }
  
  bukva = bukva >> 1;
  
  if ( bukva % 2 )
  {
    D2_SET = SET;
  }
  else
  {
    D2_CLEAR = CLEAR;
  }
  
  bukva = bukva >> 1;
  
  if ( bukva % 2 )
  {
    D3_SET = SET;
  }
  else
  {
    D3_CLEAR = CLEAR;
  }
  
  bukva = bukva >> 1;
  
  if ( bukva % 2 )
  {
    D4_SET = SET;
  }
  else
  {
    D4_CLEAR = CLEAR;
  }
  
  bukva = bukva >> 1;
  
  if ( bukva % 2 )
  {
    D5_SET = SET;
  }
  else
  {
    D5_CLEAR = CLEAR;
  }
  
  bukva = bukva >> 1;
  
  if ( bukva % 2 )
  {
    D6_SET = SET;
  }
  else
  {
    D6_CLEAR = CLEAR;
  }
  
  bukva = bukva >> 1;
  
  if ( bukva % 2 )
  {
    D7_SET = SET;
  }
  else
  {
    D7_CLEAR = CLEAR;
  }
  
  Cip_Enable();
}