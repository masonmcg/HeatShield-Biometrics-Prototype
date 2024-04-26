const int hapticControl = 10; // D0 button pin

// function hapticInit
// sets up output pin for use
void hapticInit() {
  pinMode(hapticControl, OUTPUT); // Initialize pin 10 as output
  digitalWrite(hapticControl, LOW); // Set pin 10 to low
}

// function hapticChirp
// chirps haptic feedback vibration motor
void hapticChirp() {
  digitalWrite(hapticControl, HIGH);
  delay(100);
  digitalWrite(hapticControl, LOW);
}