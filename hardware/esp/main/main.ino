#include <JardiniereServer.h>
//#include <JardiniereDatabase.h>

JardiniereServer jardinierServer;
//JardiniereDatabase jardinierDatabase;


void setup() {
    Serial.begin(115200);
    //jardinierDatabase.begin();
    jardinierServer.begin();
}

void loop() {
    jardinierServer.loop();
    //jardinierDatabase.loop();
}
