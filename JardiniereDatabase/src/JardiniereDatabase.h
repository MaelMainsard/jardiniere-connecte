#ifndef JARDINIERE_DATABASE_H
#define JARDINIERE_DATABASE_H

#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <LedManager.h>

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
    LedManager ledManager;

    String getTimestamp();
	void connectDatabase();
};

#endif
