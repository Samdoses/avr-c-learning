                                                       /* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {

  // -------- Inits --------- //
  DDRB |= (1 << 5);            /* Data Direction Register B:
                                   writing a one to the bit
                                   enables output. */

  // ------ Event loop ------ //
  while (1) {

    PORTB |= (1 << 5);   /*turn on PB5 pin*/
    _delay_ms(1000);    /*wait 1 s*/

    PORTB &= ~(1 << 5);   /*turn off PB5 pin*/
    _delay_ms(1000);    /*wait 1 s*/                                              /* End event loop */
  }
  return 0;                            /* This line is never reached */
}
