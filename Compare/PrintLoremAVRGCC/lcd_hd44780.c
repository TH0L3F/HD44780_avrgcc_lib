#include <avr/io.h>
#include <util/delay.h>
#include "lcd_hd44780.h"

//Ne jamais manipuler directement cursorX et cursorY
uint8_t cursorX = 0, cursorY = 0; //Actual position corresponding on starting to the upper left corner

void E_HIGH(){
    LCD_E_PORT |= (1 << LCD_E_PIN);
}

void E_LOW(){
    LCD_E_PORT &= (~(1 << LCD_E_PIN));
}

void RS_HIGH(){
    LCD_RS_PORT |= (1 << LCD_RS_PIN);
}

void RS_LOW(){
    LCD_RS_PORT &= (~(1 << LCD_RS_PIN));
}

void RW_HIGH(){
    LCD_RW_PORT |= (1 << LCD_RW_PIN);
}

void RW_LOW(){
    LCD_RW_PORT &= (~(1 << LCD_RW_PIN));
}

//Function to write 4 bits on screen data pins
void DataPortWrite4bits(uint8_t val){
    E_HIGH();
    if(val >> 7 & 0x01){
        LCD_DATA_7_PORT |= 1 << LCD_DATA_7_PIN;
    }
    else{
        LCD_DATA_7_PORT &= (~(1 << LCD_DATA_7_PIN));
    }
    if(val >> 6 & 0x01){
        LCD_DATA_6_PORT |= 1 << LCD_DATA_6_PIN;
    }
        else{
                LCD_DATA_6_PORT &= (~(1 << LCD_DATA_6_PIN));
        }
        if(val >> 5 & 0x01){
                LCD_DATA_5_PORT |= 1 << LCD_DATA_5_PIN;
        }
        else{
                LCD_DATA_5_PORT &= (~(1 << LCD_DATA_5_PIN));
        }
        if(val >> 4 & 0x01){
                LCD_DATA_4_PORT |= 1 << LCD_DATA_4_PIN;
        }
        else{
                LCD_DATA_4_PORT &= (~(1 << LCD_DATA_4_PIN));
        }
    _delay_ms(1);
    E_LOW();
    _delay_ms(1);
    E_HIGH();
        if(val >> 3 & 0x01){
                LCD_DATA_7_PORT |= 1 << LCD_DATA_7_PIN;
        }
        else{
                LCD_DATA_7_PORT &= (~(1 << LCD_DATA_7_PIN));
        }
        if(val >> 2 & 0x01){
                LCD_DATA_6_PORT |= 1 << LCD_DATA_6_PIN;
        }
        else{
                LCD_DATA_6_PORT &= (~(1 << LCD_DATA_6_PIN));
        }
        if(val >> 1 & 0x01){
                LCD_DATA_5_PORT |= 1 << LCD_DATA_5_PIN;
        }
        else{
                LCD_DATA_5_PORT &= (~(1 << LCD_DATA_5_PIN));
        }
        if(val >> 0 & 0x01){
                LCD_DATA_4_PORT |= 1 << LCD_DATA_4_PIN;
        }
        else{
                LCD_DATA_4_PORT &= (~(1 << LCD_DATA_4_PIN));
        }
    _delay_ms(1);
    E_LOW();
    _delay_ms(1);
    E_HIGH();
}

