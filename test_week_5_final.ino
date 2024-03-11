#define BLYNK_TEMPLATE_ID "user14"
#define BLYNK_TEMPLATE_NAME "user14@server.wyns.it"

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define LED_PIN 2
#define POTENTIOMETER_PIN 34

#define BLYNK_PRINT Serial

int sliderValue = 0;
int value = 0;

Adafruit_BMP280 bmp;

char auth[] = "CDGktxsMwQA2yp-_Lv4t7r8gI4HM9KiO";
char ssid[] = "embed";
char pass[] = "weareincontrol";

#define SLIDER_PIN V3

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  if (!bmp.begin(0x76)) {
    Serial.println("Could not find BMP280 sensor, check wiring!");
    while (1)
      ;
  }
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");

  Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);
}

void loop() {
  Blynk.run();

  float bmpTemperature = bmp.readTemperature();
  Serial.print("BMP280 Temperature: ");
  Serial.print(bmpTemperature);
  Serial.println(" °C");

  Blynk.virtualWrite(V1, bmpTemperature);

  int potValue = analogRead(POTENTIOMETER_PIN);
  float setpotTemperature = map(potValue, 0, 4095, 0, 30);
  Serial.print("Setpoint Temperature: ");
  Serial.print(setpotTemperature);
  Serial.println(" °C");

  Blynk.virtualWrite(V2, setpotTemperature);

  if (setpotTemperature != value) {
    Blynk.virtualWrite(V3, setpotTemperature);
    sliderValue = setpotTemperature;
  }

  value = setpotTemperature;

  if (sliderValue > bmpTemperature) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("on");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("off");
  }
  Serial.println("----------------------------------------------------------------------------------");
  delay(200);
}

BLYNK_WRITE(SLIDER_PIN) {
  sliderValue = param.asInt();
  Serial.print("Slider Value: ");
  Serial.println(sliderValue);
}