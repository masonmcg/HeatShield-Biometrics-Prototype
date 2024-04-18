#include "display.h"
#include "battery.h"

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  displayInit();
  batteryInit();
}

void loop() {
  // put your main code here, to run repeatedly:
   displayPrint(1,"TEST L1", ST77XX_CYAN);
   delay(2000);
   
  int bat_per = batteryGetPercentage();
  char buffer[4]; // Buffer for converting int to string
  itoa(bat_per, buffer, 10); // Convert int to string
  displayPrint(2, buffer, ST77XX_RED);
  delay(2000);
   
}
