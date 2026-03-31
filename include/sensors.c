2. sensors.h - header files
#ifndef SENSORS_H
#define SENSORS_H

void initSensors();
void readDHT(float *temp, float *hum);
void readMPU6050(float *ax, float *ay, float *az);

#endif
