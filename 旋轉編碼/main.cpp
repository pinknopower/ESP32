#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#define CLK 27     //旋轉編碼器 CLK
#define DT  26      //旋轉編碼器 DT 
#define SW  14     //旋轉編碼器 SW 
int f=0;
int pin=27;           
int count = 0;
int lastCLK = 0;     //lastCLK 為旋轉編碼器 CLK 預設狀態 =0
int l;
void ClockChanged()   //副程式 void ClockChanged () 
{   
  int clkValue = digitalRead(CLK);  // 讀入旋轉編碼器 CLK 狀態
  int dtValue = digitalRead(DT);    // 讀入旋轉編碼器 DT 狀態
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
