#include "display.h"
#include "battery.h"
#include "optical.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  displayInit();
  batteryInit();
  opticalInit();
  //loraInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  displayPrint(1,"TEST L1", ST77XX_CYAN);
  delay(100);
   
  displayPrint(2, batteryGetPercentageString(), ST77XX_RED);
  delay(100);

  displayPrint(3, opticalGetHeartRateString(), ST77XX_RED);
  delay(100);

  //example lora stuff below
  /*
  const char* receivedMessage = loraRX();
  loraTX("Hello from LoRa sender!");
  */
  
}
