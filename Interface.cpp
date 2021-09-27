#include <Arduino.h>
#include <Keypad.h>
#include "Sequencer.h"
#include "logging.h"

char lastKey;
void keypadEventTest(KeypadEvent key);

//=============== keypad setup
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

//define the cymbols on the buttons of the keypads
unsigned char keys[ROWS][COLS] = {
    {'0', 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11},
    {12, 13, 14, 15}};

byte rowPins[ROWS] = {8, 7, 6, 5};    //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 10, 11, 12}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

enum controlStates
{
    PLAY,
    GATES,
    NOTES,
    EDIT
};

enum controlStates controlState = GATES;

void initInterface()
{
    customKeypad.addEventListener(keypadEventTest);
    customKeypad.setHoldTime(500);
}

void checkKeys()
{
    customKeypad.getKey();
}

void getKeypress()
{
    //char customKey = customKeypad.getKey();
    logInt("test", lastKey);
    if (lastKey)
    {
        int key = (int)lastKey;
        if (key == 48)
            key = 0;
        //  logInt("keyChar", customKey);
        //  logInt("key", key);
        if (controlState == GATES)
            changeStepGate(key);
        if (controlState == NOTES)
            chooseStep(key);
    }
}

void getKeyHold()
{
    //char customKey = customKeypad.getKey();
    logInt("testHold", lastKey);
    if (lastKey)
    {
        int key = (int)lastKey;
        if (key == 48)
            key = 0;
        switch (key)
        {
        case 12:
            controlState = GATES;
            break;
        case 13:
            controlState = NOTES;
            break;
        case 14:
            controlState = EDIT;
            break;
        case 15:
            controlState = PLAY;
            break;
        }
    }
}

int keyHold = 0;

void keypadEventTest(KeypadEvent key)
{
    logInt("event", 1);
    lastKey = key;
    switch (customKeypad.getState())
    {
    case PRESSED:
        keyHold = 0;
        break;

    case RELEASED:
        if (keyHold == 0)
            getKeypress();
        break;

    case HOLD:
        keyHold = 1;
        getKeyHold();
        break;
    }
}
