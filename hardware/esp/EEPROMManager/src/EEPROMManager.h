#ifndef EEPROMMANAGER_H
#define EEPROMMANAGER_H

#include <Arduino.h>
#include <EEPROM.h>
#include <EspParams.h>
#include <WifiParams.h>

#define EEPROM_SIZE 512

class EEPROMManager {
public:
    EEPROMManager();

    const int WIFI_PARAMS_ADRESS[2] = {0,99};
    const int ESP_PARAMS_ADRESS[2] = {100,199};
    const int DATABASE_PARAMS_ADRESS[2] = {200,299};

    void saveWifiParams(WifiParams params);
    bool readWifiParams(WifiParams& params);
    void clearWifiParams();

    void saveEspParams(EspParams params);
    bool readEspParams(EspParams& params);
    void clearEspParams();


private:

};

#endif