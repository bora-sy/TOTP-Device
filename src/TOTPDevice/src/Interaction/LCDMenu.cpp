#include <Arduino.h>
#include "Interaction/LCDMenu.h"
#include "Interaction/LCD.h"

const char rightArrow = 126;
const char leftArrow = 127;


LCDMenu::~LCDMenu() {}
LCDMenu::LCDMenu() {}

LCDMenu::LCDMenu(BaseLCDMenuItem *items, uint8_t itemCount)
{
    this->_itemCount = itemCount;
    this->_items = items;
}

void LCDMenu::Open()
{
    this->_loadedItem = -1;
    this->_selectedItem = 0;
}

void LCDMenu::Close()
{
    if (this->_loadedItem == -1)
        return;

    this->_items[this->_loadedItem].onClose();
}

void LCDMenu::Periodic()
{
    if (this->_loadedItem == -1)
        return;

    BaseLCDMenuItem item = this->_items[this->_loadedItem];
    if (item.periodic != nullptr)
    {
        item.periodic();
    }
}

void LCDMenu::UpdateMenuScreen()
{
    int selectedItemIndex = this->_selectedItem;

    if(selectedItemIndex == this->_itemCount - 1)
    {
        LCD::Print(&rightArrow, 0, 1, true);

        LCD::PrintCenterRow(this->_items[selectedItemIndex - 1].title, 0, false, 1);
        LCD::PrintCenterRow(this->_items[selectedItemIndex].title, 1, false, 1);
    }

    if(this->_itemCount < 2) return;

    LCD::Print(&rightArrow, 0, 0, true);
    
    LCD::PrintCenterRow(this->_items[selectedItemIndex].title, 0, false, 1);
    LCD::PrintCenterRow(this->_items[selectedItemIndex + 1].title, 1, false, 1);
}

void LCDMenu::Input(BtnInput input)
{
    if(this->_loadedItem != -1)
    {
        this->_items[this->_loadedItem].onInput(input);
        return;
    }

    switch (input)
    {
    case BtnInput::Up:
        this->_selectedItem--;
        this->UpdateMenuScreen();
        break;
    case BtnInput::Down:
        this->_selectedItem++;
        this->UpdateMenuScreen();
        break;
    case BtnInput::Enter:

        break;
    }


    // Clamp
    this->_selectedItem < 0 ? 0 : this->_selectedItem;
    this->_selectedItem >= this->_itemCount ? this->_itemCount - 1 : this->_selectedItem;
}