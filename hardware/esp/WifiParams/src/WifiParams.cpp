#include "WifiParams.h"

WifiParams::WifiParams(String ssid, String psw)
    : ssid(ssid), psw(psw) {}

String WifiParams::toString() const {
    return "ssid="+ssid+"###psw="+psw+"###";
}

WifiParams WifiParams::fromString(const String& str) {
    WifiParams params;

    char ssidArray[30];
    char pswArray[100];

    MatchState ms;

    char buffer[256];
    strncpy(buffer, str.c_str(), sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    ms.Target(buffer);


    ms.Match ("ssid=([^###]*)");
    ms.GetCapture(ssidArray, 0);
    params.ssid = String(ssidArray);

    ms.Match ("psw=([^###]*)");
    ms.GetCapture(pswArray, 0);
    params.psw = String(pswArray);


    return params;
}