#include <avr/io.h>
#include <util/delay.h>

//Pinout
#define LCD_DATA_0_DDR     DDRD
#define LCD_DATA_0_PORT    PORTD
#define LCD_DATA_0_PIN     PD5

#define LCD_DATA_1_DDR     DDRD
#define LCD_DATA_1_PORT    PORTD
#define LCD_DATA_1_PIN     PD6

#define LCD_DATA_2_DDR     DDRD
#define LCD_DATA_2_PORT    PORTD
#define LCD_DATA_2_PIN     PD7

#define LCD_DATA_3_DDR     DDRB
#define LCD_DATA_3_PORT    PORTB
#define LCD_DATA_3_PIN     PB0

#define LCD_DATA_4_DDR     DDRB
#define LCD_DATA_4_PORT    PORTB
#define LCD_DATA_4_PIN     PB1

#define LCD_DATA_5_DDR      DDRB
#define LCD_DATA_5_PORT     PORTB
#define LCD_DATA_5_PIN      PB2

#define LCD_DATA_6_DDR      DDRB
#define LCD_DATA_6_PORT     PORTB
#define LCD_DATA_6_PIN      PB3

#define LCD_DATA_7_DDR      DDRB
#define LCD_DATA_7_PORT     PORTB
#define LCD_DATA_7_PIN      PB4

#define LCD_RS_DDR          DDRD
#define LCD_RS_PORT         PORTD
#define LCD_RS_PIN          PD2

#define LCD_RW_DDR          DDRD
#define LCD_RW_PORT         PORTD
#define LCD_RW_PIN          PD3

#define LCD_E_DDR           DDRD
#define LCD_E_PORT          PORTD
#define LCD_E_PIN           PD4

// LCD dimensions
#define LCD_N_COL 20
#define LCD_N_ROW 4

#define ROW0 0x00
#define ROW1 0x40
#define ROW2 0x14
#define ROW3 0x54

// LCD mode
#define LCD_MODE 0 //0 for 4 bits mode or 1 for 8 bits mode

//Cursor Style
#define no_CURSOR 0b00
#define underlined 0b10
#define blinking 0b01
#define underlined_blinking 0b11
#define CURSOR blinking //Change it by the cursor needed

void LCDSetup();
void LCDgotoXY(int8_t x, int8_t y);
void E_HIGH();
void E_LOW();
void RS_HIGH();
void RS_LOW();
void RW_HIGH();
void RW_LOW();
void DataPortWrite4bits(uint8_t val);
void DataPortWrite8bits(uint8_t val);
void LCDclear();
void LCDhome();
void ShiftRight();
void ShiftLeft();
void ShiftUp();
void ShiftDown();
void NewLine();
void LCDon();
void LCDoff();
void WriteChar(uint8_t val);
