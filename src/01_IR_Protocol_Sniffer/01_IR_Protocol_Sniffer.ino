// Define the pin where the TSOP receiver is connected
// We are using GPIO 4
const int irPin = 4; 

// Define the pin for the Built-in LED
// On most ESP32 Dev Boards (like the DOIT DevKit V1), this is GPIO 2.
const int ledPin = 2; 

void setup() {
  Serial.begin(115200);
  
  // Set the IR pin as input
  pinMode(irPin, INPUT_PULLUP);
  
  // Set the LED pin as output
  pinMode(ledPin, OUTPUT);
  
  Serial.println("ESP32 IR Receiver Active");
}

void loop() {
  // Read the sensor value
  int sensorValue = digitalRead(irPin);

  // LOGIC: TSOP4838 is "Active LOW"
  // 1 (HIGH) = No signal (Idle) -> LED OFF
  // 0 (LOW)  = 38kHz IR Signal Detected -> LED ON
  
  if (sensorValue == LOW) {
    Serial.println("IR Signal Detected! (Output: 0)");
    digitalWrite(ledPin, HIGH); // Turn LED ON
  } else {
    digitalWrite(ledPin, LOW);  // Turn LED OFF
  }
  
  // Short delay to keep Serial readable but LED responsive
  delay(20);
}