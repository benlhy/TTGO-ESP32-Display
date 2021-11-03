#include "mqtt.h"

IPAddress broker(192, 168, 1, BROKER_IP); // IP address of your MQTT broker eg. 192.168.1.50
WiFiClient wclient;
PubSubClient client(wclient); // Setup MQTT client

void mqtt_init()
{
    client.setServer(broker, 1883);
    client.connect("TTGO-Display", "", "", TOPIC_LAST_WILL, 2, false, "Offline");
    client.publish(TOPIC_LAST_WILL, "Online");
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawString("MQTT Broker:", 0, 20, 2);
    tft.drawString(broker.toString(), 100, 20, 2);
}

void process_mqtt()
{
    client.loop();
    client.publish(TOPIC_LIGHT, "on");
}