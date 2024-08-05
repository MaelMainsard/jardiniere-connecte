#include "EspParams.h"

EspParams::EspParams(String uid, String esp_ssid, String esp_psw, int interval_s)
    : uid(uid), esp_ssid(esp_ssid), esp_psw(esp_psw), interval_s(interval_s) {}

String EspParams::toString() const {
    return "uid="+uid+"esp_ssid="+esp_ssid+"esp_psw="+esp_psw+"interval_s="+String(interval_s);
}

EspParams EspParams::fromString(const String& str) {

    EspParams params;

    char uidArray[40];
    char espSsidArray[30];
    char espPswArray[10];
    char intervalArray[200];

    MatchState ms;

    char buffer[256];
    strncpy(buffer, str.c_str(), sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    ms.Target(buffer);


    ms.Match ("uid=([^ ]*)esp_ssid");
    ms.GetCapture(uidArray, 0);
    params.uid = String(uidArray);

    ms.Match ("esp_ssid=([^ ]*)esp_psw");
    ms.GetCapture(espSsidArray, 0);
    params.esp_ssid = String(espSsidArray);

    ms.Match ("esp_psw=([^ ]*)interval_s");
    ms.GetCapture(espPswArray, 0);
    params.esp_psw = String(espPswArray);

    ms.Match ("interval_s=(.*)");
    ms.GetCapture(intervalArray, 0);
    params.interval_s = atoi(intervalArray);

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

String EspParams::formatTime(int seconds) {
    long days = seconds / 86400;
    seconds %= 86400;
    long hours = seconds / 3600;
    seconds %= 3600;
    long minutes = seconds / 60;
    seconds %= 60;

    String result = "";
    if (days > 0) {
        result += String(days) + "d ";
    }
    if (hours > 0) {
        result += String(hours) + "h ";
    }
    if (minutes > 0) {
        result += String(minutes) + "m ";
    }
    if (seconds > 0) {
        result += String(seconds) + "s ";
    }

    return result;
}
