#pragma once
#include "Pins.h"
#include <Arduino.h>
#include "PagedView.h"



namespace ButtonHandler
{
    void Initialize();

    bool IsButtonPressed(BtnInput btn);

    BtnInput GetPressedButtons();

    BtnInput GetInput();
}