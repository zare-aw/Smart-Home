
// Zare

#define LCD_BECKLIGHT_GPIO_INIT()     (PINSEL1_bit.P0_21 = 0, FIO0CLR_bit.P0_21 = 1, FIO0DIR_bit.P0_21 = 1)
#define LCD_BECKLIGHT_GPIO_ON()       (FIO0SET_bit.P0_21 = 1)
#define LCD_BECKLIGHT_GPIO_OFF()      (FIO0CLR_bit.P0_21 = 1)


// Done

#define CIP_ENABLE_DIRECTION  IO1DIR_bit.P1_25  //direction vrednosti
#define RS_DIRECTION          IO1DIR_bit.P1_24  
#define RW_DIRECTION          IO0DIR_bit.P0_22 
#define BACK_LIGHT_DIRECTION  IO0DIR_bit.P0_30
#define D0_DIRECTION          IO1DIR_bit.P1_16  
#define D1_DIRECTION          IO1DIR_bit.P1_17
#define D2_DIRECTION          IO1DIR_bit.P1_18
#define D3_DIRECTION          IO1DIR_bit.P1_19
#define D4_DIRECTION          IO1DIR_bit.P1_20
#define D5_DIRECTION          IO1DIR_bit.P1_21
#define D6_DIRECTION          IO1DIR_bit.P1_22
#define D7_DIRECTION          IO1DIR_bit.P1_23

#define CIP_ENABLE_SET        IO1SET_bit.P1_25  //set vrednosti
#define RS_SET                IO1SET_bit.P1_24
#define RW_SET                IO0SET_bit.P0_22 
#define BACK_LIGHT_SET        IO0SET_bit.P0_30
#define D0_SET                IO1SET_bit.P1_16
#define D1_SET                IO1SET_bit.P1_17
#define D2_SET                IO1SET_bit.P1_18
#define D3_SET                IO1SET_bit.P1_19
#define D4_SET                IO1SET_bit.P1_20
#define D5_SET                IO1SET_bit.P1_21
#define D6_SET                IO1SET_bit.P1_22
#define D7_SET                IO1SET_bit.P1_23

#define CIP_ENABLE_CLEAR      IO1CLR_bit.P1_25  //clear vrednosti
#define RS_CLEAR              IO1CLR_bit.P1_24
#define RW_CLEAR              IO0CLR_bit.P0_22 
#define BACK_LIGHT_CLEAR      IO0CLR_bit.P0_30
#define D0_CLEAR              IO1CLR_bit.P1_16
#define D1_CLEAR              IO1CLR_bit.P1_17
#define D2_CLEAR              IO1CLR_bit.P1_18
#define D3_CLEAR              IO1CLR_bit.P1_19
#define D4_CLEAR              IO1CLR_bit.P1_20
#define D5_CLEAR              IO1CLR_bit.P1_21
#define D6_CLEAR              IO1CLR_bit.P1_22
#define D7_CLEAR              IO1CLR_bit.P1_23

#define DELAY_LCD             2050
#define DIRECTION_IZLEZ       1                 //vrednost za nasoka
#define DIRECTION_VLEZ        0
#define SET                   1
#define CLEAR                 1
#define INCREMENT             SET
#define SHIFT_SPORED_ID       SET
#define DECREMENT             CLEAR
#define NOT_SHIFT             CLEAR


#define D1_INCREMENT          D1_SET
#define D1_DECREMENT          D1_CLEAR
#define D1_SHIFT              D0_SET
#define D1_NOT_SHIFT          D0_CLEAR
//Configuring DISPLAY
#define DISPLAY_OFF           CLEAR //clear = 1, in case if sometimes clear is 0 or set is 0
#define DISPLAY_ON            SET
#define D2_DISPLAY_ON         D2_SET
#define D2_DISPLAY_OFF        D2_CLEAR
#define DISPLAY               1   //if DISPLAY = 1 then DISPLAY_ON else DISPLAY_OFF
//Configuring CURSOR
#define CURSOR_ON             SET   //clear = 1, in case if sometimes clear is 0 or set is 0
#define CURSOR_OFF            CLEAR
#define D1_CURSOR_ON          D1_SET
#define D1_CURSOR_OFF         D1_CLEAR
#define CURSOR                0   //if CURSOR = 1 then CURSOR_ON else CURSOR_OFF
//Configuring BLINK
#define BLINK_ON              SET
#define BLINK_OFF             CLEAR
#define D0_BLINK_ON           D0_SET
#define D0_BLINK_OFF          D0_CLEAR
#define BLINK                 0   //if BLINK = 1 then BLINK_ON else BLINK_OFF

#define D4_MOD_8_BITEN        D4_SET
#define D4_MOD_4_BITEN        D4_CLEAR
#define MOD_8_BITEN           SET
#define MOD_4_BITEN           CLEAR
#define D3_EDNA_LINIJA        D3_SET
#define D3_DVE_LINII          D3_CLEAR
#define ONE_LINE              SET
#define TWO_LINE              CLEAR
#define D2_FONT_5x7           D2_SET
#define D2_FONT_5x10          D2_CLEAR
#define FONT_5x7              SET
#define FONT_5x10             CLEAR

/*************************************************************************
 * Description: Init Direction Pins for LCD
 * @IN NONE
 * @OUT: NONE
 *************************************************************************/
void Init_Direction_Pins_Lcd(void);

/*************************************************************************
 * Description: Write “20H” to DDRAM and set DDRAM address to “00H” from AC
 * @IN NONE
 * @OUT: NONE
 *************************************************************************/
void Clear_Display(void);

/*************************************************************************
 * Description: Set DDRAM address to “00H” from AC and return cursor 
   to its original position if shifted.
 * @IN NONE
 * @OUT: NONE
 *************************************************************************/
void Return_Home(void);

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
void Entry_Mode_Set(uint8 increment_decrement_DDRAM_adress, uint8 shift_display);

void Display_Cursos_Blink_ONN_OFF ();

/*************************************************************************
 * Description: Init Lcd in 8 bit Mode, 
 * @IN line Description: How much line on display ONE_LINE or TWO_LINE
 * @IN font Description: D2_FONT_5x7 or 
 * @OUT: none
 *************************************************************************/
void Mod_8(uint8 linii, uint8 font);

void Write_Display             ( uint8 bukva );

void Delay_Lcd                ( void );

/*************************************************************************
 * Description: Init Lcd in 8 bit Mode, 
 * @IN line Description: How much line on display ONE_LINE or TWO_LINE
 * @IN font Description: D2_FONT_5x7 or 
 * @OUT: none
 *************************************************************************/
void Init_Lcd_Mode_8                  ( uint8 line, uint8 font );