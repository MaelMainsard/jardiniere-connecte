#ifndef EEPROMMANAGER_H
#define EEPROMMANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 512

class EEPROMManager {
public:
    EEPROMManager();

    const int SSID_PSW_ADRESS[2] = {0,99};
    const int AIR_HUM_ADRESS[2] = {100,149};
    const int GND_HUM_ADRESS[2] = {150,199};
    const int TEMP_ADRESS[2] = {200,249};
    const int LUM_ADRESS[2] = {250,299};

    void saveWiFiCredentials(const String& ssid, const String& password);
    bool readWiFiCredentials(String& ssid, String& password);
    void clearWiFiCredentials();

    void saveEepromAirHum(float value);
    bool readEepromAirHum(float& value);
    void clearEepromAirHum();

    void saveEepromGndHum(float value);
    bool readEepromGndHum(float& value);
    void clearEepromGndHum();

    void saveEepromTemp(float value);
    bool readEepromTemp(float& value);
    void clearEepromTemp();

    void saveEepromLum(float value);
    bool readEepromLum(float& value);
    void clearEepromLum();


private:

};

#endif