#include "Interaction/Pages/MenuPage.h"





void MenuPage::OnLoad()
{
}

void MenuPage::OnExit()
{
    
}


int i = 0;
void MenuPage::OnInput(BtnInput input)
{
    Titles[i].UpdateInverted(false);

    switch (input)
    {
    case BtnInput::Up: i++; break;
    case BtnInput::Down: i--; break;
    case BtnInput::Enter: Titles[i].UpdateText("Selected99"); break;
    }

    i = i < 0 ? 0 : i;
    i = i > 2 ? 2 : i;

    Titles[i].UpdateInverted(true);




}


void MenuPage::Periodic()
{

}

MenuPage::MenuPage()
{
    this->Titles[0] = RectLabel(RelativePoint(0,0.05), RelativeSize(1, 0.26), "Menu1",2, Color::White, Color::Black);
    this->Titles[1] = RectLabel(RelativePoint(0,0.37), RelativeSize(1, 0.26), "Menu2",2, Color::White, Color::Black);
    this->Titles[2] = RectLabel(RelativePoint(0,0.69), RelativeSize(1, 0.26), "Menu3",2, Color::White, Color::Black);
    
    this->AddComponent(&Titles[0]);
    this->AddComponent(&Titles[1]);
    this->AddComponent(&Titles[2]);

    Titles[0].UpdateInverted(true);
}