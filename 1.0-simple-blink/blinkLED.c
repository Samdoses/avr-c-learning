                                                       /* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {

  // -------- Inits --------- //
  DDRB |= 0b00100000;            /* Data Direction Register B:
                                   writing a one to the bit
                                   enables output. */

  // ------ Event loop ------ //
  while (1) {

    PORTB = 0b00100000;   /*turn on PB5 pin*/
    _delay_ms(1000);      /*wait 1 s*/

    PORTB = 0b00000000;   /*turn off PB5 pin*/
    _delay_ms(1000);      /*wait 1 s*/                                              /* End event loop */
  }
  return 0;                            /* This line is never reached */
}
