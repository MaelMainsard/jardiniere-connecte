#include "DisplayManager.h"


DisplayManager::DisplayManager()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void DisplayManager::init(){
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    display.clearDisplay();
    display.drawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, SSD1306_WHITE);
    displayDbDisconnected();
}

void DisplayManager::displayDbConnected() {
   display.fillRect(0, 0, SCREEN_WIDTH, 15, SSD1306_BLACK);
   display.fillRect(0, 0, SCREEN_WIDTH, 15, SSD1306_WHITE);

   display.setTextColor(SSD1306_BLACK);
   display.setTextSize(1);
   display.setCursor(40, 4);
   display.print("Connected");
   display.display();
}

void DisplayManager::displayDbDisconnected(){
   display.fillRect(0, 0, SCREEN_WIDTH, 15, SSD1306_BLACK);
   display.drawRect(0, 0, SCREEN_WIDTH, 15, SSD1306_WHITE);

   display.setTextColor(SSD1306_WHITE);
   display.setTextSize(1);
   display.setCursor(30, 4);
   display.print("Disconnected");
   display.display();
}

void DisplayManager::displayTemp(float value){
  display.fillRect(0, 15, SCREEN_WIDTH / 2, 16, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(5, 21);
  display.print(String(value,1)+"C");
  display.display();
}

void DisplayManager::displayDbTemp(String value){
  display.fillRect((SCREEN_WIDTH / 2)+1, 15, SCREEN_WIDTH / 2, 12, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor((SCREEN_WIDTH / 2) + 6,18);
  display.print(value+"C");
  display.display();
}

void DisplayManager::displayHum(float value){
  display.fillRect((SCREEN_WIDTH / 2)+1, 31, SCREEN_WIDTH / 2, 16, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(5, 36);
  display.print(String(value,1)+"%");
  display.display();
}

void DisplayManager::displayDbHum(String value){
  display.fillRect((SCREEN_WIDTH / 2)+1, 27, SCREEN_WIDTH / 2, 12, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor((SCREEN_WIDTH / 2) + 6,30);
  display.print(value+"%");
  display.display();
}

void DisplayManager::displayLum(float value){
  display.fillRect(0, 45, SCREEN_WIDTH / 2, 16, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(5, 51);
  display.print(String(value,1)+"lm");
  display.display();
}

void DisplayManager::displayDbLum(String value){
  display.fillRect((SCREEN_WIDTH / 2)+1, 39, SCREEN_WIDTH / 2, 12, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor((SCREEN_WIDTH / 2) + 6, 42);
  display.print(value+"lm");
  display.display();
}
void DisplayManager::displayDbInter(String value){
  display.fillRect((SCREEN_WIDTH / 2)+1, 51, SCREEN_WIDTH / 2, 12, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor((SCREEN_WIDTH / 2) + 6, 54);
  display.print(value);
  display.display();
}
