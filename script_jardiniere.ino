#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <EEPROM.h> // Include EEPROM library

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
#define OLED_RESET -1

const String DEVICE_NAME = "Jardiniere1";
const byte DNS_PORT = 53;
const int MAX_NETWORKS = 20;
const int EEPROM_SIZE = 512; // Define EEPROM size

String availableSSIDs[MAX_NETWORKS];
int networkCount = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ESP8266WebServer webServer(80);
DNSServer dnsServer;

/**
 * Initializes the web server and DNS server.
 */
void setupWebServerAndDNS() {
  initializeDisplay();
  WiFi.softAP(DEVICE_NAME);
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
  
  webServer.on("/", handleRootRequest);
  webServer.on("/disconnect", handleDisconnectPage);
  webServer.on("/disconnect_action", handleDisconnect);
  webServer.on("/submit", HTTP_POST, handleFormSubmission);
  webServer.onNotFound(handleNotFound);
  webServer.begin();
}

/**
 * Initializes the OLED display.
 */
void initializeDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

/**
 * Scans for available WiFi networks and stores their SSIDs.
 */
void scanAvailableNetworks() {
  networkCount = WiFi.scanNetworks();
  for (int i = 0; i < networkCount && i < MAX_NETWORKS; ++i) {
    availableSSIDs[i] = WiFi.SSID(i);
  }
}

/**
 * Attempts to connect to a specified WiFi network.
 * @param ssid SSID of the network
 * @param password Password for the network
 */
void connectToWiFi(const String& ssid, const String& password) {
  initializeDisplay();
  display.println("Connecting to WiFi");
  display.display();
  
  WiFi.begin(ssid.c_str(), password.c_str());
  int attempt = 0;
  
  while (WiFi.status() != WL_CONNECTED && attempt < 20) {
    delay(500);
    display.print(".");
    display.display();
    attempt++;
  }

  initializeDisplay();
  if (WiFi.status() == WL_CONNECTED) {
    display.println("Connected to WiFi: " + WiFi.SSID());
    display.display();
    saveWiFiCredentials(ssid, password); // Save SSID and password to EEPROM
    webServer.sendHeader("Location", "/disconnect");
    webServer.send(302, "text/plain", "");
  } else {
    display.println("Failed to connect to WiFi.");
    display.display();
    delay(3000);
    initializeDisplay();
    display.println("Connect to this WiFi to configure the device.");
    display.display();
    webServer.sendHeader("Location", "/");
    webServer.send(302, "text/plain", "");
  }
}

/**
 * Saves the SSID and password to EEPROM.
 * @param ssid SSID of the network
 * @param password Password for the network
 */
void saveWiFiCredentials(const String& ssid, const String& password) {
  EEPROM.begin(EEPROM_SIZE);
  
  // Save SSID
  int address = 0;
  for (size_t i = 0; i < ssid.length(); ++i) {
    EEPROM.write(address++, ssid[i]);
  }
  EEPROM.write(address++, 0); // Null-terminate the SSID
  
  // Save password
  for (size_t i = 0; i < password.length(); ++i) {
    EEPROM.write(address++, password[i]);
  }
  EEPROM.write(address++, 0); // Null-terminate the password
  
  EEPROM.commit();
}

/**
 * Reads SSID and password from EEPROM.
 * @param ssid Reference to the String to store the SSID
 * @param password Reference to the String to store the password
 * @return true if credentials are read successfully, false otherwise
 */
bool readWiFiCredentials(String &ssid, String &password) {
  EEPROM.begin(EEPROM_SIZE);
  
  // Read SSID
  int address = 0;
  String storedSSID = "";
  char ch;
  while ((ch = EEPROM.read(address++)) != 0) {
    storedSSID += ch;
  }
  
  // Read password
  String storedPassword = "";
  while ((ch = EEPROM.read(address++)) != 0) {
    storedPassword += ch;
  }
  
  // Check if credentials are valid
  if (storedSSID.length() > 0 && storedPassword.length() > 0) {
    ssid = storedSSID;
    password = storedPassword;
    return true;
  }
  return false;
}

/**
 * Clears SSID and password from EEPROM.
 */
void clearWiFiCredentials() {
  EEPROM.begin(EEPROM_SIZE);
  
  // Clear SSID
  int address = 0;
  for (int i = 0; i < EEPROM_SIZE; ++i) {
    EEPROM.write(address++, 0);
  }
  
  EEPROM.commit();
}

/**
 * Handles WiFi disconnection.
 */
void handleDisconnect() {
  if (WiFi.status() == WL_CONNECTED) {
    initializeDisplay();
    WiFi.disconnect();
    display.println("WiFi disconnected.");
    display.display();
    delay(3000);
    initializeDisplay();
    display.println("Connect to this WiFi to configure the device.");
    display.display();
    
    clearWiFiCredentials(); // Clear stored credentials
  }
  webServer.sendHeader("Location", "/");
  webServer.send(302, "text/plain", "");
}

/**
 * Handles form submission for WiFi connection.
 */
void handleFormSubmission() {
  String ssid = webServer.arg("ssid");
  String password = webServer.arg("password");
  connectToWiFi(ssid, password);
}

/**
 * Generates the HTML for the main page.
 * @return HTML content as a String
 */
String generateMainPageHTML() {
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

/**
 * Generates the HTML for the disconnect page.
 * @return HTML content as a String
 */
String generateDisconnectPageHTML() {
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

/**
 * Handles the root request and provides the main page or redirects if connected.
 */
void handleRootRequest() {
  if (WiFi.status() == WL_CONNECTED) {
    webServer.sendHeader("Location", "/disconnect");
    webServer.send(302, "text/plain", "");
  } else {
    webServer.send(200, "text/html", generateMainPageHTML());
  }
}

/**
 * Handles requests to pages that do not exist.
 */
void handleNotFound() {
  if (WiFi.status() == WL_CONNECTED) {
    webServer.sendHeader("Location", "/disconnect");
    webServer.send(302, "text/plain", "");
  } else {
    handleRootRequest();
  }
}

/**
 * Handles the disconnect page request.
 */
void handleDisconnectPage() {
  webServer.send(200, "text/html", generateDisconnectPageHTML());
}

/**
 * Setup function for initializing the WiFi and web server.
 */
void setup() {
  scanAvailableNetworks();
  setupWebServerAndDNS();
  
  String ssid, password;
  if (readWiFiCredentials(ssid, password)) {
    connectToWiFi(ssid, password);
  } else {
    display.println("Connect to this WiFi to configure the device.");
    display.display();
  }
}

/**
 * Main loop for processing web server and DNS requests.
 */
void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
