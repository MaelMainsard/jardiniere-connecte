#include "WifiParams.h"

WifiParams::WifiParams(String ssid, String psw)
    : ssid(ssid), psw(psw) {}

String WifiParams::toString() const {
    return ssid + ":::SP:::" + psw;
}

WifiParams WifiParams::fromString(const String& str) {
    WifiParams params;

    // Convertir la chaîne en un tableau de caractères modifiable
    char input[str.length() + 1];
    str.toCharArray(input, sizeof(input));

    // Définir le modèle regex
    const char* pattern = "(.*):::\\SP:::(.*)";

    // Créer les objets MatchState et utiliser l'expression régulière
    MatchState ms(input);
    char result = ms.Match(pattern);

    // Vérifiez les captures
    if (result == REGEXP_MATCHED && ms.level == 3) { // ms.level donne le nombre de captures réussies
        char captureBuf[100]; // Assurez-vous que ce buffer est assez grand pour vos besoins

        ms.GetCapture(captureBuf, 0);
        params.ssid = String(captureBuf);

        ms.GetCapture(captureBuf, 1);
        params.psw = String(captureBuf);
    }

    return params;
}