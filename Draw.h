#ifndef DRAW_H
#define DRAW_H

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

void initDraw();
void draw();
void drawData(int y, int x, int value, int size);
void drawText();
void drawClear();
void drawGrid(int stepArray[], int w, int h, int startX, int startY);
void drawNotes(int noteArray[], int w, int h, int startX, int startY);

#endif