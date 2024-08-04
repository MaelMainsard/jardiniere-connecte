#include "EspParams.h"

EspParams::EspParams(String uid, String esp_ssid, String esp_psw)
    : uid(uid), esp_ssid(esp_ssid), esp_psw(esp_psw) {}

String EspParams::toString() const {
    return "uid="+uid+"###esp_ssid="+esp_ssid+"###esp_psw="+esp_psw+"###";
}

String EspParams::getUid(){
    return uid;
}

EspParams EspParams::fromString(const String& str) {
    EspParams params;

    char uidArray[40];
    char espSsidArray[30];
    char espPswArray[10];

    MatchState ms;

    char buffer[256];
    strncpy(buffer, str.c_str(), sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    ms.Target(buffer);


    ms.Match ("uid=([^###]*)");
    ms.GetCapture(uidArray, 0);
    params.uid = String(uidArray);

    ms.Match ("esp_ssid=([^###]*)");
    ms.GetCapture(espSsidArray, 0);
    params.esp_ssid = String(espSsidArray);

    ms.Match ("esp_psw=([^###]*)");
    ms.GetCapture(espPswArray, 0);
    params.esp_psw = String(espPswArray);


    return params;

}

String EspParams::generateRandomID(int length) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int numCharacters = sizeof(characters) - 1; // -1 pour exclure le caractère '\0'

    String id = "";
    for (int i = 0; i < length; i++) {
        char randomChar = characters[random(numCharacters)];
        id += randomChar;
    }

    return id;
}

String EspParams::generateRandomUUID() { // Corrected spelling
    UUID uuid;
    uuid.generate();
    return String(uuid.toCharArray());
}
