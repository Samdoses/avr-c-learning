                                                       /* SOS Beacon Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define ALL_LEDS ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))


int main(void) {

  // -------- Inits --------- //
  DDRD |= ALL_LEDS;            /* Data Direction Register D:
                                   writing a one to the bit
                                   enables output. */

  // ------ Event loop ------ //
  while (1) {

    for(int i = 0; i < 9; i++){
      if(i < 3 || i >= 6){
        PORTD |= ALL_LEDS;   /*turn on PD2 -> PD7 pin*/
        _delay_ms(300);      /*wait 1 s*/

        PORTD &= ~ALL_LEDS;   /*turn off PD2 -> PD7 pin*/
        _delay_ms(300);      /*wait 1 s*/
      }

      else{
        PORTD |= ALL_LEDS;   /*turn on PD2 -> PD7 pin*/
        _delay_ms(900);      /*wait 0.3 s*/

        PORTD &= ~ALL_LEDS;   /*turn off PD2 -> PD7 pin*/
        _delay_ms(300);      /*wait 0.3 s*/
      }
    }
    _delay_ms(2000);
  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
