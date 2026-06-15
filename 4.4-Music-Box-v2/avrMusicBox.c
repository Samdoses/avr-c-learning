// Music Box Input Demo

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale16.h"
#include "pinDefines.h"
#include <avr/interrupt.h>
//#define SONG_LENGTH  (sizeof(song) / sizeof(uint16_t))
#define DEBOUNCE_TIME 8

// -- Var declarations --//
volatile uint32_t system_millis = 0; /*An interrupt ,fired every ms, to increment a global variable*/
uint8_t buttonState = 0; /*Defaults to being off*/
uint32_t first_click_millis = 0; /* The time since the double click was being checked */

/*- Method declaratins (You could make a .h interface later to make the code neater?) -*/
void checkButtonDoubleClick();
void playSong(uint16_t* song);

/* -The notes of each song- */
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
const uint16_t* playlist[2] = {song0, song1};

int main(void) {
  /* starting at end b/c routine starts by incrementing and then playing
   *     this makes the song start at the beginning after reboot */

  // -------- Inits --------- //
  initTimer();                                      /*initialise the timers*/
  SPEAKER_16_DDR |= (1 << SPEAKER_16);                 /* speaker for output */
  BUTTON_PORT |= (1 << BUTTON);                    /* pullup on button */

  LED_DDR |= (1 << LED7);

  // ------ Event loop ------ //
  while (1) {
    checkButtonDoubleClick();
  }                                                  /* End event loop */
  return 0;
}

ISR(TIMER0_COMPA_vect) {
  system_millis++;
}

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

/*- model the button click as a final state machine -*/
void checkButtonDoubleClick(){
  /*!!MAKE THESE VAR VISIBLE FOR ENTIRE CLASS!!*/


  //menu to choose the correct song
  if (buttonState == 0 && debouncePress()){
    first_click_millis = system_millis;                 /*Record the time of the button being pressed the first time*/
    buttonState = 1;                                    /*Update the button state*/
    playSong(playlist[0]);                              /*Play the first song*/
  }
  else if (buttonState == 1 && debouncePress() && (system_millis - first_click_millis) < 200){
    buttonState = 2;                                    /*Update the button state*/
    playSong(playlist[1]);                              /*Play the second song*/
  }

  //stop playing song
  if ((buttonState == 1 || buttonState == 2) && debouncePress()){
    buttonState = 0;                                    /*Stop playing songs*/
  }
}

void playSong(uint16_t* song){
  LED_PORT |= (1 << LED7);                         /*Turn on status led*/
  SPEAKER_16_DDR |= (1 << SPEAKER_16);             /* enable speaker output */

  for (int whichNote = 0; song[whichNote] != 0xFFFF; whichNote++){
    playNote(song[whichNote], 300);
    if (buttonState == 0){
      break;
    }
  }

  SPEAKER_16_DDR &= ~(1 << SPEAKER_16);             /* disable speaker output */
  LED_PORT &= ~(1 << LED7);                         /*Turn off status led*/

}
