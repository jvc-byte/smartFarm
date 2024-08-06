#define soilMoisturePin 33

void setup() {
  Serial.begin(115200);
  pinMode(soilMoisturePin, INPUT);
  analogReadResolution(12);  // Optional: Set resolution
}

void loop() {
  int soilMoistureValueRaw = analogRead(soilMoisturePin);

  // Convert raw value to 0-1 range (inverted for most sensors)
  float scaledValue = 1.0 - (float)soilMoistureValueRaw / 4095.0;
  Serial.print("Soil moisture value: ");
  Serial.println(scaledValue, 2);  // Print with 2 decimal places
  delay(1000);
}