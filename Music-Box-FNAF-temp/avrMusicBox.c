// Music Box Input Demo

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale8.h"
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
/*DELETE
 *Make record array of notes,
 *initialise a second timer for left hand notes
 *change paragmeter of playnote method
 *play both simultaniously in the playnote method???*/
int main(void) {

  typedef struct {
    char noteName;
    int leftNote;
    int rightNote;
  }

  const uint16_t song[] = {
    0, 0,
    A3, A3, F4, F4, A3, E4, E4, D4, D4,
    0, 0, 0, 0, 0, 0, 0,
    Ax3, Ax3,
    D4, F4, D4, A4, A4, G4, G4,
    F4, F4, G4, F4, A3, A3, F4, F4,
    A3, E4, E4, D4, D4, Ax3, Ax3, Cx4,
    F4, Cx4, A4, A4,  G4, G4, F4, F4, G4,
    F4, A3, A3, F4, F4, A3, E4, E4, D4, D4, Ax3,
    Ax3, D4, F4, D4, A4, A4, G4, G4, F4, F4, G4, G4,
    A3, A3, F4, F4, A3, E4, E4, D4, D4, Ax3, Ax3, Cx4,
    F4, Cx4, A4, A4, G4, G4, F4, F4, G4, F4
  };

  const Note song[] = {
    {'A', LF2, 0}, {'A', LF2, 0}, {'A', LF2, A3}, {'A', LF2, A3},
    {'A', LF2, F4}, {'A', LF2, F4}, {'A', LF2, A3}, {'A', LF2, E4},
  }

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
