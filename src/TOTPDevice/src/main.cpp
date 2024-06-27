#include <Arduino.h>
#include <PagedView.h>
#include "Interaction/Pages/MenuPage.h"
#include "Interaction/ButtonHandler.h"





void setup() {
  Serial.begin(921600);

  ButtonHandler::Initialize();
  PagedView::Begin();
  MenuPage* p = new MenuPage();

  p->Show();
}

void loop() {
  BtnInput inp = ButtonHandler::GetInput();
  if(inp != BtnInput::NONE) PagedView::HandleInput(inp);
  PagedView::Periodic();
}
