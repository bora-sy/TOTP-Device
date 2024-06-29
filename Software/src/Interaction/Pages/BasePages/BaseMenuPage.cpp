#include "Interaction/Pages/BasePages/BaseMenuPage.h"

void BaseMenuPage::OnLoad()
{
    if(itemCount > 0 && selected == 0) this->Select(0);
}

void BaseMenuPage::OnExit()
{
    
}

void BaseMenuPage::Periodic()
{
    
}

void BaseMenuPage::OnInput(BtnInput input)
{
    if(input.key == BtnKey::NONE) return;
    int8_t change = 0;

    switch (input.key)
    {
    case BtnKey::Up: change=-1; break;
    case BtnKey::Down: change=1; break;
    case BtnKey::Enter: 
        switch (input.mode)
        {
        case BtnInputMode::Click:
            this->OnItemClicked(selected);
        break;
        case BtnInputMode::LongClick:
            this->OnItemLongClicked(selected);
        }
        return;
    }

    if(change == 0) return;

    if((change == -1 && selected == 0) || (change == 1 && selected == itemCount-1)) return;


    this->Select(selected + change);
}



void BaseMenuPage::Select(int index)
{
    if(index < 0 || index >= itemCount) return;
    this->selected = index;

    String newTitles[3];

    if(index < 2)
    {
        for(int i = 0; i<3; i++) newTitles[i] = items[i];
    }
    else
    {
        newTitles[0] = items[index - 2];
        newTitles[1] = items[index - 1];
        newTitles[2] = items[index];
    }

    for(int i = 0; i<3; i++) this->titles[i].UpdateText(newTitles[i], false);
    this->SetInvertedSingle(this->selected, true, false);

    this->OnItemSelected(index);

    this->DrawIfShown();
}

void BaseMenuPage::SetInvertedSingle(int index, bool inverted, bool draw)
{
    if(index < 0 || index > 2) return;

    titles[0].UpdateInverted(index == 0 ? inverted : !inverted, draw);
    titles[1].UpdateInverted(index == 1 ? inverted : !inverted, draw);
    titles[2].UpdateInverted(index == 2 ? inverted : !inverted, draw);
}

int BaseMenuPage::AddItem(String title)
{
    items[itemCount] = title;

    return itemCount++;
}

void BaseMenuPage::ClearItems()
{
    itemCount = 0;
}

bool BaseMenuPage::GetItem(int index, String& title)
{
    if(index < itemCount)
    {
        title = items[index];
        return true;
    }

    return false;


}

BaseMenuPage::BaseMenuPage()
{
    this->titles[0] = RectLabel(RelativePoint(0,0.05), RelativeSize(1, 0.26), "",2, Color::White, Color::Black);
    this->titles[1] = RectLabel(RelativePoint(0,0.37), RelativeSize(1, 0.26), "",2, Color::White, Color::Black);
    this->titles[2] = RectLabel(RelativePoint(0,0.69), RelativeSize(1, 0.26), "",2, Color::White, Color::Black);
    
    this->AddComponent(&titles[0]);
    this->AddComponent(&titles[1]);
    this->AddComponent(&titles[2]);
}