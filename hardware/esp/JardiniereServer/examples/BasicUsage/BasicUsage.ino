#include <JardiniereServer.h>
#include <DisplayManager.h>

JardiniereServer jardinierServer;
DisplayManager display;

void setup() {
    display.begin();
    jardinierServer.begin();
}

void loop() {
    jardinierServer.loop();
    display.handlePageChange();
}