#pragma once

#include <PagedView.h>
#include "Interaction/Components/RectLabel.h"

class MenuPage : public Page
{
private:
RectLabel Titles[3];

ulong val;
public:
    void OnLoad() override;
    void OnExit() override;
    void OnInput(BtnInput input) override;
    void Periodic() override;

    MenuPage();
};