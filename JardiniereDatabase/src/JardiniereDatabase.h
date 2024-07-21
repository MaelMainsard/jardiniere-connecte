#ifndef JARDINIERE_DATABASE_H
#define JARDINIERE_DATABASE_H

#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
#define OLED_RESET -1

class JardiniereDatabase {
public:
    JardiniereDatabase(const String& deviceName);
    void begin();
    void loop();
    void sendHumidityData(float humidity);
    bool databaseIsConnect;

private:
    String deviceName;
    String api_key = "AIzaSyBiBaPZsKrFY7om8_myBmOomVgpMgzvF2E";
    String db_url = "https://jardiniere-b4923-default-rtdb.europe-west1.firebasedatabase.app/";


    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    Adafruit_SSD1306 display;

    String getTimestamp();
	void connectDatabase();
    void clearDisplay();
};

#endif
