#INCLUDE    <16F887.H>
#bit tmr0if = 0x0b.2
#DEVICE     ADC=10
#FUSES      NOWDT,PUT,HS,NOPROTECT,NOLVP
#USE        DELAY(CLOCK=20M)
#USE        I2C(MASTER,SLOW,SDA=PIN_B0,SCL=PIN_B1)
#DEFINE      SSDO             PIN_B4       //CHUNG TAT CA
#DEFINE      SSCK             PIN_B6        //CHUNG TAT CA
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX 
#DEFINE      RCK_8LEDQUET     PIN_B5       //B - 2 BYTE DAO
#DEFINE      G_8LEDQUET       PIN_B7       //B - 2 BYTE DAO

#DEFINE      RCK_RELAY        PIN_D4       //B - 2 BYTE K DAO
#DEFINE      G_RELAY          PIN_D5       //B - 2 BYTE K DAO



#DEFINE      MO_8_LED_QUET        G_8LEDQUET=0;  //OUTPUT_LOW(G_8LEDQUET)
#DEFINE      TAT_8_LED_QUET       G_8LEDQUET=1;  //OUTPUT_LOW(G_8LEDQUET)

unsigned int1 BAT_RELAY;
unsigned int8 bdn;
unsigned int8 gio, phut, giay,mp,s;


VOID XUAT_1BYTE(UNSIGNED INT8 BYTEXUAT)                  //XUAT 1 BYTE
{
   UNSIGNED INT8   SB,X;   
   #BIT BSERI  = X.7
   X = BYTEXUAT;
   FOR (SB=0;SB<8;SB++)
      {                                                 
         OUTPUT_BIT(SSDO,BSERI);    
         OUTPUT_LOW(SSCK); OUTPUT_HIGH(SSCK);
         X= X<<1;         
     }
}
//CHUONG TRINH CON XUAT 2 BYTE RA DK 1 LED QUET SANG
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_8LED_7DOAN_QUET_1(UNSIGNED INT MA,SO_HTHI)
{     
      XUAT_1BYTE(~MA);   XUAT_1BYTE(~SO_HTHI);
      OUTPUT_LOW(G_8LEDQUET);
      OUTPUT_HIGH(RCK_8LEDQUET); OUTPUT_LOW(RCK_8LEDQUET);      
}
//HAM 502
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH CON XUAT 2 BYTE RA TAT 8 LED QUET
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_8LED_7DOAN_QUET_TAT_LED()
{
   XUAT_8LED_7DOAN_QUET_1(0XFF,0XFF);
}
//HAM 503
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH CON HIEN THI LED THEO THU TU
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
CONST UNSIGNED CHAR TTLEDQUET[8]= {0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};
VOID XUAT_8LED_7DOAN_QUET_2(UNSIGNED INT THUTULED,SO_HTHI)
{         
      XUAT_1BYTE( (~TTLEDQUET[THUTULED]));   XUAT_1BYTE(~SO_HTHI);
      OUTPUT_LOW(G_8LEDQUET);
      OUTPUT_HIGH(RCK_8LEDQUET); OUTPUT_LOW(RCK_8LEDQUET);
      
}
//HAM 504
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH CON HIEN THI 8 SO TREN 8 LED QUET - CO KIEM TRA
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
UNSIGNED INT8 LED_7DQ[8]={0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF};
UNSIGNED INT8 TT8LED=0;
VOID HIEN_THI_8LED_7DOAN_QUET()
{     
      FOR(TT8LED=0;TT8LED<3;TT8LED++)
         IF (LED_7DQ[TT8LED]!=0XFF)
         {           
            XUAT_8LED_7DOAN_QUET_2(TT8LED, LED_7DQ[TT8LED]);
            //DELAY_US(100);  //THUC TE
            DELAY_MS(20);     //MO PHONG PROTEUS
            XUAT_8LED_7DOAN_QUET_TAT_LED();           
            }
}
//HAM 505
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//CHUONG TRINH CON HIEN THI 8 SO TREN 8 LED QUET - KHONG KIEM TRA
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID HIEN_THI_8LED_7DOAN_QUET_ALL()
{     
      FOR(TT8LED=0;TT8LED<8;TT8LED++)         
         {           
            XUAT_8LED_7DOAN_QUET_2(TT8LED, LED_7DQ[TT8LED]);
            //DELAY_US(100);  //THUC TE
            DELAY_US(500);     //MO PHONG PROTEUS
            XUAT_8LED_7DOAN_QUET_TAT_LED();           
            }
}
#int_timer1
void ngat_timer1(){   
   HIEN_THI_8LED_7DOAN_QUET_ALL();
   set_timer1(60535);
}

