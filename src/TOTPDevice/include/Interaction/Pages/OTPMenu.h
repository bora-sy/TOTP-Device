#pragma once

#include <PagedView.h>
#include "Interaction/Pages/BasePages/BaseMenuPage.h"

class OTPMenu : public BaseMenuPage
{
private:

public:

    void OnItemSelected(int index) override;
    void OnItemClicked(int index) override;
    void OnItemLongClicked(int index) override;

    OTPMenu();
};