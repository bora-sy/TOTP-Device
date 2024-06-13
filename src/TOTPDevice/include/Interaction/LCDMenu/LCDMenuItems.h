#pragma once
#include <Arduino.h>
#include "Interaction/InputHandler.h"
#include "Interaction/LCD.h"

struct LCDMenuItem
{
    private:

    public:
    String title;
    
    std::function<void()> onClose;
    std::function<void()> onLoad;
    std::function<void(BtnInput input)> onInput;
    std::function<void()> periodic;

};


LCDMenuItem* CreateOkCancelMenuItem(String title, String content, void (*onClose)(bool result));

/*
struct BaseLCDMenuItem
{
    public:
    String title;

    virtual void handleClose(){};
    virtual void handleLoad(){Serial.println("Aww default load");};
    virtual void handleInput(BtnInput input){};
    virtual void periodic(){};

    BaseLCDMenuItem(){};

};


struct LCDMenuOkCancelItem : public BaseLCDMenuItem
{
    String content;

    LCDMenuOkCancelItem();

    void handleClose() override;
    void handleLoad() override;
    void handleInput(BtnInput input) override;
    void periodic() override;

    LCDMenuOkCancelItem(String title, String content);
};


*/