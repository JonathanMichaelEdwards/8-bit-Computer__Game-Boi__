#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "AT28C16_Programmer.h"
#include "uart.h"



int main(void)
{
    uartInit();
    initEEPROM();


    // for (int i = 0; i < 8; i++) writeEEPROM(i, BIT(i));

    // for (int i = 0; i < 8; i++) printf("%d\n", readEEPROM(i));

    uint8_t map[8][8] = {
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', '.', '.', 'X', '.', '.', '.', 'X'},
        {'X', '.', '.', '.', '.', 'X', '.', 'X'},
        {'X', '.', '.', 'X', '.', '.', '.', 'X'},
        {'X', '.', '.', '.', '.', 'X', 'X', 'X'},
        {'X', '.', '.', '.', '.', '.', '.', 'X'},
        {'X', '.', '.', '.', '.', '.', '.', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
    };

    uint8_t storedMap[8][8] = {0};

    uint16_t addr = 0;
    uint8_t data = 0;
       
    /* Writing information to the EEPROM */
    for (uint8_t row = 0; row < 8; row++) {
        for (uint8_t col = 0; col < 8; col++) {
            if (map[col][row] == 'X') data |= BIT(col);
            else data &= ~BIT(col);
            
            printf("%c ", map[row][col]);
        }
        puts("");
        writeEEPROM(addr++, data);
        data = 0;
    }
    
    // /* Reading information from the EEPROM */
    // addr = 0;
    // for (uint8_t row = 0; row < 8; row++) {
    //     for (uint8_t col = 0; col < 8; col++) {
    //         if ((readEEPROM(addr) & BIT(col))) storedMap[row][col] = 'X';
    //         else storedMap[row][col] = '.';
    //     }
    //     addr++;
    // }

    // /* Printing the new map */
    // puts("");
    // addr = 0;
    // for (uint8_t row = 0; row < 8; row++) {
    //     for (uint8_t col = 0; col < 8; col++) {
    //         printf("%c ", storedMap[col][row]);
    //     }
    //     puts("");
    //     addr++;
    // }
}