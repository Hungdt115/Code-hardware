#include<SPI.h>
#define inputbutton 2
#define outputLED   4
volatile  boolean received;
volatile  byte Slavereceived, Slavesend;
int buttonvalue;
int x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
   pinMode(inputbutton,INPUT);
   pinMode(outputLED,OUTPUT);
   pinMode(MISO,OUTPUT);

   SPCR |= _BV(SPE);
   received = false;
   SPI.attachInterrupt(); 
}
ISR (SPI_STC_vect){
  Slavereceived = SPDR;
  received = true;
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(received){  
      if(Slavereceived==1)
        digitalWrite(outputLED,HIGH);
      else
        digitalWrite(outputLED, LOW);
        buttonvalue =  digitalRead(inputbutton);
        if(buttonvalue==HIGH)
        x=1;
        else x=0;
        Slavesend = x;
        SPDR = Slavesend;
        delay(1000);
      }
    } 
