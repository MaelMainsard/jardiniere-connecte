#include "EEPROMManager.h"

EEPROMManager::EEPROMManager() {}

//----------------------------------------------------
//Save, read, clear Air Humidity Value
//----------------------------------------------------

void EEPROMManager::saveEepromAirHum(float value) {
    EEPROM.begin(EEPROM_SIZE);

    String stringValue = String(value);

    for (int i = 0; i < AIR_HUM_ADRESS[1]; ++i) {
        EEPROM.write(AIR_HUM_ADRESS[0] + i, stringValue[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromAirHum(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    int address = AIR_HUM_ADRESS[0];
    String storedValue = "";
    char ch;
    while ((ch = EEPROM.read(address++)) != 0) {
        storedValue += ch;
    }

    if (storedValue.length() > 0) {
        value = storedValue.toFloat();
        return true;
    }
    return false;
}
void EEPROMManager::clearEepromAirHum() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < AIR_HUM_ADRESS[1] ; ++i) {
        EEPROM.write(AIR_HUM_ADRESS[0] + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear Ground Humidity Value
//----------------------------------------------------

void EEPROMManager::saveEepromGndHum(float value) {

    EEPROM.begin(EEPROM_SIZE);

    String stringValue = String(value);

    for (int i = 0; i < GND_HUM_ADRESS[1]; ++i) {
        EEPROM.write(GND_HUM_ADRESS[0] + i, stringValue[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromGndHum(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    int address = GND_HUM_ADRESS[0];
    String storedValue = "";
    char ch;
    while ((ch = EEPROM.read(address++)) != 0) {
        storedValue += ch;
    }

    if (storedValue.length() > 0) {
        value = storedValue.toFloat();
        return true;
    }
    return false;
}
void EEPROMManager::clearEepromGndHum() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < GND_HUM_ADRESS[1]; ++i) {
        EEPROM.write(GND_HUM_ADRESS[0] + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear Temperature Value
//----------------------------------------------------

void EEPROMManager::saveEepromTemp(float value) {

    EEPROM.begin(EEPROM_SIZE);

    String stringValue = String(value);

    for (int i = 0; i < TEMP_ADRESS[1]; ++i) {
        EEPROM.write(TEMP_ADRESS[0] + i, stringValue[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromTemp(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    int address = TEMP_ADRESS[0];
    String storedValue = "";
    char ch;
    while ((ch = EEPROM.read(address++)) != 0) {
        storedValue += ch;
    }

    if (storedValue.length() > 0) {
        value = storedValue.toFloat();
        return true;
    }
    return false;
}
void EEPROMManager::clearEepromTemp() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < TEMP_ADRESS[1]; ++i) {
        EEPROM.write(TEMP_ADRESS[0] + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear Luminosity Value
//----------------------------------------------------

void EEPROMManager::saveEepromLum(float value) {

    EEPROM.begin(EEPROM_SIZE);

    String stringValue = String(value);

    for (int i = 0; i < LUM_ADRESS[1]; ++i) {
        EEPROM.write(LUM_ADRESS[0] + i, stringValue[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromLum(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    int address = LUM_ADRESS[0];
    String storedValue = "";
    char ch;
    while ((ch = EEPROM.read(address++)) != 0) {
        storedValue += ch;
    }

    if (storedValue.length() > 0) {
        value = storedValue.toFloat();
        return true;
    }
    return false;
}
void EEPROMManager::clearEepromLum() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < LUM_ADRESS[1]; ++i) {
        EEPROM.write(LUM_ADRESS[0] + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear ssid & psw
//----------------------------------------------------

void EEPROMManager::saveWiFiCredentials(const String& ssid, const String& password) {
    EEPROM.begin(EEPROM_SIZE);

    int address = SSID_PSW_ADRESS[0];
    for (size_t i = 0; i < ssid.length(); ++i) {
        EEPROM.write(address++, ssid[i]);
    }
    EEPROM.write(address++, 0);

    for (size_t i = 0; i < password.length(); ++i) {
        EEPROM.write(address++, password[i]);
    }
    EEPROM.write(address++, 0);

    EEPROM.commit();
}

bool EEPROMManager::readWiFiCredentials(String& ssid, String& password) {
    EEPROM.begin(EEPROM_SIZE);

    int address = SSID_PSW_ADRESS[0];
    String storedSSID = "";
    char ch;
    while ((ch = EEPROM.read(address++)) != 0) {
        storedSSID += ch;
    }

    String storedPassword = "";
    while ((ch = EEPROM.read(address++)) != 0) {
        storedPassword += ch;
    }

    if (storedSSID.length() > 0 && storedPassword.length() > 0) {
        ssid = storedSSID;
        password = storedPassword;
        return true;
    }
    return false;
}

void EEPROMManager::clearWiFiCredentials() {
    EEPROM.begin(EEPROM_SIZE);

    int address = SSID_PSW_ADRESS[0];
    for (int i = 0; i < SSID_PSW_ADRESS[1]; ++i) {
        EEPROM.write(address++, 0);
    }

    EEPROM.commit();
}
