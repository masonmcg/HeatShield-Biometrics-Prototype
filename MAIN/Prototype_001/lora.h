// rf69 demo tx rx.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client
// with the RH_RF69 class. RH_RF69 class does not provide for addressing
// or reliability, so you should only use RH_RF69 if you do not need the
// higher level messaging abilities.
// It is designed to work with the other example RadioHead69_RawDemo_TX.
// Demonstrates the use of AES encryption, setting the frequency and
// modem configuration.

#include <SPI.h>
#include <RH_RF69.h>

/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!
#define RF69_FREQ 915.0

#define RFM69_CS   5  // "B"
#define RFM69_INT  9  // "A"
#define RFM69_RST  6  // same as LED
#define LED        LED_BUILTIN

/* Teensy 3.x w/wing
#define RFM69_CS     10  // "B"
#define RFM69_INT     4  // "C"
#define RFM69_RST     9  // "A"
#define RFM69_IRQN   digitalPinToInterrupt(RFM69_INT)
*/

/* WICED Feather w/wing
#define RFM69_CS     PB4  // "B"
#define RFM69_INT    PA15 // "C"
#define RFM69_RST    PA4  // "A"
#define RFM69_IRQN   RFM69_INT
*/

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

int16_t packetnum = 0;  // packet counter, we increment per xmission

// function loraInit
// sets up the lora chip for use
void loraInit() {
  Serial.println("loraInit start");

  pinMode(LED, OUTPUT);
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("Feather RFM69 TX Test!");
  Serial.println();

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1);
  }
  Serial.println("RFM69 radio init OK!");
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);

  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");

  Serial.println("loraInit complete");
}

// function loraRX
// checks for a LoRa transmission and returns it as a C-style string (const char*)
// if no LoRa transmission it returns "RX fail"
bool loraRX(void) {
  /*
  if (rf69.available()) {
    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf69.recv(buf, &len)) {
        return (char*)buf;
      }
    else {
        return "RX fail";
    }
  }
  else {
    return "RX fail";
  }
  */
  if (rf69.available()) {
    // Should be a message for us now
    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf69.recv(buf, &len)) {
      if (!len) return false;
      buf[len] = 0;
      Serial.print("Received [");
      Serial.print(len);
      Serial.print("]: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf69.lastRssi(), DEC);

      if (strstr((char *)buf, "heat stress")) {
        return true;
      }
    } else {
      Serial.println("Receive failed");
      return false;
    }
  }


}

// function loraTX
// takes a C-style string (const char*) and transmits over LoRa
void loraTX(void) {
  //rf69.send((uint8_t *)message, strlen(message));
  //rf69.waitPacketSent();

  char radiopacket[20] = "heat stress";
  itoa(packetnum++, radiopacket+13, 10);
  Serial.print("Sending "); Serial.println(radiopacket);

  // Send a message!
  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf69.waitPacketSent();
}

/*
// function loraHeatStressTX
// send a heat stress signal over lora and waits to recieve valid return signal
// returns true if heat stress signal successfully sent
// returns false if not
bool loraHeatStressTX() {
  loraTX("heat stress event");
  const char* RXcheck = loraRX();
  if (strcmp(RXcheck, "valid") == 0) { // if RXcheck is "valid"
    return true;
  }
  else {
    return false;
  }
}

// function loraHeatStressRX
// checks to recieve heat stress signal over lora, sends valid signal back if successful
// returns true if heat stress signal successfully recieved
// returns false if not
bool loraHeatStressRX() {
  const char* message = loraRX();
  if (strcmp(message, "heat stress event") == 0) { // if message is "heat stress event"
    loraTX("valid");
    return true;
  }
  else {
    return false;
  }
}
*/