#include <Arduino.h>
#include "Ds1302.h"
#include <PagedView.h>
#include "Interaction/Pages/OTPPage.h"



Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);



void setup() {
  Serial.begin(921600);

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);

  PagedView::Begin();


  OTPPage* p = new OTPPage();

  p->Show();
}

void loop() {
  if (!digitalRead(BTN1)) PagedView::HandleInput(BtnInput::Up);
  if (!digitalRead(BTN2)) PagedView::HandleInput(BtnInput::Enter);
  if (!digitalRead(BTN3)) PagedView::HandleInput(BtnInput::Down);
  
  PagedView::Periodic();
  
  delay(100);

}
