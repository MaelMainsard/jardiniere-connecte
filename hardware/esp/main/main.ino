#include <JardiniereServer.h>
#include <JardiniereDatabase.h>
#include <DisplayManager.h>

JardiniereServer jardinierServer;
JardiniereDatabase jardinierDatabase;
DisplayManager myDisplay;

void setup() {
    myDisplay.begin();
    jardinierDatabase.begin();
    jardinierServer.begin();
    Serial.begin(115200);
}

void loop() {
    myDisplay.handlePageChange();
    jardinierServer.loop();
    jardinierDatabase.loop();
}
