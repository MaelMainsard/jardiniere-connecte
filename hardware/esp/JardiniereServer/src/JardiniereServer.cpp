#include "JardiniereServer.h"

JardiniereServer::JardiniereServer()
    : eepromManager(), webServer(80){
        pinMode(LED_BUILTIN,OUTPUT);
    }


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
    init();
    Serial.begin(115200);
    SPIFFS.begin();
    setupWebServerAndDNS();
}

void JardiniereServer::loop() {
    dnsServer.processNextRequest();
    webServer.handleClient();

    WifiParams params;
    if (eepromManager.readWifiParams(params) && WiFi.status() != WL_CONNECTED) {
        connectToWiFi(params);
    }

    if(WiFi.status() == WL_CONNECTED){
        digitalWrite(LED_BUILTIN,LOW);
    }
    else {
        digitalWrite(LED_BUILTIN,HIGH);
    }
}


void JardiniereServer::connectToWiFi(WifiParams params) {

    WiFi.begin(params.ssid.c_str(), params.psw.c_str());
    int attempt = 0;

    while (WiFi.status() != WL_CONNECTED && attempt < 60) {
        delay(500);
        attempt++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        eepromManager.saveWifiParams(params);
        webServer.sendHeader("Location", "/logout");
        webServer.send(302, "text/plain", "");
    } else {
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/plain", "");
    }
}




void JardiniereServer::setupWebServerAndDNS() {
    WiFi.softAPdisconnect(true);
    EspParams params;
    eepromManager.readEspParams(params);
    WiFi.softAP(params.esp_ssid);
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
    webServer.on("/", HTTP_GET, std::bind(&JardiniereServer::handleRoot, this));
    webServer.on("/logout", HTTP_GET,  std::bind(&JardiniereServer::handleDisconnect, this));
    webServer.on("/wifiLogin", HTTP_POST, std::bind(&JardiniereServer::handleWifiLogin, this));
    webServer.on("/wifiLogout", HTTP_POST, std::bind(&JardiniereServer::handleWifiLogout, this));
    webServer.onNotFound(std::bind(&JardiniereServer::handleNotFound, this));
    webServer.begin();
}

void JardiniereServer::handleWifiLogout() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.disconnect();
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/plain", "");
        eepromManager.clearWifiParams();
    }
}

void JardiniereServer::handleWifiLogin() {
    String ssid = webServer.arg("ssid");
    String password = webServer.arg("password");
    WifiParams params = {ssid,password};
    connectToWiFi(params);
}


String JardiniereServer::getSsidArray() {
    String ssid_array = "[";
    int numNetworks = WiFi.scanNetworks();

    for (int i = 0; i < numNetworks; ++i) {
        ssid_array += "\"" + WiFi.SSID(i) + "\"";
        if (i < numNetworks - 1) {
            ssid_array += ",";
        }
    }

    return ssid_array += "]";
}


void JardiniereServer::handleRoot() {
    WifiParams params;
    if(eepromManager.readWifiParams(params)){
        webServer.sendHeader("Location", "/logout");
        webServer.send(302, "text/plain", "");
    }
    else {
        File file = SPIFFS.open("/WifiLogin.html", "r");
        if (!file) {
            webServer.send(404, "text/plain", "Fichier non trouvé");
            return;
        }
        String htmlContent = file.readString();
        htmlContent.replace("{{network_array}}", getSsidArray());
        webServer.send(200, "text/html", htmlContent);
        file.close();
    }
}

void JardiniereServer::handleDisconnect() {
    File file = SPIFFS.open("/WifiLogout.html", "r");
    if (!file) {
        webServer.send(404, "text/plain", "Fichier non trouvé");
        return;
    }
    String htmlContent = file.readString();
    WifiParams params;
    eepromManager.readWifiParams(params);
    htmlContent.replace("{{ssid_name}}", params.ssid);
    webServer.send(200, "text/html", htmlContent);
    file.close();
}

void JardiniereServer::handleNotFound() {
  webServer.sendHeader("Location", String("http://") + WiFi.softAPIP().toString(), true);
  webServer.send(302, "text/plain", ""); // Redirection
}