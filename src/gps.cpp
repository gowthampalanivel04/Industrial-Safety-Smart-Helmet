#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include "gps.h"

// GPS pins
#define GPS_RX 16
#define GPS_TX 17

TinyGPSPlus gps;
HardwareSerial GPSserial(1);

void initGPS() {
    GPSserial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
}

void updateGPS(float *lat, float *lon) {
    while (GPSserial.available()) {
        gps.encode(GPSserial.read());
    }

    if (gps.location.isValid()) {
        *lat = gps.location.lat();
        *lon = gps.location.lng();
    }
}
