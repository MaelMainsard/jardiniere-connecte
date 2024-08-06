#ifndef JARDINIERE_DATABASE_H
#define JARDINIERE_DATABASE_H

#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <EEPROMManager.h>
#include <SensorsManager.h>
#include <SensorsData.h>

class JardiniereDatabase {
public:
    JardiniereDatabase();
    void begin();
    void loop();
    bool databaseIsConnect;

private:
    String api_key = "AIzaSyBiBaPZsKrFY7om8_myBmOomVgpMgzvF2E";
    String db_url = "https://jardiniere-b4923-default-rtdb.europe-west1.firebasedatabase.app/";
	unsigned long previousSndMillis = 0;

    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    EEPROMManager eepromManager;
	SensorsManager sensorsManager;
	EspParams espParams;

    String getTimestamp();

	void connectDatabase();
	void sendingInterval();
	void sendSensorData();

	void handlePlanterParams();
};

#endif
