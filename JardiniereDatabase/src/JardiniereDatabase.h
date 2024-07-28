#ifndef JARDINIERE_DATABASE_H
#define JARDINIERE_DATABASE_H

#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DisplayManager.h>
#include <EEPROMManager.h>

class JardiniereDatabase {
public:
    JardiniereDatabase(const String& deviceName);
    void begin();
    void loop();
    bool databaseIsConnect;

private:
    String deviceName;
    String api_key = "AIzaSyBiBaPZsKrFY7om8_myBmOomVgpMgzvF2E";
    String db_url = "https://jardiniere-b4923-default-rtdb.europe-west1.firebasedatabase.app/";
	unsigned long previousUptMillis = 0;
	long intervalUpt = 1000;
	unsigned long previousSndMillis = 0;
	long intervalSnd = 1000;

    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    DisplayManager display;
    EEPROMManager eepromManager;

    String getTimestamp();
	String formatTime(long seconds);
	void connectDatabase();

	void getDbAirHum();
	void getDbGndHum();
	void getDbTemp();
	void getDbLum();
	void getDbIntUpd();
	void getDbIntSend();

	void sendDbAirHum(float airHumidity);
	void sendDbGndHum(float gndHumidity);
	void sendDbTemp(float temp);
	void sendDbLum(float lum);

	float getEepromAirHum();
	float getEepromGndHum();
	float getEepromTemp();
	float getEepromLum();

	void displayEepromValues();
	void updateInterval();
	void sendingInterval();

	void getAllDataDromDb();
	void sendSensorData();

	float truncateToOneDecimal(float number);
};

#endif
