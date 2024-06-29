#pragma once
#include <PagedView.h>

class RectLabel : public PageComponent
{
private:
    Size size;
    String text;
    Color textColor;
    Color rectColor;
    uint8_t textSize;

    bool colorsInverted = false;

public:
    void Draw() override;
    RectLabel();

    RectLabel(RelativePoint _rp, RelativeSize _rs, String _text, uint8_t _textSize, Color _textColor, Color _rectColor, RelativePoint _anchor = RelativePoint(0,0));
    RectLabel(Point _p, Size _s, String _text, uint8_t _textSize, Color _textColor, Color _rectColor, RelativePoint _anchor = RelativePoint(0,0));


    void UpdateText(String _text, bool draw = true);

    void UpdateInverted(bool _inverted, bool draw = true);
};