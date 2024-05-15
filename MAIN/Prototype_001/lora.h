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
// checks for lora transmission and returns message received as String
// returns "Receive failed" otherwise
String loraRX(void) {
  if (rf69.available()) {
    // Should be a message for us now
    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf69.recv(buf, &len)) {
      if (!len) return "Receive failed";
      buf[len] = 0;
      //Serial.print("Received [");
      //Serial.print(len);
      //Serial.print("]: ");
      //Serial.println((char*)buf);
      //Serial.print("RSSI: ");
      //Serial.println(rf69.lastRssi(), DEC);

      return String((char*)buf);
    } else {
      return "Receive failed";
    }
  } else {
    return "Receive failed";
  }
}

// function loraTX
// sends a String radiopacket over lora
void loraTX(String radiopacket) {
  rf69.send((uint8_t *)radiopacket.c_str(), radiopacket.length());
  rf69.waitPacketSent();
}

// function loraGetRSSI
// returns last RSSI
int loraGetRSSI() {
  return rf69.lastRssi();
}