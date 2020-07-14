#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>
#include <WiFiUdp.h>

#include "secret.h"
#include "display.h"

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
IPAddress timeServer(129, 6, 15, 28); // time.nist.gov
unsigned int localPort = 2390;        // local port to listen for UDP packets
const int NTP_PACKET_SIZE = 48;       // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[NTP_PACKET_SIZE];   //buffer to hold incoming and outgoing packets

uint8_t local_h, local_m, local_s;
unsigned long ntp_got_time; // this is the local millis() that we got the time.

void setup_wifi();
void set_ntp();
void deep_sleep();

unsigned long sendNTPpacket(IPAddress &address);

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
        if (counter == 20)
        {
            WiFi.disconnect(true);
            WiFi.mode(WIFI_OFF);

            esp_sleep_enable_timer_wakeup(5 * 1000000ULL);
            esp_deep_sleep_start();
                }
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    tft.fillScreen(TFT_BLACK);

    tft.drawString("IP address:", 0, 5, 2);
    tft.drawString(WiFi.localIP().toString(), 80, 5, 2);
}

void set_ntp(uint8_t local_time)
{
    Udp.begin(localPort);
    sendNTPpacket(timeServer);
    int count = 0;
    tft.drawString("NTP: ", 0, 35, 2);
    while (count < 10)
    {
        count++;
        tft.drawString(". ", 40 + count * 3, 35, 2);
        if (Udp.parsePacket())
        {
            ntp_got_time = millis();
            Serial.println("packet received");
            // We've received a packet, read the data from it
            Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

            //the timestamp starts at byte 40 of the received packet and is four bytes,
            // or two words, long. First, esxtract the two words:

            unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
            unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
            // combine the four bytes (two words) into a long integer
            // this is NTP time (seconds since Jan 1 1900):
            unsigned long secsSince1900 = highWord << 16 | lowWord;
            Serial.print("Seconds since Jan 1 1900 = ");
            Serial.println(secsSince1900);

            // now convert NTP time into everyday time:
            Serial.print("Unix time = ");
            // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
            const unsigned long seventyYears = 2208988800UL;
            // subtract seventy years:
            unsigned long epoch = secsSince1900 - seventyYears;

            // print Unix time:
            Serial.println(epoch);

            // print the hour, minute and second:
            Serial.print("The UTC time is "); // UTC is the time at Greenwich Meridian (GMT)

            Serial.print((epoch % 86400L) / 3600); // print the hour (86400 equals secs per day)
            Serial.print(':');
            if (((epoch % 3600) / 60) < 10)
            {
                // In the first 10 minutes of each hour, we'll want a leading '0'
                Serial.print('0');
            }
            Serial.print((epoch % 3600) / 60); // print the minute (3600 equals secs per minute)
            Serial.print(':');
            if ((epoch % 60) < 10)
            {
                // In the first 10 seconds of each minute, we'll want a leading '0'
                Serial.print('0');
            }
            Serial.println(epoch % 60);              // print the second
            tft.drawRect(0, 30, 150, 10, TFT_BLACK); // clear line.
            local_h = (epoch % 86400L) / 3600 + local_time;
            local_m = (epoch % 3600) / 60;
            local_s = epoch % 60;

            char buf[128];
            snprintf(buf, sizeof(buf), "NTP: %d:%d:%d", hh, mm, ss);
            tft.drawString(buf, 0, 35, 2);
            break;
        }
        delay(1000);
    }
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress &address)
{
    //Serial.println("1");
    // set all bytes in the buffer to 0
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    //Serial.println("2");
    packetBuffer[0] = 0b11100011; // LI, Version, Mode
    packetBuffer[1] = 0;          // Stratum, or type of clock
    packetBuffer[2] = 6;          // Polling Interval
    packetBuffer[3] = 0xEC;       // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;

    //Serial.println("3");

    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    Udp.beginPacket(address, 123); //NTP requests are to port 123
    //Serial.println("4");
    Udp.write(packetBuffer, NTP_PACKET_SIZE);
    //Serial.println("5");
    Udp.endPacket();
    //Serial.println("6");
}
#endif