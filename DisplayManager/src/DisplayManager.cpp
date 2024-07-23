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
// X Y
//-------------------------------------
// 0 0
//-------------------------------------
void DisplayManager::displayAirHum(String value){
  display.fillRect(0, 15, (SCREEN_WIDTH / 2)-1, 12, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(5, 18);
  display.print(value+"%");
  display.setCursor((SCREEN_WIDTH / 2)-10, 18);
  display.print("A");
  display.display();
}
//-------------------------------------
// 0 1
//-------------------------------------
void DisplayManager::displayGndHum(String value){
  display.fillRect(0, 27, (SCREEN_WIDTH / 2)-1, 12, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(5, 30);
  display.print(value+"%");
  display.setCursor((SCREEN_WIDTH / 2)-10, 30);
  display.print("G");
  display.display();
}
//-------------------------------------
// 0 2
//-------------------------------------
void DisplayManager::displayTemp(String value){
  display.fillRect(0, 39, (SCREEN_WIDTH / 2)-1, 12, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(5, 42);
  display.print(value+"C");
  display.setCursor((SCREEN_WIDTH / 2)-10, 42);
  display.print("T");
  display.display();
}
//--------------------------------------
// 0 3
//--------------------------------------
void DisplayManager::displayLum(String value){
  display.fillRect(0, 51, (SCREEN_WIDTH / 2)-1, 12, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(5, 54);
  display.print(value+"lm");
  display.setCursor((SCREEN_WIDTH / 2)-10, 54);
  display.print("L");
  display.display();
}
//--------------------------------------
// 1 0
//--------------------------------------
void DisplayManager::displayIntUpd(String value){
  display.fillRect((SCREEN_WIDTH / 2)+1, 15, SCREEN_WIDTH / 2, 12, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor((SCREEN_WIDTH / 2)+6, 18);
  display.print(value);
  display.setCursor(SCREEN_WIDTH - 10, 18);
  display.print("R");
  display.display();
}
//--------------------------------------
// 1 1
//--------------------------------------
void DisplayManager::displayIntSend(String value){
  display.fillRect((SCREEN_WIDTH / 2)+1, 27, SCREEN_WIDTH / 2, 12, SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor((SCREEN_WIDTH / 2)+6, 30);
  display.print(value);
  display.setCursor(SCREEN_WIDTH - 10, 30);
  display.print("S");
  display.display();
}
