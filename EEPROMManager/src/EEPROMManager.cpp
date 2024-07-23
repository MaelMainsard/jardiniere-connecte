#include "EEPROMManager.h"

EEPROMManager::EEPROMManager() {}

//----------------------------------------------------
//Save, read, clear Air Humidity Value
//----------------------------------------------------

void EEPROMManager::saveEepromAirHum(float value) {
    clearEepromAirHum();
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(AIR_HUM_ADRESS + i, bytePointer[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromAirHum(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        bytePointer[i] = EEPROM.read(AIR_HUM_ADRESS + i);
    }

    for (int i = 0; i < sizeof(float); ++i) {
        if (bytePointer[i] == 0xFF || bytePointer[i] != 0) {
            return false;
        }
    }

    return true;
}
void EEPROMManager::clearEepromAirHum() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(AIR_HUM_ADRESS + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear Ground Humidity Value
//----------------------------------------------------

void EEPROMManager::saveEepromGndHum(float value) {
    clearEepromGndHum();
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(GND_HUM_ADRESS + i, bytePointer[i]);
    }

    EEPROM.commit();
}
void EEPROMManager::readEepromGndHum(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        bytePointer[i] = EEPROM.read(GND_HUM_ADRESS + i);
    }

    for (int i = 0; i < sizeof(float); ++i) {
        if (bytePointer[i] == 0xFF || bytePointer[i] != 0) {
            return false;
        }
    }

    return true;
}
void EEPROMManager::clearEepromGndHum() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(GND_HUM_ADRESS + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear Temperature Value
//----------------------------------------------------

void EEPROMManager::saveEepromTemp(float value) {
    clearEepromTemp();
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(TEMP_ADRESS + i, bytePointer[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromTemp(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        bytePointer[i] = EEPROM.read(TEMP_ADRESS + i);
    }

    for (int i = 0; i < sizeof(float); ++i) {
        if (bytePointer[i] == 0xFF || bytePointer[i] != 0) {
            return false;
        }
    }

    return true;
}
void EEPROMManager::clearEepromTemp() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(TEMP_ADRESS + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear Luminosity Value
//----------------------------------------------------

void EEPROMManager::saveEepromLum(float value) {
    clearEepromLum();
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(LUM_ADRESS + i, bytePointer[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromLum(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        bytePointer[i] = EEPROM.read(LUM_ADRESS + i);
    }

    for (int i = 0; i < sizeof(float); ++i) {
        if (bytePointer[i] == 0xFF || bytePointer[i] != 0) {
            return false;
        }
    }

    return true;
}
void EEPROMManager::clearEepromLum() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(LUM_ADRESS + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear Interval update Value
//----------------------------------------------------

void EEPROMManager::saveEepromUpdInt(float value) {
    clearEepromUpdInt();
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(UPD_INT_ADRESS + i, bytePointer[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromUpdInt(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        bytePointer[i] = EEPROM.read(UPD_INT_ADRESS + i);
    }

    for (int i = 0; i < sizeof(float); ++i) {
        if (bytePointer[i] == 0xFF || bytePointer[i] != 0) {
            return false;
        }
    }

    return true;
}
void EEPROMManager::clearEepromUpdInt() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(UPD_INT_ADRESS + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear Interval send Value
//----------------------------------------------------

void EEPROMManager::saveEepromSndInt(float value) {
    clearEepromSndInt();
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(SND_INT_ADRESS + i, bytePointer[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromSndInt(float& value) {
    EEPROM.begin(EEPROM_SIZE);

    byte* bytePointer = (byte*)(void*)&value;

    for (int i = 0; i < sizeof(float); ++i) {
        bytePointer[i] = EEPROM.read(SND_INT_ADRESS + i);
    }

    for (int i = 0; i < sizeof(float); ++i) {
        if (bytePointer[i] == 0xFF || bytePointer[i] != 0) {
            return false;
        }
    }

    return true;
}
void EEPROMManager::clearEepromSndInt() {
    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < sizeof(float); ++i) {
        EEPROM.write(SND_INT_ADRESS + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear ssid
//----------------------------------------------------

void EEPROMManager::saveEepromSsid(String ssid) {
    clearEepromSsid();
    EEPROM.begin(EEPROM_SIZE);

    const char* charPointer = value.c_str();
    int length = value.length();

    for (int i = 0; i <= length; ++i) {
        EEPROM.write(SSID_ADRESS + i, charPointer[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromSsid(String& ssid) {
    EEPROM.begin(EEPROM_SIZE);

    char charArray[EEPROM_SIZE - SSID_ADRESS];
    int i = 0;

    while (i < (EEPROM_SIZE - SSID_ADRESS - 1)) {
        char c = EEPROM.read(SSID_ADRESS + i);
        if (c == '\0') {
            break;
        }
        charArray[i++] = c;
    }

    charArray[i] = '\0';

    ssid = String(charArray);

    if (ssid.length() == 0) {
        return false;
    }

    return true;
}
void EEPROMManager::clearEepromSsid() {

    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < 50; ++i) {
        EEPROM.write(SSID_ADRESS + i, 0);
    }

    EEPROM.commit();
}

//----------------------------------------------------
// Save, read, clear password
//----------------------------------------------------

void EEPROMManager::saveEepromPsw(String psw) {
    clearEepromSsid();
    EEPROM.begin(EEPROM_SIZE);

    const char* charPointer = psw.c_str();
    int length = psw.length();

    for (int i = 0; i <= length; ++i) {
        EEPROM.write(PSW_ADRESS + i, charPointer[i]);
    }

    EEPROM.commit();
}
bool EEPROMManager::readEepromPsw(String& psw) {
    EEPROM.begin(EEPROM_SIZE);

    char charArray[EEPROM_SIZE - PSW_ADRESS];
    int i = 0;

    while (i < (EEPROM_SIZE - PSW_ADRESS - 1)) {
        char c = EEPROM.read(PSW_ADRESS + i);
        if (c == '\0') {
            break;
        }
        charArray[i++] = c;
    }

    charArray[i] = '\0';

    psw = String(charArray);

    if (psw.length() == 0) {
        return false;
    }

    return true;
}
void EEPROMManager::clearEepromPsw() {

    EEPROM.begin(EEPROM_SIZE);

    for (int i = 0; i < 100; ++i) {
        EEPROM.write(PSW_ADRESS + i, 0);
    }

    EEPROM.commit();
}