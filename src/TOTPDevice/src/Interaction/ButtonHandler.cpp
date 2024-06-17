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

    uint8_t GetPinByButton(BtnInput btn)
    {
        switch (btn)
        {
        case BtnInput::Up:
            return PIN_BTN1;

        case BtnInput::Enter:
            return PIN_BTN2;

        case BtnInput::Down:
            return PIN_BTN3;

        default:
            return 0;
        }
    }

    BtnInput GetButtonByPin(uint8_t pin)
    {
        switch (pin)
        {
        case PIN_BTN1:
            return BtnInput::Up;
        case PIN_BTN2:
            return BtnInput::Enter;
        case PIN_BTN3:
            return BtnInput::Down;
        default:
            return BtnInput::NONE;
        }
    }

    int8_t GetButtonIndex(BtnInput btn)
    {
        switch(btn)
        {
            case BtnInput::Up:
                return 0;
            case BtnInput::Enter:
                return 1;
            case BtnInput::Down:
                return 2;
            default:
                return -1;
        }
    }

    
    bool IsButtonPressed(BtnInput btn)
    {
        return digitalRead(GetPinByButton(btn)) == LOW;
    }

    BtnInput GetPressedButtons()
    {
        BtnInput input = BtnInput::NONE;

        if(IsButtonPressed(BtnInput::Up)) input = (BtnInput)((int)input | (int)BtnInput::Up);
        if(IsButtonPressed(BtnInput::Enter)) input = (BtnInput)((int)input | (int)BtnInput::Enter);
        if(IsButtonPressed(BtnInput::Down)) input = (BtnInput)((int)input | (int)BtnInput::Down);

        return input;
    }


    bool CheckSingleButton(BtnInput btn)
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
        if(CheckSingleButton(BtnInput::Up)) return BtnInput::Up;
        if(CheckSingleButton(BtnInput::Enter)) return BtnInput::Enter;
        if(CheckSingleButton(BtnInput::Down)) return BtnInput::Down;

        return BtnInput::NONE;
    }
}