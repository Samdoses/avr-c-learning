/*
Simple routines to play notes out to a speaker
*/


#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "pinDefines.h"
#include <avr/interrupt.h>


volatile uint16_t phaseAcc1 = 0;      /*Phase accumulators keep track of where we are in the sound wave (speaker only turns on at 32,000)*/
volatile uint16_t phaseAcc2 = 0;


volatile uint16_t note1 = 0;          /* The pitch of the note */
volatile uint16_t note2 = 0;

void initTimer(void) {
  TCCR0A |= (1 << WGM01);                                  /* CTC mode */
  TCCR0A |= (1 << COM0A0);           /* Toggles pin each cycle through */
  TCCR0B |= (1 << CS01);               /* CPU clock / 8 */
  TIMSK0 |= (1 << OCIE0A);                                  /* Enable Timer0 Compare Match Interrupt */

  OCR0A = 63;                               /* *Set Compare Match Value for 31.25 kHz (a good balance between speed and CPU usage)
                                               *Formula: (16,000,000 / (8 * 31250)) - 1 = 63  */
}

void playNote(uint16_t period1, uint16_t period2, uint16_t duration) {
  note1 = period1;
  note2 = period2;

  while (duration) {                                 /* Variable delay */
    _delay_ms(1);
    duration--;
  }

  note1 = 0;                                          /*disable notes after the delay is over*/
  note2 = 0;
}

/* --- THE ISR (Fires exactly 31,250 times a second) --- */
ISR(TIMER0_COMPA_vect) {
  // 1. Increment Acc by the note's pitch
  phaseAcc1 += note1;
  phaseAcc2 += note2;

  // 2. Extract the most significant bit (Bit 15) where 1 represents speaker ON and 0 represents speaker OFF
  uint8_t wave1 = (phaseAcc1 >> 15);
  uint8_t wave2 = (phaseAcc2 >> 15);

  // 3. Mix the waves using XOR and output to the speaker
  if (wave1 ^ wave2) {
    SPEAKER_16_PORT |= (1 << SPEAKER_16);  // Turn speaker pin HIGH
  } else {
    SPEAKER_16_PORT &= ~(1 << SPEAKER_16); // Turn speaker pin LOW
  }
}
