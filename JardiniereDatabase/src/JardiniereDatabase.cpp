#include "JardiniereDatabase.h"

JardiniereDatabase::JardiniereDatabase(const String& deviceName)
  : deviceName(deviceName), databaseIsConnect(false), timeClient(ntpUDP), display() {}

void JardiniereDatabase::begin() {
	display.init();
    timeClient.begin();
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

String JardiniereDatabase::getTimestamp() {
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    return String(epochTime);
}