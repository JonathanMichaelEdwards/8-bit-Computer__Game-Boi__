# ****************************************************************************
# File:      Makefile                                                        *
# Authors:   Jonathan Edwards                                                *
# Date:      08/28/2019                                                      *
# Descr:     Makefile for the ATMEGA-328p to program the AT28C16             *
# ****************************************************************************


MCU         = atmega328p
USBPORT     = /dev/ttyUSB0
CC          = avr-gcc
OBJCOPY     = avr-objcopy
SIZE        = avr-size --format=avr --mcu=$(MCU)
CFLAGS      = -mmcu=$(MCU) -Os -DF_CPU=16000000UL -Wall -Wstrict-prototypes -Wextra -g -I. -I../../../Extra/lib/uart
PROGRAMMER  = avrdude -F -V -c arduino -p $(MCU) -P $(USBPORT)



# Default target.
all: main.out


# Compile: create object files from C source files.
main.o: main.c 
	$(CC) -c $(CFLAGS) $< -o $@

uart.o: ../../../Extra/lib/uart/uart.c ../../../Extra/lib/uart/uart.h
	$(CC) -c $(CFLAGS) $< -o $@
	
AT28C16_Programmer.o: AT28C16_Programmer.c AT28C16_Programmer.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
main.out: main.o uart.o AT28C16_Programmer.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# remove compiled files
.PHONY: clean
clean:
	rm *.o main.hex main.out


.PHONY: screen
screen: 
	screen $(USBPORT)


# Target: program project.
.PHONY: program
program: main.out
	$(OBJCOPY) -O ihex main.out main.hex
	$(PROGRAMMER) -U flash:w:main.out
