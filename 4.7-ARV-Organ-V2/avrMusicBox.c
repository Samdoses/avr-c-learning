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
#define ALL_BUTTONS ((1 << BUTTON) | (1 << BUTTON2) | (1 << BUTTON3) | (1 << BUTTON4) | (1 << BUTTON5) | (1 << BUTTON6))

// -- Var declarations --//
volatile uint32_t system_millis = 0; /*An interrupt ,fired every ms, to increment a global variable*/
uint8_t buttonState = 0; /*Defaults to being off*/
uint32_t first_click_millis = 0; /* The time since the double click was being checked */

/*- Method declaratins (You could make a .h interface later to make the code neater?) -*/
void checkButtonDoubleClick();
void playSong(uint16_t* song);
uint16_t whichNote();
void initNote(uint16_t currentNote);

/* -The notes of each song- */
const uint16_t songStartup[] = {
  D4, F4, A4, A4, 0xFFFF
};

const uint16_t song0[] = {
  G4, G4, G4, E4, E4, E4,
  C4, C4, C4, G3, G3, G3,
  A3, B3, C4, A3, A3, C4,
  G3, G3, G3, G3, G3, G3,
  D4, D4, D4, G4, G4, G4,
  E4, E4, E4, C4, C4, C4,
  A3, B3, C4, D4, D4, E4,
  D4, D4, D4, D4, D4,
  E4, F4, E4, D4, G4, G4,
  E4, D4, C4, C4, C4, C4,
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
  BUTTON_PORT |= ALL_BUTTONS;                    /* pullup on button */

  STATUS_LED_DDR |= (1 << STATUS_LED);

  sei();                                          /*Enables global interupts*/

  // ------ Startup sound ------ //
  playSong(songStartup);

  // ------ Event loop ------ //
  while (1) {
    checkButtonDoubleClick();
    initNote(whichNote());
  }                                                  /* End event loop */
  return 0;
}

ISR(TIMER0_COMPA_vect) {
  system_millis++;
}

//-- Debounce method --//
uint8_t debouncePress(void){// static variable remembers its value between function calls
  static uint8_t last_button_state = 1; // Assume 1 means unpressed (pull-up)

  // Read the current physical state of the pin (0 if pressed, 1 if not)
  uint8_t current_button_state = bit_is_clear(BUTTON_PIN, BUTTON6) ? 0 : 1;

  // Check for a FALLING EDGE (Transition from unpressed -> pressed)
  if (last_button_state == 1 && current_button_state == 0) {
    _delay_ms(DEBOUNCE_TIME); // Wait for bounce to settle

    if (bit_is_clear(BUTTON_PIN, BUTTON6)) { // If it's still pressed
      last_button_state = 0; // Update our memory
      return 1; // <-- Return 1 ONLY ONCE per press!
    }
  }
  // Check for a RISING EDGE (Transition from pressed -> unpressed)
  else if (last_button_state == 0 && current_button_state == 1) {
    _delay_ms(DEBOUNCE_TIME); // Debounce the release too

    if (!bit_is_clear(BUTTON_PIN, BUTTON6)) { // If it's still released
      last_button_state = 1; // Reset memory so it can be pressed again
    }
  }

  return 0; // Return 0 for all other cases
}

/*- model the button click as a final state machine -*/
void checkButtonDoubleClick(){
  /*!!MAKE THESE VAR VISIBLE FOR ENTIRE CLASS!!*/


  //menu to choose the correct song
  if(debouncePress()){
    if (buttonState == 0){
      first_click_millis = system_millis;                 /*Record the time of the button being pressed the first time*/
      buttonState = 1;                                    /*Update the button state*/
    }
    else if (buttonState == 1) {
      buttonState = 2;
      }
  }

  if((system_millis - first_click_millis) > 600){         /*If the double click time is up, play the relavant song*/
    if (buttonState == 1){
      playSong(playlist[0]);                              /*Play the first song*/
      buttonState = 0;
    }
    else if  (buttonState == 2){
      playSong(playlist[1]);                              /*Play the second song*/
      buttonState = 0;
    }
  }
}

void playSong(uint16_t* song){
  STATUS_LED_PORT |= (1 << STATUS_LED);                         /*Turn on status led*/
  SPEAKER_16_DDR |= (1 << SPEAKER_16);             /* enable speaker output */

  for (int whichNote = 0; song[whichNote] != 0xFFFF; whichNote++){
    playNote(song[whichNote], 300);
    if (debouncePress()){
      playNote(E4, 300); //sound to indicate that the song has been stopped
      break;
    }
  }

  SPEAKER_16_DDR &= ~(1 << SPEAKER_16);             /* disable speaker output */
  STATUS_LED_PORT &= ~(1 << STATUS_LED);                         /*Turn off status led*/

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

void initNote(uint16_t currentNote){
  if (currentNote != 0) {
    STATUS_LED_PORT |= (1 << STATUS_LED);
    SPEAKER_16_DDR |= (1 << SPEAKER_16);             /* enable speaker output */
    playNote(currentNote, 50);
    SPEAKER_16_DDR &= ~(1 << SPEAKER_16);             /* disable speaker output */
    STATUS_LED_PORT &= ~(1 << STATUS_LED);
  }
}

