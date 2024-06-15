#pragma once
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

enum BtnInput
{
    Up,
    Enter,
    Down
};

struct Point
{
    uint8_t x;
    uint8_t y;

    Point() {}
    Point(uint8_t _x, uint8_t _y) : x(_x), y(_y) {}
};

struct Size
{
    uint8_t width;
    uint8_t height;

    Size() {}
    Size(uint8_t _width, uint8_t _height);

    Point GetCenter(Point offset = Point(0, 0));
};


struct RelativePoint
{
    double x;
    double y;

    RelativePoint(double _x, double _y);
    RelativePoint(Point p, Size size);

    Point ToPoint(Size size);
};

class PageComponent
{
public:
    virtual void ToggleVisibility() = 0;
    virtual void Draw() = 0;
};

class Page
{
    private:
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
    void Draw();
    
};

class PageComponent
{
    private:
    bool visible = true;
    Page* parentPage = nullptr;
    Point pos = Point(0, 0);

    public:
    PageComponent(Page* _parentPage, Point _pos);
    PageComponent(Page *_parentPage, RelativePoint _pos);

    void SetVisible(bool v);
    bool IsVisible();

    virtual void Draw() = 0;
};

namespace PagedView
{
    Adafruit_SSD1306 display;

    bool Begin();
    void HandleInput(BtnInput input);
    void Periodic();
    void SwitchToPage(Page *page);
    Page* GetCurrentPage();
}