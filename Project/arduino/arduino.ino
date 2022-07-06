#include <SoftwareSerial.h>


#define bt1 4
#define bt2 5
#define bt3 6
#define bt4 7

#define dv1 8
#define dv2 9
#define dv3 10
#define dv4 11



int RID = 15;
unsigned int t;
bool st_1, st_2, st_3, st_4;
SoftwareSerial mySerial(2, 3); // RX, TX


void setup() {
  //Serial Begin at 9600 Baud
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

  //seting digital pin
  pinMode(bt1, INPUT_PULLUP);//input pin button
  pinMode(bt2, INPUT_PULLUP);
  pinMode(bt3, INPUT_PULLUP);
  pinMode(bt4, INPUT_PULLUP);

  pinMode(13, OUTPUT);



}

void loop() {
  
  // Sending data use to uart
  if (millis() - t > 100)
  {  
    if (mySerial.available())
      Serial.write(mySerial.read());
    if (Serial.available())
      mySerial.write(RID);
  }t = millis();

  
  //Read value of buton 
  int sensor1 = digitalRead(bt1);
  int sensor2 = digitalRead(bt2);
  int sensor3 = digitalRead(bt3);
  int sensor4 = digitalRead(bt4);
  

  //Process signal for button
  if (sensor1 == 0 )
  {     
    st_1 = !st_1; // toggle station
    while (digitalRead(bt1) == 0) { }//wait for button1 open
  }
  if (sensor2 == 0 )
  {  
    
    st_2 = !st_2; // toggle station
    while (digitalRead(bt2) == 0) { }
  }
  if (sensor3 == 0 )
  {  
    
    st_3 = !st_3; // toggle station
    while (digitalRead(bt3) == 0) { }
  }
  if (sensor4 == 0 )
  {  
    
    st_4 = !st_4; // toggle station
    while (digitalRead(bt4) == 0) { }
  }
  

  //Output value of state
  digitalWrite(dv1, st_1);
  digitalWrite(dv2, st_2);
  digitalWrite(dv3, st_3);
  digitalWrite(dv4, st_4);
  Serial.println();
  Serial.println(st_1);  

}
