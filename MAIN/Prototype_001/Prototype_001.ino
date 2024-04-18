#include "display.h"

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  displayInit();
}

void loop() {
  // put your main code here, to run repeatedly:
   displayPrint(1,"TEST L1", ST77XX_CYAN);
   delay(2000);
   displayPrint(2,"Line2", ST77XX_RED);
   delay(2000);
   displayPrint(3,"Balls", ST77XX_WHITE);
   delay(2000);
   displayPrint(4,"Heat RTOKE", ST77XX_GREEN);
   delay(2000);
   displayPrint(1,"Line 1 rewrite", ST77XX_GREEN);
   delay(2000);
}
