#include <LedManager.h>

LedManager ledManager(D6, D7, D8);

void setup() {
    ledManager.tryingToConnectToWifi();
    delay(5000);
    ledManager.tryingToConnectToDatabase();
    delay(5000);
}

void loop() {}