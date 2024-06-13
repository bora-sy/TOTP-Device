#pragma once
#include <Arduino.h>
#include "Interaction/LCD.h"
#include "Interaction/LCDMenu/LCDMenuItems.h"
#include "Interaction/InputHandler.h"

class LCDMenu
{
private:
LCDMenuItem* _items;
uint8_t _itemCount;

int _selectedItem = 0;
int _loadedItem = -1;

void UpdateMenuScreen();

public:
    LCDMenu(LCDMenuItem items[], uint8_t itemCount);
    LCDMenu();
    ~LCDMenu();

    void Open();
    void Close();

    void Periodic();

    void Input(BtnInput input);
};

