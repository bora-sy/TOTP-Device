#pragma once
#include <Arduino.h>

enum BtnInput
{
    Up,
    Enter,
    Down
};

struct BaseLCDMenuItem
{
    public:
    char* title;
    void (*onLoad)();
    void (*onClose)();

    void (*onInput)(BtnInput input);

    void (*periodic)();

};


struct LCDMenuOkCancelItem : public BaseLCDMenuItem
{
    char* content;
    void (*okAction)();
};




class LCDMenu
{
private:
BaseLCDMenuItem* _items;
uint8_t _itemCount;

int _selectedItem = 0;
int _loadedItem = -1;

void UpdateMenuScreen();

public:
    LCDMenu(BaseLCDMenuItem* items, uint8_t itemCount);
    LCDMenu();
    ~LCDMenu();

    void Open();
    void Close();

    void Periodic();

    void Input(BtnInput input);
};