void dong_ho()
{
   if(bdn>=10)
   {
      bdn=0;
      giay++;
      if(giay>=59)
      {
         giay = 0;
         phut++;
         if(phut>=59)
         {
            phut=0;
            gio++;
            if(gio>=23) gio = 0;
         }
      }
   }
}
CONST UNSIGNED CHAR MA7DOAN[16]= {0XC0,0XF9,0xA4,0XB0,0X99,0X92,0X82,0XF8,
0X80,0X90,0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
void gm_ht_led_7dq()
{
    led_7dq[0]=ma7doan[giay%10];
   led_7dq[1]=ma7doan[giay/10];
   led_7dq[2]=0xbf;
   led_7dq[3]=ma7doan[phut%10];
   led_7dq[4]=ma7doan[phut/10];
   led_7dq[5]=0xbf;
   led_7dq[6]=ma7doan[gio%10];
   led_7dq[7]=ma7doan[gio/10];      
}
#DEFINE COI1(X)   
CONST UNSIGNED CHAR MAQUETKEY[4]= {0x03,0x07,0x0B,0x0F};
UNSIGNED INT8  MPT1=0,MPT2=0;  
SIGNED INT8 MAPHIM,HANG,COT;
UNSIGNED INT KEY_NHAN()
{     
      MAPHIM=HANG=0XFF;
      FOR(COT=0;COT<4;COT++)
            {   
               OUTPUT_D(MAQUETKEY[COT]);
               IF         (!INPUT(PIN_B0))      {HANG=0;   BREAK;}
               ELSE    IF (!INPUT(PIN_B1))      {HANG=1;   BREAK;}
               ELSE    IF (!INPUT(PIN_B2))      {HANG=2;   BREAK;}
               ELSE    IF (!INPUT(PIN_B3))      {HANG=3;   BREAK;}
                 DELAY_MS(30); //THEM VAO DE XU LY LOI QUA TAI CPU
            }          
         IF (HANG!=0XFF)   MAPHIM   = COT*4 + HANG;
         RETURN(MAPHIM);
}

UNSIGNED INT key_4x4_dw()
{     
      mpt1=key_nhan();      
      IF (mpt1!=0XFF)   
      {  delay_ms(1);  
         mpt1=key_nhan();
         DO{MPT2=key_nhan(); delay_ms(30);}
         WHILE (MPT2==mpt1);
      }             
      RETURN(mpt1);
}

UNSIGNED INT16 RBDC;
#BIT RELAY_0            = RBDC.0   //1=ON,0=OFF
#BIT RELAY_1            = RBDC.1   //1=ON,0=OFF
#BIT RELAY_2            = RBDC.2   //1=ON,0=OFF
#BIT RELAY_3            = RBDC.3   //1=ON,0=OFF
#BIT RELAY_4            = RBDC.4   //1=ON,0=OFF
#BIT RELAY_5            = RBDC.5   //1=ON,0=OFF
#BIT RELAY_6            = RBDC.6   //1=ON,0=OFF
#BIT RELAY_7            = RBDC.7   //1=ON,0=OFF
#BIT RELAY_8            = RBDC.8   //1=ON,0=OFF
#BIT RELAY_9            = RBDC.9   //1=ON,0=OFF
#BIT RELAY_10           = RBDC.10   //1=ON,0=OFF
#BIT RELAY_11           = RBDC.11  //1=ON,0=OFF
#BIT RELAY_12           = RBDC.12  //1=ON,0=OFF
#BIT RELAY_13           = RBDC.13   //1=ON,0=OFF
#BIT RELAY_14           = RBDC.14   //1=ON,0=OFF
#BIT BUZZER            = RBDC.15   //1=ON,0=OFF
UNSIGNED INT8 RBDC1,RBDC2;
//MODULE DIEU KHIEN RELAY
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID XUAT_BUZZER_RELAY()
{     
   

      RBDC1=RBDC; RBDC2=RBDC>>8;      
      //XUAT_1BYTE(RBDC2);      
      
      XUAT_1BYTE(RBDC1);           
      OUTPUT_LOW(G_RELAY);      
      OUTPUT_HIGH(RCK_RELAY);OUTPUT_LOW(RCK_RELAY);               
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_0_ON()
{    
      RELAY_0=1;
      XUAT_BUZZER_RELAY();         
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_1_ON()
{    
      RELAY_1=1;
      XUAT_BUZZER_RELAY();         
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_2_ON()
{    
      RELAY_2=1;
      XUAT_BUZZER_RELAY();         
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_3_ON()
{    
      RELAY_3=1;
      XUAT_BUZZER_RELAY();         
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_4_ON()
{    
      RELAY_4=1;
      XUAT_BUZZER_RELAY();         
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_5_ON()
{    
      RELAY_5=1;
      XUAT_BUZZER_RELAY();         
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_6_ON()
{    
      RELAY_6=1;
      XUAT_BUZZER_RELAY();         
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID RELAY_7_ON()
{    
      RELAY_7=1;
      XUAT_BUZZER_RELAY();         
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID BUZZER_ON()
{    
      BUZZER=1;
      XUAT_BUZZER_RELAY();         
}
//HAM 603
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID BUZZER_OFF()
{     
      BUZZER=0;
      XUAT_BUZZER_RELAY();
}
VOID RELAY_0_OFF()
{    
      RELAY_0=0;
      XUAT_BUZZER_RELAY();         
}
VOID RELAY_1_OFF()
{    
      RELAY_1=1;
      XUAT_BUZZER_RELAY();         
}
unsigned int1 ss0, ss1, ss2, ss3, ss4, ss5, ss6, ss7, ss8, ss9;
void matran_phim()                              // MA TRAN PHIM
{
mp=key_4x4_dw();
 if(mp!=0xff)
 {
   if(mp==0)
   {
      RELAY_0_ON();
      
   }
   else if(mp==1)   
   {
      ss1 = !ss1; 
      RELAY_0_OFF();
   }
   else if(mp == 2)
   {
      ss2 = !ss2;
   }
   else if(mp == 3)
   {
      ss3 = !ss3;
   }
   else if(mp == 4)
   {
      ss4 = !ss4;
   }
    else if(mp == 5)
   {
      ss5 = !ss5;
   }
   else if(mp == 6)
   {
      ss6 = !ss6;
   }
   else if(mp == 7)
   {
      ss7 = !ss7;
   }
    else if(mp == 8)
   {
      ss8 = !ss8;
   }
   else if(mp == 3)
   {
      ss9 = !ss3;
   }
   else if(mp == 9)
   {
      ss9 = !ss9;
   }
 }
}
VOID MAIN()
{      
       
      PORT_B_PULLUPS(0x0F);
      SET_TRIS_D(0X00);
      setup_timer_0(t0_internal | t0_div_256);//1s tran
      set_timer0(61);
      enable_interrupts(int_timer1);
      setup_timer_1(t1_internal|t1_div_by_8);
      enable_interrupts(int_timer1);
      enable_interrupts(global);
      set_timer1(60535);
      
   WHILE(1)
   {
      gm_ht_led_7dq();                  
      matran_phim();
      dong_ho();
      
//!      if(ss0==1)
//!      {
//!         //RELAY_0_ON();
//!      }
//!      else
//!      {
//!         ///RELAY_0_OFF();
//!      }
//!       if(ss1==1)
//!      {
//!         RELAY_1_ON();
//!      }
//!      else
//!      {
//!        // RELAY_1_OFF();
//!      }
      if (tmr0if==1)
      {
        tmr0if=0;
        bdn++;
        set_timer0(61);
      }
   }
}
