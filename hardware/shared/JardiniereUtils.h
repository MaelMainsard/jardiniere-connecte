#include <Arduino.h>
#ifndef JARDINIEREUTILS_H
#define JARDINIEREUTILS_H

struct SensorData {
    float airHumidity;
    float groundHumidity;
    float luminosity;
    float temperature;
};

struct String generateRandomID(int length) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int numCharacters = sizeof(characters) - 1; // -1 pour exclure le caractère '\0'

    String id = "";
    for (int i = 0; i < length; i++) {
        char randomChar = characters[random(numCharacters)];
        id += randomChar;
    }

    return id;
};

#endif
