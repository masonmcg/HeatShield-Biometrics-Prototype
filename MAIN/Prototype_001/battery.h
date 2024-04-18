#include "Adafruit_MAX1704X.h"

Adafruit_MAX17048 maxlipo;

// function batteryInit
// initializes battery stuff and prints status
void batteryInit() {
  if (!maxlipo.begin()) {
    Serial.println(F("Could not find Adafruit MAX17048?"));
    Serial.println(F("Make sure a battery is plugged in!"));
    while (1) delay(10);
  }
  Serial.println(F("Battery monitor initialized"));
}

// function batteryGetPercentage
// returns battery percentage as an int
int batteryGetPercentage() {
  return maxlipo.cellPercent();
}