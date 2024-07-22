#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
#define OLED_RESET -1

class DisplayManager {
public:
    DisplayManager();
    void init();
    void displayDbConnected();
    void displayDbDisconnected();
    void displayTemp(float value);
    void displayDbTemp(String value);
    void displayHum(float value);
    void displayDbHum(String value);
    void displayLum(float value);
    void displayDbLum(String value);
    void displayDbInter(String value);

private:
    Adafruit_SSD1306 display;
};

#endif