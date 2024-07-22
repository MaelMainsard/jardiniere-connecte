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
	getDbTemp();
	getDbLum();
	getDbHum();
	getDbInt();
}

float JardiniereDatabase::truncateToOneDecimal(float number) {
	return int(number * 10) / 10.0;
}

void JardiniereDatabase::getDbTemp(){

	bool hasDbTemperature = false;
	float dbTemperature;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/temperature/degre";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			dbTemperature = fbdo.floatData();
			hasDbTemperature = true;
		}
	}

	float eepromTemperature;
	bool eepromExists = eepromManager.readEepromTemp(eepromTemperature);

	if (hasDbTemperature) {
		display.displayDbTemp(String(dbTemperature,1));
		if (eepromExists) {
			if (dbTemperature != eepromTemperature) {
				eepromManager.clearEepromTemp();
				eepromManager.saveEepromTemp(dbTemperature);
			}
		} else {
			eepromManager.saveEepromTemp(dbTemperature);
		}
	} else {
		display.displayDbTemp(eepromExists ? String(eepromTemperature,1) : "?");
	}

}

void JardiniereDatabase::getDbLum(){

	bool hasDbLuminisity = false;
	float dbLuminisity;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/luminosity/lumen";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			dbLuminisity = fbdo.floatData();
			hasDbLuminisity = true;
		}
	}

	float eepromLuminosity;
	bool eepromExists = eepromManager.readEepromLum(eepromLuminosity);

	if (hasDbLuminisity) {
		display.displayDbLum(String(dbLuminisity,1));
		if (eepromExists) {
			if (dbLuminisity != eepromLuminosity) {
				eepromManager.clearEepromLum();
				eepromManager.saveEepromLum(dbLuminisity);
			}
		} else {
			eepromManager.saveEepromLum(dbLuminisity);
		}
	} else {
		display.displayDbLum(eepromExists ? String(eepromLuminosity,1) : "?");
	}
}

void JardiniereDatabase::getDbHum(){

	bool hasDbHumidity = false;
	float dbHumidity;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/humidity/percentage";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			dbHumidity = fbdo.floatData();
			hasDbHumidity = true;
		}
	}

	float eepromHumidity;
	bool eepromExists = eepromManager.readEepromHum(eepromHumidity);

	if (hasDbHumidity) {
		display.displayDbHum(String(dbHumidity,1));
		if (eepromExists) {
			if (dbHumidity != eepromHumidity) {
				eepromManager.clearEepromHum();
				eepromManager.saveEepromHum(dbHumidity);
			}
		} else {
			eepromManager.saveEepromHum(dbHumidity);
		}
	} else {
		display.displayDbHum(eepromExists ? String(eepromHumidity,1) : "?");
	}

}

void JardiniereDatabase::getDbInt(){

	bool hasDbIntervale = false;
	float dbIntervale;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/interval_s";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			dbIntervale = fbdo.floatData();
			hasDbIntervale = true;
		}
	}

	float eepromIntervale;
	bool eepromExists = eepromManager.readEepromInt(eepromIntervale);

	if (hasDbIntervale) {
		display.displayDbInter(String(dbIntervale,1));
		if (eepromExists) {
			if (dbIntervale != eepromIntervale) {
				eepromManager.clearEepromInt();
				eepromManager.saveEepromInt(dbIntervale);
			}
		} else {
			eepromManager.saveEepromInt(dbIntervale);
		}
	} else {
		display.displayDbInter(eepromExists ? String(eepromIntervale,1) : "?");
	}

}

String JardiniereDatabase::getTimestamp() {
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    return String(epochTime);
}