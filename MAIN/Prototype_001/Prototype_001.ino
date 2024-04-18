#include "Display.h"

void setup() {
  // put your setup code here, to run once:
  displayInit();
}

void loop() {
  // put your main code here, to run repeatedly:
   displayPrint(1,"TEST");
   delay(2000);
}
