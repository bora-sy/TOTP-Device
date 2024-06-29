#pragma once

#include <PagedView.h>
#include "Interaction/Pages/OTPMenu.h"
#include "Interaction/Pages/OTPPage.h"


namespace Pages
{
    extern OTPMenu* otpMenu;
    extern OTPPage* otpPage;

    void Initialize();
}