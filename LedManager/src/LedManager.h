#ifndef LEDMANAGER_H
#define LEDMANAGER_H

#include <Arduino.h>
#include <Ticker.h>

class LedManager {
public:
    LedManager(int pinR, int pinG, int pinB);
    void notConnectedToWifi();
    void tryingToConnectToWifi();
    void isConnectedAndHaveInternet();
    void failedToConnectToDatabase();
    void databaseIsConnected();

private:
    int LED_R, LED_G, LED_B;

    bool LED_G_STATE = LOW;

    bool greenBlinking = false;

    Ticker greenBlinkTicker;

    void blinkGreen();
    void startBlinkGreen();

    void stopAllBlink();
};

#endif