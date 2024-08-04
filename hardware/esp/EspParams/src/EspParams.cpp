#include "EspParams.h"

EspParams::EspParams(String uid, String esp_ssid, String esp_psw)
    : uid(uid), esp_ssid(esp_ssid), esp_psw(esp_psw) {}

String EspParams::toString() const {
    return uid + ":::SP:::" + esp_ssid + ":::SP:::" + esp_psw;
}

EspParams EspParams::fromString(const String& str) {
    EspParams params;

    // Convertir la chaîne en un tableau de caractères modifiable
    char input[str.length() + 1];
    str.toCharArray(input, sizeof(input));

    // Définir le modèle regex
    const char* pattern = "([^:]+):::\\SP:::(.*):::\\SP:::(.*)";

    // Créer les objets MatchState et utiliser l'expression régulière
    MatchState ms(input);
    char result = ms.Match(pattern);

    // Vérifiez les captures
    if (result == REGEXP_MATCHED && ms.level == 4) { // ms.level donne le nombre de captures réussies
        char captureBuf[100]; // Assurez-vous que ce buffer est assez grand pour vos besoins

        ms.GetCapture(captureBuf, 0);
        params.uid = String(captureBuf);

        ms.GetCapture(captureBuf, 1);
        params.esp_ssid = String(captureBuf);

        ms.GetCapture(captureBuf, 2);
        params.esp_psw = String(captureBuf);
    }

    return params;
}

String EspParams::generateRandomID(int length) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int numCharacters = sizeof(characters) - 1; // -1 pour exclure le caractère '\0'

    String id = "";
    for (int i = 0; i < length; i++) {
        char randomChar = characters[random(numCharacters)];
        id += randomChar;
    }

    return id;
}

String EspParams::generateRandomUUID() { // Corrected spelling
    UUID uuid;
    uuid.generate();
    return String(uuid.toCharArray());
}
