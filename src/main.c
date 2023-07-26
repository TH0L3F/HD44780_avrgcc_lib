#include"lcd_hd44780.h"
#include <avr/interrupt.h>

void USART_init(uint8_t ubrr) { //F_CPU en Hz et BAUD en bit/s
  // Définit la vitesse de transmission
  UBRR0H = (uint8_t)(ubrr >> 8);
  UBRR0L = (uint8_t)ubrr;

  // Active la transmission et la réception
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  // Définit le format de trame : 7 bits de données, 1 bit de stop
  UCSR0C = (1 << UCSZ01);
}

uint8_t USART_receiveChar() {
  // Attendre la réception d'un caractère
  while (!(UCSR0A & (1 << RXC0)));

  // Renvoyer le caractère reçu
  return UDR0;
}

int main() {
  //initialisation du port série
  USART_init(103);

  //Configuration et séquence d'initilisation de l'écran LCD
  LCDSetup();

  // Activation des interruptions globales
  sei();
  
  while (1) {
    // Attendre la réception d'un caractère
    uint8_t receivedChar = USART_receiveChar();
    if(receivedChar == '\n' || receivedChar == 13){ //Si touche ENTER ou retour chariot
      NewLine(); //Saut de ligne
    }
    else if(receivedChar == 27){//Si ECHAP
      uint8_t receivedChar2 = USART_receiveChar();
      if(receivedChar2 = '['){//Si [
        uint8_t receivedChar3 = USART_receiveChar();
        if(receivedChar3 == 'A'){
          ShiftUp();
        }
        else if(receivedChar3 == 'B'){
          ShiftDown();
        }
        else if(receivedChar3 == 'C'){
          ShiftRight();
        }
        else if(receivedChar3 == 'D'){
          ShiftLeft();
        }
        else if(receivedChar3 == 'H'){
          LCDhome();
        }
        else{//Sinon il ne s'agit pas d'une VT100 et on affiche les caractères
          WriteChar(receivedChar);
          ShiftRight();
          WriteChar(receivedChar2);
          ShiftRight();
          WriteChar(receivedChar3);
          ShiftRight();
        }
      }
      else{//Sinon il ne s'agit pas d'une VT100 et on affiche les caractères
        WriteChar(receivedChar);
        ShiftRight();
        WriteChar(receivedChar2);
        ShiftRight();
      }        
    }
    else{//On affiche le caractère si ce n'est pas un saut de ligne ou une VT100
      WriteChar(receivedChar);
      ShiftRight();
    }
  }
  return 0;
}

