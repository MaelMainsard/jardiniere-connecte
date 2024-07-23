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
	getDbGndHum();
	getDbTemp();
	getDbLum();
	getDbIntUpd();
	getDbIntSend();
}

float JardiniereDatabase::truncateToOneDecimal(float number) {
	return int(number * 10) / 10.0;
}

void JardiniereDatabase::getDbAirHum(){

	bool hasDb = false;
	float db;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/air-humidity/percentage";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			db = fbdo.floatData();
			hasDb = true;
		}
	}


	float eeprom;
	bool eepromExists = eepromManager.readEepromAirHum(eeprom);

	if (hasDb) {
		display.displayAirHum(String(db,1));
		if (eepromExists) {
			if (db != eeprom) {
				eepromManager.clearEepromAirHum();
				eepromManager.saveEepromAirHum(db);
			}
		} else {
			eepromManager.saveEepromAirHum(db);
		}
	} else {
		display.displayAirHum(eepromExists ? String(eeprom,1) : "?");
	}

}

void JardiniereDatabase::getDbGndHum(){

	bool hasDb = false;
	float db;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/ground-humidity/percentage";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			db = fbdo.floatData();
			hasDb = true;
		}
	}


	float eeprom;
	bool eepromExists = eepromManager.readEepromGndHum(eeprom);

	if (hasDb) {
		display.displayGndHum(String(db,1));
		if (eepromExists) {
			if (db != eeprom) {
				eepromManager.clearEepromGndHum();
				eepromManager.saveEepromGndHum(db);
			}
		} else {
			eepromManager.saveEepromGndHum(db);
		}
	} else {
		display.displayGndHum(eepromExists ? String(eeprom,1) : "?");
	}

}

void JardiniereDatabase::getDbTemp(){

	bool hasDb = false;
	float db;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/temperature/degre";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			db = fbdo.floatData();
			hasDb = true;
		}
	}


	float eeprom;
	bool eepromExists = eepromManager.readEepromTemp(eeprom);

	if (hasDb) {
		display.displayTemp(String(db,1));
		if (eepromExists) {
			if (db != eeprom) {
				eepromManager.clearEepromTemp();
				eepromManager.saveEepromTemp(db);
			}
		} else {
			eepromManager.saveEepromTemp(db);
		}
	} else {
		display.displayTemp(eepromExists ? String(eeprom,1) : "?");
	}

}

void JardiniereDatabase::getDbLum(){

	bool hasDb = false;
	float db;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/luminosity/lumen";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			db = fbdo.floatData();
			hasDb = true;
		}
	}


	float eeprom;
	bool eepromExists = eepromManager.readEepromLum(eeprom);

	if (hasDb) {
		display.displayLum(String(db,1));
		if (eepromExists) {
			if (db != eeprom) {
				eepromManager.clearEepromLum();
				eepromManager.saveEepromLum(db);
			}
		} else {
			eepromManager.saveEepromLum(db);
		}
	} else {
		display.displayLum(eepromExists ? String(eeprom,1) : "?");
	}

}

void JardiniereDatabase::getDbIntUpd(){

	bool hasDb = false;
	float db;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/interval/update_s";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			db = fbdo.floatData();
			hasDb = true;
		}
	}


	float eeprom;
	bool eepromExists = eepromManager.readEepromUpdInt(eeprom);

	if (hasDb) {
		display.displayIntUpd(String(db,1));
		if (eepromExists) {
			if (db != eeprom) {
				eepromManager.clearEepromUpdInt();
				eepromManager.saveEepromUpdInt(db);
			}
		} else {
			eepromManager.saveEepromUpdInt(db);
		}
	} else {
		display.displayIntUpd(eepromExists ? String(eeprom,1) : "?");
	}

}

void JardiniereDatabase::getDbIntSend(){

	bool hasDb = false;
	float db;

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/interval/sending_s";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			db = fbdo.floatData();
			hasDb = true;
		}
	}


	float eeprom;
	bool eepromExists = eepromManager.readEepromSndInt(eeprom);

	if (hasDb) {
		display.displayIntSend(String(db,1));
		if (eepromExists) {
			if (db != eeprom) {
				eepromManager.clearEepromSndInt();
				eepromManager.saveEepromSndInt(db);
			}
		} else {
			eepromManager.saveEepromSndInt(db);
		}
	} else {
		display.displayIntSend(eepromExists ? String(eeprom,1) : "?");
	}

}


String JardiniereDatabase::getTimestamp() {
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    return String(epochTime);
}