//Function to write 8 bits on screen data pins
void DataPortWrite8bits(uint8_t val){
        E_HIGH();
        if(val >> 7 & 0x01){
                LCD_DATA_7_PORT |= 1 << LCD_DATA_7_PIN;
        }
        else{
                LCD_DATA_7_PORT &= (~(1 << LCD_DATA_7_PIN));
        }
        if(val >> 6 & 0x01){
                LCD_DATA_6_PORT |= 1 << LCD_DATA_6_PIN;
        }
        else{
                LCD_DATA_6_PORT &= (~(1 << LCD_DATA_6_PIN));
        }
        if(val >> 5 & 0x01){
                LCD_DATA_5_PORT |= 1 << LCD_DATA_5_PIN;
        }
        else{
                LCD_DATA_5_PORT &= (~(1 << LCD_DATA_5_PIN));
        }
        if(val >> 4 & 0x01){
                LCD_DATA_4_PORT |= 1 << LCD_DATA_4_PIN;
        }
        else{
                LCD_DATA_4_PORT &= (~(1 << LCD_DATA_4_PIN));
        }
        if(val >> 3 & 0x01){
                LCD_DATA_3_PORT |= 1 << LCD_DATA_3_PIN;
        }
        else{
                LCD_DATA_3_PORT &= (~(1 << LCD_DATA_3_PIN));
        }
        if(val >> 2 & 0x01){
                LCD_DATA_2_PORT |= 1 << LCD_DATA_2_PIN;
        }
        else{
                LCD_DATA_2_PORT &= (~(1 << LCD_DATA_2_PIN));
        }
        if(val >> 1 & 0x01){
                LCD_DATA_1_PORT |= 1 << LCD_DATA_1_PIN;
        }
        else{
                LCD_DATA_1_PORT &= (~(1 << LCD_DATA_1_PIN));
        }
        if(val & 0x01){
                LCD_DATA_0_PORT |= 1 << LCD_DATA_0_PIN;
        }
        else{
                LCD_DATA_0_PORT &= (~(1 << LCD_DATA_0_PIN));
        }
        _delay_ms(1);
        E_LOW();
        _delay_ms(1);
}

void LCDSetup(){
    // Wait for screen power up
    _delay_ms(100);
    
    //Data port configuration
    if(LCD_MODE){    
        LCD_DATA_7_DDR |= 1 << LCD_DATA_7_PIN;
        LCD_DATA_6_DDR |= 1 << LCD_DATA_6_PIN;
        LCD_DATA_5_DDR |= 1 << LCD_DATA_5_PIN;
        LCD_DATA_4_DDR |= 1 << LCD_DATA_4_PIN;
        LCD_DATA_3_DDR |= 1 << LCD_DATA_3_PIN;
        LCD_DATA_2_DDR |= 1 << LCD_DATA_2_PIN;
        LCD_DATA_1_DDR |= 1 << LCD_DATA_1_PIN;
        LCD_DATA_0_DDR |= 1 << LCD_DATA_0_PIN;
        DataPortWrite8bits(0x00);//Preset to LOW
    }
    else{
        LCD_DATA_7_DDR |= 1 << LCD_DATA_7_PIN;
        LCD_DATA_6_DDR |= 1 << LCD_DATA_6_PIN;
        LCD_DATA_5_DDR |= 1 << LCD_DATA_5_PIN;
        LCD_DATA_4_DDR |= 1 << LCD_DATA_4_PIN;
        DataPortWrite4bits(0x00);//Preset to LOW
    }
    
    //Config port for RS RW & E
    LCD_RS_DDR |= (1 << LCD_RS_PIN);
    LCD_RW_DDR |= (1 << LCD_RW_PIN);
    LCD_E_DDR  |= (1 << LCD_E_PIN);
    E_LOW();
    RW_LOW();
    RS_LOW();
    if(LCD_MODE){
        DataPortWrite8bits(0b00111000);
        DataPortWrite8bits(0b00010000);
        LCDon();
        DataPortWrite8bits(0b00000001);
        DataPortWrite8bits(0b00000100);
    }
    else{
        DataPortWrite4bits(0b00101000);
        DataPortWrite4bits(0b00010000);
        LCDon();
        DataPortWrite4bits(0b00000001);
        DataPortWrite4bits(0b00000100);
    }
    LCDclear();
    LCDhome();
}

