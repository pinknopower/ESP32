#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#define CLK 27     //旋轉編碼器 CLK 連接 Arduino pin 2
#define DT  26      //旋轉編碼器 DT 連接 Arduino pin 3
#define SW  14     //旋轉編碼器 SW 連接 Arduino pin 4
int f=0;
int pin=27;           //定義一些整數；
int count = 0;
int lastCLK = 0;     //lastCLK 為旋轉編碼器 CLK 預設狀態 =0
int l;
void ClockChanged()   //副程式 void ClockChanged () 
{   
  int clkValue = digitalRead(CLK);  // Arduino 讀入旋轉編碼器 CLK 狀態
  int dtValue = digitalRead(DT);    // Arduino 讀入旋轉編碼器 DT 狀態
  if (lastCLK != clkValue)
  {
    lastCLK = clkValue;
    count += (clkValue != dtValue ? 1 : -1);  //旋轉編碼器順時針旋轉時，count +1；逆時針旋轉時， count -1
    if(l!=count/2){
      f=1;
    }
    l= count/2;
  }
}
void setup()
{
  pinMode(SW, INPUT);      //Arduino 預備讀入旋轉編碼器 CLK, DT, and SW 狀態 
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  
  //設置系統岔斷模式，當pin 2 輸入狀態有改變( CHANGE ) 時，呼叫副程式 ClockChanged() 
  attachInterrupt(digitalPinToInterrupt(pin), ClockChanged, CHANGE);  

  Serial.begin(115200);
}

//本程式 void loop() 唯一做的事，是當旋轉編碼器按鍵 SW 被按下時，系統重設，整數 count 歸零，熄滅所有LED燈。
void loop()
{
  if(f==1){
    Serial.print("count:");
    Serial.println(l);
    f=0;
  }
 
  if (!digitalRead(SW) && count != 0) 
  {
    count = 0;
    Serial.print("count:");
    Serial.println(count);

  }
}