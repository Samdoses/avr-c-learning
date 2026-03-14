/*

Cylon eyes actually turns out to be a decent POV routine.
The only change here is in DELAYTIME.

 */


#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define LED_PORT PORTD
#define LED_DDR  DDRD
#define ALL_LEDS ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))
#define DELAYTIME 200                                    /* milliseconds */

int main(void) {
  uint8_t i=0;
  LED_DDR = ALL_LEDS;              /* Data Direction Register B: all on */

  while (1) {

    while (i < 7) {
      LED_PORT |= (1 << i);                 /* illuminate only i'th pin */
      _delay_ms(DELAYTIME);                                     /* wait */
      LED_PORT &= ~(1 << i);
      i = i + 1;                                /* move to the next LED */
    }

    while (i > 2) {
      LED_PORT |= (1 << i);                /* illuminate only i'th pin */
      _delay_ms(DELAYTIME);                                    /* wait */
      LED_PORT &= ~(1 << i);
      i = i - 1;                           /* move to the previous LED */
    }
  }

  return 0;
}
