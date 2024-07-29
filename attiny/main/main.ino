#include <TinyWireS.h>
#include "SensorData.h"

void sendData() {
  SensorData sensorData = {45.2, 30.5, 800.0, 22.3};
  uint8_t* sensorDataPtr = (uint8_t*)&sensorData;
  const uint8_t sensorDataSize = sizeof(SensorData);

  for (uint8_t i = 0; i < sensorDataSize; i++) {
    TinyWireS.send(sensorDataPtr[i]);
  }
}

void setup() {
  TinyWireS.begin(8);
}

void loop() {
  sendData();
}
