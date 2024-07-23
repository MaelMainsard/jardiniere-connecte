#ifndef EEPROMMANAGER_H
#define EEPROMMANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 512
#define AIR_HUM_ADRESS 0
#define GND_HUM_ADRESS 50
#define TEMP_ADRESS 100
#define LUM_ADRESS 150
#define UPD_INT_ADRESS 200
#define SND_INT_ADRESS 250
#define SSID_ADRESS 300
#define PSW_ADRESS 350


class EEPROMManager {
public:
    EEPROMManager();
    void saveEepromSsid(String ssid);
    bool readEepromSsid(String& ssid);
    void clearEepromSsid();

    void saveEepromPsw(String psw);
    bool readEepromPsw(String& psw);
    void clearEepromPsw();

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

    void saveEepromUpdInt(float value);
    bool readEepromUpdInt(float& value);
    void clearEepromUpdInt();

    void saveEepromSndInt(float value);
    bool readEepromSndInt(float& value);
    void clearEepromSndInt();


private:

};

#endif