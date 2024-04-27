// function powerInit
// sets up a button to turn on ESP32 from deep sleep
void powerInit() {
  Serial.println("powerInit start");
  touchSleepWakeUpEnable(T10,100); // Enable touchpad wake-up
  Serial.println("powerInit complete");
}

// function powerOff
// turns off all peripherals, then turns off the ESP32
void powerOff() {
  // add other functions here to turn off other sensors??
  esp_deep_sleep_start();
}