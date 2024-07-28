#include "JardiniereDatabase.h"

JardiniereDatabase::JardiniereDatabase(const String& deviceName)
  : deviceName(deviceName), databaseIsConnect(false),eepromManager(), timeClient(ntpUDP), display() {}

void JardiniereDatabase::begin() {
	display.init();
    timeClient.begin();
	displayEepromValues();
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

	if(databaseIsConnect){
		display.displayDbConnected();
		updateInterval();
		sendingInterval();
	}
	else {
		display.displayDbDisconnected();
	}

}

void JardiniereDatabase::updateInterval(){

	unsigned long currentMillis = millis();
  	if (currentMillis - previousUptMillis >= intervalUpt) {
    	previousUptMillis = currentMillis;
   		getAllDataDromDb();
  	}
	getDbIntUpd();
	getDbIntSend();

}

void JardiniereDatabase::sendingInterval(){

	unsigned long currentMillis = millis();

  	if (currentMillis - previousSndMillis >= intervalSnd) {

    	previousSndMillis = currentMillis;
		sendSensorData();
  	}
}


void JardiniereDatabase::sendSensorData(){
	// Send sensor data here the sensor data here
	sendDbAirHum(75.7);
}

void JardiniereDatabase::getAllDataDromDb(){
	getDbAirHum();
	getDbGndHum();
	getDbTemp();
	getDbLum();
}

float JardiniereDatabase::truncateToOneDecimal(float number) {
	return int(number * 10) / 10.0;
}

float JardiniereDatabase::getEepromAirHum(){
	float eeprom;
	bool eepromExists = eepromManager.readEepromAirHum(eeprom);

	if (eepromExists) {
		return eeprom;
	} else {
		return -1.0;
	}
}

float JardiniereDatabase::getEepromGndHum(){
	float eeprom;
	bool eepromExists = eepromManager.readEepromGndHum(eeprom);

	if (eepromExists) {
		return eeprom;
	} else {
		return -1.0;
	}
}

float JardiniereDatabase::getEepromTemp(){
	float eeprom;
	bool eepromExists = eepromManager.readEepromTemp(eeprom);

	if (eepromExists) {
		return eeprom;
	} else {
		return -1.0;
	}
}

float JardiniereDatabase::getEepromLum(){
	float eeprom;
	bool eepromExists = eepromManager.readEepromLum(eeprom);

	if (eepromExists) {
		return eeprom;
	} else {
		return -1.0;
	}
}

void JardiniereDatabase::displayEepromValues(){
	display.displayAirHum(getEepromAirHum() != -1.0 ? String(getEepromAirHum(),1) : "__");
	display.displayGndHum(getEepromGndHum() != -1.0 ? String(getEepromGndHum(),1) : "__");
	display.displayTemp(getEepromTemp() != -1.0 ? String(getEepromTemp(),1) : "__");
	display.displayLum(getEepromLum() != -1.0 ? String(getEepromLum(),1) : "__");
	display.displayIntUpd("__");
	display.displayIntSend("__");
}



void JardiniereDatabase::getDbAirHum(){
	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/air-humidity/percentage";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			if (fbdo.floatData() != getEepromAirHum()) {
				eepromManager.clearEepromAirHum();
				eepromManager.saveEepromAirHum(fbdo.floatData());
				display.displayAirHum(String(fbdo.floatData(),1));
			}
		}
	}
}

void JardiniereDatabase::sendDbAirHum(float airHumidity){
	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/air-humidity/data";
    	String timestamp = getTimestamp();
    	String fullPath = path + "/" + timestamp;
    	Firebase.RTDB.setFloat(&fbdo, fullPath, airHumidity);
	}
}

void JardiniereDatabase::getDbGndHum(){
	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/ground-humidity/percentage";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			if (fbdo.floatData() != getEepromGndHum()) {
				eepromManager.clearEepromGndHum();
				eepromManager.saveEepromGndHum(fbdo.floatData());
				display.displayGndHum(String(fbdo.floatData(),1));
			}
		}
	}
}

void JardiniereDatabase::sendDbGndHum(float gndHumidity){
	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/ground-humidity/data";
    	String timestamp = getTimestamp();
    	String fullPath = path + "/" + timestamp;
    	Firebase.RTDB.setFloat(&fbdo, fullPath, gndHumidity);
	}
}

void JardiniereDatabase::getDbTemp(){
	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/temperature/degre";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			if (fbdo.floatData() != getEepromTemp()) {
				eepromManager.clearEepromTemp();
				eepromManager.saveEepromTemp(fbdo.floatData());
				display.displayTemp(String(fbdo.floatData(),1));
			}
		}
	}
}

void JardiniereDatabase::sendDbTemp(float temp){
	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/temperature/data";
    	String timestamp = getTimestamp();
    	String fullPath = path + "/" + timestamp;
    	Firebase.RTDB.setFloat(&fbdo, fullPath, temp);
	}
}

void JardiniereDatabase::getDbLum(){
	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/luminosity/lumen";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			if (fbdo.floatData() != getEepromLum()) {
				eepromManager.clearEepromLum();
				eepromManager.saveEepromLum(fbdo.floatData());
				display.displayLum(String(fbdo.floatData(),1));
			}
		}
	}
}

void JardiniereDatabase::sendDbLum(float lum){
	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/luminosity/data";
    	String timestamp = getTimestamp();
    	String fullPath = path + "/" + timestamp;
    	Firebase.RTDB.setFloat(&fbdo, fullPath, lum);
	}
}

void JardiniereDatabase::getDbIntUpd(){

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/interval/update_s";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			long newInterval = (int)(fbdo.floatData()*1000);
			if(newInterval > 0 && newInterval != intervalUpt){
				intervalUpt = newInterval;
			}
			display.displayIntUpd(formatTime(fbdo.floatData()));
		}
	}

}

void JardiniereDatabase::getDbIntSend(){

	if (Firebase.ready() && databaseIsConnect) {
		String path = "/" + String(deviceName) + "/interval/sending_s";
		if (Firebase.RTDB.getFloat(&fbdo, path)) {
			long newInterval = (int)(fbdo.floatData()*1000);
			if(newInterval > 0 && newInterval != intervalSnd){
				intervalSnd = newInterval;
			}
			display.displayIntSend(formatTime(fbdo.floatData()));
		}
	}
}


String JardiniereDatabase::getTimestamp() {
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    return String(epochTime);
}

String JardiniereDatabase::formatTime(long seconds) {
    long days = seconds / 86400;
    seconds %= 86400;
    long hours = seconds / 3600;
    seconds %= 3600;
    long minutes = seconds / 60;
    seconds %= 60;

    String result = "";
    if (days > 0) {
        result += String(days) + "d ";
    }
    if (hours > 0) {
        result += String(hours) + "h ";
    }
    if (minutes > 0) {
        result += String(minutes) + "m ";
    }
    if (seconds > 0) {
        result += String(seconds) + "s ";
    }

    return result;
}