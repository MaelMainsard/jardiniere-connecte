#include <JardiniereServer.h>

// Create an instance of the JardiniereServer class with your device name
JardiniereServer jardiniereServer("Jardiniere1");

void setup() {
  // Initialize the JardiniereServer
  jardiniereServer.begin();
}

void loop() {
  // Handle client requests
  jardiniereServer.loop();
}
