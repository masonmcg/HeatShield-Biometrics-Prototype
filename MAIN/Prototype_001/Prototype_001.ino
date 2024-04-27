#include "display.h"
#include "battery.h"
#include "optical.h"
#include "temperature.h"
#include "button.h"
#include "haptic.h"
#include "power.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  
  displayInit();
  //batteryInit();
  //opticalInit();
  //loraInit();
  //temperatureInit();
  //buttonInit();
  //hapticInit();
  powerInit();
  displayDemo3();
}

void loop() {
  // put your main code here, to run repeatedly:

  if(buttonPressD1()) {
    displayDemo4();
    //hapticChirp();
    //loraTX("heat stress event");
    delay(4000);
    displayDemo3();
  }

  if(buttonPressD0()) {
    powerOff();
  }

  /*
  if(buttonPressD0()){
    displayPrint(2,"turning off", ST77XX_CYAN);
    delay(1000);
    powerOff();
  }
  */
   
  //displayPrint(2, batteryGetPercentageString(), ST77XX_RED);
  //delay(100);

  //displayPrint(3, opticalGetHeartRateString(), ST77XX_RED);
  //delay(100);

  //displayPrint(4, temperatureGetTempString(), ST77XX_RED);
  //delay(100);

  //example lora stuff below
  /*
  const char* receivedMessage = loraRX();
  loraTX("Hello from LoRa sender!");
  */
  
}
