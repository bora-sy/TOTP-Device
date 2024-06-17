#pragma once

#include <PagedView.h>
#include "Interaction/Components/Label.h"
#include "Interaction/Components/Progressbar.h"

class OTPPage : public Page
{
private:
Label labelOTPTitle;
Label labelOTP;
Progressbar pbar;

ulong val;
public:
    void OnLoad() override;
    void OnExit() override;
    void OnInput(BtnInput input) override;
    void Periodic() override;

    OTPPage();
};