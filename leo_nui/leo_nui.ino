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
#define rl2 A1
#define BT1 2
#define BT2 3
unsigned long time1 ;
unsigned long time2 ;
bool tt = true;
void setup()
{
  softSerial.begin(9600);

  pinMode(A1, OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
  if (!myDFPlayer.begin(softSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(30);  //Set volume value (0~30).


}
int old, old1;
void loop()
{
  int val1 = digitalRead(BT1) == 0;
   int val2 = digitalRead(BT2) == 0;
if(val1 != old){
  delay(50);
if(digitalRead(BT1) == 0){
  if(tt){
  myDFPlayer.play(1);  //Play the first mp3
  }
  digitalWrite(rl1, HIGH);
  tt = false;
}
}
if(val2 != old1){
  delay(50);
if(digitalRead(BT2) == 0){
  if(tt){
  myDFPlayer.play(1);  //Play the first mp3
  }
  digitalWrite(rl2, HIGH);
  tt = false;
}
}
old = val1;
old1 = val2; 
if (myDFPlayer.available()) {
    int type = myDFPlayer.readType();
    if (type == DFPlayerPlayFinished) {
      int trackNumber = myDFPlayer.read();
      digitalWrite(rl1, LOW);
      digitalWrite(rl2, LOW);
      tt = true;
    } 
  }
}
