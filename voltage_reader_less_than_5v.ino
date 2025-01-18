// --- Voltage Monitoring of a 3.7V Battery using Arduino Nano ---
//
// Notes:
// - The input voltage must be below 5V as Arduino does not support more.
//
// Connections:
// 1. Connect GND (battery) to GND (arduino)
// 2. Connect the battery's positive terminal to the Arduino's A0 pin.
//    Use a 10kΩ resistor in series to limit the current drawn by the ADC chip.
// 
// Setting accurate Vref is important for accuracy.
// The 5v pin does not give a 5v output. Measure with DMM. That will be the Vref.
// It will mostly less than 5v. 
// 
// Formula:
// input voltage = (ADC value) * (Vref/1024)

#define pin A0

const float Vref = 4.68;// This is the voltage read by DMM on the 5v pin
float ADC_output = 0;   // ADC output value
float volts = 0;        // voltage we needed to measure

void setup() {
  Serial.begin(115200);
  pinMode(pin, INPUT);  // set pin mode as input
}

void loop() {
  // Read ADC value
  ADC_output = analogRead(pin);
  Serial.println("ADC value: " + String(ADC_output));

  // Calculate input voltage
  volts = ADC_output * (Vref / 1024);
  Serial.println(String(volts));

  delay(1000);
}

// Questions:
/* Why not use less resistance like 1Ω?
      _
     / \
    /   \
   /  V  \
  /_______\
 / I  |  R \
/___________\

If Vref = 5v, then I = V/R = 5A. This will burn the Arduino
*/