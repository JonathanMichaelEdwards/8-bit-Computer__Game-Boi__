// ****************************************************************************
// File:     AT28C16_Programmer.h                                             *
// Authors:  Jonathan Edwards                                                 *
// Date:     28/08/2019                                                       *
// Descr:    Everything that is used from AT28C16_Programmer.c                *
// ****************************************************************************


#include <stdio.h>

#ifndef AT28C16_Programmer_H
#define AT28C16_Programmer_H

#define BIT(X) (1 << (X))
#define OUTPUT 1
#define INPUT 0 


void initEEPROM(void);
void writeEEPROM(uint16_t address, uint8_t data);
uint8_t readEEPROM(uint16_t address);


#endif // AT28C16_Programmer_H