#include "DHT.h"
#define DHTPIN 11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <SoftwareSerial.h>
#define RX 2
#define TX 3
SoftwareSerial mySerial(RX, TX);
#define bt1 16
#define bt2 9
#define bt3 10
#define bt4

#define dv1 5
#define dv2 6
#define dv3 7
#define Buzzer 4

bool st_1, st_2, st_3, st_4;
bool ena_1, ena_2, ena_3, ena_4;
String myString, rxdata;
float h, t;
long t1;
long sec;
long mts, mts_now;

void setup() {
  //Serial Begin
  Serial.begin(115200);
  mySerial.begin(115200);

  //seting digital pin
  pinMode(bt1, INPUT_PULLUP);//input pin button
  pinMode(bt2, INPUT_PULLUP);
  pinMode(bt3, INPUT_PULLUP);

  pinMode(dv1, OUTPUT);
  pinMode(dv2, OUTPUT);
  pinMode(dv3, OUTPUT);

  //dht.begin();
  dht.begin();
}

void loop() {
  //--------------Sending data use to uart------------------

  read_Sensor();
  send_uart();
  reci_uart();
  read_button1();
  read_button2();
  read_button3();



  //Output value of state
  digitalWrite(dv1, st_1);
  digitalWrite(dv2, st_2);
  digitalWrite(dv3, st_3);

}
void read_Sensor() {
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
}

void read_button1() {
  int ena_1 = digitalRead(bt1);
  if (ena_1 == 0 )
  {
    st_1 = !st_1; // toggle station
    if (st_1 == 1)
    {
      mySerial.println("a");
      Serial.println("a");
    }
    else
    {
      mySerial.println("b");
      Serial.println("b");
    }
    while (digitalRead(bt1) == 0) { }//wait for button1 open
  }
}
void read_button2() {
  int ena_2 = digitalRead(bt2);
  if (ena_2 == 0 )
  {
    st_2 = !st_2; // toggle station
    if (st_2 == 1)
    {
      mySerial.println("c");
      Serial.println("c");
    }
    else
    {
      mySerial.println("d");
      Serial.println("d");
    }
    while (digitalRead(bt2) == 0) { }//wait for button1 open
  }
}

void read_button3() {
  int ena_3 = digitalRead(bt3);
  if (ena_3 == 0 )
  {
    st_3 = !st_3; // toggle station
    if (st_3 == 1)
    {
      mySerial.println("e");
      Serial.println("e");
    }
    else
      mySerial.println("f");
    while (digitalRead(bt3) == 0) { }
  }
}

void send_uart() {
  if (millis() - t1 > 1000)  {
    t1 = millis();
    sec++;
//    Serial.println(sec);
    if (sec > 59) {
      mts++;
      sec = 0;
//      Serial.print("phut: "); Serial.println(mts);
      if (mts  > 2) {
        String send_data = "*" + String(t) + "/" + String(h);
        mySerial.println(send_data);
        Serial.println(send_data);
        mts = 0;
      }
    }
  }
}
void reci_uart() {
  if (mySerial.available() > 0)
  {
    char c = mySerial.read();
    rxdata = c;
    Serial.println(rxdata);
    if (rxdata == "\n") {
      rxdata = "";
    }
    else {
      if (rxdata == "a")
      {
        st_1 = 1;
      }
      if (rxdata == "b")
      {
        st_1 = 0;
      }
      if (rxdata == "c")
      {
        st_2 = 1;
      }
      if (rxdata == "d")
      {
        st_2 = 0;
      }
      if (rxdata == "t")
      {
        st_3 = 1;
      }
      if (rxdata == "f")
      {
        st_3 = 0;
      }
      if (rxdata == "g")
      {
        st_3 = 1;
        st_2 = 1;
        st_1 = 1;
      }
      if (rxdata == "h")
      {
        st_3 = 0;
        st_2 = 0;
        st_1 = 0;
      }
    }
  }
}
