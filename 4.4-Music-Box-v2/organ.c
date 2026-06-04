/*
 * Simple routines to play notes out to a speaker
 */


#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "pinDefines.h"

void initTimer(void) {
  TCCR1B |= (1 << WGM12);                               /* CTC mode */
  TCCR1A |= (1 << COM1A0);          /* Toggles pin each cycle through */
  TCCR1B |= (1 << CS11);                            /* CPU clock / 8 */
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
