#ifndef ESPPARAMS_H
#define ESPPARAMS_H

#include <Arduino.h>
#include <Regexp.h>
#include <UUID.h>

class EspParams {
public:
    String uid;
    String esp_ssid;
    String esp_psw;
    int interval_s;

    EspParams() {}
    EspParams(String uid, String esp_ssid, String esp_psw, int interval_s);

    String toString() const;
    static EspParams fromString(const String& str);
    static String generateRandomID(int length);
    static String generateRandomUUID();
    static String formatTime(int seconds);

};
#endif
