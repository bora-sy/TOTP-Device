#include <Arduino.h>
#include "Interaction/ButtonHandler.h"
#include "Pages.h"
#include "TOTP/TOTP.h"



void setup() {
  Serial.begin(921600);

  ButtonHandler::Initialize();
  PagedView::Begin();
  Pages::Initialize();

  Pages::otpMenu->Show();
}

void loop() {
  return;
  BtnInput inp = ButtonHandler::GetInput();
  if(inp.key != BtnKey::NONE) PagedView::HandleInput(inp);
  PagedView::Periodic();
}
