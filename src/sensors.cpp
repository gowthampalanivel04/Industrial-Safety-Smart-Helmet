#include <Wire.h>
#include "DHT.h"
#include "config.h"
#include "sensors.h"

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define MPU6050_ADDR 0x68

int16_t AccX, AccY, AccZ;

void initSensors() {
    dht.begin();

    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
}

void readMPU6050(float *ax) {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, 6, true);

    AccX = Wire.read() << 8 | Wire.read();
    AccY = Wire.read() << 8 | Wire.read();
    AccZ = Wire.read() << 8 | Wire.read();

    *ax = AccX / 16384.0;
}

void readSensors(float *temp, float *hum, float *ax) {
    *temp = dht.readTemperature();
    *hum  = dht.readHumidity();
    readMPU6050(ax);
}
