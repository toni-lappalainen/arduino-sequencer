#include <Arduino.h>
#include "Sequencer.h"
#include "Draw.h"
#include "logging.h"
#include "Interface.h"
#include <Keypad.h>

void setup()
{
  Serial.begin(9600);
  initDraw();
  initInterface();
  initSeq();
}

void loop()
{
  static long currentMillis;
  checkKeys();
  runSeq();
}
