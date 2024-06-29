#include "Interaction/Components/RectLabel.h"

void RectLabel::Draw()
{
    Color c_rect = this->colorsInverted ? this->textColor : this->rectColor;
    Color c_text = this->colorsInverted ? this->rectColor : this->textColor;

    Display::DrawRect(this->pos, this->size, true, 0, c_rect, this->anchor, false);
    Display::DrawText(this->pos + Point(this->size.width / 2, this->size.height / 2) + Point(0, 1), this->text, this->textSize, c_text, this->anchor + RelativePoint(0.5, 0.5), false);
}

RectLabel::RectLabel(){}




RectLabel::RectLabel(Point _p, Size _s, String _text, uint8_t _textSize, Color _textColor, Color _rectColor, RelativePoint _anchor)
{
    this->pos = _p;
    this->size = _s;
    this->text = _text;
    this->textSize = _textSize;
    this->textColor = _textColor;
    this->rectColor = _rectColor;
    this->anchor = _anchor;
}


RectLabel::RectLabel(RelativePoint _rp, RelativeSize _rs, String _text, uint8_t _textSize, Color _textColor, Color _rectColor, RelativePoint _anchor)
{
    Point p = _rp.ToPoint(Display::displaySize);
    Size s = _rs.ToSize(Display::displaySize);

    this->pos = p;
    this->size = s;
    this->text = _text;
    this->textSize = _textSize;
    this->textColor = _textColor;
    this->rectColor = _rectColor;
    this->anchor = _anchor;
}


void RectLabel::UpdateText(String _text, bool draw)
{
    this->text = _text;

    if(draw)
    this->parentPage->DrawIfShown();
}

void RectLabel::UpdateInverted(bool _inverted, bool draw)
{
    this->colorsInverted = _inverted;

    if(draw)
    this->parentPage->DrawIfShown();
}