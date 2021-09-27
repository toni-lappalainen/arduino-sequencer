#include <Arduino.h>

void log(String text, char value)
{
    Serial.print(text);
    Serial.print(": ");
    Serial.println(value);
}

void logInt(String text, int value)
{
    Serial.print(text);
    Serial.print(": ");
    Serial.println(value);
}