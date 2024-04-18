//#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


// function displayInit
// sets up the display for use
void displayInit(void) {
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

  Serial.println(F("Display Initialized"));
}

// function displayPrint
// takes a line number, clears, then displays given text in given color
void displayPrint(int lineNumber, const char* text, uint16_t textColor) {
  // Calculate the y position of the selected line
  int yPosition = lineNumber * 20; // Assuming each line has a height of 20 pixels
  
  // Clear only the area of the selected line
  tft.fillRect(0, yPosition, tft.width(), 20, ST77XX_BLACK);
  
  // Set text color, size, and position
  tft.setCursor(0, yPosition);
  tft.setTextColor(textColor); // Set text color based on the input parameter
  tft.setTextSize(2);
  
  // Print the message
  tft.println(text);
}
