 #include<ESP8266WiFi.h>

void setup() 
{  
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("This is my address: ");
  Serial.println(WiFi.macAddress());
}

void loop() 
{

}
