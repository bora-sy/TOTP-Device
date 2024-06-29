#pragma once
#include <PagedView.h>

class Progressbar : public PageComponent
{
private:
    Size size;
    Color color;
    uint16_t maxValue;
    uint16_t value;

public:
    void Draw() override;
    Progressbar();

    Progressbar(RelativePoint _rp, RelativeSize _size, Color _color, uint16_t _maxValue, uint16_t _value = 0, RelativePoint _anchor = RelativePoint(0,0));


    void UpdateValue(uint16_t _value, bool draw = true);
};