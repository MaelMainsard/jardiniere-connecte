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
    void displayAirHum(String value);
    void displayGndHum(String value);
    void displayTemp(String value);
    void displayLum(String value);
    void displayIntUpd(String value);
    void displayIntSend(String value);

private:
    Adafruit_SSD1306 display;
};

#endif