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
//////////////////////////////////////////////////

//I2C pins declaration for LCD
LiquidCrystal_I2C lcd(0x27,16,2);
Servo enteryservo; //Mo cua

//Dinh nghia chan
int enteryIrPin = 7;  int enteryIr = HIGH;
int slotAIrPin = 6;   int slotAIr = HIGH;
int slotBIrPin = 5;   int slotBIr = HIGH;  
//---------------------------------------------------
void setup() {
 pinMode(enteryIrPin, INPUT);// IR Pin Setup 

 SPI.begin();     // Initiate  SPI bus
 // Initiate MFRC522
  rfid.PCD_Init();
  Serial.println("CLEARDATA");// xóa dữ liệu trên sheet đầu tiên của file excel
  Serial.println("LABEL,Date,Time,VAO/RA,RFID UID");//Nhãn (label) cho 4 cột đầu tiên trên sheet đầu tiên của file excel
  delay(1000);
  Serial.begin(9600);

  enteryservo.attach(A0);
  pinMode(8, OUTPUT);//BUZZER
  pinMode(slotAIrPin, INPUT);
  pinMode(slotBIrPin, INPUT);

  
}

void loop() {
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
//////////////////////////////////////////////
// Check Slot 
  int slotAval = digitalRead(slotAIrPin);
  int slotBval = digitalRead(slotBIrPin);
  
  if (slotAval == 0)
  {
    Serial.println("Slot A BUSY");
  }
  else{
    Serial.println("Slot A clear");
  }
  //slotb
   if (slotBval == 0)
  {
    Serial.println("Slot B BUSY");
  }
  else{
    Serial.println("Slot B clear");
  }

   
  
 //Full slot
 if(   !(digitalRead(enteryIrPin)) && !(digitalRead(slotAIrPin)) && !(digitalRead(slotBIrPin)))  
     {
      digitalWrite(8, HIGH); delay(1500); digitalWrite(8, LOW);
      Serial.println("Welcome, Parking Full No Available Slots");  
      delay(100);
     }
  else
  { 
    
    if(strID.indexOf("9B:EA:80:22")>=0) {Serial.println( (String) "DATA,DATE,TIME,VAO," + strID);cuavao();}
  }

}
///////////////////////////////////////End loop
 void cuavao()
  {
    Serial.println("Welcome, Parking Available Slots");  //print slot1 and slo2 available
    enteryservo.write(90); 
    delay(4000);
    enteryservo.write(0);
    
  }
