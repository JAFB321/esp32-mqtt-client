#include <PubSubClient.h>
#include <WiFi.h>

 // Wifi 
const char* ssid = "WIFI SSID";
const char* pass = "WIFI PASSWORD";

// MQTT Broker 
const char* mqtt_server = "192.168.1.50";
const int mqtt_port = 1883;
const char* subscriber_topic = "test/server_data";
const char* publisher_topic = "test/sensor_data";
long last_msg = 0;

const char* device_id = "esp32-client";

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

void connectServer(){

    Serial.println("Connecting to MQTT server...");
    while(!client.connected()){

        if(client.connect(device_id)){
            // client.subscribe(subscriber_topic);
        }

        delay(500);
        Serial.println(client.state());
        Serial.print("....");
    }
    Serial.println("Connected to MQTT server!");
}

void on_message(char* topic, byte* msg, unsigned int length){
    Serial.println("A message has been received");
 }

void loop()
{
    if (!client.connected()) {
        connectServer();
    }
    client.loop();

    long now = millis();
    if(now - last_msg > 2000){
        last_msg = now;
        
        // Send data to MQTT server
        const int sensor_value = 1;
        const int battery_level = 1;

        String  json = "{";
                json += "\"sensor_id\":\""+(String(device_id))+"\",";
                json += "\"sensor_value\":"+(String(sensor_value))+String(",");
                json += "\"battery_level\":"+(String(battery_level))+String(",");
                json += "}";
        
        char data[json.length()+1];
        json.toCharArray(data, json.length()+1);

        if(client.publish(publisher_topic, data)){
            Serial.println("Message has been sent to MQTT server");
            Serial.println("data:");
            Serial.println(data);
            Serial.println("json:");
            Serial.println(json);
        }
        
    }
}
