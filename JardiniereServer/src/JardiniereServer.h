#ifndef JARDINIERESERVER_H
#define JARDINIERESERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
#define OLED_RESET -1
#define DNS_PORT 53
#define MAX_NETWORKS 20
#define EEPROM_SIZE 512

class JardiniereServer {
public:
    JardiniereServer(const String& deviceName);
    void begin();
    void loop();
    bool isConnectedToInternet();

private:
    String deviceName;
    String availableSSIDs[MAX_NETWORKS];
    int networkCount;
    Adafruit_SSD1306 display;
    ESP8266WebServer webServer;
    DNSServer dnsServer;

    void resetDisplay();
    void setupWebServerAndDNS();
    void scanAvailableNetworks();
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

#endif // JARDINIERESERVER_H
