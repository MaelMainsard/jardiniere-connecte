#include <JardiniereServer.h>
#include <JardiniereDatabase.h>
#include <Ticker.h> 

JardiniereServer jardiniereServer("Jardiniere_1");
JardiniereDatabase jardiniereDatabase("Jardiniere_1");
Ticker ticker;

void setup() {
  jardiniereServer.begin();
  jardiniereDatabase.begin();
  ticker.attach(1, sendDatas);
}

void loop() {
  jardiniereServer.loop();
  jardiniereDatabase.loop();
}



void sendDatas(){
 jardiniereDatabase.sendHumidityData(55.0);
}
