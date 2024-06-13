#include "Interaction/LCDMenu/LCDMenuItems.h"
#include "Interaction/LCDMenu/LCDChars.h"
#include "Interaction/InputHandler.h"
#include "Interaction/LCD.h"

LCDMenuItem* CreateOkCancelMenuItem(String title, String content, void (*onClose)(bool result))

{
    LCDMenuItem* item = new LCDMenuItem();
    item->title = title;

    item->onLoad = [content](){
        LCD::Clear();
        LCD::PrintCenterRow(content, 0, false);
        
        char bottom[16];

        memset(bottom, 254, 16);

        sprintf(bottom, "%s%s%s          %s%s%s", rightArrowStr, crossStr, leftArrowStr, rightArrowStr, tickStr, leftArrowStr);
        
        LCD::PrintCenterRow(bottom, 1, false);

    };


    item->onInput = [](BtnInput inp)
    {
        
    };

    item->periodic = [](){
        
    };

    return item;
}