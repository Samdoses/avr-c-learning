/*
Simple routines to play notes out to a speaker
*/


#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "pinDefines.h"

void initTimer(void) {
  //16 bit timer for right hand notes
  TCCR1B |= (1 << WGM12);                               /* CTC mode */
  TCCR1A |= (1 << COM1A0);          /* Toggles pin each cycle through */
  TCCR1B |= (1 << CS11);                            /* CPU clock / 8 */

  //8 bit timer for left hand notes
  TCCR0A |= (1 << WGM01);                                  /* CTC mode */
  TCCR0A |= (1 << COM0A0);           /* Toggles pin each cycle through */
  TCCR0B |= (1 << CS00) | (1 << CS01);               /* CPU clock / 64 */
}

void playNote(uint8_t periodL, uint16_t periodR, uint16_t duration) {
  //left hand notes
  TCNT0 = 0;                                      /* reset the counter */
  OCR0A = periodL;                                     /* set pitch */
  SPEAKER_DDR |= (1 << SPEAKER);           /* enable output on speaker */

  while (duration) {                                 /* Variable delay */
    _delay_ms(1);
    duration--;
  }
  SPEAKER_DDR &= ~(1 << SPEAKER);                  /* turn speaker off */

  //right hand notes
  TCNT1 = 0;                                  /* reset the counter */
  OCR1A = periodR;                                     /* set pitch */
  SPEAKER_16_DDR |= (1 << SPEAKER_16);      /* enable output on speaker */
  while (duration) {                              /* Variable delay */
    _delay_ms(1);
    duration--;
  }
  SPEAKER_16_DDR &= ~(1 << SPEAKER_16);             /* turn speaker off */
}
