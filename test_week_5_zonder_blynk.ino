#include <Wire.h>
#include <Adafruit_BMP280.h>

#define LED_PIN 2 
#define POTENTIOMETER_PIN 34 

Adafruit_BMP280 bmp; 

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  if (!bmp.begin(0x76)) {
    Serial.println("Could not find BMP280 sensor, check wiring!");
    while (1); 
  }
}

void loop() {
  float bmpTemperature = bmp.readTemperature();
  Serial.print("BMP280 Temperature: ");
  Serial.print(bmpTemperature);
  Serial.println(" °C");

  int potValue = analogRead(POTENTIOMETER_PIN);
  float setpointTemperature = map(potValue, 0, 4095, 0, 30); 
  Serial.print("Setpoint Temperature: ");
  Serial.print(setpointTemperature);
  Serial.println(" °C");
  Serial.println("------------");

  if (setpointTemperature > bmpTemperature) {
    digitalWrite(LED_PIN, HIGH); 
  } else {
    digitalWrite(LED_PIN, LOW); 
  }

  delay(200); 
}