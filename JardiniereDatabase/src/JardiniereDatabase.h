#ifndef JARDINIERE_DATABASE_H
#define JARDINIERE_DATABASE_H

#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
#define OLED_RESET -1

class JardiniereDatabase {
public:
    JardiniereDatabase(const char* deviceName);
    void begin();
    void loop();
    void sendHumidityData(float humidity);
    bool signupOK;

private:
    Adafruit_SSD1306 display;
    const char* device_name;
    const char* api_key = "AIzaSyBiBaPZsKrFY7om8_myBmOomVgpMgzvF2E";
    const char* db_url = "https://jardiniere-b4923-default-rtdb.europe-west1.firebasedatabase.app/";
    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    String getTimestamp();
    void resetDisplay();
};

#endif
