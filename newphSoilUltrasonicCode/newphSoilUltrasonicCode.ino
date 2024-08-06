/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2h6qqqeku"
#define BLYNK_TEMPLATE_NAME "smart farm"
#define BLYNK_AUTH_TOKEN "hlhaIneH0cTu4blunvsMISPmadcA7QjG"

/* Include necessary libraries */
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "JVC-t";
char pass[] = "val246810_@";

// Define Blynk virtual pin IDs
#define BLYNK_FERTILIZER_PIN V0
#define BLYNK_PESTICIDE_PIN V1
#define BLYNK_IRRIGATION_PIN V2
#define BLYNK_FISHPOND_PIN V3
#define BLYNK_DISTANCE_PIN V4
#define BLYNK_PH_PIN V5
#define BLYNK_SOIL_MOISTURE_PIN V6

// Define sensor pins
const int trigPin = 25;
const int echoPin = 26;
const int soilMoisturePin = 33;
const int phPin = 32;

// Define constants for ultrasonic sensor range
const int maxRange = 20; // cm
const int minRange = 2;  // cm

// Define output pins for solenoid triggering
const int fishPond = 18;       //brown
const int pesticide = 19;      //orange
const int fertilizer = 21;     //green
const int dripIrrigation = 22; //blue

// Define output pins for actuators
const int powerOn = 19;
const int fishPondLED = 26;
const int drainSolenoid = 23;
const int drainLED = 25;

// Define other variables
int distance;
float phValue;
int soilMoistureValue;
bool fishPondState = LOW;       //brown
bool pesticideState = LOW;      //orange
bool fertilizerState = LOW;     //green
bool dripIrrigationState = LOW; //blue

BlynkTimer timer;

void setup() {
 pinMode(fishPond, OUTPUT);       //brown
 pinMode(pesticide, OUTPUT);      //orange
 pinMode(fertilizer, OUTPUT);     //green
 pinMode(dripIrrigation, OUTPUT); //blue
 pinMode(fishPondLED, OUTPUT);
 pinMode(drainSolenoid, OUTPUT);
 pinMode(drainLED, OUTPUT);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

 Serial.begin(115200);
 Blynk.begin(auth, ssid, pass);

 // Set timer to read and send sensor data every second
 timer.setInterval(1000L, sendSensorData);
 analogReadResolution(10);
}

// ... BLYNK_WRITE functions ...
BLYNK_WRITE(BLYNK_FERTILIZER_PIN) {
 digitalWrite(fertilizer, param.asInt());
}
BLYNK_WRITE(BLYNK_PESTICIDE_PIN) {
 digitalWrite(pesticide, param.asInt());
}
BLYNK_WRITE(BLYNK_IRRIGATION_PIN) {
 digitalWrite(dripIrrigation, param.asInt());
}
BLYNK_WRITE(BLYNK_FISHPOND_PIN) {
 digitalWrite(fishPond, param.asInt());
}

void loop() {
 Blynk.run();
 timer.run();
}

void sendSensorData() {
 // Read sensor values with error handling
 int distance = measureDistance();
 if (distance == 0) { Serial.println("Ultrasonic sensor error!"); }
 int soilMoistureValue = readSoilMoisture();
 float phValue = readPh(32);
 if (isnan(phValue)) { Serial.println("pH sensor error!"); }

 // Send sensor data to Blynk app
 Blynk.virtualWrite(BLYNK_DISTANCE_PIN, distance);
 Blynk.virtualWrite(BLYNK_PH_PIN, phValue);
 Blynk.virtualWrite(BLYNK_SOIL_MOISTURE_PIN, soilMoistureValue);

 // Control actuators based on sensor readings with validation
 controlFishPond(distance);
 controlDrainSolenoid(phValue);
}

int measureDistance() {
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 unsigned long duration = pulseIn(echoPin, HIGH, 1000);
 if (duration <= 0) {
   Serial.println("No echo received");
 } else {
   Serial.print("Distance: ");
   int tempDistance = static_cast<int>(0.0343f * duration) / 2;
   Serial.println(tempDistance);
 }
 distance = static_cast<int>(0.0343f * duration) / 2;
 return distance;
}

int readSoilMoisture() {
 int sensorValue = analogRead(soilMoisturePin);
 float scaledValue = 100 - (sensorValue * 100 / 4095); // Scale to 0-100%
 Serial.print("Soil moisture value: ");
 float finalPh = (scaledValue, 2);          // convert to 2 decimal places
 Serial.println(finalPh);
 return finalPh; 
}

float readPh(int phPin) {
 float phVal, phAve = 0.0;
 for (int a = 0; a < 500; a++) {
   int phValue = 2500 - analogReadMilliVolts(25);
   phVal = 7.0 + ((float)phValue / 1000.0);
   phVal = phVal * 1.0354;
   phAve += phVal;
 }
 phAve = phAve / 500.0;
 return ((5.6331 * phAve) - 32.724);
}

void controlFishPond(int distance) {
 digitalWrite(fishPond, distance <= minRange ? LOW : (distance >= maxRange ? HIGH : LOW));
 String refillMessage = distance <= minRange ? "The fishpond is CLOSED" : (distance >= maxRange ? "The fishpond is OPEN" : "The water is within the NORMAL LEVEL");
 digitalWrite(fishPondLED, distance >= maxRange ? HIGH : (distance <= minRange ? HIGH : LOW));
 Serial.println(refillMessage);
}

void controlDrainSolenoid(float phValue) {
 digitalWrite(drainSolenoid, phValue <= 5 ? HIGH : (phValue >= 9.5 ? HIGH : LOW));
 String drainMessage = phValue <= 5 ? "The DRAIN SOLENOID is OPEN" : (phValue >= 9.5 ? "The DRAIN SOLENOID is OPEN" : "The DRAIN SOLENOID is CLOSED");
 Serial.println(drainMessage);
}