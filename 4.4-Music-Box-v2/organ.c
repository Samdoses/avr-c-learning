/*
 * Simple routines to play notes out to a speaker
 */


#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "pinDefines.h"

void initTimer(void) {
  /*16-bit timer to control speaker pitch*/
  TCCR1B |= (1 << WGM12);                               /* CTC mode */
  TCCR1A |= (1 << COM1A0);          /* Toggles pin each cycle through */
  TCCR1B |= (1 << CS11);                            /* CPU clock / 8 */

  /*8-bit timer to increment other software timers*/
  TCCR0A |= (1 << WGM01);                                  /* CTC mode */
  TCCR0A |= (1 << COM0A0);           /* Toggles pin each cycle through */
  TCCR0B |= (1 << CS00) | (1 << CS02);               /* CPU clock / 1024 */
  TCNT0 = 0;                                      /* reset the counter */
  OCR0A = 249;                                    /* sends out an interupt every ms */
}

void playNote(uint16_t period, uint16_t duration) {

  /* Only reset the timer if it exceeds the new pitch threshold to prevent overflow gaps */
  if (TCNT1 > period) {
    TCNT1 = 0;
  }

  OCR1A = period;                                     /* set pitch */
  SPEAKER_16_PORT |= (1 << SPEAKER_16);      /* enable output on speaker */
  while (duration) {                              /* Variable delay */
    _delay_ms(1);
    duration--;
  }
}
