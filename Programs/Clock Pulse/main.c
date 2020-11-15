/******************************************************************************
- File:     main.c                                                            *
- Authors:  Jonathan Edwards                                                  *
- Date:     08/28/2019                                                        *
- Descr:    Simple Clock Pulse                                                *
 *****************************************************************************/

#include <avr/io.h>
#include <util/delay.h>

#define BIT(X) (1 << (X))
#define CLK 5
#define DELAY 500


int main(void)
{
  DDRB = BIT(CLK);
  while (1) {
    PORTB ^= BIT(CLK);
  	_delay_ms(DELAY);
  }
}
