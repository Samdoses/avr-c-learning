// Music Box Input Demo

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale.h"
#include "pinDefines.h"
#include <avr/interrupt.h>

#define SONG_LENGTH  (sizeof(song) / sizeof(song[0])) /*the sizeof method determines the memory size of data structure so this calc will find the number of elements*/
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

  struct Note {
    char noteName;
    int note1;
    int note2;
  };

  const struct Note song[] = {
    {'A', DDS(F4), 0}, {'A', DDS(F4), 0}, {'A', DDS(F4), DDS(A5)}, {'A', DDS(F4), DDS(A5)},
    {'A', DDS(F4), DDS(F6)}, {'A', DDS(F4), DDS(F6)}, {'A', DDS(F4), DDS(A6)}, {'A', DDS(F4), DDS(E6)},
  };

  /* starting at end b/c routine starts by incrementing and then playing
   *     this makes the song start at the beginning after reboot */
//  uint8_t whichNote = SONG_LENGTH - 1;
  uint8_t wasButtonPressed = 0;

  // -------- Inits --------- //
  initTimer();                                     /*initialise the timers*/
  SPEAKER_16_DDR |= (1 << SPEAKER_16);             /* speaker for output */
  BUTTON_PORT |= (1 << BUTTON);                    /* pullup on button */
  LED_DDR |= (1 << LED7);                          /* enable output for led */
  sei();                                           /* Enable global interrupts */

  // ------ Event loop ------ //
  while (1) {
    if (debouncePress()) {
      if (!wasButtonPressed) {              /* if it's a new press ... */
        LED_PORT |= (1 << LED7);
        for (int whichNote = 0; whichNote < SONG_LENGTH; whichNote++){
          playNote(song[whichNote].note1, song[whichNote].note2, 150);
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
