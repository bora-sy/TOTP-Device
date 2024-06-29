#include "Pages.h"
//#include "Interaction/Pages/OTPMenu.h"

String arr[] = 
{
    "Item 1",
    "Item 2",
    "Item 3",
    "Item 4",
    "Item 5",
    "Item 6",
    "Item 7",
};

void OTPMenu::OnItemSelected(int index)
{
}

void OTPMenu::OnItemClicked(int index)
{
    Pages::otpPage->Show();
 
}

void OTPMenu::OnItemLongClicked(int index)
{
 Serial.printf("Long Clicked: %d\n", index);
}

OTPMenu::OTPMenu()
{
    for (int i = 0; i < 7; i++)
    {
        AddItem(arr[i]);
    }
}