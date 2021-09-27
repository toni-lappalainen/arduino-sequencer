#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <Arduino.h>

void initSeq();
void runSeq();
void tempoInit();
void changeStepGate(int step);
void chooseStep(int step);
void changeStepNote(int noteStep, int value);
int getSteps();

#endif