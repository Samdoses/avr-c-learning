/*
A simple test of serial-port functionality.
Takes in a character at a time and sends it right back out,
 displaying the ASCII value on the LEDs.
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

#define LED_PORT PORTD
#define LED_DDR  DDRD
#define ALL_LEDS ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))

int main(void) {
  char serialCharacter;

  // -------- Inits --------- //
  LED_DDR = ALL_LEDS;                            /* set up LEDs for output */
  initUSART();
  printString("Hello World!\r\n");                          /* to test */

  // ------ Event loop ------ //
  while (1) {

    serialCharacter = receiveByte();
    transmitByte(serialCharacter);
    LED_PORT |= (serialCharacter << 2);
                           /* display ascii/numeric value of character */
    _delay_ms(400);
    LED_PORT &= ~ALL_LEDS;
  }                                                  /* End event loop */
  return 0;
}
