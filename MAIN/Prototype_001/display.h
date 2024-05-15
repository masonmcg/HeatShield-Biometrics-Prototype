//#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int currentBackground = ST77XX_WHITE;

// function displayInit
// sets up the display for use
void displayInit(void) {
  Serial.println("displayInit start");

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
  tft.fillScreen(currentBackground);

  Serial.println("displayInit complete");
}

// function displayPrint
// takes a line number, clears, then displays given text in given color
void displayPrint(int lineNumber, const char* text, uint16_t textColor) {
  // Calculate the y position of the selected line
  int yPosition = lineNumber * 20; // Assuming each line has a height of 20 pixels
  
  // Clear only the area of the selected line
  tft.fillRect(0, yPosition, tft.width(), 20, currentBackground);
  
  // Set text color, size, and position
  tft.setCursor(0, yPosition);
  tft.setTextColor(textColor); // Set text color based on the input parameter
  tft.setTextSize(2);
  
  // Print the message
  tft.println(text);
}

// function displayDemo1
// iQ demo screen "press to simulate alert"
void displayDemo1() {
  currentBackground = ST77XX_WHITE;
  tft.fillScreen(currentBackground);
  displayPrint(0,"HeatShield Biometrics", ST77XX_ORANGE);
  displayPrint(1,"iQ Demo", ST77XX_ORANGE);
  displayPrint(3,"<- press to simulate alert", ST77XX_ORANGE);
}

// function displayDemo2
// iQ demo screen "HEAT STRESS WARNING"
void displayDemo2() {
  currentBackground = ST77XX_RED;
  tft.fillScreen(currentBackground);
  displayPrint(0,"HeatShield Biometrics", ST77XX_WHITE);
  displayPrint(1,"iQ Demo", ST77XX_WHITE);
  displayPrint(3,"HEAT STRESS WARNING", ST77XX_WHITE);
  displayPrint(4,"take a break", ST77XX_WHITE);
}

// function displayDemo3
// iQ demo screen "waiting for alert"
void displayDemo3() {
  currentBackground = ST77XX_WHITE;
  tft.fillScreen(currentBackground);
  displayPrint(0,"HeatShield Biometrics", ST77XX_ORANGE);
  displayPrint(1,"iQ Demo", ST77XX_ORANGE);
  displayPrint(3,"waiting for alert", ST77XX_ORANGE);
}

// function displayDemo4
// iQ demo screen "ALERT - heat stress warning for john doe"
void displayDemo4() {
  currentBackground = ST77XX_RED;
  tft.fillScreen(currentBackground);
  displayPrint(0,"HeatShield Biometrics", ST77XX_WHITE);
  displayPrint(1,"iQ Demo", ST77XX_WHITE);
  displayPrint(3,"ALERT - heat stress warning for john doe", ST77XX_WHITE);
}

// function displayDemo5
// iQ demo screen "transmission failed - retrying"
void displayDemo5() {
  currentBackground = ST77XX_WHITE;
  tft.fillScreen(currentBackground);
  displayPrint(0,"HeatShield Biometrics", ST77XX_ORANGE);
  displayPrint(1,"iQ Demo", ST77XX_ORANGE);
  displayPrint(3,"transmission failed", ST77XX_ORANGE);
  displayPrint(4,"retrying...", ST77XX_ORANGE);
}

// function displayDemo6
// iQ demo screen "transmission success"
void displayDemo6() {
  currentBackground = ST77XX_WHITE;
  tft.fillScreen(currentBackground);
  displayPrint(0,"HeatShield Biometrics", ST77XX_ORANGE);
  displayPrint(1,"iQ Demo", ST77XX_ORANGE);
  displayPrint(3,"transmission success", ST77XX_ORANGE);
}

// function displayDemo7
// iQ demo screen "transmission failed - giving up"
void displayDemo7() {
  currentBackground = ST77XX_WHITE;
  tft.fillScreen(currentBackground);
  displayPrint(0,"HeatShield Biometrics", ST77XX_ORANGE);
  displayPrint(1,"iQ Demo", ST77XX_ORANGE);
  displayPrint(3,"transmission failed", ST77XX_ORANGE);
  displayPrint(4,"giving up", ST77XX_ORANGE);
}

// function displayLoraTx1
// lora test screen for Tx device
// prints line that says what number message was sent
void displayLoraTx1(int number) {
  currentBackground = ST77XX_WHITE;
  tft.fillScreen(currentBackground);
  String msg = "Sent msg #" + String(number);
  displayPrint(0,"LoRa range test", ST77XX_ORANGE);
  displayPrint(1,"Tx Device", ST77XX_ORANGE);
  displayPrint(2,"Press D1 to transmit", ST77XX_ORANGE);
  displayPrint(4, msg.c_str(), ST77XX_ORANGE);
}

// function displayLoraRx1
// lora test screen for Rx device
// prints line that says what number was recieved and RSSI
void displayLoraRx1(int number, int RSSI) {
  currentBackground = ST77XX_WHITE;
  tft.fillScreen(currentBackground);
  String msg = "Received msg #" + String(number);
  String rssiMsg = "RSSI: " + String(RSSI);
  displayPrint(0,"LoRa range test", ST77XX_ORANGE);
  displayPrint(1,"Rx Device", ST77XX_ORANGE);
  displayPrint(3, msg.c_str(), ST77XX_ORANGE);
  displayPrint(4, rssiMsg.c_str(), ST77XX_ORANGE);
}

// function displayPowerOff
// displays powering down screen before powering down
void displayPowerOff() {
  currentBackground = ST77XX_BLACK;
  tft.fillScreen(currentBackground);
  displayPrint(3,"powering down", ST77XX_WHITE);
}