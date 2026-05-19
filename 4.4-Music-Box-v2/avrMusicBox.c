// Music Box Input Demo

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale16.h"
#include "pinDefines.h"

#define SONG_LENGTH  (sizeof(song) / sizeof(uint16_t))
#define DEBOUNCE_TIME 4


//-- Debounce method --//
uint8_t debouncePress(void){
  if (bit_is_clear(BUTTON_PIN, BUTTON)){
    _delay_ms(DEBOUNCE_TIME);
  }
  if (bit_is_clear(BUTTON_PIN, BUTTON)){
    return(1);
  }
  else{
    return(0);
  }
}

int main(void) {
  const uint16_t song[] = {
    G5, G5, G5, E5, E5, E5,
    C5, C5, C5, G4, G4, G4,
    A4, B4, C5, A4, A4, C5,
    G4, G4, G4, G4, G4, G4,
    D5, D5, D5, G5, G5, G5,
    E5, E5, E5, C5, C5, C5,
    A4, B4, C5, D5, D5, E5,
    D5, D5, D5, D5, D5,
    E5, F5, E5, D5, G5, G5,
    E5, D5, C5, C5, C5, C5,
  };
  /* starting at end b/c routine starts by incrementing and then playing
   *     this makes the song start at the beginning after reboot */
//  uint8_t whichNote = SONG_LENGTH - 1;
  uint8_t wasButtonPressed = 0;

  // -------- Inits --------- //
  initTimer();                                      /*initialise the timers*/
  SPEAKER_16_DDR |= (1 << SPEAKER_16);                 /* speaker for output */
  BUTTON_PORT |= (1 << BUTTON);                    /* pullup on button */

  LED_DDR |= (1 << LED7);

  // ------ Event loop ------ //
  while (1) {
    if (debouncePress()) {
      if (!wasButtonPressed) {              /* if it's a new press ... */
        LED_PORT |= (1 << LED7);
        for (int whichNote = 0; whichNote < SONG_LENGTH; whichNote++){
          playNote(song[whichNote], 300);
          if (debouncePress()){
            break;                          /*if the button is clicked end the song*/
          }
        }
        LED_PORT &= ~(1 << LED7);
        wasButtonPressed = 1;
      }
    }
    else {
      wasButtonPressed = 0;
    }
  }                                                  /* End event loop */
  return 0;
}
