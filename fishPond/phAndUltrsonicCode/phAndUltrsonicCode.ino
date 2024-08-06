const int refillSolenoid = 16;
const int powerOn = 17;
const int trigpin = 18;
const int echopin = 19;
const int refillLED = 21;
const int drainSolenoid = 22;
const int drainLED = 23;

const int maxRange = 20;
const int minRange = 2;

void setup() {
  Serial.begin(115200);
  
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(refillSolenoid, OUTPUT);
  pinMode(refillLED, OUTPUT);
  pinMode(drainSolenoid, OUTPUT);
  pinMode(drainLED, OUTPUT);

  digitalWrite(refillLED, LOW);
  Serial.println("welcome");

  analogReadResolution(12);
}

void loop() {
  // ULTRASONIC SENSOR WORKINGS
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  unsigned long startTime = micros();
  int duration = pulseIn(echopin, HIGH, 20000);
  int distance = (0.0343f * duration) / 2;
  if(duration <= 0){Serial.println("No echo received");}else{Serial.print("Distance: ");Serial.println(distance);}
  digitalWrite(refillSolenoid, distance <= minRange ? LOW : (distance >= maxRange ? HIGH : LOW));
  String refillMessage = distance <= minRange ? "The refill solenoid is CLOSED" : (distance >= maxRange ? "The refill solenoid is OPEN" : "The water is within the NORMAL LEVEL");
  digitalWrite(refillLED, distance >= maxRange ? HIGH : (distance <= minRange ? HIGH : LOW));
  Serial.println(refillMessage);
  delay(2000);

  // PH SENSOR WORKINGS
  float phValue = readPh(22);
  Serial.print("pH value = ");
  Serial.println(phValue);
  digitalWrite(drainSolenoid, phValue <= 5 ? HIGH : (phValue >= 9.5 ? HIGH : LOW));
  String drainMessage = phValue <= 5 ? "The DRAIN SOLENOID is OPEN" : (phValue >= 9.5 ? "The DRAIN SOLENOID is OPEN" : "The DRAIN SOLENOID is CLOSED");
  delay(2000);
}

float readPh(int phPin) {
  float phVal, phAve = 0.0;
  for (int a = 0; a < 500; a++) {
    int phValue = 2500 - analogReadMilliVolts(25);
    phVal = 7.0 + ((float)phValue / 1000.0);
    phVal = phVal * 1.0354;
    phAve += phVal;
    delay(1);
  }
  phAve = phAve / 500.0;
  return ((5.6331 * phAve) - 32.724);
}