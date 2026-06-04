// Music Box Input Demo

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale16.h"
#include "pinDefines.h"
//#define SONG_LENGTH  (sizeof(song) / sizeof(uint16_t))
#define DEBOUNCE_TIME 8


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
  const uint16_t song0[] = {
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
    0xFFFF, /*The stop note*/
  };

  const uint16_t song1[] = {
    A3, A3, F4, F4, A3, E4, E4,
    D4, D4, D4, D4, D4,
    Ax3, Ax3, D4, F4, D4,
    A4, A4,
    G4, G4, F4, F4, G4,
    F4, F4,
    A3, A3, F4, F4, A3, E4, E4,
    D4, D4, D4, D4, D4,
    Ax3, Ax3, Cx4, F4, Cx4,
    A4, A4, A4,
    G4, G4, F4, F4, G4,
    F4, F4,
    A3, A3, F4, F4, A3, E4, E4, D4, D4, Ax3, Ax3,
    D4, F4, D4, A4, A4, G4, G4, F4, F4,G4, G4,
    A3, A3, F4, F4, A3, E4, E4, D4, D4, Ax4, Ax4, Cx4,
    F4, Cx4, A4, A4, G4, G4, F4, F4, G4, F4,
    0xFFFF, /*The stop note*/
  };


  /*An array where each index points to the songs found on this program*/
  const uint16_t* psong[2] = {song0, song1};

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
      _delay_ms(200);
      uint16_t* song;
        if (debouncePress()){
          song = psong[0]; /*I the button is clicked twice within 200ms the play the first song*/
        }
        else {
          song = psong[1]; /*else play the second song*/
        }
      if (!wasButtonPressed) {              /* if it's a new press ... */
        LED_PORT |= (1 << LED7);
        SPEAKER_16_DDR |= (1 << SPEAKER_16);             /* enable speaker output */
        for (int whichNote = 0; song[whichNote] != 0xFFFF; whichNote++){
          playNote(song[whichNote], 300);
          if (debouncePress()){
            break;                          /*if the button is clicked end the song*/
          }
        }
        SPEAKER_16_DDR &= ~(1 << SPEAKER_16);             /* disable speaker output */
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
