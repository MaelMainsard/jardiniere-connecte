#include "JardiniereServer.h"

JardiniereServer::JardiniereServer()
    : ledManager(D6, D7),eepromManager(),attemptingReconnect(false),lastReconnectAttempt(0),reconnectInterval(60000),webServer(80){}


void JardiniereServer::init(){

    EspParams params;
    if(!eepromManager.readEspParams(params)){
        String uid = EspParams::generateRandomUUID();
        String esp_ssid = "planter-"+EspParams::generateRandomID(6);
        String esp_psw = EspParams::generateRandomID(8);
        int interval_s = 60;

        EspParams newParams = EspParams(uid,esp_ssid,esp_psw,interval_s);

        eepromManager.saveEspParams(newParams);
    }

}



void JardiniereServer::begin(){
    Serial.begin(115200);
    init();
    setupWebServerAndDNS();
    scanAvailableNetworks();
    scanAndReconnect();
}

void JardiniereServer::loop() {

    dnsServer.processNextRequest();
    webServer.handleClient();

    WifiParams params;
    if (WiFi.status() != WL_CONNECTED && eepromManager.readWifiParams(params)) {
        unsigned long currentMillis = millis();
        if (!attemptingReconnect && (currentMillis - lastReconnectAttempt >= reconnectInterval)) {
            attemptingReconnect = true;
            lastReconnectAttempt = currentMillis;
            scanAndReconnect();
            attemptingReconnect = false;
        }
    }
    else if(WiFi.status() != WL_CONNECTED && !eepromManager.readWifiParams(params)){
        ledManager.notConnectedToWifi();
    }
    else if(WiFi.status() != WL_CONNECTED){
        ledManager.isConnectedToWifi();
    }
    else if(WiFi.status() != WL_CONNECTED){
        ledManager.notConnectedToWifi();
    }

}



void JardiniereServer::scanAndReconnect() {
    WifiParams params;
    if (eepromManager.readWifiParams(params)) {
        connectToWiFi(params);
    }
}

void JardiniereServer::setupWebServerAndDNS() {
    WiFi.softAPdisconnect(true);
    EspParams params;
    eepromManager.readEspParams(params);
    WiFi.softAP(params.esp_ssid, params.esp_psw);
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

void JardiniereServer::connectToWiFi(const WifiParams& params) {
    ledManager.tryingToConnectToWifi();

    WiFi.begin(params.ssid.c_str(), params.psw.c_str());
    int attempt = 0;

    while (WiFi.status() != WL_CONNECTED && attempt < 60) {
        delay(500);
        attempt++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        eepromManager.saveWifiParams(params);
        webServer.sendHeader("Location", "/disconnect");
        webServer.send(302, "text/plain", "");
    } else {
        ledManager.notConnectedToWifi();
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/plain", "");
    }
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
    WifiParams params = {ssid,password};
    connectToWiFi(params);
}

void JardiniereServer::handleDisconnect() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.disconnect();
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/plain", "");
        eepromManager.clearWifiParams();
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
                 "<label for=\"ssid\">SSID:</label>"
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
            "<label for=\"password\">Password:</label>"
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