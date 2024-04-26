const int buttonD0 = 0; // D0 button pin
const int buttonD1 = 1; // D1 button pin
const int buttonD2 = 2; // D2 button pin

// function buttonInit
// sets up buttons for use
void buttonInit() {
  pinMode(buttonD0, INPUT_PULLUP); // Initialize D0 button as input
  pinMode(buttonD1, INPUT_PULLDOWN); // Initialize D1 button as input
  pinMode(buttonD2, INPUT_PULLDOWN); // Initialize D2 button as input
}

// function buttonD0
// returns True if pressed, False if not
bool buttonPressD0() {
  return digitalRead(buttonD0) == LOW; // Return true if the button is pressed (LOW), false otherwise
}

// function buttonD1
// returns True if pressed, False if not
bool buttonPressD1() {
  return digitalRead(buttonD1) == HIGH; // Return true if the button is pressed (HIGH), false otherwise
}

// function buttonD2
// returns True if pressed, False if not
bool buttonPressD2() {
  return digitalRead(buttonD2) == HIGH; // Return true if the button is pressed (HIGH), false otherwise
}
