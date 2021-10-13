#include <PubSubClient.h>
#include <WiFi.h>

 // Wifi 
const char* ssid = "WIFI SSID";
const char* pass = "WIFI PASSWORD";

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
}

void loop()
{
	
}
