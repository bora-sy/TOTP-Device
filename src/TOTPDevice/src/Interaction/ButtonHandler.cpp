#include "Interaction/ButtonHandler.h"

namespace ButtonHandler
{
    const int16_t debounceMS = 50;

    ulong debounces[3] = {0, 0, 0};
    bool lastStates[3] = {false,false,false};
    

    void Initialize()
    {
        pinMode(PIN_BTN1, INPUT_PULLUP);
        pinMode(PIN_BTN2, INPUT_PULLUP);
        pinMode(PIN_BTN3, INPUT_PULLUP);
    }

    uint8_t GetPinByButton(BtnKey btn)
    {
        switch (btn)
        {
        case BtnKey::Up:
            return PIN_BTN1;

        case BtnKey::Enter:
            return PIN_BTN2;

        case BtnKey::Down:
            return PIN_BTN3;

        default:
            return 0;
        }
    }

    BtnKey GetButtonByPin(uint8_t pin)
    {
        switch (pin)
        {
        case PIN_BTN1:
            return BtnKey::Up;
        case PIN_BTN2:
            return BtnKey::Enter;
        case PIN_BTN3:
            return BtnKey::Down;
        default:
            return BtnKey::NONE;
        }
    }

    int8_t GetButtonIndex(BtnKey btn)
    {
        switch(btn)
        {
            case BtnKey::Up:
                return 0;
            case BtnKey::Enter:
                return 1;
            case BtnKey::Down:
                return 2;
            default:
                return -1;
        }
    }

    
    bool IsButtonPressed(BtnKey btn)
    {
        return digitalRead(GetPinByButton(btn)) == LOW;
    }

    BtnKey GetPressedButtons()
    {
        BtnKey input = BtnKey::NONE;

        if(IsButtonPressed(BtnKey::Up)) input = (BtnKey)((int)input | (int)BtnKey::Up);
        if(IsButtonPressed(BtnKey::Enter)) input = (BtnKey)((int)input | (int)BtnKey::Enter);
        if(IsButtonPressed(BtnKey::Down)) input = (BtnKey)((int)input | (int)BtnKey::Down);

        return input;
    }


    bool CheckSingleButton(BtnKey btn)
    {
        bool state = IsButtonPressed(btn);

        
        int8_t i = GetButtonIndex(btn);

        if(lastStates[i] == state)
        {
            
            return false;
        }

        if(millis() - debounces[i] < debounceMS)
        {
            return false;
        }

        debounces[i] = millis();
        
        lastStates[i] = state;

        return state;
    }

    BtnInput GetInput()
    {
        // TODO: Actually decide whether the input mode is click or long click
        if(CheckSingleButton(BtnKey::Up)) return BtnInput(BtnKey::Up, BtnInputMode::Click);
        if(CheckSingleButton(BtnKey::Enter)) return BtnInput(BtnKey::Enter, BtnInputMode::Click);
        if(CheckSingleButton(BtnKey::Down)) return BtnInput(BtnKey::Down, BtnInputMode::Click);

        return BtnInput(BtnKey::NONE, BtnInputMode::Click);
    }
}