#include "Interaction/Components/Label.h"

void Label::Draw()
{
    /*
    Display::DrawLine(Point(64, 0), Point(64,64), Color::White);
    Display::DrawLine(Point(63, 0), Point(63,64), Color::White);

    Display::DrawLine(Point(0, 32), Point(128,32), Color::White);
    Display::DrawLine(Point(0, 31), Point(128,31), Color::White);

    */

    Display::DrawText(this->pos, this->text, this->textSize, this->color, this->anchor);
}

Label::Label(){}

Label::Label(Point _p, String _text, uint8_t _textSize, Color _color, RelativePoint _anchor)
{
    this->pos = _p;
    this->text = _text;
    this->textSize = _textSize;
    this->anchor = _anchor;
    this->color = _color;
}

Label::Label(RelativePoint _rp, String _text, uint8_t _textSize, Color _color, RelativePoint _anchor)
{
    this->pos = _rp.ToPoint(Display::displaySize);
    this->text = _text;
    this->textSize = _textSize;
    this->anchor = _anchor;
    this->color = _color;
}

void Label::UpdateText(String _text, bool draw)
{
    Serial.printf("Updating label (parent: %d)\n", (int)this->parentPage);
    this->text = _text;
    
    if(draw)
    this->parentPage->DrawIfShown();
}

void Label::UpdateColor(Color _color, bool draw)
{
    this->color = _color;
    
    if(draw)
    this->parentPage->DrawIfShown();
}

void Label::UpdateTextSize(uint8_t _textSize, bool draw)
{
    this->textSize = _textSize;
    
    if(draw)
    this->parentPage->DrawIfShown();
}