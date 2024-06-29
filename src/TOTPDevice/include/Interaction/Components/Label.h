#pragma once
#include <PagedView.h>

class Label : public PageComponent
{
private:
    String text;
    Color color;
    uint8_t textSize;

public:
    void Draw() override;
    Label();
    Label(Point _p, String _text, uint8_t _textSize, Color _color, RelativePoint _anchor = RelativePoint(0,0));

    Label(RelativePoint _rp, String _text, uint8_t _textSize, Color _color, RelativePoint _anchor = RelativePoint(0,0));


    void UpdateText(String _text, bool draw = true);
    void UpdateColor(Color _color, bool draw = true);
    void UpdateTextSize(uint8_t _textSize, bool draw = true);
};