                                                       /* SOS Beacon Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define LED_PORT PORTD
#define LED_DDR  DDRD
#define ALL_LEDS ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))
#define SHORT_DELAYTIME 300
#define LONG_DELAYTIME 900
#define RESET_DELAYTIME 2000

int main(void) {

  // -------- Inits --------- //
  LED_DDR |= ALL_LEDS;            /* Data Direction Register D:
                                   writing a one to the bit
                                   enables output. */

  // ------ Event loop ------ //
  while (1) {

    for(int i = 0; i < 9; i++){
      if(i < 3 || i >= 6){
        LED_PORT |= ALL_LEDS;   /*turn on PD2 -> PD7 pin*/
        _delay_ms(SHORT_DELAYTIME);      /*wait 300 ms*/

        LED_PORT &= ~ALL_LEDS;   /*turn off PD2 -> PD7 pin*/
        _delay_ms(SHORT_DELAYTIME);      /*wait 300 ms*/
      }

      else{
        LED_PORT |= ALL_LEDS;   /*turn on PD2 -> PD7 pin*/
        _delay_ms(LONG_DELAYTIME);      /*wait 900 ms*/

        LED_PORT &= ~ALL_LEDS;   /*turn off PD2 -> PD7 pin*/
        _delay_ms(SHORT_DELAYTIME);      /*wait 300 ms*/
      }
    }
    _delay_ms(RESET_DELAYTIME);          /*wait 2000 ms, before resetting loop*/
  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
