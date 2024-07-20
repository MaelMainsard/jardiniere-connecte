#include "JardiniereServer.h"

JardiniereServer::JardiniereServer(const String& deviceName)
    : deviceName(deviceName), display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), webServer(80) {}

void JardiniereServer::begin() {
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    scanAvailableNetworks();
    setupWebServerAndDNS();

    String ssid, password;
    if (readWiFiCredentials(ssid, password)) {
        connectToWiFi(ssid, password);
    } else {
		resetDisplay();
        display.println("Connect to this WiFi to configure the device.");
        display.display();
    }
}

void JardiniereServer::loop() {
    dnsServer.processNextRequest();
    webServer.handleClient();
}

void JardiniereServer::resetDisplay() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.display();
}

void JardiniereServer::setupWebServerAndDNS() {
    resetDisplay();
    WiFi.softAP(deviceName);
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

    webServer.on("/", std::bind(&JardiniereServer::handleRootRequest, this));
    webServer.on("/disconnect", std::bind(&JardiniereServer::handleDisconnectPage, this));
    webServer.on("/disconnect_action", std::bind(&JardiniereServer::handleDisconnect, this));
    webServer.on("/submit", HTTP_POST, std::bind(&JardiniereServer::handleFormSubmission, this));
    webServer.onNotFound(std::bind(&JardiniereServer::handleNotFound, this));
    webServer.begin();
}

void JardiniereServer::scanAvailableNetworks() {
    networkCount = WiFi.scanNetworks();
    for (int i = 0; i < networkCount && i < MAX_NETWORKS; ++i) {
        availableSSIDs[i] = WiFi.SSID(i);
    }
}

void JardiniereServer::connectToWiFi(const String& ssid, const String& password) {
    resetDisplay();
    display.println("Connecting to WiFi");
    display.display();

    WiFi.begin(ssid.c_str(), password.c_str());
    int attempt = 0;

    while (WiFi.status() != WL_CONNECTED && attempt < 30) {
        delay(500);
        display.print(".");
        display.display();
        attempt++;
    }

    resetDisplay();
    if (WiFi.status() == WL_CONNECTED) {
        display.println("Connected to WiFi: " + WiFi.SSID());
        display.display();
        saveWiFiCredentials(ssid, password);
        webServer.sendHeader("Location", "/disconnect");
        webServer.send(302, "text/plain", "");
		delay(3000);
		resetDisplay();
    } else {
        display.println("Failed to connect to WiFi.");
        display.display();
        delay(3000);
        resetDisplay();
        display.println("Connect to this WiFi to configure the device.");
        display.display();
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/plain", "");
    }
}

void JardiniereServer::saveWiFiCredentials(const String& ssid, const String& password) {
    EEPROM.begin(EEPROM_SIZE);

    int address = 0;
    for (size_t i = 0; i < ssid.length(); ++i) {
        EEPROM.write(address++, ssid[i]);
    }
    EEPROM.write(address++, 0);

    for (size_t i = 0; i < password.length(); ++i) {
        EEPROM.write(address++, password[i]);
    }
    EEPROM.write(address++, 0);

    EEPROM.commit();
}

bool JardiniereServer::readWiFiCredentials(String& ssid, String& password) {
    EEPROM.begin(EEPROM_SIZE);

    int address = 0;
    String storedSSID = "";
    char ch;
    while ((ch = EEPROM.read(address++)) != 0) {
        storedSSID += ch;
    }

    String storedPassword = "";
    while ((ch = EEPROM.read(address++)) != 0) {
        storedPassword += ch;
    }

    if (storedSSID.length() > 0 && storedPassword.length() > 0) {
        ssid = storedSSID;
        password = storedPassword;
        return true;
    }
    return false;
}

void JardiniereServer::clearWiFiCredentials() {
    EEPROM.begin(EEPROM_SIZE);

    int address = 0;
    for (int i = 0; i < EEPROM_SIZE; ++i) {
        EEPROM.write(address++, 0);
    }

    EEPROM.commit();
}

