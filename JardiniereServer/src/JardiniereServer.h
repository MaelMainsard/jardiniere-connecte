#ifndef JARDINIERESERVER_H
#define JARDINIERESERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include <LedManager.h>

#define DNS_PORT 53
#define MAX_NETWORKS 20
#define EEPROM_SIZE 512

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

    void setupWebServerAndDNS();
    void scanAvailableNetworks();
	void scanAndReconnect();
    void connectToWiFi(const String& ssid, const String& password);
    void saveWiFiCredentials(const String& ssid, const String& password);
    bool readWiFiCredentials(String& ssid, String& password);
    void clearWiFiCredentials();

    void handleRootRequest();
    void handleFormSubmission();
    void handleDisconnect();
    void handleNotFound();
    void handleDisconnectPage();

    String generateMainPageHTML();
    String generateDisconnectPageHTML();
};

#endif
