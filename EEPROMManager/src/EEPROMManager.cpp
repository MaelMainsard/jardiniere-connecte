#include "EEPROMManager.h"

EEPROMManager::EEPROMManager() {}

void EEPROMManager::saveWiFiCredentials(const String& ssid, const String& password) {
    EEPROM.begin(EEPROM_SIZE);

    int address = 0;
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

    int address = 0;
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

    int address = 0;
    for (int i = 0; i < EEPROM_SIZE; ++i) {
        EEPROM.write(address++, 0);
    }

    EEPROM.commit();
}

void EEPROMManager::saveEepromTemp(float value) {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 100;
    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(startAddress + i, bytePointer[i]);
    }

    EEPROM.commit();
}

bool EEPROMManager::readEepromTemp(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 100;
    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        bytePointer[i] = EEPROM.read(startAddress + i);
    }

    for (int i = 0; i < sizeof(float); ++i) {
        if (bytePointer[i] == 0xFF) {
            return false;
        }
    }

    return true;
}

void EEPROMManager::clearEepromTemp() {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 100;
    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(startAddress + i, 0);
    }

    EEPROM.commit();
}

//------------------------------------------------------------------------

void EEPROMManager::saveEepromLum(float value) {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 200;
    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(startAddress + i, bytePointer[i]);
    }

    EEPROM.commit();
}

bool EEPROMManager::readEepromLum(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 200;
    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        bytePointer[i] = EEPROM.read(startAddress + i);
    }

    for (int i = 0; i < sizeof(float); ++i) {
        if (bytePointer[i] == 0xFF) {
            return false;
        }
    }

    return true;
}

void EEPROMManager::clearEepromLum() {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 200;
    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(startAddress + i, 0);
    }

    EEPROM.commit();
}

//------------------------------------------------------

void EEPROMManager::saveEepromHum(float value) {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 300;
    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(startAddress + i, bytePointer[i]);
    }

    EEPROM.commit();
}

bool EEPROMManager::readEepromHum(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 300;
    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        bytePointer[i] = EEPROM.read(startAddress + i);
    }

    for (int i = 0; i < sizeof(float); ++i) {
        if (bytePointer[i] == 0xFF) {
            return false;
        }
    }

    return true;
}

void EEPROMManager::clearEepromHum() {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 300;
    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(startAddress + i, 0);
    }

    EEPROM.commit();
}

//-------------------------------------------------------

void EEPROMManager::saveEepromInt(float value) {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 400;
    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(startAddress + i, bytePointer[i]);
    }

    EEPROM.commit();
}

bool EEPROMManager::readEepromInt(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 400;
    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        bytePointer[i] = EEPROM.read(startAddress + i);
    }

    for (int i = 0; i < sizeof(float); ++i) {
        if (bytePointer[i] == 0xFF) {
            return false;
        }
    }

    return true;
}

void EEPROMManager::clearEepromInt() {
    EEPROM.begin(EEPROM_SIZE);

    const int startAddress = 400;
    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(startAddress + i, 0);
    }

    EEPROM.commit();
}