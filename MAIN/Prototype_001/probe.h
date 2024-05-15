const int resistorSize = 10000;  // Resistance of the series resistor in ohms
const double totalMillivolts = 3300;  // Total millivolts of the ADC reference voltage

// Steinhart-Hart coefficients for the thermistor
const double A = 0.0008726155159398184;
const double B = 0.00025407742513515415;
const double C = 1.8079912307987547e-07;

// Function probeInit
// Sets up analog read pins to get voltage
void probeInit() {
  // Initialize analog pins for temperature probes
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

// Function to convert voltage to temperature
// mason made this with chatGPT, might be worth a try
// otherwise I left your code below in the comment
double voltageToTemperature(double voltage) {
  // Calculate resistance of the thermistor using voltage divider formula
  double resistance = resistorSize * (totalMillivolts / voltage - 1);

  // Apply the Steinhart-Hart equation
  double logR = log(resistance);
  double tempK = 1.0 / (A + B * logR + C * logR * logR * logR);  // Temperature in Kelvin
  double tempC = tempK - 273.15;  // Convert Kelvin to Celsius
  double tempF = tempC * 9.0 / 5.0 + 32;  // Convert Celsius to Fahrenheit

  return tempF;
}

/*
// Function to convert voltage to temperature
double voltageToTemperature(double voltage) {
  // Calculate resistance of the thermistor using voltage divider formula
  double resistance = resistorSize * (totalMillivolts / voltage - 1);
  
  // Assuming a linear relationship between temperature and resistance
  // Replace the coefficients with your calibration values
  double slope = 0.1;  // Example slope
  double intercept = 25;  // Example intercept
  
  // Calculate temperature using the linear equation: temperature = m * resistance + b
  double temperature = slope * resistance + intercept;
  
  return temperature;
}
*/

// Function probeReadTemp1
// Reads analog pin voltage for probe 1 and returns it as a temperature
double probeReadTemp1() {
  // Read analog voltage
  int rawValue = analogRead(A0);
  // Convert analog value to voltage (in millivolts)
  double voltage = rawValue * (totalMillivolts / 1023.0);
  // Convert voltage to temperature
  double temperature = voltageToTemperature(voltage);
  return temperature;
}

// Function probeReadTemp2
// Reads analog pin voltage for probe 2 and returns it as a temperature
double probeReadTemp2() {
  // Read analog voltage
  int rawValue = analogRead(A1);
  // Convert analog value to voltage (in millivolts)
  double voltage = rawValue * (totalMillivolts / 1023.0);
  // Convert voltage to temperature
  double temperature = voltageToTemperature(voltage);
  return temperature;
}