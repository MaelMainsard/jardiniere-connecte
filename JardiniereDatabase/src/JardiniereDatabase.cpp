#include "JardiniereDatabase.h"

JardiniereDatabase::JardiniereDatabase(const char* deviceName)
  : device_name(deviceName),display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), signupOK(false), timeClient(ntpUDP) {}

void JardiniereDatabase::begin() {
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    timeClient.begin();
}

void JardiniereDatabase::loop() {
    if (WiFi.status() != WL_CONNECTED) {
        if (signupOK) {
            signupOK = false;
        }
    } else if (!signupOK) {
        resetDisplay();
        config.api_key = api_key;
        config.database_url = db_url;

        if (Firebase.signUp(&config, &auth, "", "")) {
            display.println("Successfuly connected to database.");
            display.display();
            signupOK = true;
            delay(2000);
            resetDisplay();
        } else {
            display.println("Failed to connect database.");
            display.display();
            signupOK = false;
        }

        Firebase.begin(&config, &auth);
    }
}

void JardiniereDatabase::resetDisplay() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.display();
}

void JardiniereDatabase::sendHumidityData(float humidity) {
    String path = "/" + String(device_name) + "/humidity/data";
    String timestamp = getTimestamp();
    String fullPath = path + "/" + timestamp;
    Firebase.RTDB.setString(&fbdo, fullPath, String(humidity, 1))
}

String JardiniereDatabase::getTimestamp() {
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    return String(epochTime);
}