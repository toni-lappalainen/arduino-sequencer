#include "Sequencer.h"
#include "Draw.h"
#include "Notes.h"
#include "logging.h"

int gatePin = 13;
int gateSteps[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};                 // gate on/off array.
int noteSteps[] = {36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36}; // note values in midi ints
int stepsAmount = 16;
int currentStep = 0; // index of  the step  where the sequencer is at the current moment
int bpm = 100;
int stepLength = 4;      // note length as in time signature, eg the latter number in 4/4. Smaller is longer.
int stepInMillis;        // step length in millisecond
int chosenStep = 0;      // index of step that is chosen for editing;
int analogNoteValue = 0; //

void tempoSet()
{
   stepInMillis = 60000 / (bpm * stepLength);
}

void initSeq()
{
   tempoSet();
   initDAC();
}

// TODO: Not used anywhere, delete?
int getStep(int step)
{
   return gateSteps[step];
}

void chooseStep(int step)
{
   chosenStep = step;
}

void changeStepGate(int step)
{
   //chosenStep = step;
   gateSteps[step] ^= 1;
}

void changeStepNote()
{
   int analogNoteValueTemp = analogRead(A0);
   if (analogNoteValue != analogNoteValueTemp)
   {
      int noteValue = (analogNoteValueTemp / 85) + 36;
      noteValue = max(noteValue, 0);
      noteValue = min(noteValue, 47);
      noteSteps[chosenStep] = noteValue;
      analogNoteValue = analogNoteValueTemp;
   }
}

void runSeq()
{
   static long currentMillis;
   changeStepNote();

   // shut gate after half cycle
   if (millis() - currentMillis >= stepInMillis / 2)
   {
      digitalWrite(gatePin, LOW);
   }

   // check if enough time has passed, open gate if current step is true
   if (millis() - currentMillis >= stepInMillis)
   {
      drawGrid(gateSteps, stepsAmount, 2, 5, 5);
      drawNotes(noteSteps, stepsAmount, 2, 5, 32);

      int isGateOpen = 3;

      if (gateSteps[currentStep])
      {
         sendNote(noteSteps[currentStep]);
         digitalWrite(gatePin, HIGH);
         isGateOpen = 14;
         //   drawData(currentStep * 10 + 5, 23, 14, 1);
      }
      else
      {
      }
      drawData(currentStep * 10 + 5, 18, isGateOpen, 1);

      currentStep++;
      if (currentStep >= stepsAmount)
      {
         currentStep = 0;
      }
      drawClear();
      currentMillis = millis();
   }
};
