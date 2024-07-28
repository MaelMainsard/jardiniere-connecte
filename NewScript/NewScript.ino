#include <JardiniereServer.h>
#include <JardiniereDatabase.h>

const String DEVICE_NAME = "Jardiniere_1";

JardiniereServer jardinierServer(DEVICE_NAME);
JardiniereDatabase jardinierDatabase(DEVICE_NAME);

void setup() {
    jardinierDatabase.begin();
    jardinierServer.begin();
    Serial.begin(115200);
}

void loop() {
    jardinierServer.loop();
    jardinierDatabase.loop();
}
