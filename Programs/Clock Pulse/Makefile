# ****************************************************************************
# File:      Makefile                                                        *
# Authors:   Jonathan Edwards                                                *
# Date:      08/23/2019                                                      *
# Descr:     Makefile for the Arduino                                        *
# ****************************************************************************


MCU         = atmega328p
USBPORT     = /dev/ttyUSB0
CC          = avr-gcc
OBJCOPY     = avr-objcopy
SIZE        = avr-size --format=avr --mcu=$(MCU)
CFLAGS      = -mmcu=$(MCU) -Os -DF_CPU=16000000UL -Wall -Wstrict-prototypes -Wextra -g
PROGRAMMER  = avrdude -F -V -c arduino -p $(MCU) -P $(USBPORT)



# Default target.
all: main.out


# Compile: create object files from C source files.
main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
main.out: main.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# remove compiled files
clean:
	rm *.o main.hex main.out


# Target: program project.
.PHONY: program
program: main.out
	$(OBJCOPY) -O ihex main.out main.hex
	$(PROGRAMMER) -U flash:w:main.out
