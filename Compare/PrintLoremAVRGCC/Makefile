# Paramètres de compilation
CC = avr-gcc
MCU = atmega328p
F_CPU = 16000000UL
BAUD_RATE = 9600
PROGRAMMER = arduino
PORT = /dev/ttyUSB0
PROGRAMMER_PARAMS = -c $(PROGRAMMER) -p $(MCU) -b $(BAUD_RATE) -P $(PORT)

# Options du compilateur
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU)

# Fichiers source
SRC = main.c ../../src/lcd_hd44780.c

# Nom de l'exécutable
TARGET = lcd_lorem_program

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $< $@

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) -O2 -o $@ $^

upload: $(TARGET).hex
	#Commande pour oldbootloader
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 57600 -U flash:w:lcd_lorem_program.hex:i
	
	#Commande pour new bootloader
	#avrdude -c avrisp -p m328p -P /dev/ttyUSB0 -U flash:w:lcd_uart_program.hex:i

clean:
	rm -f $(TARGET).elf $(TARGET).hex

.PHONY: all upload clean

