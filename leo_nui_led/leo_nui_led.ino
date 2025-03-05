/*
- Trẻ đập vào nút bấm, đền cảnh báo sáng và phát 1 đoạn nhạc khoảng 5s 
- Thiết bị: 1 Nút bấm tự nhả, 1 Đèn cảnh báo, 1 Loa, 1 mạch phát âm thanh DFPLAYER
*/
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/8, /*tx =*/9);

DFRobotDFPlayerMini myDFPlayer;
#define rl1 A0 
#define BT1 3
#define STR 2
#define nhac A1
unsigned long time1 ;
unsigned long time2 ;
int thoigian = 0;
bool tt = false;
int strobePin = 4; // Pin kết nối với Data (pin 2) của 4094
int dataPin = 5;   // Pin kết nối với Clock (pin 3) của 4094
int clockPin = 6;  // Pin kết nối với Strobe (pin 1) của 4094

// Mã 7 đoạn cho các ký tự số từ 0 đến 9
byte segChar[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6};
byte segChardot[] = {0xfd, 0x61, 0xdb, 0xf3, 0x67, 0xb7, 0xbf, 0xe1, 0xff, 0xf7};
void setup()
{
  softSerial.begin(9600);
  pinMode(A0,OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(strobePin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(nhac, OUTPUT);
  Serial.begin(9600); 
  digitalWrite(nhac,HIGH);
  //if (!myDFPlayer.begin(softSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
   /* Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(30);  //Set volume value (0~30).
  */
  hienthit(0);

}
int old, old1;
void loop()
{ 
  if(digitalRead(STR) == 0){
    tt = true;
    time2 = millis();
    time1 = millis();
    thoigian = 0;
    hienthit(thoigian);
  }
  if(tt){
    thoigian = (millis()- time1)/1000;
    hienthit(thoigian);
    time2 = millis();
   if(digitalRead(BT1) == 0){
  //myDFPlayer.play(1);  //Play the first mp3
  digitalWrite(nhac,LOW);
  delay(150);
  digitalWrite(nhac,HIGH);
  digitalWrite(rl1, HIGH);
  time2 = millis();
  tt = false;
  delay(500);
}
}
if(millis() - time2 >= 5000){
  digitalWrite(nhac,HIGH);
  digitalWrite(rl1, LOW);
}
/*
if (myDFPlayer.available()) {
    int type = myDFPlayer.readType();
    if (type == DFPlayerPlayFinished) {
      int trackNumber = myDFPlayer.read();
      digitalWrite(rl1, LOW);
    } 
  }*/
}

void hienthit(int t) {
  unsigned char hundred = 0, ten = 0, unit = 0;
  
  hundred = char(t / 100);
  ten = char((t - hundred * 100) / 10);
  unit = char(t % 10);

  digitalWrite(strobePin, LOW);

  // Hiển thị 3 số trên màn hình
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[unit]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[ten]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[hundred]);

  digitalWrite(strobePin, HIGH);
  delay(10);
}

 
