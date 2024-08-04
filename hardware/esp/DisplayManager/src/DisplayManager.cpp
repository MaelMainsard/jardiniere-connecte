#include "DisplayManager.h"


DisplayManager::DisplayManager()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), eepromManager() {}

void DisplayManager::begin(){
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    display.clearDisplay();
    display.display();
}


void DisplayManager::handlePageChange(){
  displayPage1();
}

void DisplayManager::displayPage1(){

  EspParams params;
  if(eepromManager.readEspParams(params)){
    String wifiCred = "WIFI:S:"+params.esp_ssid+";T:WPA2;P:"+params.esp_psw+";;";
    generateQRCode(wifiCred);
  }

}

void DisplayManager::displayPage2(){

  EspParams params;
  if(eepromManager.readEspParams(params)){
    generateQRCode(params.uid);
  }

}

void DisplayManager::generateQRCode(String text) {
  const char* textCStr = text.c_str();
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 3, 0, textCStr);
  display.clearDisplay();
  int scale = min(SCREEN_WIDTH / qrcode.size, SCREEN_HEIGHT / qrcode.size);
  int shiftX = (SCREEN_WIDTH - qrcode.size * scale) / 2;
  int shiftY = (SCREEN_HEIGHT - qrcode.size * scale) / 2;
  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        display.fillRect(shiftX + x * scale, shiftY + y * scale, scale, scale, SSD1306_WHITE);
      }
    }
  }
  display.display();
}