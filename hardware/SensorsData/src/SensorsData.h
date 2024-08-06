#ifndef SENSORSDATA_H
#define SENSORSDATA_H

#include <Arduino.h>
#include <Regexp.h>

class SensorsData {
public:
    float airHumidity;
    float groundHumidity;
    float luminosity;
    float temperature;

    SensorsData() {}
    SensorsData(float airHumidity, float groundHumidity, float luminosity, float temperature);

};
#endif