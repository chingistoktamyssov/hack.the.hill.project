#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <ArduinoBLE.h>

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;


BLEService healthService("180D"); // Health service UUID
BLECharacteristic heartRateChar("2A37", BLERead | BLENotify, sizeof(int));
// BLECharacteristic spo2Char("2A38", BLERead | BLENotify, sizeof(int));

void onBeatDetected() {
    Serial.println("Beat!");
    Serial.println(pox.getHeartRate());
}

void setup() {
  
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;) ;
  } else {
    Serial.println("SUCCESS");
  }
   pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
   pox.setOnBeatDetectedCallback(onBeatDetected);
  while (!Serial) ;

  if (!BLE.begin()) {
      Serial.println("starting BLE failed!");
      while (1) ;
  }
  BLE.setLocalName("Nano33BLE");
  BLE.setAdvertisedServiceUuid(healthService.uuid());
  healthService.addCharacteristic(heartRateChar);
  // healthService.addCharacteristic(spo2Char);
  BLE.addService(healthService);
  BLE.advertise();

  Serial.println("BLE Device is now advertising");
}

void loop() {
    BLEDevice central = BLE.central();
    
    while(central.connected()){
      pox.update();
      Serial.println("Connected BLE");
      delay(500); 
      int heartRate = pox.getHeartRate();
      if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
          
          // int spo2 = pox.getSpO2();

          Serial.print("Heart rate:");
          Serial.print(pox.getHeartRate());
          Serial.print(" bpm");
          // Serial.print(spo2);
          // Serial.println("%");

          // Update BLE characteristics
          heartRateChar.setValue(String(heartRate).c_str());
          // spo2Char.setValue(String(spo2).c_str());
          
          tsLastReport = millis();
      }
    }
    
    //BLE.poll();
}