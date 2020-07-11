# TTGO ESP32 Display

This repo is for the development on the TTGO ESP32 Display module.

## Getting started
1. Install [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
2. Install [Button2](https://github.com/LennartHennigs/Button2)

## Configure TFT_eSPI
1. Check your location of your installed library: `~/Documents/Arduino/libraries/TFT_eSPI/`
2. Change `User_Setup_Select.h`
   1. Comment out `#include <User_Setup.h>`
   2. Uncomment `#include <User_Setups/Setup25_TTGO_T_Display.h>`

## Configure Arduino
If you don't have ESP32 installed:
1. Under `File>Preferences>Additional Boards Manager URLs` add in `https://dl.espressif.com/dl/package_esp32_index.json`
2. Use `ESP Dev Module` as the board.

## Included Modules
1. MQTT - PubSubClient
2. WiFi
3. TFT