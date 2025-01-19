// --- Voltage Monitoring of a 12V Battery using Arduino Nano ---
//
// Notes:
// - 12V is nominal. So, it can go till 14V. For safety, we will consider 15V.
// - Arduino can take only 5V. So, we need to use a voltage divider to reduce the
// - voltage levels for the Arduino
//
// Voltage Divider Basics:
// - We need 5V max where the input is 15V max.
// - This means we need 15/5=3 resistors in series. 
// - What will be the voltage drop on each resistor?
// - It will be (Vin/R_total)*single resistance. Which is 5V. 
/*
    +15v
     |
     |
     |
     _
    | |
    | | 1Ω
    |_|
     |-----------------------------x Vout = 10V (5V dropped by the first resistor)
     |
     |--------------------
     _                   |
    | |                  |
    | | 1Ω               |
    |_|                  |
     |                   |
     |             equivalent to 2Ω
     |                   |
     _                   |
    | |                  |
    | | 1Ω               |
    |_|                  |
     |--------------------
     |
     |
    GND

*/
//
// - Add up the resistances above the Vout and below the Vout point to apply the voltage divider.
// - Voltage divider = Vin * ( R2/ (R1+R2) )
// - Since 5V is 3rd of Vin, we need to multiply output volts with 3 in the code

// Connections:
// 1. Connect GND (battery) to GND (arduino)
// 2. Connect Vout point to the Arduino's A0 pin.
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

float multiplier = 3;   // As output is 1/3rd of Vin

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
  volts = volts * multiplier;
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