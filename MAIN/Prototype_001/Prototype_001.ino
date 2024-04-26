#include "display.h"
#include "battery.h"
#include "optical.h"
#include "temperature.h"
#include "button.h"
#include "haptic.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  displayInit();
  batteryInit();
  //opticalInit();
  //loraInit();
  //temperatureInit();
  buttonInit();
  hapticInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(buttonPressD0()){
    displayPrint(1,"D0, vibrate", ST77XX_CYAN);
    hapticChirp();
  }
  else if(buttonPressD1()){
    displayPrint(1,"D1", ST77XX_CYAN);
  }
  else if(buttonPressD2()){
    displayPrint(1,"D2", ST77XX_CYAN);
  }
  else {
    displayPrint(1,"no button", ST77XX_CYAN);
  }
   
  displayPrint(2, batteryGetPercentageString(), ST77XX_RED);
  delay(100);

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
