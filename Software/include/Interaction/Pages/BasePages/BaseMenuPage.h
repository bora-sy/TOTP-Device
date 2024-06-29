#pragma once
#include <PagedView.h>
#include "Interaction/Components/RectLabel.h"



class BaseMenuPage : public Page
{
private:
RectLabel titles[3];
String items[64];
uint8_t itemCount = 0;

int16_t selected = 0;

ulong val;

void SetInvertedSingle(int index, bool inverted, bool draw);
public:
    void OnLoad() override;
    void OnExit() override;
    void OnInput(BtnInput input) override;
    void Periodic() override;

    void Select(int index);

    int AddItem(String title);
    void ClearItems();
    bool GetItem(int index, String& title);
    
    virtual void OnItemSelected(int index) = 0;
    virtual void OnItemClicked(int index) = 0;
    virtual void OnItemLongClicked(int index) = 0;

    BaseMenuPage();
};