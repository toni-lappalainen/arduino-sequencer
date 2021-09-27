#include "Draw.h"
#include "Notes.h"

// Display pins
int DC = 2;
int DIN = 3;
int CLK = 4;
int RST = 15;
int CE = 16;

int width = 84;
int height = 48;

// Declare LCD object for software SPI
// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);

int rotatetext = 1;

void initDraw()
{
    //Initialize Display
    display.begin();

    display.setContrast(64);

    display.clearDisplay();

    display.setCursor(5, 10);
    display.setTextSize(2);
    display.setTextColor(BLACK);

    display.println("MYRRYS");
    display.setCursor(15, 30);
    delay(200);
    display.println("AUDIO");
    display.display();

    delay(1000);
    display.clearDisplay();
    display.setTextSize(1);
}

void drawData(int x, int y, int value = 1, int size = 1)
{
    //display.clearDisplay();
    //display.setTextColor(BLACK);
    display.setTextSize(size);
    if (x >= width)
    {
        x = x - width + 5;
        y = y + size * 5;
    }
    if (y >= height)
    {
        y = height - y;
        x = x + size * 5;
    }
    display.setCursor(x, y);
    display.write((char)value);
}

void drawClear()
{
    display.display();
    display.clearDisplay();
}

void drawText()
{
}

void drawNotes(int noteArray[], int w, int h, int startX = 0, int startY = 0)
{
    int octave = 0;
    char note = 'c';
    int x;
    for (int i = 0; i < w; i++)
    {
        if (i >= 8)
        {
            x = (i - 8) * 10 + startX;
            display.setCursor(x, startY + 7);
        }
        else
        {
            x = i * 10 + startX;
            display.setCursor(x, startY);
        }
        octave = noteArray[i] / 12;
        //Serial.print("1: ");
        //Serial.println(noteArray[i] - 36);
        //Serial.print("2: ");
        //Serial.println((char)dac_notes[noteArray[i] - 36]);

        note = (char)dac_notes[noteArray[i] - 36];
        display.print(note);
    }
    //display.display();
}

void drawGrid(int stepArray[], int w, int h, int startX = 0, int startY = 0)
{
    //display.clearDisplay();
    int x;
    for (int i = 0; i < w; i++)
    {
        if (i >= 8)
        {
            x = (i - 8) * 10 + startX;
            display.setCursor(x, startY + 7);
        }
        else
        {
            x = i * 10 + startX;
            display.setCursor(x, startY);
        }
        if (stepArray[i] == 1)
        {
            display.write(14);
        }
        else
        {
            display.write(3);
        }
    }
    //display.display();
}
