#include "JardiniereDatabase.h"

JardiniereDatabase::JardiniereDatabase()
  : databaseIsConnect(false),eepromManager(),sensorsManager(), timeClient(ntpUDP) {
  	pinMode(D5, OUTPUT);
  }

void JardiniereDatabase::begin() {
	sensorsManager.begin();
    timeClient.begin();
    
	EspParams params;
	if(eepromManager.readEspParams(params)){
		espParams = params;
	}
}

void JardiniereDatabase::connectDatabase() {
	config.api_key = api_key;
	config.database_url = db_url;

	if (Firebase.signUp(&config, &auth, "", "")) {
		databaseIsConnect = true;
	} else {
		databaseIsConnect = false;
	}

	Firebase.begin(&config, &auth);
}

void JardiniereDatabase::loop() {


    if(WiFi.status() == WL_CONNECTED && !databaseIsConnect){
    	connectDatabase();
    }
    else if(WiFi.status() != WL_CONNECTED && databaseIsConnect){
    	databaseIsConnect = false;
    }

	if(databaseIsConnect && WiFi.status() == WL_CONNECTED){
		digitalWrite(D5, HIGH);
		sendingInterval();
		handlePlanterParams();
	}
	else {
		digitalWrite(D5, LOW);
	}

}

void JardiniereDatabase::sendingInterval(){

	if(WiFi.status() == WL_CONNECTED && Firebase.ready()){
		unsigned long currentMillis = millis();

		if (currentMillis - previousSndMillis >= espParams.interval_s*1000) {

			previousSndMillis = currentMillis;
			sendSensorData();
		}
	}
}


void JardiniereDatabase::sendSensorData(){

	SensorsData dataFromSensor = sensorsManager.readSensorData();
	String fullPath = "/plenters/" + espParams.uid;

	Firebase.RTDB.setFloat(&fbdo, fullPath + "/air-humidity/data/" + getTimestamp(), dataFromSensor.airHumidity);
	Firebase.RTDB.setFloat(&fbdo, fullPath + "/ground-humidity/data/" + getTimestamp(), dataFromSensor.groundHumidity);
	Firebase.RTDB.setFloat(&fbdo, fullPath + "/luminosity/data/" + getTimestamp(), dataFromSensor.luminosity);
	Firebase.RTDB.setFloat(&fbdo, fullPath + "/temperature/data/" + getTimestamp(), dataFromSensor.temperature);
}

void JardiniereDatabase::handlePlanterParams() {
	if(Firebase.ready()){
		String fullPath = "/plenters/" + espParams.uid;

		if (Firebase.RTDB.getString(&fbdo, fullPath + "/name")) {
			String name = fbdo.stringData();
			if (name != espParams.esp_ssid) {
			/*
				espParams.esp_ssid = name;
				eepromManager.clearEspParams();
				eepromManager.saveEspParams(espParams);

			 */
			}
		}
		else {
			Firebase.RTDB.setString(&fbdo, fullPath + "/name", espParams.esp_ssid);
		}

	}
}



String JardiniereDatabase::getTimestamp() {
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    return String(epochTime);
}