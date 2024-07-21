#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <EEPROM.h>

const String DEVICE_NAME = "Jardiniere1";
const byte DNS_PORT = 53;
const int MAX_NETWORKS = 20;
const int EEPROM_SIZE = 512;

String availableSSIDs[MAX_NETWORKS];
int networkCount = 0;
bool attemptingReconnect = false;
unsigned long lastReconnectAttempt = 0;
const unsigned long reconnectInterval = 30000; // 30 secondes

ESP8266WebServer webServer(80);
DNSServer dnsServer;


void setupWebServerAndDNS() {
  WiFi.softAP(DEVICE_NAME);
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  webServer.on("/", handleRootRequest);
  webServer.on("/disconnect", handleDisconnectPage);
  webServer.on("/disconnect_action", handleDisconnect);
  webServer.on("/submit", HTTP_POST, handleFormSubmission);
  webServer.onNotFound(handleNotFound);
  webServer.begin();
}

void scanAvailableNetworks() {
  networkCount = WiFi.scanNetworks();
  for (int i = 0; i < networkCount && i < MAX_NETWORKS; ++i) {
    availableSSIDs[i] = WiFi.SSID(i);
  }
}

void connectToWiFi(const String& ssid, const String& password) {
  
  WiFi.begin(ssid.c_str(), password.c_str());
  int attempt = 0;

  while (WiFi.status() != WL_CONNECTED && attempt < 20) {
    delay(500);
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    saveWiFiCredentials(ssid, password);
    webServer.sendHeader("Location", "/disconnect");
    webServer.send(302, "text/plain", "");
  } else {
    webServer.sendHeader("Location", "/");
    webServer.send(302, "text/plain", "");
  }
}


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
    WiFi.disconnect();
  }
  clearWiFiCredentials();
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

void scanAndReconnect() {
  String ssid, password;
  if (readWiFiCredentials(ssid, password)) {
    Serial.println("Tentative de reconnexion avec les identifiants sauvegardés");
    connectToWiFi(ssid, password);
  }
}

void setup() {
  Serial.begin(115200);
  setupWebServerAndDNS();
  scanAvailableNetworks();
  scanAndReconnect();
}

/**
 * Main loop for processing web server and DNS requests.
 */
void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
  
  String ssid, password;
  if (WiFi.status() != WL_CONNECTED && readWiFiCredentials(ssid, password)) {
    unsigned long currentMillis = millis();
    if (!attemptingReconnect && (currentMillis - lastReconnectAttempt >= reconnectInterval)) {
      attemptingReconnect = true;
      lastReconnectAttempt = currentMillis;
      
      Serial.println("WiFi non connecté, tentative de reconnexion...");
      scanAndReconnect();
      
      attemptingReconnect = false;
    }
  }
}
