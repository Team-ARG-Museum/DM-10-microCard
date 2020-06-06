#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"


void showArduboySlideDown()
{
  if (arduboy.everyXFrames(1)) arduboyX--;
  if (arduboyX < 58) introFase++;
}

void showArduboySlideUp()
{
  if (arduboy.everyXFrames(1)) arduboyX++;
  if (arduboyX > 109)
  {
    introFase++;
    teamArgLogoIsVisible = true;
  }
}

void waitIntro()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 24)
  {
    introFase++;
    globalCounter = 0;
  }
}

void goToDemo()
{
  gameState = STATE_DEMO;
  globalCounter = 0;
  introFase = 0;
  teamArgLogoIsVisible = false;
}

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM nextFaseIntro[] =
{
  showArduboySlideDown,
  waitIntro,
  showArduboySlideUp,
  waitIntro,
  goToDemo,
};


void stateIntro()
{
  ((FunctionPointer) pgm_read_word (&nextFaseIntro[introFase]))();
  if (arduboyLogoIsVisible) sprites.drawSelfMasked(arduboyX, 6, arduboyLogo, 0);
  if (teamArgLogoIsVisible) sprites.drawSelfMasked(36, 0, T_arg, 0);
}



#endif
