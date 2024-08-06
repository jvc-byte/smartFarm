/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2o5CUfp9r"
#define BLYNK_TEMPLATE_NAME "liquid level"
#define BLYNK_AUTH_TOKEN "j1STWY_7ucznT7fcjLfvbw2k13jRebLk"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "JVC-t";
char pass[] = "val246810_@";

// Define pins for ultrasonic sensors
#define trigPin1 18
#define echoPin1 19
#define trigPin2 21
#define echoPin2 22
#define trigPin3 23
#define echoPin3 25

// Define virtual pins for Blynk app (change these if needed)
#define BLYNK_FERTILIZER_PIN V0
#define BLYNK_PESTICIDE_PIN V1
#define BLYNK_WATER_PIN V2

long duration1;
int distance1;
long duration2;
int distance2;
long duration3;
int distance3;

BlynkTimer timer;

void setup() {
  // Debug console
  Serial.begin(115200);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
void sendSensor() {
  int finalDistance1 = measureDistance1();
  if (finalDistance1 == 0) { Serial.println("Ultrasonic sensor 1 (one) error!"); }
  int finalDistance2 = measureDistance2();
  if (finalDistance2 == 0) { Serial.println("Ultrasonic sensor 2 (two) error!"); }
  int finalDistance3 = measureDistance3();
  if (finalDistance3 == 0) { Serial.println("Ultrasonic sensor 3 (three) error!"); }

  Blynk.virtualWrite(V0, finalDistance1);
  Blynk.virtualWrite(V1, finalDistance2);
  Blynk.virtualWrite(V2, finalDistance3);
}

int measureDistance1(){
  digitalWrite(trigPin1, LOW);  // Makes trigPin low
  delayMicroseconds(2);     // 2 micro second delay
  digitalWrite(trigPin1, HIGH);  // tigPin high
  delayMicroseconds(10);     // trigPin high for 10 micro seconds
  digitalWrite(trigPin1, LOW);   // trigPin low
  duration1 = pulseIn(echoPin1, HIGH);   //Read echo pin, time in microseconds
  distance1 = duration1 * 0.034 / 2;  //Calculating actual/real distance
  Serial.print("Distance 1 = ");  //Output distance on arduino serial monitor
  Serial.println(distance1);
  return distance1;
}

int measureDistance2(){
  digitalWrite(trigPin2, LOW);  // Makes trigPin low
  delayMicroseconds(2);     // 2 micro second delay
  digitalWrite(trigPin2, HIGH);  // tigPin high
  delayMicroseconds(10);     // trigPin high for 10 micro seconds
  digitalWrite(trigPin2, LOW);   // trigPin low
  duration2 = pulseIn(echoPin2, HIGH);   //Read echo pin, time in microseconds
  distance2 = duration2 * 0.034 / 2;  //Calculating actual/real distance
  Serial.print("Distance 2 = ");  //Output distance on arduino serial monitor
  Serial.println(distance2);
  return distance2;
}

int measureDistance3(){
  digitalWrite(trigPin3, LOW);  // Makes trigPin low
  delayMicroseconds(2);     // 2 micro second delay
  digitalWrite(trigPin3, HIGH);  // tigPin high
  delayMicroseconds(10);     // trigPin high for 10 micro seconds
  digitalWrite(trigPin3, LOW);   // trigPin low
  duration3 = pulseIn(echoPin3, HIGH);   //Read echo pin, time in microseconds
  distance3 = duration3 * 0.034 / 2;  //Calculating actual/real distance
  Serial.print("Distance 3 = ");  //Output distance on arduino serial monitor
  Serial.println(distance3);
  return distance3;
}
