#include <SensorsManager.h>
#include <SensorsData.h>

SensorsManager sensorsManager;
void setup() {
    Serial.begin(115200);
    sensorsManager.begin();

}

void loop() {
    SensorsData response = sensorsManager.readSensorData();
    Serial.println(response.temperature);
}