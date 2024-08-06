#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <SensorsData.h>

#define SENSOR_ADDRESS 0x08

class SensorsManager {
public:
    SensorsManager();
    void begin();
    SensorsData readSensorData();
};

#endif