#include "display.h"
#include "battery.h"
#include "optical.h"
#include "temperature.h"
#include "button.h"
#include "haptic.h"
#include "power.h"
#include "lora.h"
#include "probe.h"

bool probeTest = false; // if selected true, will not do lora stuff at all and only probe stuff
bool txDevice = true;   // select true if Tx device, false if Rx device
int messageCount = 0;   // messageCount varible for LoRa testing

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
  probeInit();
  
  // below code chooses starting screen based on which device
  if(txDevice) {
    displayLoraTx1(0);
  }
  else {
    displayLoraRx1(0, 0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // if probeTest, only do this stuff forever
  if(probeTest) {
    while(1) {
      // Print values to serial monitor
      Serial.print("Probe 1 Temperature: ");
      Serial.print(probeReadTemp1());
      Serial.println(" F");

      Serial.print("Probe 2 Temperature: ");
      Serial.print(probeReadTemp2(););
      Serial.println(" F");

      delay(1000); // Wait 1 second before the next reading
    }
  }
  
  // if this is txDevice, do Tx things
  if(txDevice) {
    if(buttonPressD1()) {                    // buttonPressD1 sends next message
      messageCount += 1;                     // increment message count
      String message = String(messageCount); // cast messageCount int to String
      loraTX(message);                       // transmit message String over lora
      displayLoraTx1(messageCount);          // display what messageCount was sent
      delay(1000);                           // delay so it doesnt transmit a million times
    }
  }

  // if this is rxDevice, do Rx things
  else {
    String message = loraRX();                     // get message from loraRx
    if(message != "Receive failed") {              // if message was recieved
      messageCount = message.toInt();              // set message count as message num recieved
      displayLoraRx1(messageCount, loraGetRSSI()); // display what message was recieved and signal strength
      delay(1000);                                 // delay so it doesnt rx a million times
    }
  }

}
