// Music Box Input Demo

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "scale16.h"

#define LED_PORT PORTD
#define LED_DDR  DDRD
#define ALL_LEDS ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))
#define SONG_LENGTH  (sizeof(song) / sizeof(uint16_t))
#define DELAYTIME 300                                    /* milliseconds */

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

  const char* songNames[] = {
    "G5", "G5", "G5", "E5", "E5", "E5",
    "C5", "C5", "C5", "G4", "G4", "G4",
    "A4", "B4", "C5", "A4", "A4", "C5",
    "G4", "G4", "G4", "G4", "G4", "G4",
    "D5", "D5", "D5", "G5", "G5", "G5",
    "E5", "E5", "E5", "C5", "C5", "C5",
    "A4", "B4", "C5", "D5", "D5", "E5",
    "D5", "D5", "D5", "D5", "D5",
    "E5", "F5", "E5", "D5", "G5", "G5",
    "E5", "D5", "C5", "C5", "C5", "C5"
  };

  LED_DDR = ALL_LEDS;

  // ------ Event loop ------ //
  while (1) {
    for(int i = 0; i < SONG_LENGTH; i++){
      const char* whichNote = songNames[i];//get the string
      char note = whichNote[0];//get the letter
      //flash the led based on its relavant character
      switch(note){
        /*
         * !!!Enable once you figure out 7 leds!!!
        case A:
          LED_PORT |= (1 << 1);
          break;
        */
        case 'B':
          LED_PORT |= (1 << 2);
          _delay_ms(DELAYTIME);                                     /* wait */
          LED_PORT &= ~(1 << 2);
          break;
        case 'C':
          LED_PORT |= (1 << 3);
          _delay_ms(DELAYTIME);                                     /* wait */
          LED_PORT &= ~(1 << 3);
          break;
        case 'D':
          LED_PORT |= (1 << 4);
          _delay_ms(DELAYTIME);                                     /* wait */
          LED_PORT &= ~(1 << 4);
          break;
        case 'E':
          LED_PORT |= (1 << 5);
          _delay_ms(DELAYTIME);                                     /* wait */
          LED_PORT &= ~(1 << 5);
          break;
        case 'F':
          LED_PORT |= (1 << 6);
          _delay_ms(DELAYTIME);                                     /* wait */
          LED_PORT &= ~(1 << 6);
          break;
        case 'G':
          LED_PORT |= (1 << 7);
          _delay_ms(DELAYTIME);                                     /* wait */
          LED_PORT &= ~(1 << 7);
          break;
      }
    }
      /* End event loop */
  return 0;
  }
}
