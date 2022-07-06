#include <common.h>
#include <FirebaseESP8266.h>
#include <FirebaseFS.h>
#include <Utils.h>

#include <ESP8266WiFi.h>

const char *ssid = "th_hung76";
const char *pass = "08102003";
IPAddress staticIP(192,168,1,22);
IPAddress gateway(192,168,1,9);
IPAddress subnet(255,255,255,0);
#define LED 2

void setup(void)
  {
    Serial.begin(115200);
    delay(500);
    Serial.println();
    pinMode(LED, OUTPUT);
  
    Serial.printf("Connection status: %d\n", WiFi.status());
    Serial.println("Mode: Outdoor");
    Serial.printf("Connecting to - %s\n", ssid);
    WiFi.begin(ssid, pass);
    Serial.printf("Connection status: %d\n", WiFi.status());
    while (WiFi.status() != WL_CONNECTED)
    {
    delay(500);
    Serial.print(".");
    }
    Serial.printf("\nConnection status: %d\n", WiFi.status());
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());
    Serial.printf("Gataway IP: %s\n", WiFi.gatewayIP().toString().c_str());
    Serial.println("Mode: indoor");
    Serial.print(WiFi.status());
    delay(5000);
}

void loop() 
{
    Serial.printf("Connection status: %d\n", WiFi.status());//Connected == 3
    if(WiFi.status()!= WL_CONNECTED)//7
    {
      WiFi.begin(ssid, pass);
      Serial.println("Mode: Outdoor");
      digitalWrite(LED,HIGH);
      while (WiFi.status() != WL_CONNECTED)
      {
      delay(500);
      Serial.print(".");
      }
    }    
   
    if(WiFi.status()== WL_CONNECTED)//3
    {
    Serial.printf("\nConnection status: %d\n", WiFi.status());   
    Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());    
    Serial.println("Mode: indoor");
    digitalWrite(LED,LOW);
    }      
    delay(2000);  
}
  
  
