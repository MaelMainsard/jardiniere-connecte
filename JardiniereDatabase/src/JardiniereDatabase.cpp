#include "JardiniereDatabase.h"

JardiniereDatabase::JardiniereDatabase(const String& deviceName)
  : deviceName(deviceName), databaseIsConnect(false),eepromManager(), timeClient(ntpUDP), display() {}

void JardiniereDatabase::begin() {
	display.init();
    timeClient.begin();
	getAllDataDromDb();
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

	getAllDataDromDb();

    if(WiFi.status() == WL_CONNECTED && !databaseIsConnect){
    	connectDatabase();
    }
    else if(WiFi.status() != WL_CONNECTED && databaseIsConnect){
    	databaseIsConnect = false;
    }

	if(databaseIsConnect){
		display.displayDbConnected();
	} else {
		display.displayDbDisconnected();
	}
}


void JardiniereDatabase::sendHumidityData(float humidity) {
    String path = "/" + String(deviceName) + "/humidity/data";
    String timestamp = getTimestamp();
    String fullPath = path + "/" + timestamp;
    Firebase.RTDB.setString(&fbdo, fullPath, String(humidity, 1));
}

void JardiniereDatabase::getAllDataDromDb(){
	getDbAirHum();
}

float JardiniereDatabase::truncateToOneDecimal(float number) {
	return int(number * 10) / 10.0;
}

void JardiniereDatabase::getDbAirHum(){

	bool hasDbAirHum = false;
	float dbAirHum;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/air-humidity/percentage";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			dbAirHum = fbdo.floatData();
			hasDbAirHum = true;
		}
	}

	float eepromAirHum;
	bool eepromExists = eepromManager.readEepromAirHum(eepromAirHum);

	if (hasDbAirHum) {
		display.displayAirHum(String(dbAirHum,1));
		if (eepromExists) {
			if (dbAirHum != eepromAirHum) {
				eepromManager.saveEepromAirHum(dbAirHum);
			}
		} else {
			eepromManager.saveEepromAirHum(dbAirHum);
		}
	} else {
		display.displayAirHum(eepromExists ? String(eepromAirHum,1) : "?");
	}

}



String JardiniereDatabase::getTimestamp() {
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    return String(epochTime);
}