void JardiniereServer::handleRootRequest() {
    if (WiFi.status() == WL_CONNECTED) {
        webServer.sendHeader("Location", "/disconnect");
        webServer.send(302, "text/plain", "");
    } else {
        webServer.send(200, "text/html", generateMainPageHTML());
    }
}

void JardiniereServer::handleFormSubmission() {
    String ssid = webServer.arg("ssid");
    String password = webServer.arg("password");
    connectToWiFi(ssid, password);
}

void JardiniereServer::handleDisconnect() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.disconnect();
		resetDisplay();
        display.println("WiFi Disconnect.");
        display.display();
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/plain", "");
		delay(3000);
 		resetDisplay();
        display.println("Connect to this WiFi to configure the device.");
        display.display();
        clearWiFiCredentials();
    }
}

void JardiniereServer::handleNotFound() {
    if (WiFi.status() == WL_CONNECTED) {
        webServer.sendHeader("Location", "/disconnect");
        webServer.send(302, "text/plain", "");
    } else {
        handleRootRequest();
    }
}

void JardiniereServer::handleDisconnectPage() {
    webServer.send(200, "text/html", generateDisconnectPageHTML());
}

bool JardiniereServer::isConnectedToInternet() {
    return WiFi.status() == WL_CONNECTED;
}

String JardiniereServer::generateMainPageHTML() {
    String html = "<!DOCTYPE html>"
                  "<html>"
                  "<head><title>ESP8266 Configuration</title>"
                  "<style>"
                  "body { font-family: Arial, sans-serif; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; background-color: #f0f0f0; }"
                  ".form-container { background-color: white; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }"
                  ".form-group { margin-bottom: 15px; }"
                  "label { display: block; margin-bottom: 5px; }"
                  "input[type=\"text\"], input[type=\"password\"] { width: 100%; padding: 8px; border: 1px solid #ccc; border-radius: 4px; }"
                  "button { padding: 10px 15px; background-color: #007bff; color: white; border: none; border-radius: 4px; cursor: pointer; }"
                  "button:hover { background-color: #0056b3; }"
                  "</style>"
                  "</head>"
                  "<body>"
                  "<div class=\"form-container\">"
                  "<form action=\"/submit\" method=\"post\">"
                  "<div class=\"form-group\">"
                  "<label for=\"ssid\">SSID :</label>"
                  "<select id=\"ssid\" name=\"ssid\" required>";

    if (networkCount > 0) {
        for (int i = 0; i < networkCount && i < MAX_NETWORKS; ++i) {
            html += "<option value=\"" + availableSSIDs[i] + "\">" + availableSSIDs[i] + "</option>";
        }
    } else {
        html += "<option value=\"\">No networks found</option>";
    }

    html += "</select>"
            "</div>"
            "<div class=\"form-group\">"
            "<label for=\"password\">Password :</label>"
            "<input type=\"password\" id=\"password\" name=\"password\" required>"
            "</div>"
            "<button type=\"submit\">Submit</button>"
            "</form>"
            "</div>"
            "</body>"
            "</html>";

    return html;
}

String JardiniereServer::generateDisconnectPageHTML() {
    String html = "<!DOCTYPE html>"
                  "<html>"
                  "<head><title>Disconnect</title>"
                  "<style>"
                  "body { font-family: Arial, sans-serif; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; background-color: #f0f0f0; }"
                  ".button-container { background-color: white; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }"
                  "button { padding: 10px 20px; background-color: #dc3545; color: white; border: none; border-radius: 4px; cursor: pointer; }"
                  "button:hover { background-color: #c82333; }"
                  "</style>"
                  "<script>"
                  "function disconnect() {"
                  "    fetch('/disconnect_action').then(response => {"
                  "        if (response.ok) {"
                  "            window.location.href = '/';"
                  "        } else {"
                  "            alert('Error disconnecting.');"
                  "        }"
                  "    });"
                  "}"
                  "</script>"
                  "</head>"
                  "<body>"
                  "<div class=\"button-container\">"
                  "<button onclick=\"disconnect()\">Disconnect</button>"
                  "</div>"
                  "</body>"
                  "</html>";

    return html;
}
