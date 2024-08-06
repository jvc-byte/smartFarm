/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2h6qqqeku"
#define BLYNK_TEMPLATE_NAME "smart farm"
#define BLYNK_AUTH_TOKEN "hlhaIneH0cTu4blunvsMISPmadcA7QjG"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "JVC-t";
char pass[] = "val246810_@";
BlynkTimer timer;

// Define connection pins
const int fishPond = 18;   //brown
const int pesticide = 19;  //orange
const int trigPin = 25;
const int echoPin = 26;
const int fertilizer = 21;      //green
const int dripIrrigation = 22;  //blue
const int phPin = 32;
const int soilMoisturePin = 33;

const int powerOn = 19;
const int fishPondLED = 26;
const int drainSolenoid = 23;
const int drainLED = 25;

const int maxRange = 20;
const int minRange = 2;

int distance;

bool fishPondState = LOW;  //brown
bool pesticideState = LOW;
bool fertilizerState = LOW;      //green
bool dripIrrigationState = LOW;  //blue

void setup() {
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  // timer.setInterval(100L, sendSensor);
  analogReadResolution(10);
}

BLYNK_WRITE(V0) {
  digitalWrite(21, param.asInt());
}
BLYNK_WRITE(V1) {
  digitalWrite(19, param.asInt());
}
BLYNK_WRITE(V2) {
  digitalWrite(22, param.asInt());
}
BLYNK_WRITE(V3) {
  digitalWrite(18, param.asInt());
}

void sendSensor(int distance) {
  int phSensor = analogRead(phPin);
  int SiolMoisture = analogRead(soilMoisturePin);

  Blynk.virtualWrite(V4, distance);
  Blynk.virtualWrite(V5, phSensor);
  Blynk.virtualWrite(V6, SiolMoisture);
  delay(500);
}

void loop() {
  Blynk.run();
  timer.run();

  // ULTRASONIC SENSOR WORKINGS
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long startTime = micros();
  int duration = pulseIn(echoPin, HIGH, 1000);
  distance = (0.0343f * duration) / 2;
  sendSensor(distance);
  if (duration <= 0) {
    Serial.println("No echo received");
  } else {
    Serial.print("Distance: ");
    Serial.println(distance);
  }
  digitalWrite(fishPond, distance <= minRange ? LOW : (distance >= maxRange ? HIGH : LOW));
  String refillMessage = distance <= minRange ? "The fishpond is CLOSED" : (distance >= maxRange ? "The fishpond is OPEN" : "The water is within the NORMAL LEVEL");
  digitalWrite(fishPondLED, distance >= maxRange ? HIGH : (distance <= minRange ? HIGH : LOW));
  Serial.println(refillMessage);
  delay(1000);

  // SOIL SENSOR WORKINGS
  int soilMoistureValueRaw = analogRead(soilMoisturePin);
  // Convert raw value to 0-1 range (inverted for most sensors)
  float scaledValue = (float)soilMoistureValueRaw / 4095.0;
  Serial.print("Soil moisture value: ");
  Serial.println(scaledValue, 2);  // Print with 2 decimal places
  delay(1000);

  // PH SENSOR WORKINGS
  float phValue = readPh(22);
  Serial.print("pH value = ");
  Serial.println(phValue);
  digitalWrite(drainSolenoid, phValue <= 5 ? HIGH : (phValue >= 9.5 ? HIGH : LOW));
  String drainMessage = phValue <= 5 ? "The DRAIN SOLENOID is OPEN" : (phValue >= 9.5 ? "The DRAIN SOLENOID is OPEN" : "The DRAIN SOLENOID is CLOSED");
  Serial.println(drainMessage);
  delay(1000);
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
