#include <LiquidCrystal.h>
//#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
//#include <ArduinoBLE.h>
# include "pitches.h"

int noteDuration[51] = {8, 8, 3, 8, 4, 4, 4, 8, 8, 4, 3, 8, 4, 4, 8, 8, 2, 8, 8, 2, 8, 8, 8, 8, 4, 4, 2, 8, 8, 2, 
                      8, 8, 2, 8, 8, 4, 4, 4, 2, 8, 8, 2, 8, 8, 2, 8, 8, 4, 4, 4, 2};//note durations
int melody[51] = {NOTE_G4, NOTE_G4, NOTE_AS4, NOTE_G4, NOTE_G4, NOTE_AS4, 0, NOTE_G4, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_C5,
                NOTE_C5, NOTE_AS4, NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_F4, NOTE_GS4, NOTE_D5, NOTE_C5,
                NOTE_AS4, NOTE_D5, NOTE_DS5, NOTE_DS4, NOTE_DS4, NOTE_DS5, NOTE_C5, NOTE_GS4, NOTE_AS4, NOTE_G4, NOTE_DS4,
                NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_G4, NOTE_DS4, NOTE_DS4, NOTE_DS5, NOTE_C5, NOTE_GS4, NOTE_AS4, NOTE_G4,
                NOTE_DS4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_DS4};


 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
#define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
int temp = 0;
 

// BLEService healthService("180D"); // Health service UUID
// BLECharacteristic heartRateChar("2A37", BLERead | BLENotify, sizeof(int));
// BLECharacteristic spo2Char("2A38", BLERead | BLENotify, sizeof(int));

void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
    lcd.begin(16,2);
    lcd.print("Initializing...");
    delay(3000);
    lcd.clear();
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
    
    // BLE.setLocalName("Nano33BLE");
    // BLE.setAdvertisedServiceUuid(healthService.uuid());
    // healthService.addCharacteristic(heartRateChar);
    // healthService.addCharacteristic(spo2Char);
    // BLE.addService(healthService);
    // BLE.advertise();
    // Serial.println("BLE Device is now advertising");

    // pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // // Register a callback for the beat detection
    // pox.setOnBeatDetectedCallback(onBeatDetected  );
}
 
void loop()
{

    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        // Serial.print("Heart rate:");
        // Serial.print(pox.getHeartRate());
        // Serial.print("bpm / SpO2:");
        // Serial.print(pox.getSpO2());
        // Serial.println("%");
 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BPM : ");
        lcd.print(pox.getHeartRate());
        
        lcd.setCursor(0,1);
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.print("%");
 
        tsLastReport = millis();
    }
    if(pox.getHeartRate()>40 && pox.getHeartRate()<80){
      setColor(0, 255, 0);
    }
    else if(pox.getHeartRate()<100){
      setColor(0, 0, 255);
    }
    else{
      setColor(255, 0, 0);
    }
     // put your main code here, to run repeatedly:

    if(pox.getHeartRate()>30){
      if(temp != 51){
        for(int i = 0; i<51; i++){
          int lenght = 1000;
          tone(9, melody[i], lenght/noteDuration[i]);
          delay(lenght/noteDuration[i]*1.3);
          temp++;

        // Serial.println("t");
        // delay(1000);

        }
      }

    }
    
}
void setColor(int red, int green, int blue) {
  analogWrite(6, red);//rgb lights
  analogWrite(7, green);
  analogWrite(8, blue);
}