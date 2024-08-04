#ifndef JARDINIERE_DATABASE_H
#define JARDINIERE_DATABASE_H

#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <EEPROMManager.h>
#include <SensorManager.h>
#include "../shared/JardiniereUtils.h"

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
	long intervalSnd = 1000;

    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    EEPROMManager eepromManager;
	SensorManager sensorManager;

    String getTimestamp();
	String formatTime(long seconds);
	void connectDatabase();

	void getDbData();

	void getDbAirHum();
	void getDbGndHum();
	void getDbTemp();
	void getDbLum();
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
	void sendingInterval();

	void getAllDataDromDb();
	void sendSensorData();

	String getUid();
	String getFirstPart(String uid);

	float truncateToOneDecimal(float number);
};

#endif
