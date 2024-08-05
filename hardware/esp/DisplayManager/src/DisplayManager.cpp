#include "DisplayManager.h"


DisplayManager::DisplayManager()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), eepromManager() {pinMode(D8, INPUT);}

void DisplayManager::begin(){
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    display.clearDisplay();
    display.display();
    displayPage1();
}


void DisplayManager::handlePageChange(){
  // Lit l'état actuel du bouton
  bool reading = digitalRead(D8);

  // Vérifie si l'état du bouton a changé
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Remet le compteur de débounce à zéro
  }

  // Si le délai de débounce est écoulé
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Si l'état du bouton a changé
    if (reading != buttonState) {
      buttonState = reading;
      // Si le bouton est pressé (état LOW)
      if (buttonState == HIGH) {
        // Change la page actuelle
        switch(currentPage) {
          case 1:
            currentPage = 2;
            displayPage2();
            break;

          case 2:
            currentPage = 3;
            displayPage3();
            break;

          case 3:
            currentPage = 4;
            displayPage4();
            break;

          case 4:
            currentPage = 5;
            displayPage5();
            break;

          default:
            currentPage = 1; // Valeur par défaut au cas où currentPage ne correspondrait à aucune page
            displayPage1();
            break;
        }
      }
    }
  }

  // Sauvegarde l'état du bouton pour la prochaine lecture
  lastButtonState = reading;
}

void DisplayManager::displayPage1(){

  display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_BLACK);

  displayTitle("Wifi config (1)");

  EspParams params;
  if(eepromManager.readEspParams(params)){
    String wifiCred = "WIFI:S:"+params.esp_ssid+";T:WPA2;P:"+params.esp_psw+";;";
    generateQRCode(wifiCred,(SCREEN_WIDTH - 40) / 2);
  }

}

void DisplayManager::displayPage2(){

  display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_BLACK);

  displayTitle("Wifi config (2)");

  EspParams params;
  if(eepromManager.readEspParams(params)){

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(5, 22);
    display.print("ssid="+params.esp_ssid);

    display.setCursor(5, 32);
    display.print("psw="+params.esp_psw);

    display.display();

  }
}


void DisplayManager::displayPage3(){

  display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_BLACK);

  displayTitle("Esp config (1)");

  EspParams params;
  if(eepromManager.readEspParams(params)){
    generateQRCode(params.toString(),(SCREEN_WIDTH - 40) / 2);
  }


}

void DisplayManager::displayPage4(){

  display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_BLACK);

  displayTitle("Esp Config (2)");

  EspParams params;
  if(eepromManager.readEspParams(params)){

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(5, 22);
    display.print("uid="+params.uid);

    display.setCursor(5, 42);
    display.print("name="+params.esp_ssid);

    display.display();

  }

}

void DisplayManager::displayPage5(){

  display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_BLACK);

  displayTitle("Esp Config (3)");

  EspParams params;
  if(eepromManager.readEspParams(params)){

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(5, 22);
    display.print("psw="+params.esp_psw);

    display.setCursor(5, 32);
    display.print("refresh interval="+EspParams::formatTime(params.interval_s));

    display.display();

  }

}

void DisplayManager::displayTitle(String str) {
  display.fillRect(0, 0, SCREEN_WIDTH, 15, SSD1306_WHITE);

  display.setTextColor(SSD1306_BLACK);
  display.setTextSize(1);
  display.setCursor(30, 4);
  display.print(str);
  display.display();
}

void DisplayManager::generateQRCode(String text, int x) {

  const char* textCStr = text.c_str();
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(5)]; // Taille du tampon pour le QR code de version 3
  qrcode_initText(&qrcode, qrcodeData, 5, 0, textCStr); // QR code version 3

  int scale = 40 / qrcode.size; // Redimensionner pour que le QR code ait 40 pixels de côté
  int shiftX = x;
  int shiftY = 22;

  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        display.fillRect(shiftX + x * scale, shiftY + y * scale, scale, scale, SSD1306_WHITE);
      }
    }
  }
  display.display();
}