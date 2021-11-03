#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <WiFi.h>

#include "display.h"
#include "secret.h"

// process_mqtt

void mqtt_init();
void process_mqtt();
void cmnd_callback(char *topic, byte *payload, unsigned int length);

#endif
