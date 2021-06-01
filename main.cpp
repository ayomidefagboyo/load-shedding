//LOAD SHEDDING IN A COMMERCIAL BUILDING
//FAGBOYO AYOMIDE
//KEYPAD CONTROL: https://github.com/bitwiseAr/Curso-Arduino-desde-cero/blob/master/Capitulo9/Capitulo9-Programa1.txt
//LCD CONTROL: https://www.makerguides.com/character-i2c-lcd-arduino-tutorial/ 
//RELAY MODULE: http://arduinolearning.com/code/5-volt-4-channel-arduino-relay-module-example.php#codesyntax_1
/*
Firmware functions:
  SWITCHES THE FOUR DIFFERENT LOADS BASED ON SET TIMES IN THE DAY AND PROGRAMMABLE USING KEYPAD
*/

//LIBRARIES TO USE
#include "Wire.h"
#include "LiquidCrystal.h"
#include "math.h"
int RelayLoad1 = 4;  // Digital Pin used to control the relay
int RelayLoad2 = 2;  
int RelayLoad3 = 7;  
int RelayLoad4 = 8;  
 
void setup()  
{   
  Serial.begin(9600);
  pinMode(RelayLoad1, OUTPUT);
  pinMode(RelayLoad2, OUTPUT);
  pinMode(RelayLoad3, OUTPUT);
  pinMode(RelayLoad4, OUTPUT);

   //initializam DS_1307
   Wire.begin();
   lcd.begin(16,2);
    lcd.setCursor(0,0);
  lcd.print("please wait...");
   lcd.setCursor(0,2);
  lcd.print("system loading");
  delay(3000);
  lcd.clear();
  lcd.print("TIME MANAGEMENT");
  lcd.setCursor(0,1);
  lcd.print("****************");
  delay(2000);
  lcd.clear();
  lcd.print("   AUTOMATIC   ");
  lcd.setCursor(0,2);
  lcd.print("LOAD SHEDDING");
  delay(3000);
   Serial.begin(9600);
   struct ds1307_time time;
   time.second = 15;
   time.minute = 55;
   time.hour = 11;
   time.dayOfWeek = 5;
   time.dayOfMonth = 14;
   time.month = 3;
   time.year = 14;
}
/*  THIS  SECTION  IMPLEMENTS  THE  POWER  DISTRIBUTION  OF 
TABLES 1 AND 2 BASED ON THE DIFFERENT TIME ZONES */ 
 
//TME ZONE 1: 00:00AM TO 5:59AM 
void loop() { 
digitalWrite(4,LOW); 
digitalWrite(2,LOW); 
digitalWrite(7,HIGH); 
digitalWrite(8,LOW); 
delay(300000); 
 
//TIME 2: 6:00AM TO 10:59AM 
digitalWrite(4,HIGH); 
digitalWrite(2,OFF); 
digitalWrite(7,HIGH); 
digitalWrite(8,HIGH); 


delay(3000); 
 
//TIME 3: 11:00AM TO 17:59PM 
digitalWrite(4,HIGH); 
digitalWrite(2,HIGH); 
digitalWrite(7,HIGH); 
digitalWrite(8,HIGH); 
delay(240000); 
 
//TIME  4: 18:00 TO 18:59
digitalWrite(4,HIGH); 
digitalWrite(2,LOW); 
digitalWrite(7,HIGH); 
digitalWrite(8,HIGH); 
delay(60000); 
//TIME  5: 19:00 TO 00:00
digitalWrite(4,LOW); 
digitalWrite(2,LOW); 
digitalWrite(7,HIGH); 
digitalWrite(8,LOW); 
delay(300000); 
} 

FOR THE DISPLAY AND KEYPAD
void showSubMenu(){
   if(menuPos==1 || menuPos==2){ //data sau ora
      switch(subMenuPos){
        case 1://zile
          cursorPos = 1;
          break;
        case 2:
          cursorPos = 4;
          break;
        case 3:
          cursorPos = 7;
          break;
        case 4:
          if(menuPos==1){
            cursorPos=12;
            break;
          }
        default:
          subMenuPos = 0;
          cursorPos = -1;
          break;
      }
   }else if((menuPos+1)%4==0){
      switch(subMenuPos){
        case 1: //ora
          cursorPos = 1;
          break;
        case 2: //minutul
          cursorPos = 4;
          break;
        default:
          subMenuPos = 0;
          cursorPos = -1;
          break;
      }
   }else if((menuPos)%4==0){ 
     if(subMenuPos>0 && subMenuPos<8){
        cursorPos = subMenuPos*2-1;
     }else{
        subMenuPos = 0;
        cursorPos = -1;
     }
   }else if((menuPos-1)%4==0){ 
     if(subMenuPos==1){
        cursorPos = 0;
     }else if(subMenuPos==2){
        cursorPos=4;
     }else{
        subMenuPos=0;
        cursorPos = -1;
     }
   }else if((menuPos-2)%4==0){ 
     if(subMenuPos>0 && subMenuPos<8){
        cursorPos = subMenuPos*2-1;
     }else{
        subMenuPos = 0;
        cursorPos = -1;
     }
   }
}    
