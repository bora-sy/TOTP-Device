#include "Pages.h"

namespace Pages
{
    OTPMenu* otpMenu;
    OTPPage* otpPage;

    void Initialize()
    {
        otpMenu = new OTPMenu();
        otpPage = new OTPPage();
    }
}