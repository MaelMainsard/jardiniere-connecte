#include "SensorsManager.h"

SensorsManager::SensorsManager() {}

void SensorsManager::begin(){
    Wire.begin();
}

SensorsData SensorsManager::readSensorData() {
    SensorsData sensorsData;

    if (Wire.requestFrom(SENSOR_ADDRESS, sizeof(SensorsData)) == sizeof(SensorsData)) {
        Wire.readBytes((char*)&sensorsData, sizeof(SensorsData));
    }

    return sensorsData;
}