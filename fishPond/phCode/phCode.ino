void setup() {
  Serial.begin(115200);  
  analogReadResolution(12);

}

void loop() {
  //int analogValue = analogRead(2);
  float phValue = readPh(15);  
  Serial.print("pH value = ");  Serial.println(phValue);
  delay(500);
}
float readPh(int phPin)
{
  float phVal, phAve = 0.0;
  for(int a=0; a<500; a++){
    int phValue = 2500 - analogReadMilliVolts(15);    
    phVal = 7.0 + ((float)phValue/1000.0);
    phVal = phVal * 1.0354;
    phAve += phVal;
    delay(1);
  }
  phAve = phAve / 500.0;
  return ((5.6331*phAve) - 32.724);
}