// Music Box Input Demo

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale16.h"
#include "pinDefines.h"

#define SONG_LENGTH  (sizeof(song) / sizeof(uint16_t))
#define DEBOUNCE_TIME 8
#define ALL_BUTTONS ((1 << BUTTON) | (1 << BUTTON2) | (1 << BUTTON3) | (1 << BUTTON4) | (1 << BUTTON5) | (1 << BUTTON6))

/*- Method declaratins (You could make a .h interface later to make the code neater?) -*/
uint16_t whichNote();
void initNote(uint16_t currentNote);

int main(void) {
  // -------- Inits --------- //
  initTimer();                                      /*initialise the timers*/
  BUTTON_PORT |= ALL_BUTTONS;                    /* pullup on button */
  STATUS_LED_DDR |= (1 << STATUS_LED);

  //STARTUP SOUNTS
  SPEAKER_16_DDR |= (1 << SPEAKER_16);                 /* speaker for output */
  STATUS_LED_PORT |= (1 << STATUS_LED);
  playNote(D4, 300);
  playNote(F4, 300);
  playNote(A4, 300);
  playNote(A4, 300);
  SPEAKER_16_DDR &= ~(1 << SPEAKER_16);
  SPEAKER_16_DDR &= ~(1 << SPEAKER_16);                 /* speaker for output */



  // ------ Event loop ------ //
  while (1) {
    initNote(whichNote());
  }                                            /* End event loop */
  return 0;
}

uint16_t whichNote(){
  if (bit_is_clear(BUTTON_PIN, BUTTON)) { /* If button 1 is pressed */
    return C4;     /* Return button 1 note */
  }
  else if (bit_is_clear(BUTTON_PIN, BUTTON2)) { /* If button 2 is pressed*/
    return D4;     /* Return button 2 note etc */
  }
  else if (bit_is_clear(BUTTON_PIN, BUTTON3)) {
    return E4;
  }
  else if (bit_is_clear(BUTTON_PIN, BUTTON4)) {
    return F4;
  }
  else if (bit_is_clear(BUTTON_PIN, BUTTON5)) {
    return G4;
  }
  else if (bit_is_clear(BUTTON_PIN, BUTTON6)) {
    return 0;
  }
  else{
    return 0;     /* No buttons are currently being pressed */
  }
}

/*void initNote(uint16_t currentNote){
  uint
  if (currentNote != 0) {
      LED_PORT |= (1 << PB4);
      SPEAKER_16_DDR |= (1 << SPEAKER_16);
      while (currentNote != 0) {
        playNote(currentNote, 300);
        currentNote = whichNote();
      }
      SPEAKER_16_DDR &= ~(1 << SPEAKER_16);
      LED_PORT &= ~(1 << PB4);
  }
}*/

void initNote(uint16_t currentNote){
  if (currentNote != 0) {
    STATUS_LED_PORT |= (1 << STATUS_LED);
    SPEAKER_16_DDR |= (1 << SPEAKER_16);             /* enable speaker output */
      playNote(currentNote, 50);
//      currentNote = whichNote();                     /*update note*/
    SPEAKER_16_DDR &= ~(1 << SPEAKER_16);             /* disable speaker output */
    STATUS_LED_PORT &= ~(1 << STATUS_LED);
  }
}


/*
 BUGS
 *For some reason C4 / D4 always plays???
 */
