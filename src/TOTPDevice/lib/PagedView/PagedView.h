#pragma once

#include <Arduino.h>
#include "Display.h"

enum BtnInput
{
    NONE = 0,  // 000
    Up = 1,    // 001
    Enter = 2, // 010
    Down = 4   // 100
};

class Page;

class PageComponent
{
    protected:
    bool visible = true;
    Point pos = Point(0, 0);
    RelativePoint anchor = RelativePoint(0,0);
    Page* parentPage = nullptr;

    public:

    void SetVisible(bool v);
    bool IsVisible();

    void SetParentPage(Page* _page);

    virtual void Draw() = 0;
};

class Page
{
    protected:
    PageComponent* components[32];
    uint8_t componentsCount = 0;

    
    void AddComponent(PageComponent* component);

public:
    void Show();
    void ShowDialog();
    void Close();
    bool IsShown();

    virtual void OnLoad() = 0;
    virtual void OnExit() = 0;
    virtual void OnInput(BtnInput input) = 0;
    virtual void Periodic() = 0;
    void DrawIfShown();
    
};


namespace PagedView
{

    bool Begin();
    void HandleInput(BtnInput input);
    void Periodic();
    void SwitchToPage(Page *page);
    Page* GetCurrentPage();
}