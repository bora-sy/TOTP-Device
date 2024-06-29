#include "Pages.h"




void OTPPage::OnLoad()
{
    val = millis() + 30000;
}

void OTPPage::OnExit()
{
    
}

void OTPPage::OnInput(BtnInput input)
{
    //Serial.printf("OTPPage Input %d\n", input);

    if(input.key == BtnKey::Enter) Pages::otpMenu->Show();
    //else this->label.UpdateText(String(this->c++));
}

void OTPPage::Periodic()
{
    long remaining = val - millis();
    remaining = remaining < 0 ? 0 : remaining;
    
    pbar.UpdateValue(map(remaining, 0, 30000, 0, 128));
}

OTPPage::OTPPage()
{
    this->labelOTPTitle = Label(RelativePoint(0.5,0), "Title", 2, Color::White, RelativePoint(0.5, 0));
    this->labelOTP = Label(RelativePoint(0.5,0.8), "123 456", 3, Color::White, RelativePoint(0.5, 1));
    this->pbar = Progressbar(RelativePoint(0, 0.95), RelativeSize(1, 0.05), Color::White, 128, 128);
    
    this->AddComponent(&labelOTPTitle);
    this->AddComponent(&labelOTP);
    this->AddComponent(&pbar);
}