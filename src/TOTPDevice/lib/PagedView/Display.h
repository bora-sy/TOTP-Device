#pragma once
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

enum Color
{
    Black = 0,
    White
};

struct Point;
struct RelativePoint;
struct Size;
struct RelativeSize;

struct Point
{
    int16_t x;
    int16_t y;

    Point();
    Point(int16_t _x, int16_t _y);
    
    Point operator+(Point const& obj);
    Point operator-(Point const& obj);
    Point operator*(Point const& obj);
    Point operator/(Point const& obj);
};



struct RelativePoint
{
    double x;
    double y;

    RelativePoint(double _x, double _y);
    RelativePoint(Point p, Size size);

    Point ToPoint(Size size);

    RelativePoint operator+(RelativePoint const& obj);
    RelativePoint operator-(RelativePoint const& obj);
    RelativePoint operator*(RelativePoint const& obj);
    RelativePoint operator/(RelativePoint const& obj);
};

struct Size
{
    uint16_t width;
    uint16_t height;

    Size() {}
    Size(uint16_t _width, uint16_t _height);

    Point GetCenter(Point offset = Point(0, 0));

    
    Size operator+(Size const& obj);
    Size operator-(Size const& obj);
    Size operator*(Size const& obj);
    Size operator/(Size const& obj);
};

struct RelativeSize
{
    double width;
    double height;

    RelativeSize() {}
    RelativeSize(double _width, double _height);

    
    Size ToSize(Size size);

    
    RelativeSize operator+(RelativeSize const& obj);
    RelativeSize operator-(RelativeSize const& obj);
    RelativeSize operator*(RelativeSize const& obj);
    RelativeSize operator/(RelativeSize const& obj);
};


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

namespace Display
{
    
    const Size displaySize = Size(SCREEN_WIDTH, SCREEN_HEIGHT);

    bool Begin();
    void Update();
    void Clear(bool update = false);

    
    void DrawRect(RelativePoint rp, RelativeSize rs, bool fill, int16_t fillet, Color color, RelativePoint anchor, bool update = false);
    void DrawRect(Point p, Size s, bool fill, int16_t fillet, Color color, RelativePoint anchor, bool update = false);

    void DrawText(Point p, String text, uint8_t textSize, Color color, RelativePoint anchor, bool update = false);
    
    void DrawText(RelativePoint p, String text, uint8_t textSize, Color color, RelativePoint anchor, bool update = false);



}
