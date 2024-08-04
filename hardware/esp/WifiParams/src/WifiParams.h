#ifndef WIFIPARAMS_H
#define WIFIPARAMS_H

#include <Arduino.h>
#include <Regexp.h>

class WifiParams {
public:
    String ssid;
    String psw;

    WifiParams() {}
    WifiParams(String ssid, String psw);

    String toString() const;
    static WifiParams fromString(const String& str);

};
#endif