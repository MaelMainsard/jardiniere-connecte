#ifndef JARDINIERESERVER_H
#define JARDINIERESERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <EEPROMManager.h>
#include <EspParams.h>
#include <WifiParams.h>
#include <FS.h>

#define DNS_PORT 53

class JardiniereServer {
public:
    JardiniereServer();
	void begin();
    void loop();

private:

    ESP8266WebServer webServer;
    DNSServer dnsServer;
    EEPROMManager eepromManager;

	void init();
    void setupWebServerAndDNS();

    void connectToWiFi(WifiParams params);
    void handleWifiLogin();
    void handleWifiLogout();

    void handleDisconnect();
    String getSsidArray();
    void handleRoot();
    void handleNotFound();
};

#endif
