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

    EspParams() {}
    EspParams(String uid, String esp_ssid, String esp_psw);

    String toString() const;
    static EspParams fromString(const String& str);
    static String generateRandomID(int length);
    static String generateRandomUUID();

    String getUid();

};
#endif
