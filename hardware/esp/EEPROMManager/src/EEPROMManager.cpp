#include "EEPROMManager.h"

EEPROMManager::EEPROMManager() {}


void EEPROMManager::saveWifiParams(WifiParams params) {
    EEPROM.begin(EEPROM_SIZE);

    String stringValue = params.toString();

    for (int i = 0; i < WIFI_PARAMS_ADRESS[1]; ++i) {
        EEPROM.write(WIFI_PARAMS_ADRESS[0] + i, stringValue[i]);
    }

    EEPROM.commit();
}

bool EEPROMManager::readWifiParams(WifiParams& params) {
    EEPROM.begin(EEPROM_SIZE);

    int address = WIFI_PARAMS_ADRESS[0];
    String storedValue = "";
    char ch;
    while ((ch = EEPROM.read(address++)) != 0) {
        storedValue += ch;
    }

    if (storedValue.length() > 0) {
        params = WifiParams::fromString(storedValue);
        return true;
    }
    return false;
}

void EEPROMManager::clearWifiParams() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < WIFI_PARAMS_ADRESS[1] ; ++i) {
        EEPROM.write(WIFI_PARAMS_ADRESS[0] + i, 0);
    }

    EEPROM.commit();
}

//--------------------------------------------------------------

void EEPROMManager::saveEspParams(EspParams params) {
    EEPROM.begin(EEPROM_SIZE);

    String stringValue = params.toString();

    for (int i = 0; i < ESP_PARAMS_ADRESS[1]; ++i) {
        EEPROM.write(ESP_PARAMS_ADRESS[0] + i, stringValue[i]);
    }

    EEPROM.commit();
}

bool EEPROMManager::readEspParams(EspParams& params) {
    EEPROM.begin(EEPROM_SIZE);

    int address = ESP_PARAMS_ADRESS[0];
    String storedValue = "";
    char ch;
    while ((ch = EEPROM.read(address++)) != 0) {
        storedValue += ch;
    }

    if (storedValue.length() > 0) {
        params = EspParams::fromString(storedValue);
        return true;
    }
    return false;
}

void EEPROMManager::clearEspParams() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < ESP_PARAMS_ADRESS[1] ; ++i) {
        EEPROM.write(ESP_PARAMS_ADRESS[0] + i, 0);
    }

    EEPROM.commit();
}
