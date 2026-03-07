                                                       /* SOS Beacon Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {

  // -------- Inits --------- //
  DDRD |= 0b11111100;            /* Data Direction Register D:
                                   writing a one to the bit
                                   enables output. */

  // ------ Event loop ------ //
  while (1) {

    for(int i = 0; i < 9; i++){
      if(i < 3 || i >= 6){
        PORTD = 0b11111100;   /*turn on PD2 -> PD7 pin*/
        _delay_ms(300);      /*wait 1 s*/

        PORTD = 0b00000000;   /*turn off PD2 -> PD7 pin*/
        _delay_ms(300);      /*wait 1 s*/
      }

      else{
        PORTD = 0b11111100;   /*turn on PD2 -> PD7 pin*/
        _delay_ms(900);      /*wait 0.3 s*/

        PORTD = 0b00000000;   /*turn off PD2 -> PD7 pin*/
        _delay_ms(300);      /*wait 0.3 s*/
      }
    }
    _delay_ms(2000);
  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
