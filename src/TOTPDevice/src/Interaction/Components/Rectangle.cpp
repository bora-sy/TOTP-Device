#include "Interaction/Components/Rectangle.h"

void Rectangle::Draw()
{
    PagedView::display.drawRect(0,0,50,50, WHITE);
}