void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); // Seed the random number generator
}

void loop() {
  static int value = 0;
  
  int variation = random(10, 150); // Generate a random number between 1 and 10
  value += (5 + variation); // Increment value by 10 plus the random variation
  Serial.println(value);
  value -= variation;
  delay(500);  // Adjust delay as needed
}