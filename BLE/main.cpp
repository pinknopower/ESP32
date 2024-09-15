
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
int aleatorio;
String alea = "2";
String d="";
int flag=0;
int flag2=0;
BLECharacteristic* pCharacteristic = NULL;
BLEServer* pServer = NULL;
class MyServerCallbacks: public BLEServerCallbacks{
  void onConnect(BLEServer* pServer) {
      flag2=1;
    };
    void onDisconnect(BLEServer* pServer) {
      flag2=0;
    };
};
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      if(value.length() > 0) {
        StaticJsonDocument<100> doc;
        DeserializationError error = deserializeJson(doc, value);
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.c_str());
          return;
        }
        String a=doc["SSID"];
        String b=doc["TOKEN"];
        String c=doc["command"];
        Serial.println(a);
        Serial.println(b);
        Serial.println(c);
        Serial.println("*********");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++){
            Serial.print(value[i]);
            d=value[i];
        }
        flag=1;
        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("device online");
  BLEDevice::init("MyESP32");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);

   pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE|
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();


}

void loop() {
  if(flag2){
    aleatorio = random(1,100);
    alea = (String) aleatorio;  
    pCharacteristic->setValue(alea.c_str());
    pCharacteristic->notify();
    Serial.println(alea.c_str());
  }
  delay(200);
}