//Move to XY position on the screen
void LCDgotoXY(int8_t x, int8_t y){
    uint8_t ddram_addr = 0;
    
    //Check the screen overflow
    if(x < 0){
        cursorX = 0;
    }
    else if(x > LCD_N_COL-1){
        cursorX = LCD_N_COL-1;
    }
    else{
        cursorX = x;
    }
    if(y < 0){
        cursorY = 0;
    }
    else if(y > LCD_N_ROW-1){
        cursorY = LCD_N_ROW-1;
    }
    else{
        cursorY = y;
    }
    
    //Create the function ADDR    
    if(LCD_N_ROW == 2){
        if(cursorY == 0){
            ddram_addr = ROW0 + cursorX;    
        }
        else if(cursorY == 1){
            ddram_addr = ROW2 + cursorX;
        }
        else{
            return;
        }
    }
    else if(LCD_N_ROW == 4){
        if(cursorY == 0){
            ddram_addr = ROW0 + cursorX;
        }
        else if(cursorY == 1){
            ddram_addr = ROW1 + cursorX;
        }
        else if(cursorY == 2){
            ddram_addr = ROW2 + cursorX;
        }
        else if(cursorY == 3){
            ddram_addr = ROW3 + cursorX;
        }
        else{
            return;
        }
    }
    else{
        return;
    }

    //Send the ADDR
    if(LCD_MODE){
        RS_LOW();
        RW_LOW();
        DataPortWrite8bits(ddram_addr | 0b10000000);
    }
    else{
        RS_LOW();
        RW_LOW();
        DataPortWrite4bits(ddram_addr | 0b10000000);
    }
}

void LCDclear(){ //Clear all the screen
    RS_LOW();
    RW_LOW();
    if(LCD_MODE){ DataPortWrite8bits(0x01); }
    else{ DataPortWrite4bits(0x01); }
}

void LCDhome(){ //Move to upper left corner
    RS_LOW();
    RW_LOW();
    if(LCD_MODE){ DataPortWrite8bits(0x02); }
    else{ DataPortWrite4bits(0x02); }
    cursorX = 0;
    cursorY = 0;
}

void ShiftRight(){ //Move one case on the left
    /*RS_LOW(); 
    RW_LOW();
    if(cursorX < LCD_N_COL-1){
        cursorX++;
    }
    else{
        if(cursorY < LCD_N_ROW-1){
            cursorX = 0;
            cursorY++;
        }
        else{return;}
    }
    if(LCD_MODE){ DataPortWrite8bits(0b00011100); }
    else{ DataPortWrite4bits(0b00011100); }
    */ //CURSOR++ Make +2 instead of +1 ¯\_(ツ)_/¯ 
    LCDgotoXY(cursorX+1,cursorY);
}    

void ShiftLeft(){ //Move one case on the right
    /*RS_LOW();
    RW_LOW();
    if(cursorX > 0){
        cursorX-- ;
    }
    else{
        if(cursorX > 0){
            cursorX = 19;
            cursorY--;
        }
        else{return;}
    }
    if(LCD_MODE){ DataPortWrite8bits(0b00011000); }
    else{ DataPortWrite4bits(0b00011000); }
    */ //CURSOR-- Make -2 instead of -1 ¯\_(ツ)_/¯ 
    LCDgotoXY(cursorX-1,cursorY);
}

void ShiftUp(){
    LCDgotoXY(cursorX,cursorY-1);
}

void ShiftDown(){
    LCDgotoXY(cursorX,cursorY+1);
}

void NewLine(){
    LCDgotoXY(0,cursorY+1);
}

void LCDon(){ //Start the screen
    RS_LOW();
    RW_LOW();
    if(LCD_MODE){ DataPortWrite8bits(0b00001100|CURSOR); }
    else{ DataPortWrite4bits(0b00001100|CURSOR); }
}

void LCDoff(){ //Shutdown the screen
    RS_LOW();
    RW_LOW();
    if(LCD_MODE){ DataPortWrite8bits(0b00001000|CURSOR); }
    else{ DataPortWrite4bits(0b00001000|CURSOR); }
}

void WriteChar(uint8_t val){ //Write a caractere on the screen at the actual position
    RS_HIGH();
    RW_LOW();
    if(LCD_MODE){ DataPortWrite8bits(val); }
    else{ DataPortWrite4bits(val); }
}
