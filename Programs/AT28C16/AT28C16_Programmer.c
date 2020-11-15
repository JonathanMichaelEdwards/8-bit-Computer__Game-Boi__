// ****************************************************************************
// File:     AT28C16_Programmer.c                                             *
// Authors:  Jonathan Edwards                                                 *
// Date:     28/08/2019                                                       *
// Descr:    Contains read and write funtions for the EEPROM                  *
// ****************************************************************************


#include <avr/io.h>
#include <util/delay.h>
#include "AT28C16_Programmer.h"


/* Reg B Pins */
#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define SHIFT_REG 4
#define EEPROM_B1 1
#define EEPROM_B0 0

/* Reg D Pins */
#define EEPROM_D7 7
#define EEPROM_D2 2

/* Reg C Pins */
#define OUTPUT_EN 1
#define WRITE_EN 0



/*
 * Initializing the AT28C16 EEPROM.
 */
void initEEPROM(void)
{
    DDRB = BIT(SHIFT_DATA) | BIT(SHIFT_CLK) | BIT(SHIFT_REG);
    DDRC = BIT(WRITE_EN) | BIT(OUTPUT_EN);
    PORTC = BIT(WRITE_EN);
}


/*
 * Determining which bits get set for the shift registers.
 */
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint16_t addr)
{
	for (uint8_t bit = 0; bit < 16; bit++) {
        if ((BIT(bit) & addr)) PORTB |= BIT(dataPin);  // Set bit
        else PORTB &= ~BIT(dataPin);                   // Clear bit
			
        /* Pulse clock pin (HIGH -> LOW) */
        PORTB |= BIT(clockPin);	
        PORTB &= ~BIT(clockPin);	
	}
}


/*
 * Setting the address bits for the shift registers.
 */
void setAddress(uint16_t address) 
{
    shiftOut(SHIFT_DATA, SHIFT_CLK, address);

    /* Pulse shift register pin (LOW -> HIGH -> LOW) */
    PORTB &= ~BIT(SHIFT_REG);
    PORTB |= BIT(SHIFT_REG);	
    PORTB &= ~BIT(SHIFT_REG);	
}


/* 
 * Initialize byte data pins for both input and output.
 */
void setReg(volatile uint8_t *reg, uint8_t min, uint8_t max, uint8_t io)
{
    for (uint8_t pin = min; pin <= max; pin++) {
        if (io) *reg |= BIT(pin);  // Set bit for Output
        else *reg &= ~BIT(pin);    // Clear bit for Input
    }
}


/* 
 * Writting byte data to the EEPROM.
 */
void setPort(volatile uint8_t *port, uint8_t min, uint8_t max, uint8_t data)
{
    for (uint8_t pin = min; pin <= max; pin++) {
        if ((BIT(pin) & data)) *port |= BIT(pin);  // Set bit
        else *port &= ~BIT(pin);                   // Clear bit
    }
}


/* 
 * Reading byte data from the EEPROM.
 */
void readPin(volatile uint8_t *pin, uint8_t min, uint8_t max, uint8_t *data)
{
    for (uint8_t bit = min; bit <= max; bit++) {
        if ((*pin & BIT(bit))) *data += BIT(bit);  // Add bit data
    }
}


/*
* Write a byte to the EEPROM at the specified address.
*/
void writeEEPROM(uint16_t address, uint8_t data) 
{
    setAddress(address);
    PORTC |= BIT(OUTPUT_EN);  // Set bit for ~OE

    /* Initialize the regirster's */
    setReg(&DDRB, EEPROM_B0, EEPROM_B1, OUTPUT);
    setReg(&DDRD, EEPROM_D2, EEPROM_D7, OUTPUT);

    /* Set the port's */
    setPort(&PORTB, EEPROM_B0, EEPROM_B1, data);
    setPort(&PORTD, EEPROM_D2, EEPROM_D7, data);

    /* Pulse Write Enable pin (LOW -> HIGH) */
    PORTC &= ~BIT(WRITE_EN);
    _delay_us(1);
    PORTC |= BIT(WRITE_EN);
    _delay_ms(10);
}


/*
 * Read a byte from the EEPROM at the specified address.
 * - Returns the byte data stored at that address.
 */
uint8_t readEEPROM(uint16_t address) 
{
    uint8_t data = 0;
    setAddress(address);
    PORTC &= ~BIT(OUTPUT_EN);  // Clear bit for ~OE
  
    /* Initialize the regirster's */
    setReg(&DDRB, EEPROM_B0, EEPROM_B1, INPUT);
    setReg(&DDRD, EEPROM_D2, EEPROM_D7, INPUT);
    
    /* Reading from Pins */
    readPin(&PINB, EEPROM_B0, EEPROM_B1, &data);
    readPin(&PIND, EEPROM_D2, EEPROM_D7, &data);

    return data;
}
