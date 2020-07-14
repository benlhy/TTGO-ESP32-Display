#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>

#include "secret.h"
#include "display.h"

// Connect to WiFi network
void setup_wifi()
{
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawString("Connecting: ", 0, 10, 2);
    Serial.print("\nConnecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, PASSWORD); // Connect to network
    int counter = 0;
    while (WiFi.status() != WL_CONNECTED)
    { // Wait for connection
        delay(500);
        Serial.print(".");
        tft.drawString(".", counter, 30, 2);
        counter++;
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    tft.fillScreen(TFT_BLACK);

    tft.drawString("IP address:", 0, 120, 2);
    tft.drawString(WiFi.localIP().toString(), 80, 120, 2);
}

#endif