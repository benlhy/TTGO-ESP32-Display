#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <WiFi.h>
#include "secret.h"

// process_mqtt

IPAddress broker(192, 168, 1, BROKER_IP); // IP address of your MQTT broker eg. 192.168.1.50
WiFiClient wclient;
PubSubClient client(wclient); // Setup MQTT client

void setup_mqtt()
{
    client.setServer(broker, 1883);
    client.connect("TTGO-Display", "", "", TOPIC_LAST_WILL, 2, false, "Offline");
    client.publish(TOPIC_LAST_WILL, "Online");
}

void process_mqtt()
{
    client.loop();
    client.publish(TOPIC_LIGHT, "on");
}

#endif