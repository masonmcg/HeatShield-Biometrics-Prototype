//#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  Serial.begin(9600);
  Serial.print(F("Hello! Feather TFT Test"));

  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  Serial.println(F("Initialized"));
}

void printMessage(int lineNumber, const char* text) {
  // Clear the screen
  tft.fillScreen(ST77XX_BLACK);
  
  // Set text color, size, and position
  int yPosition = lineNumber * 20; // Assuming each line has a height of 20 pixels
  tft.setCursor(0, yPosition);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  
  // Print the message
  tft.println(text);
}