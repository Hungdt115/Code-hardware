#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
///////////////////////////////////////////////////
#include<SPI.h>
#include<MFRC522.h>
#define SS_PIN 10//sda
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);
//MFRC522::MIFARE_Key key;
 // Create MFRC522 instance.
///////////////////////////////////////

// Servo Config
Servo enteryservo;

// IR Config
int enteryIrPin = 7; int enteryIr = HIGH;
int slotAIrPin = 6; int slotAIr = HIGH;
int slotBIrPin = 5; int slotBIr = HIGH;  



String strID = "";
void setup() 
{
  /////////////////////////////////////
SPI.begin();     // Initiate  SPI bus
 // Initiate MFRC522
  rfid.PCD_Init();
  Serial.println("CLEARDATA");// xóa dữ liệu trên sheet đầu tiên của file excel
  Serial.println("LABEL,Date,Time,VAO/RA,RFID UID");//Nhãn (label) cho 4 cột đầu tiên trên sheet đầu tiên của file excel
  delay(1000);
  Serial.begin(9600);
  //////////////////////////////////////////


//Servo Setup
enteryservo.attach(A0); 
enteryservo.write(0);
// IR Pin Setup
pinMode(enteryIrPin, INPUT);

pinMode(slotAIrPin, INPUT);
pinMode(slotBIrPin, INPUT);
//Gate LED setup
pinMode(8, OUTPUT);//BUZZER
}

void loop() 
{  

  //////////////////////////////////////////
if ( ! rfid.PICC_IsNewCardPresent()){
    return;
  }

  // Doc the
  if ( !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
  Serial.println(strID);
//////////////////////////////////////////////

//  Serial.print("Tap card key: ");
//  Serial.println(strID);

  //////////////////////////////////////////
// Check Slot 
int slotAval = digitalRead(slotAIrPin);
int slotBval = digitalRead(slotBIrPin);

   // Check Slot A
if (slotAval == 0)
    {
    Serial.println("Slot A BUSY");
    }
else{
    Serial.println("Slot A clear");
    delay(100);
    }
    // Check Slot B
if (slotBval == 0)
    {
    Serial.println("Slot B BUSY");
    }
else{
    Serial.println("Slot B clear");
   }
//==============================================================================================================================
    //Case Park Full
if(   !(digitalRead(enteryIrPin)) && !(digitalRead(slotAIrPin)) && !(digitalRead(slotBIrPin)) )
     {
     Serial.println("Welcome, Parking Full No Available Slots");  //print slot1 and slo2 available
     digitalWrite(8, HIGH); delay(1000); digitalWrite(8, LOW);
     }
//===============================================================================================================================
   //Case Park Avalibale 1
else if(   !(digitalRead(enteryIrPin)))   
  {
         if(strID.indexOf("FB:BC:85:22")>=0) {Serial.println( (String) "DATA,DATE,TIME,VAO," + strID);delay(100);cuavao();}
   

          else  {  digitalWrite(8, HIGH); delay(1000); digitalWrite(8, LOW);}

  }
}//end loop
//================================================================================================================================     
       
void cuavao()
{
Serial.println("Welcome, Parking Available Slots");  //print slot1 and slo2 available
enteryservo.write(90); 
delay(4000);
enteryservo.write(0);
}
