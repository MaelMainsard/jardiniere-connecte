#include <JardiniereServer.h>

const String DEVICE_NAME = "JardiniereAP";

JardiniereServer jardinierServer(DEVICE_NAME);

void setup() {
    // Initialisation du moniteur s
}

void loop() {
    // Appel de la méthode loop() de la bibliothèque pour gérer le serveur et les mises à jour
    jardinierServer.loop();
}