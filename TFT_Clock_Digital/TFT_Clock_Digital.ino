/*
 An example digital clock using a TFT LCD screen to show the time.
 Demonstrates use of the font printing routines. (Time updates but date does not.)
 
 For a more accurate clock, it would be better to use the RTClib library.
 But this is just a demo. 
 
 This examples uses the hardware SPI only. Non-hardware SPI
 is just too slow (~8 times slower!)
 
 Based on clock sketch by Gilchrist 6/2/2014 1.0
 Updated by Bodmer
A few colour codes:
 
code	color
0x0000	Black
0xFFFF	White
0xBDF7	Light Gray
0x7BEF	Dark Gray
0xF800	Red
0xFFE0	Yellow
0xFBE0	Orange
0x79E0	Brown
0x7E0	Green
0x7FF	Cyan
0x1F	Blue
0xF81F	Pink

 */

#include "wifi.h"
#include "mqtt.h"
#include "display.h"

void setup(void)
{
  setup_display();
  setup_wifi();
  setup_mqtt();
}

void loop()
{
}
