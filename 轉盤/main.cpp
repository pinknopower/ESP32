#include <Arduino.h>
int f=0;
int temp1;
int temp2;
int count=0;
void setup() {
    Serial.begin(115200);
}

void loop() {
    int a;
    int b;
    a=analogRead(13);
    b=analogRead(27);
    Serial.print("A:");
    Serial.println(a);
    Serial.print("B:");
    Serial.println(b);
    if(f==1){
      if(temp1==0&&temp2==0){
        if(a>=2000&&b<=2000){
          count++;
          f=0;
        }
        if(a<=2000&&b>=2000){
          count--;
          f=0;
        }
      }//00
      if(temp1==1&&temp2==0){
        if(a>=2000&&b>=2000){
          count++;
          f=0;
        }
        if(a<=2000&&b<=2000){
          count--;
          f=0;
        }
      }//10
      if(temp1==0&&temp2==1){
        if(a<=2000&&b<=2000){
          count++;
          f=0;
        }
        if(a>=2000&&b>=2000){
          count--;
          f=0;
        }
      }//01
      if(temp1==1&&temp2==1){
        if(a<=2000&&b>2000){
          count++;
          f=0;
        }
        if(a>=2000&&b<2000){
          count--;
          f=0;
        }
      }//11
    }
    if(f==0){
      if(a<2000){
        a=0;
      }else a=1;
      if(b<2000){
        b=0;
      }else b=1;
      temp1=a;
      temp2=b;
      f=1;
    }
    Serial.print("count:  ");
    Serial.println(count);
    Serial.print("temp1:");
    Serial.println(temp1);
    Serial.print("temp2:");
    Serial.println(temp2);
    delay(100);
}
