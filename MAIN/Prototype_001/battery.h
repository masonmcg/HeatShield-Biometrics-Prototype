#include "Adafruit_MAX1704X.h"

Adafruit_MAX17048 maxlipo;

// function batteryInit
// initializes battery stuff and prints status
void batteryInit() {
  Serial.println("batteryInit start");
  if (!maxlipo.begin()) {
    Serial.println("Could not find Adafruit MAX17048?");
    Serial.println("Make sure a battery is plugged in!");
    while (1) delay(10);
  }
  Serial.println("batteryInit complete");
}

// function batteryGetPercentage
// returns battery percentage as an int
int batteryGetPercentage() {
  return maxlipo.cellPercent();
}

// function batteryGetPercentageString
// returns battery percentage as a C-style string (const char*)
const char* batteryGetPercentageString() {
  static char buffer[10]; // Assuming the percentage will fit in a 10-character buffer
  int percentage = maxlipo.cellPercent();
  snprintf(buffer, sizeof(buffer), "%d%%", percentage);
  return buffer;
}