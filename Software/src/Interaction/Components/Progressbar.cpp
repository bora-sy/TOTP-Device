#include "Interaction/Components/Progressbar.h"

void Progressbar::Draw()
{

    uint8_t width = map(this->value, 0, maxValue, 0, this->size.width);


    Size rectSize = Size(width, this->size.height);


    Display::DrawRect(pos, rectSize, true, 0, this->color, anchor);
}

Progressbar::Progressbar(){}

Progressbar::Progressbar(RelativePoint _rp, RelativeSize _size, Color _color, uint16_t _maxValue, uint16_t _value, RelativePoint _anchor)
{
    this->pos = _rp.ToPoint(Display::displaySize);
    this->size = _size.ToSize(Display::displaySize);

    this->color = _color;
    this->maxValue = _maxValue;
    this->value = _value;
    this->anchor = _anchor;
}

void Progressbar::UpdateValue(uint16_t _value, bool draw)
{
    _value = _value > maxValue ? maxValue : _value;

    this->value = _value;
    
    if(draw)
    this->parentPage->DrawIfShown();
}