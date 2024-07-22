#ifndef EEPROMMANAGER_H
#define EEPROMMANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 512

class EEPROMManager {
public:
    EEPROMManager();
    void saveWiFiCredentials(const String& ssid, const String& password);
    bool readWiFiCredentials(String& ssid, String& password);
    void clearWiFiCredentials();

    void saveEepromTemp(const float value);
    bool readEepromTemp(float& value);
    void clearEepromTemp();

    void saveEepromLum(const float value);
    bool readEepromLum(float& value);
    void clearEepromLum();

    void saveEepromHum(const float value);
    bool readEepromHum(float& value);
    void clearEepromHum();

    void saveEepromInt(const float value);
    bool readEepromInt(float& value);
    void clearEepromInt();

private:

};

#endif