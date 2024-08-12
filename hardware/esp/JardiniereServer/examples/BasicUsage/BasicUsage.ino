#include <JardiniereServer.h>

JardiniereServer jardinierServer;

void setup() {
    Serial.begin(115200);
    jardinierServer.begin();
}

void loop() {
    jardinierServer.loop();
}