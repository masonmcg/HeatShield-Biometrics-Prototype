
#include "display.h"
#include "battery.h"
#include "optical.h"
#include "temperature.h"
#include "button.h"
#include "haptic.h"
#include "power.h"
#include "lora.h"

bool cheifWatch = true; // select true if cheifWatch, false if crewWatch

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  
  displayInit();
  //batteryInit();
  //opticalInit();
  loraInit();
  //temperatureInit();
  buttonInit();
  //hapticInit();
  //powerInit();
  
  // below code chooses starting screen based on which type watch
  if(cheifWatch) {
    displayDemo3();
  }
  else {
    displayDemo1();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // if this is cheif watch, do cheif watch things like wait for alerts
  if(cheifWatch) {

    if(loraRX()) {
      displayDemo4();        // go to alert recieved screen
      delay(4000);           // delay so user can read alert screen
      displayDemo3();        // go back to waiting screen
    }

    /*
    Serial.println("1");
    if(loraHeatStressRX()) { // if recieve heat stress alert
      Serial.println("2");
      displayDemo4();        // go to alert recieved screen
      //hapticChirp();       // buzz so user notices alert
      delay(4000);           // delay so user can read alert screen
      displayDemo3();        // go back to waiting screen
    }
    //if(buttonPressD0()) { // if power button pressed, turn off
    //  powerOff();
    //}
    */
  }

  // if this is crew watch, do crew watch things like send alerts
  else {
    
    if(buttonPressD1()) {      // buttonPressD1 simulates sending alert
      displayDemo2();          // display heat stress alert screen
      loraTX();
      delay(4000);             // delay so user can read alert screen
      displayDemo1();
    }

    /*
    if(buttonPressD1()) {      // buttonPressD1 simulates sending alert
      displayDemo2();          // display heat stress alert screen
      delay(4000);             // delay so user can read alert screen
      //hapticChirp();         // buzz so user notices alert
      if(loraHeatStressTX()) { // if alert transmission successful
        delay(4000);           // delay so user can read alert screen
        displayDemo1();        // go back to waiting screen
      }
      else {                   // if alert transmission unsuccessful
        int i = 0;
        while(loraHeatStressTX() == false && i < 10) {
          displayDemo5();      // display communication issue - retrying screen
          delay(1000);         // delay so user can read screen
          i++;
        }
        //add displayDemo7(); here if failed and giving up
        displayDemo6();        // after successful transmission, display transmission successful
        delay(2000);           // delay so user can read screen
        displayDemo1();        // go back to waiting screen
      }
    }
    //if(buttonPressD0()) { // if power button pressed, turn off
    //  powerOff();
    //}
    */
  }
  
  
   
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
