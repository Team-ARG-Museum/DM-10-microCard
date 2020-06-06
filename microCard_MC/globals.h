#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#include "bitmaps.h"

//define menu states (on main menu)
#define STATE_INTRO               0
#define STATE_DEMO                1

#define DEMO_FASE_TO_START_WITH   0
#define INTRO_FASE_TO_START_WITH  0

Arduboy2Base arduboy;
Sprites sprites;

byte gameState = STATE_INTRO;   // start the game with the TEAM a.r.g. logo
byte globalCounter = 0;
byte demoFase = DEMO_FASE_TO_START_WITH;
byte introFase = INTRO_FASE_TO_START_WITH;
boolean arduboyLogoIsVisible = true;;
boolean teamArgLogoIsVisible = false;
byte arduboyX = 128;

#endif
