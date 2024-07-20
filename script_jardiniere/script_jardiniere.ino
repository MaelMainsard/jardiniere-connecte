#include <JardiniereServer.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

JardiniereServer jardiniereServer("Jardiniere_1");

const char* api_key = "AIzaSyBiBaPZsKrFY7om8_myBmOomVgpMgzvF2E";
const char* db_url = "https://jardiniere-b4923-default-rtdb.europe-west1.firebasedatabase.app/";

bool signupOK = false;
bool ledstatus = false;
unsigned long sendDataPrevMillis = 0;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);
  jardiniereServer.begin();
  pinMode(D8, OUTPUT);
  digitalWrite(D8, LOW);
}

void loop() {
  // Handle client requests
  jardiniereServer.loop();

  // Vérifier l'état de la connexion Internet
  if (!jardiniereServer.isConnectedToInternet()) {
    // Si la connexion Internet est perdue, arrêter Firebase
    if (signupOK) {
      signupOK = false;
      Serial.println("Internet connection lost. Stopping Firebase.");
    }
  } else if (!signupOK) {
    config.api_key = api_key;
    config.database_url = db_url;

    if (Firebase.signUp(&config, &auth, "", "")) {
      Serial.println("Sign up ok");
      signupOK = true;
    } else {
      Serial.println(config.signer.signupError.message.c_str());
    }

    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
  }

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    if (Firebase.RTDB.getBool(&fbdo, "/LED/digital")) {
      if (fbdo.dataType() == "boolean") {
        ledstatus = fbdo.boolData();
        if(ledstatus){
            digitalWrite(D8, HIGH);
        }
        else {
            digitalWrite(D8, LOW);
        }
        Serial.println("Successful READ from " + fbdo.dataPath() + ": " + String(ledstatus) + " {" + fbdo.dataType() + "}");
      }
    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    }
  }
}
