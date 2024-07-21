#include "JardiniereDatabase.h"

JardiniereDatabase::JardiniereDatabase(const String& deviceName)
  : deviceName(deviceName), databaseIsConnect(false), timeClient(ntpUDP), display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void JardiniereDatabase::begin() {
	display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
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

	clearDisplay();

	if(databaseIsConnect){
		display.println("Connected to Database");
		display.display();
	} else {
		display.println("Disconnected from Database");
		display.display();
	}

}

void JardiniereDatabase::clearDisplay() {
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
	display.display();
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