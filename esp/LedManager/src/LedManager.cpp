#include "LedManager.h"


LedManager::LedManager(int pinR, int pinG)
    : LED_R(pinR), LED_G(pinG) {
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
}

void LedManager::notConnectedToWifi() {
    stopAllBlink();
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
}

void LedManager::tryingToConnectToWifi() {
    startBlinkGreen();
    digitalWrite(LED_R, LOW);
}

void LedManager::isConnectedToWifi() {
    stopAllBlink();
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, LOW);
}


void LedManager::blinkGreen() {
    LED_G_STATE = !LED_G_STATE;
    digitalWrite(LED_G, LED_G_STATE);
}

void LedManager::startBlinkGreen() {
    greenBlinkTicker.attach(0.5, [this]() { this->blinkGreen(); });
    greenBlinking = true;
}

void LedManager::stopAllBlink() {
    greenBlinkTicker.detach();
    greenBlinking = false;
}