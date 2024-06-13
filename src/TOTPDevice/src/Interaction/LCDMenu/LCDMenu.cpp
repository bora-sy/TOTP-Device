#include <Arduino.h>
#include "Interaction/LCDMenu/LCDMenu.h"
#include "Interaction/LCDMenu/LCDMenuItems.h"
#include "Interaction/LCD.h"
#include "Interaction/LCDMenu/LCDChars.h"
/*
const char rightArrowStr[] = {126, 0};
const char leftArrowStr[] = {127, 0};
*/

LCDMenu::~LCDMenu() {}
LCDMenu::LCDMenu() {}

LCDMenu::LCDMenu(LCDMenuItem items[], uint8_t itemCount)
{
    this->_items = items;
    this->_itemCount = itemCount;
}

void LCDMenu::Open()
{
    this->_loadedItem = -1;
    this->_selectedItem = 0;

    this->UpdateMenuScreen();
}

void LCDMenu::Close()
{
    if (this->_loadedItem == -1)
        return;

    LCDMenuItem item = this->_items[this->_loadedItem];

    if (item.onClose != nullptr)
        item.onClose();
}

void LCDMenu::Periodic()
{
    if (this->_loadedItem == -1)
        return;

    LCDMenuItem item = this->_items[this->_loadedItem];

    if (item.periodic != nullptr)
        item.periodic();
}

void LCDMenu::UpdateMenuScreen()
{

    LCD::Clear();

    int selectedItemIndex = this->_selectedItem;

    if (selectedItemIndex == this->_itemCount - 1)
    {

        LCD::PrintCenterRow(this->_items[selectedItemIndex - 1].title, 0, false);
        LCD::PrintCenterRow(this->_items[selectedItemIndex].title, 1, false);
        
        LCD::Print((char *)&rightArrowStr, 0, 1, false);
        LCD::Print((char *)&leftArrowStr, 15, 1, false);

        return;
    }

    if (this->_itemCount < 2)
        return;


    LCD::PrintCenterRow(this->_items[selectedItemIndex].title, 0, false);

    LCD::PrintCenterRow(this->_items[selectedItemIndex + 1].title, 1, false);

    LCD::Print((char *)&rightArrowStr, 0, 0, false);
    LCD::Print((char *)&leftArrowStr, 15, 0, false);
}

void LCDMenu::Input(BtnInput input)
{
    if (this->_loadedItem != -1)
    {
        LCDMenuItem item = this->_items[this->_loadedItem];

        if (item.onInput != nullptr)
            item.onInput(input);
        
        return;
    }

    int previousSelectedItem = this->_selectedItem;

    switch (input)
    {
    case BtnInput::Up:
        this->_selectedItem--;
        break;
    case BtnInput::Down:
        this->_selectedItem++;
        break;
    case BtnInput::Enter:
        this->_loadedItem = this->_selectedItem;

        LCDMenuItem item = this->_items[this->_loadedItem];

        if(item.onLoad != nullptr)
        item.onLoad();
        break;
    }

    // Clamp
    this->_selectedItem = this->_selectedItem < 0 ? 0 : this->_selectedItem;
    this->_selectedItem = this->_selectedItem >= this->_itemCount ? this->_itemCount - 1 : this->_selectedItem;

    if (previousSelectedItem == this->_selectedItem)
        return;

    this->UpdateMenuScreen();
}