#include "LedManager.h"


LedManager::LedManager(int pinR, int pinG, int pinB)
    : LED_R(pinR), LED_G(pinG), LED_B(pinB) {
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
}

void LedManager::notConnectedToWifi() {
    stopAllBlink();
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
}

void LedManager::tryingToConnectToWifi() {
    startBlinkGreen();
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_B, LOW);
}

void LedManager::isConnectedAndHaveInternet() {
    stopAllBlink();
    digitalWrite(LED_G, HIGH);
}

void LedManager::failedToConnectToDatabase() {
    digitalWrite(LED_B, LOW);
}

void LedManager::databaseIsConnected() {
    digitalWrite(LED_B, HIGH);
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