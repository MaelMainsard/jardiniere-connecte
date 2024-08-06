#include <SensorsData.h>
#include <TinyWireS.h>
#include <dht.h>

#define ADDRESS 0x08
#define DHT22_PIN PB1

dht DHT;

float oldTemp;
float oldAirHum;

void setup() {
  TinyWireS.begin(ADDRESS);
  TinyWireS.onRequest(sendData);
  pinMode(DHT22_PIN, INPUT);
}

void loop() {
 TinyWireS_stop_check();
}

void sendData() {
  DHT.read22(DHT22_PIN);
  
  if(DHT.temperature != -102.30 && DHT.humidity != 102.30){
    oldTemp = DHT.temperature;
    oldAirHum = DHT.humidity;
  }


  SensorsData sensorsData = SensorsData(oldAirHum, getGroundHum(), getLuminosity(), oldTemp);
  uint8_t* sensorDataPtr = (uint8_t*)&sensorsData;
  const uint8_t sensorDataSize = sizeof(SensorsData);

  for (uint8_t i = 0; i < sensorDataSize; i++) {
    TinyWireS.send(sensorDataPtr[i]);
  }

}

float getLuminosity() {
  
  int analogValLum = analogRead(A2);
  float voltLum = float(5 * analogValLum) / 1023;
  float ohmLum = 10000 * (5 - voltLum) / voltLum;
  float illuminance = (10.0 * pow(14000.0, 1.0 / 0.7)) / pow(ohmLum, 1.0 / 0.7);

  return illuminance*21.93;
}

float getGroundHum(){
  
  int analogValGndHum = analogRead(A3);
  int percentage = map(analogValGndHum,655, 646, 0, 100);
  percentage = constrain(percentage, 0, 100);
  return analogValGndHum;
}
