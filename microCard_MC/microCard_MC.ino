/*
  DEMO: microCard

  MADE by TEAM a.r.g. : http://www.team-arg.org/demos.html

  2016 - JO3RI

  License: MIT : https://opensource.org/licenses/MIT

*/

//determine the demo
#define DEMO_ID 10

#include "globals.h"
#include "menu.h"
#include "demo.h"


typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM mainGameLoop[] = {
  stateIntro,
  stateDemo,
};


void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);                                 // set the frame rate of the game at 60 fps
  arduboy.initRandomSeed();                                 // This sets the random to more random, remove this if no random is needed !
}


void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}

