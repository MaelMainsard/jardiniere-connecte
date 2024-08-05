#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROMManager.h>
#include <qrcode.h>
#include <EspParams.h>
#include <WifiParams.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
#define OLED_RESET -1

class DisplayManager {
public:
    DisplayManager();
    void begin();
    void handlePageChange();

private:
    Adafruit_SSD1306 display;
    EEPROMManager eepromManager;

    unsigned long lastDebounceTime = 0;
    const unsigned long debounceDelay = 100;
    bool lastButtonState = HIGH;
    bool buttonState = HIGH;


    int currentPage = 1;

    void displayTitle(String str);
    void generateQRCode(String text, int x);
    void displayPage1(); // QRCode Wifi
    void displayPage2(); // Wifi Cred
    void displayPage3(); // QRCode Esp
    void displayPage4(); // Esp Cred
    void displayPage5(); // Esp Cred
};

#endif