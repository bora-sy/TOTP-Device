#pragma once
#include "Pins.h"
#include <Arduino.h>
#include "PagedView.h"



namespace ButtonHandler
{
    void Initialize();

    bool IsButtonPressed(BtnKey btn);

    BtnKey GetPressedButtons();

    BtnInput GetInput();
}