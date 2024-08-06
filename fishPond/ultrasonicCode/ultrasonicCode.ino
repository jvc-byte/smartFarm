const int echopin = 19;
const int trigpin = 18;
const int refillLED = 21;
const int refillSolenoid = 16;
const int powerOn = 17;
const int maxRange = 20;
const int minRange = 2;

void setup() {
  Serial.begin(115200);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(refillSolenoid, OUTPUT);
  pinMode(refillLED, OUTPUT);
  digitalWrite(refillLED, LOW);
  Serial.println("welcome");
}

void loop() {
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  // unsigned long startTime = micros();
  int duration = pulseIn(echopin);
  int distance = (0.0343f * duration) / 2;

  if (duration <= 0) {
    Serial.println("No echo received");
  } else {
    Serial.print("Distance: ");
    Serial.println(distance);
  }
  digitalWrite(refillSolenoid, distance <= minRange ? LOW : (distance >= maxRange ? HIGH : LOW));
  String message = distance <= minRange ? "The refill solenoid is CLOSED" : (distance >= maxRange ? "The refill solenoid is OPEN" : "The water is within the NORMAL LEVEL");
  digitalWrite(refillLED, distance >= maxRange ? HIGH : (distance <= minRange ? HIGH : LOW));

  Serial.println(message);

  delay(2000);
}