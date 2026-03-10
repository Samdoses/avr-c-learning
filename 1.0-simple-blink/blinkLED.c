                                                       /* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                    /* Functions to waste time */

#define DELAYTIME 1000                     /* C macros to make code more readable and portable */
#define LED_PORT  PORTB
#define LED_DDR   DDRB

int main(void) {

  // -------- Inits --------- //
  LED_DDR |= (1 << 5);            /* Data Direction Register B:
                                   writing a one to the bit
                                   enables output. */

  // ------ Event loop ------ //
  while (1) {

    LED_PORT |= (1 << 5);   /*turn on PB5 pin*/
    _delay_ms(DELAYTIME);   /*wait 1 s*/

    LED_PORT &= ~(1 << 5);   /*turn off PB5 pin*/
    _delay_ms(DELAYTIME);    /*wait 1 s*/                                              /* End event loop */
  }
  return 0;                            /* This line is never reached */
}
