# TTGO ESP32 Display

This repo is for the development on the TTGO ESP32 Display module.

Please note that `secret.h` is not included. 

## Getting started
1. Install [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
2. Install [Button2](https://github.com/LennartHennigs/Button2)
3. Install PubSubClient in Library Manager

## Configure TFT_eSPI
1. Check your location of your installed library: `~/Documents/Arduino/libraries/TFT_eSPI/`
2. Change `User_Setup_Select.h`
   1. Comment out `#include <User_Setup.h>`
   2. Uncomment `#include <User_Setups/Setup25_TTGO_T_Display.h>`

## Configure Arduino
If you don't have ESP32 installed:
1. Under `File>Preferences>Additional Boards Manager URLs` add in `https://dl.espressif.com/dl/package_esp32_index.json`
2. Use `ESP Dev Module` as the board in the Board Manager. Other values can remain as default.

## #defines in secret.h

- SSID: ssid of the wifi access point
- PASSWORD: password of the wifi access point
- TOPIC_LAST_WILL: last will topic
- TOPIC_LIGHT: topic that this display will publish to
- BROKER_IP: last value of the IP address of the MQTT broker 192.168.1.x 


## Included Modules
1. MQTT - PubSubClient
2. WiFi - Default
3. TFT - TFT_eSPI