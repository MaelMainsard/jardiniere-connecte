#ifndef JARDINIERESERVER_H
#define JARDINIERESERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <LedManager.h>
#include <EEPROMManager.h>

#define DNS_PORT 53
#define MAX_NETWORKS 20

class JardiniereServer {
public:
    JardiniereServer(const String& deviceName);
	void begin();
    void loop();

private:
    String deviceName;
    String availableSSIDs[MAX_NETWORKS];
    int networkCount;

    bool attemptingReconnect;
    unsigned long lastReconnectAttempt;
    const unsigned long reconnectInterval;

    ESP8266WebServer webServer;
    DNSServer dnsServer;
	LedManager ledManager;
    EEPROMManager eepromManager;

    void setupWebServerAndDNS();
    void scanAvailableNetworks();
	void scanAndReconnect();
    void connectToWiFi(const String& ssid, const String& password);

    void handleRootRequest();
    void handleFormSubmission();
    void handleDisconnect();
    void handleNotFound();
    void handleDisconnectPage();

    String generateMainPageHTML();
    String generateDisconnectPageHTML();
};

#endif
