#include "Interaction/Pages/TestPage.h"





void TestPage::OnLoad()
{
    Serial.println("TestPage Loaded");
}

void TestPage::OnExit()
{
    Serial.println("TestPage Exit");
}

void TestPage::OnInput(BtnInput input)
{
    Serial.printf("TestPage Input %d\n", input);

    if(input == BtnInput::Enter) this->Close();
}

void TestPage::Periodic()
{
    
}