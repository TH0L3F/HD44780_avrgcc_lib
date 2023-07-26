#include"../../src/lcd_hd44780.h"

char lorem[80] = "Lorem ipsum dolor\nsit amet,consectetur\nadipiscing elit, sed\n do eiusmod tempor\n";

int main() {

    LCDSetup();
    int y = 0;
    for(int i = 0; y<4; i++){
        if(lorem[i] == '\n'){
            NewLine();
            y++;
        } 
        else{
                    
            WriteChar(lorem[i]);
            ShiftRight();
        }
    }

    return 0;
    
}
