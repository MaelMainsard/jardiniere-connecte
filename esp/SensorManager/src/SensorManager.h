#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include "SensorData.h"

#define SENSOR_ADDRESS 8

class SensorManager {
public:
    SensorManager();
    void begin();
    SensorData readSensorData();
};

#endif