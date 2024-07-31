#include <JardiniereServer.h>

JardiniereServer jardiniereServer("Jardiniere1");

void setup() {
    jardiniereServer.begin();
}

void loop() {
    jardiniereServer.loop();
}
