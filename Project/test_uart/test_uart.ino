#include <SoftwareSerial.h>
SoftwareSerial mySerial(D5, D6); // RX, TX

byte c;
void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
}

void loop() {
  //Write '123' to Serial
  if (Serial.available())
  {
    c = Serial.read();
    Serial.println(c);
  }
  Serial.println(c);
}
