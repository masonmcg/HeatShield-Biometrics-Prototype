#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

// function opticalInit
// sets up the optical heart rate sensor for use
void opticalInit(void) {
  Serial.println("Initializing optical...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}

// function opticalGetHeartRateString
// returns heart rate as a C-style string (const char*)
const char* opticalGetHeartRateString() {
  // Declare irValue here to ensure it's within the loop scope
  long irValue;

  // Loop 100 times for heart rate calculation
  for (int i = 0; i < 100; i++) {
    irValue = particleSensor.getIR(); // Assign value to irValue within the loop

    if (checkForBeat(irValue) == true) {
      //We sensed a beat!
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20) {
        rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
        rateSpot %= RATE_SIZE; //Wrap variable

        //Take average of readings
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }
  }

  static char buffer[10]; // Assuming the heart rate will fit in a 10-character buffer
  if (irValue < 50000) {
    sprintf(buffer, "No finger?");
  } else {
    sprintf(buffer, "%d", beatAvg); // Convert beatAvg to string using sprintf
  }

  return buffer;
}
