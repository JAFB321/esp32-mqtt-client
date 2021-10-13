#include <PubSubClient.h>
#include <WiFi.h>

 // Wifi 
const char* ssid = "WIFI SSID";
const char* pass = "WIFI PASSWORD";

// MQTT Broker 
const char* mqtt_server = "192.168.1.50";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
	Serial.begin(9600);

    WiFi.begin(ssid, pass);
    
    Serial.println("Connecting Wifi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("1.- Connected");
    Serial.println(WiFi.localIP());
    Serial.println();

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(on_message);
}

void on_message(char* topic, byte* msg, unsigned int length){
    Serial.println("A message has been received");
 }

void loop()
{
	
}
