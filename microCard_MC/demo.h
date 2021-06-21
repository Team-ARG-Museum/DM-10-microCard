#ifndef DEMO_H
#define DEMO_H

#include <Arduino.h>
#include "globals.h"

byte blinkingCounter = 0;
byte loadingFrame = 0;
byte beltFrame = 0;
int connector = 0;
boolean pressKeyIsVisible = false;
boolean flashingIsVisible = false;

void showMachine()
{
  sprites.drawSelfMasked(2, 0, conveyorBeltOne, beltFrame % 6);
  sprites.drawSelfMasked(9, 16, conveyorBeltTwo, beltFrame % 6);
  sprites.drawSelfMasked(16, 32, conveyorBeltThree, beltFrame % 6);
  sprites.drawSelfMasked(24, 48, conveyorBeltFour, beltFrame % 6);
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 + (i * 12) - beltFrame, (i * 24) - 2 - (2 * beltFrame), device, 0);
  for (byte i = 0; i < 4; i++) sprites.drawPlusMask(0, i * 16, machine_plus_mask, i);
  sprites.drawSelfMasked(2, 45, joeri, 0);
}

void pressKeyBlinking()
{
  if (arduboy.everyXFrames(4)) blinkingCounter++;
  if (blinkingCounter > 12)
  {
    pressKeyIsVisible = !pressKeyIsVisible;
    blinkingCounter = 0;
  }
}

void wait()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 16)
  {
    demoFase++;
    globalCounter = 0;
  }
}

void showBeltScrolling()
{

  if (arduboy.everyXFrames(8)) beltFrame++;
  if (beltFrame > 11)
  {
    beltFrame = 0;
    demoFase++;
  }
  pressKeyBlinking();
  showMachine();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON | UP_BUTTON | DOWN_BUTTON | RIGHT_BUTTON | LEFT_BUTTON))
  {
    demoFase = 3;
    globalCounter = 0;
  }
}

void showScanning()
{
  flashingIsVisible = !flashingIsVisible;
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 16)
  {
    demoFase++;
    globalCounter = 0;
    flashingIsVisible = false;
  }
  pressKeyBlinking();
  showMachine();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON | UP_BUTTON | DOWN_BUTTON | RIGHT_BUTTON | LEFT_BUTTON))
  {
    demoFase = 3;
    flashingIsVisible = false;
    globalCounter = 0;
  }
}

void showCleared()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 16)
  {
    demoFase = 0;
    globalCounter = 0;
  }
  pressKeyBlinking();
  showMachine();
  if (globalCounter > 4)
  {
    sprites.drawSelfMasked(39, 49, scannedOk, 0);
  }
  if (arduboy.justPressed(A_BUTTON | B_BUTTON | UP_BUTTON | DOWN_BUTTON | RIGHT_BUTTON | LEFT_BUTTON))
  {
    demoFase = 3;
    globalCounter = 0;
  }
}

void showUrl()
{
  sprites.drawSelfMasked(81, 5, visit, 0);
  sprites.drawSelfMasked(0, 3, forMore, 0);
  pressKeyBlinking();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON | UP_BUTTON | DOWN_BUTTON | RIGHT_BUTTON | LEFT_BUTTON)) demoFase++;
}

void showConnect()
{
  if (arduboy.everyXFrames(4))
  {
    if (connector < 13) connector++;
    globalCounter++;
  }
  for (byte i = 0; i < 2; i++)sprites.drawSelfMasked(56, 2 + ( 32 * i), createYourOwn, i);
  for (byte i = 0; i < 2; i++)sprites.drawSelfMasked(13, 32 * i, arduboyDevice, i);
  sprites.drawSelfMasked(-13 + connector, 27, connectorUSB, 0);
  pressKeyBlinking();
  if (globalCounter > 16)
  {
    demoFase++;
    connector = 0;
    globalCounter = 0;
  }
  if (arduboy.justPressed(A_BUTTON | B_BUTTON | UP_BUTTON | DOWN_BUTTON | RIGHT_BUTTON | LEFT_BUTTON))
  {
    connector = 0;
    globalCounter = 0;
    demoFase = 0;
  }
}

void showUpload()
{
  if (arduboy.everyXFrames(4))
  {
    globalCounter++;
    if (loadingFrame < 7) loadingFrame++;
  }
  for (byte i = 0; i < 2; i++)sprites.drawSelfMasked(56, 2 + ( 32 * i), createYourOwn, i);
  for (byte i = 0; i < 2; i++)sprites.drawSelfMasked(13, 32 * i, arduboyDevice, i);
  sprites.drawSelfMasked(30, 27, logoA, 0);
  sprites.drawSelfMasked(27, 25, loading, loadingFrame);
  sprites.drawSelfMasked(0, 27, connectorUSB, 0);
  pressKeyBlinking();
  if (globalCounter > 32)
  {
    loadingFrame = 0;
    globalCounter = 0;
    demoFase = 4;
  }
  if (arduboy.justPressed(A_BUTTON | B_BUTTON | UP_BUTTON | DOWN_BUTTON | RIGHT_BUTTON | LEFT_BUTTON))
  {
    loadingFrame = 0;
    globalCounter = 0;
    connector = 0;
    demoFase = 0;
  }
}

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM nextFase[] =
{
  showBeltScrolling,
  showScanning,
  showCleared,
  showUrl,
  showConnect,
  showUpload,
};


void stateDemo()
{
  ((FunctionPointer) pgm_read_word (&nextFase[demoFase]))();
  if (arduboyLogoIsVisible) sprites.drawSelfMasked(arduboyX, 6, arduboyLogo, 0);
  if (pressKeyIsVisible) sprites.drawSelfMasked(96, 6, pressKey, 0);
  if (flashingIsVisible) sprites.drawSelfMasked(35, 8, flashing, 0);
}




#endif
