#include "SensorManager.h"

SensorManager::SensorManager() {}

void SensorManager::begin(){
    Wire.begin();
}

SensorData SensorManager::readSensorData() {
    SensorData sensorData = {0, 0, 0, 0};

    if (Wire.requestFrom(SENSOR_ADDRESS, sizeof(SensorData)) == sizeof(SensorData)) {
        Wire.readBytes((char*)&sensorData, sizeof(SensorData));
    }

    return sensorData;
}