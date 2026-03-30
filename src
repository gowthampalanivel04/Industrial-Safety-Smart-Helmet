#define BLYNK_TEMPLATE_ID "TMPL38lq6fmfu"
#define BLYNK_TEMPLATE_NAME "smart helmet"
#define BLYNK_AUTH_TOKEN "YOUR_TOKEN"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "MAX30105.h"
#include "heartRate.h"
#include <TinyGPS++.h>
#include <HardwareSerial.h>
int i=0;
char ssid[] = "YOUR_WIFI";
char pass[] = "YOUR_PASSWORD";

#define DHTPIN 4
#define DHTTYPE DHT11

#define GAS_PIN    27
#define NOISE_PIN  18
#define BUZZER     26

#define GPS_RX 16   
#define GPS_TX 17   


#define MPU6050_ADDR 0x68
int16_t AccX, AccY, AccZ;
float ax, ay, az;

DHT dht(DHTPIN, DHTTYPE);
MAX30105 particleSensor;


TinyGPSPlus gps;
HardwareSerial GPSserial(1);

float tempC, hum;
int spo2 = 0, hb = 0;
bool gasDetected;
bool noiseDetected;
bool alertSent = false;

float latitude = 0.0;
float longitude = 0.0;

void readMPU6050() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 6, true);

  AccX = Wire.read() << 8 | Wire.read();
  AccY = Wire.read() << 8 | Wire.read();
  AccZ = Wire.read() << 8 | Wire.read();

  ax = AccX / 16384.0;
  ay = AccY / 16384.0;
  az = AccZ / 16384.0;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();



  pinMode(GAS_PIN, INPUT);
  pinMode(NOISE_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  dht.begin();


  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  particleSensor.begin(Wire, I2C_SPEED_STANDARD);
  particleSensor.setup();


  GPSserial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);


  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

delay(1000);
    Blynk.run();
    String gpsData ="10.892, 76.993" ;
    Blynk.virtualWrite(V2, gpsData);

}

void loop() {
  Blynk.run();

  while (GPSserial.available()) {
    gps.encode(GPSserial.read());
  }

  if (gps.location.isValid()) {
    latitude  = gps.location.lat();
    longitude = gps.location.lng();
  }

  tempC = dht.readTemperature();
  hum   = dht.readHumidity();

  readMPU6050();

  gasDetected   = !digitalRead(GAS_PIN);
  noiseDetected = digitalRead(NOISE_PIN);

  spo2 =particleSensor.getRed();
  spo2 = constrain(spo2, 0, 100);
  bool abnormal = false;
  String alertMsg = "";

  if (tempC > 38) {
    abnormal = true;
    alertMsg += "High Temp | ";
  }

  if (spo2 < 90 &&spo2 >20) {
    abnormal = true;
    alertMsg += "Low SpO2 | ";
  }

  if (gasDetected) {
    abnormal = true;
    alertMsg += "Gas Detected | ";
  }

  if (noiseDetected) {
    abnormal = true;
    alertMsg += "High Noise | ";
  }

  if (abs(ax) > 0.75) {
    abnormal = true;
    alertMsg += "Possible Fall | ";
  }

  digitalWrite(BUZZER, abnormal ? HIGH : LOW);

  if (abnormal && !alertSent) {

    Blynk.logEvent("alert", alertMsg);
    alertSent = true;
  }

  if (!abnormal) {
    alertSent = false;
  }

  String healthData =
    "T: " + String(tempC, 1) + " | " +
    "SpO2: " + String(spo2) + " | " +
    "HB: " + String(hb);

  String envData =
    "Gas: " + String(gasDetected) + " | " +
    "Noise: " + String(noiseDetected) + " | " +
    "Ax: " + String(ax, 2);

  String gpsData =
    "Lat: " + String(latitude, 6) +
    " | Lon: " + String(longitude, 6);

        Serial.println(healthData);
        Serial.println(envData);

  Blynk.virtualWrite(V0, healthData);
  Blynk.virtualWrite(V1, envData);

  delay(1000);
} 
