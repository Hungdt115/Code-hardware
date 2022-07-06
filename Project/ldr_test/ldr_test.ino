#include <LiquidCrystal.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS.h>
#include <DS3231.h>
DS3231 rtc(SDA, SCL);
Time t;
TinyGPS gps;
int ldr = A0;//chân analog kết nối LDR
int RSS1 = A1; // cuong do tin hieu nhan duoc cua cot song 1
int RSS2 = A2; // cuong do tin hieu nhan duoc cua cot song 2
int RSS3 = A3; // cuong do tin hieu nhan duoc cua cot song 3

void setup()
{
  Serial.begin(9600);
  
  rtc.begin();
  rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(20, 10, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(14, 12, 2021);
  
  pinMode(ldr, INPUT);
  pinMode(RSS1, INPUT);
  pinMode(RSS2, INPUT);
  pinMode(RSS3, INPUT);
}

void loop()
{
  bool availabled = false;
  bool newData = false;
  bool kq_ldr, kq_rss;
  unsigned long chars;
  unsigned short sentences, failed;
  float cl;
  unsigned short  RSSValue1, RSSValue_temp1;
  unsigned short  RSSValue2, RSSValue_temp2;
  unsigned short  RSSValue3, RSSValue_temp3;
  signed int i, different1,different2,different3;
  float cc,cc1,cc2,sl_indoor, sl_outdoor;
  
  
  
  float ldrValue = 5 * analogRead(ldr)-random(1,50);
  Serial.print("LDR:  ");Serial.println(ldrValue);

  t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(" Gio, ");
  Serial.print(t.min);
  Serial.print(" Phut, ");
  Serial.print(t.sec);
  Serial.print(" Giay ");
  Serial.println(" ");

  //-----------------------------------------------------------------
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    if (Serial.available() > 0)
    {
      char c = Serial.read();
      if (gps.encode(c))  availabled = true;
    }
  }
//ldr resuls
       
        if (ldrValue > 2000)
        {
          //Serial.println("Mode outdoor GPS app ON");
          //Serial.print  ("Light values is:  "); Serial.println(ldrValue);
          //if (availabled == 1) newData = true;
          cl=1;
          kq_ldr =0;//do tin cay cua ldr la do tin cay ngoai troi
//          Serial.print("Do tin cay ldr: ");Serial.println(cl);
        }
        else
        {
          if(t.hour >=8 && t.hour<=17)
          {
            //Serial.println("Indoor");
            //Serial.print  ("Light values is :  "); Serial.println(ldrValue);
            cl=1;
            kq_ldr =1;//do tin cay cua ldr la do tin cay trong nha
            //newData = false;
//            Serial.print("Do tin cay ldr: ");Serial.println(cl);
          }
          else
          {
            if(ldrValue > 50 )
            {
              //Serial.println("Indoor");
              cl = (2000-ldrValue)/2000;
              kq_ldr =1;//do tin cay cua ldr la do tin cay trong nha
//              Serial.print("Do tin cay ldr: ");Serial.println(cl,5);
             }
             else
              {
                //Serial.println("Outdoor");
                cl = (50 - ldrValue)/50;
                kq_ldr =0;//do tin cay cua ldr la do tin cay ngoai troi
//                Serial.print("Do tin cay ldr: ");Serial.println(cl);
            }
          }
        }
               //RSS simulation
  if(t.sec%10==0)
  {
    {int RSSValue1 = analogRead(RSS1);
    if (RSSValue_temp1 != RSSValue1)
      {different1 = RSSValue_temp1 - RSSValue1;}
    RSSValue_temp1 = RSSValue1;
    if(different1>0)
      {
        kq_rss = 0;
        cc=0.8;
      }
     else
     {
        kq_rss = 1;
        cc=0.8;
     }
    }
  }
  
//  if(cc1>cc2) {cc = cc1; kq_rss = 1;}//do tin cay cua RSS la do tin cay trong nha
//  else  {cc = cc2; kq_rss =0;}//o tin cay cua RSS la do tin cay ngoai troi
//----------------------------------------------------    
  if(availabled==true)
  {
    if(cl>cc)
    {
      newData = kq_ldr;
     
      }
    else 
    {
      newData = kq_rss;
      }
    }
        
        if (kq_ldr==0)
        {
           float flat, flon;
           unsigned long age;
           gps.f_get_position(&flat, &flon, &age);
           Serial.print("Do tin cay ldr: ");Serial.println(cl,5);
          
           Serial.println("Mode: Outdoor");
           Serial.println("GPS is ON");
           Serial.print("LAT:"); Serial.println(flat, 5);
           Serial.print("LON:"); Serial.println(flon, 5);
        }
        else 
        {
        Serial.print("Do tin cay ldr: ");Serial.println(cl,5);
        
        Serial.println("Mode: Indoor");
        Serial.println("GPS is OFF");
        }
        gps.stats(&chars, &sentences, &failed);
        Serial.println();
}
