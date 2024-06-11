#pragma once
#include <Arduino.h>

enum BtnInput
{
    Up,
    Enter,
    Down
};

struct BaseLCDMMenuItem
{
    void (*onLoad)(void*, uint8_t);
    void (*onInput)(void*, uint8_t);
    void (*periodic)(void*, uint8_t);
};


struct LCDMenuOkCancelItem : public BaseLCDMMenuItem
{
    char* title;
    char* content;

    void (*action)(void*, uint8_t);
    void* callbackParam;
};



class LCDMenu
{

};