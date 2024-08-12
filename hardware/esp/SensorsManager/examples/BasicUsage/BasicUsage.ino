#include <SensorsManager.h>
#include <SensorsData.h>

SensorsManager sensorsManager;
void setup() {
    Serial.begin(115200);
    sensorsManager.begin();

}

void loop() {
    SensorsData response = sensorsManager.readSensorData();
    Serial.println("=========================");
    Serial.println(response.airHumidity);
    Serial.println(response.groundHumidity);
    Serial.println(response.luminosity);
    Serial.println(response.temperature);
    delay(2000);
}