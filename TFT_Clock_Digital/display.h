#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

extern TFT_eSPI tft;

void display_init();

#endif