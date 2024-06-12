#include <Arduino.h>
#include "Interaction/LCD.h"
#include "Interaction/LCDMenu.h"
#include "Ds1302.h"


#define BTN1 2
#define BTN2 14
#define BTN3 3

#define PIN_ENA 15
#define PIN_CLK 12
#define PIN_DAT 13

Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);

LCDMenu menu;

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);



  LCD::Initialize();
  LCD::PrintCenterRow("Hello");


  rtc.init();
  Serial.printf("Halted: %d\n", rtc.isHalted());


  LCDMenuOkCancelItem* items = new LCDMenuOkCancelItem[10];

  for (size_t i = 0; i < 10; i++)
  {
    items[i].title = (char*)("Item " + String(i)).c_str();
    items[i].content = (char*)("Content " + String(i)).c_str();
  }

  menu = LCDMenu(items, 10);
  menu.Open();
}

void loop() {
  if (!digitalRead(BTN1)) menu.Input(BtnInput::Up);
  if (!digitalRead(BTN2)) menu.Input(BtnInput::Enter);
  if (!digitalRead(BTN3)) menu.Input(BtnInput::Down);
  
  menu.Periodic();
}
