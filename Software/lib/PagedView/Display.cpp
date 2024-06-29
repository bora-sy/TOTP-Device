#include "Display.h"

#define SSD1306_NO_SPLASH

#define SCREEN_ADDR 0x3C

namespace Display
{

    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


    bool Begin()
    {
        if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR))
            return false;

        Clear();

        return true;
    }

    void Update()
    {
        display.display();
    }

    void Clear(bool update)
    {
        display.clearDisplay();
        if (update)
            Update();
    }

    void SetCursor(Point p)
    {
        display.setCursor(p.x, p.y);
    }

    Size GetTextSize(String text, uint8_t textSize)
    {
        Point UL;
        Size size;

        display.setTextSize(textSize);

        display.getTextBounds(text, 0,0, &UL.x, &UL.y, &size.width, &size.height);

        return size;
    }

    //--------------------------------------------------------------------------------

    void DrawRect(Point p, Size s, bool fill, int16_t fillet, Color color, RelativePoint anchor, bool update)
    {
        
        if (fillet > 0)
        {
            if (fill)
                display.fillRoundRect(p.x, p.y, s.width, s.height, fillet, color);
            else
                display.drawRoundRect(p.x, p.y, s.width, s.height, fillet, color);
        }
        else
        {
            if (fill)
                display.fillRect(p.x, p.y, s.width, s.height, color);
            else
                display.drawRect(p.x, p.y, s.width, s.height, color);
        }

        if (update)
            Update();
    }

    void DrawRect(RelativePoint rp, RelativeSize rs, bool fill, int16_t fillet, Color color, RelativePoint anchor, bool update)
    {
        Point p = rp.ToPoint(displaySize);
        Size s = rs.ToSize(displaySize);
        
        DrawRect(p,s,fill,fillet,color,anchor,update);
    }

    void DrawText(Point p, String text, uint8_t textSize, Color color, RelativePoint anchor, bool update)
    {

        Size size = GetTextSize(text, textSize);

        Point offset = anchor.ToPoint(size);

        Point pos = p - offset;

        display.setTextSize(textSize);
        display.setTextColor(color);
        SetCursor(pos);
        display.print(text);
        //DrawRect(pos, size, false, 0, Color::White);

        if (update)
            Update();
    }

    void DrawText(RelativePoint p, String text, uint8_t textSize, Color color, RelativePoint anchor, bool update)
    {
        DrawText(p.ToPoint(displaySize), text, textSize, color, anchor, update);
    }
}

// SIZE
Size::Size(uint16_t _width, uint16_t _height) : width(_width), height(_height) {}

Point Size::GetCenter(Point offset)
{
    return Point((width / 2) + (offset.x / 2), (height / 2) + (offset.y / 2));
}

Size Size::operator+(Size const &obj)
{
    return Size(width + obj.width, height + obj.height);
}

Size Size::operator-(Size const &obj)
{
    return Size(width - obj.width, height - obj.height);
}

Size Size::operator*(Size const &obj)
{
    return Size(width * obj.width, height * obj.height);
}

Size Size::operator/(Size const &obj)
{
    return Size(width / obj.width, height / obj.height);
}

// RELATIVE SIZE
RelativeSize::RelativeSize(double _width, double _height)
{

    _width = _width > 1 ? 1 : _width;
    _height = _height > 1 ? 1 : _height;

    _width = _width < 0 ? 0 : _width;
    _height = _height < 0 ? 0 : _height;


    this->width = _width;
    this->height = _height;
}

Size RelativeSize::ToSize(Size size)
{
    width = width > 1 ? 1 : width;
    height = height > 1 ? 1 : height;
    
    width = width < 0 ? 0 : width;
    height = height < 0 ? 0 : height;


    double absWidth = width * (double)size.width;
    double absHeight = height * (double)size.height;

    return Size(absWidth, absHeight);    

}

RelativeSize RelativeSize::operator+(RelativeSize const& obj){return RelativeSize(width + obj.width, height + obj.height);}
RelativeSize RelativeSize::operator-(RelativeSize const& obj){return RelativeSize(width - obj.width, height - obj.height);}
RelativeSize RelativeSize::operator*(RelativeSize const& obj){return RelativeSize(width * obj.width, height * obj.height);}
RelativeSize RelativeSize::operator/(RelativeSize const& obj){return RelativeSize(width / obj.width, height / obj.height);}

// POINT

Point::Point(int16_t _x, int16_t _y) : x(_x), y(_y) {}
Point::Point() {}

Point Point::operator+(Point const &obj) { return Point(x + obj.x, y + obj.y); }
Point Point::operator-(Point const &obj) { return Point(x - obj.x, y - obj.y); }
Point Point::operator*(Point const &obj) { return Point(x * obj.x, y * obj.y); }
Point Point::operator/(Point const &obj) { return Point(x / obj.x, y / obj.y); }

// RELATIVE POINT

RelativePoint::RelativePoint(Point p, Size s)
{
    this->x = (double)p.x / (double)s.width;
    this->y = (double)p.y / (double)s.height;
}

RelativePoint::RelativePoint(double _x, double _y)
{

    _x = _x > 1 ? 1 : _x;
    _x = _x < 0 ? 0 : _x;

    _y = _y > 1 ? 1 : _y;
    _y = _y < 0 ? 0 : _y;

    this->x = _x;
    this->y = _y;
}

Point RelativePoint::ToPoint(Size size)
{

    x = x > 1 ? 1 : x;
    x = x < 0 ? 0 : x;

    y = y > 1 ? 1 : y;
    y = y < 0 ? 0 : y;

    double absX = x * (double)size.width;
    double absY = y * (double)size.height;

    return Point(absX, absY);
}

RelativePoint RelativePoint::operator+(RelativePoint const &obj) { return RelativePoint(x + obj.x, y + obj.y); }
RelativePoint RelativePoint::operator-(RelativePoint const &obj) { return RelativePoint(x - obj.x, y - obj.y); }
RelativePoint RelativePoint::operator*(RelativePoint const &obj) { return RelativePoint(x * obj.x, y * obj.y); }
RelativePoint RelativePoint::operator/(RelativePoint const &obj) { return RelativePoint(x / obj.x, y / obj.y); }