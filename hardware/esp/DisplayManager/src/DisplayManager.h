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
    void generateQRCode(String text);
    void displayPage1(); // QRCode Wifi + cred
    void displayPage2(); // QRCode Db
};

#endif