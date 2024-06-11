#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

namespace LCD
{
    const int LCD_COLS = 16;
    const int LCD_ROWS = 2;

    LiquidCrystal_I2C display(0x27, LCD_COLS, LCD_ROWS);

    bool Initialize()
    {
        //Wire.setClock(10000);
        bool suc = display.init();
        display.backlight();
        display.clear();
        
        return suc;
    }

    void ClearRow(uint8_t row)
    {
        display.setCursor(0, row);
        display.print(F("                "));
        delay(50);
    }

    void Clear()
    {
        display.clear();
        delay(50);
    }

    void Refresh()
    {
        display.Refresh();
    }

    void ToggleBlink(bool state)
    {
        if(state) display.blink();
        else display.noBlink();
    }

    void SetCursor(uint8_t col, uint8_t row)
    {
        display.setCursor(col, row);
    }

    void Print(String str, uint8_t col = 0, uint8_t row = 0, bool clear = true)
    {
        if (clear) ClearRow(row);

        display.setCursor(col, row);
        display.print(str);
    }

    void PrintCenterRow(String str, uint8_t row = 0, bool clear = true)
    {
        String string(str);
        string.trim();
        if(string.length() > LCD_COLS)
        {
            Print(string, 0, row, clear);
        }

        uint8_t pos = (LCD_COLS - string.length()) / 2;

        if(string.length() > LCD_COLS) string = string.substring(0, LCD_COLS + 1);

        Print(string, pos, row, clear);
    }

    void PrintCenterRow(char *str, uint8_t row = 0, bool clear = true)
    {
        String string(str);

        PrintCenterRow(string, row, clear);
    }

    void PrintCenterRow(const char *str, uint8_t row = 0, bool clear = true)
    {
        PrintCenterRow((char *)str, row, clear);
    }

    
    void PrintCenter(String string, bool clear = true)
    {
        if (string.length() <= LCD_COLS)
        {
            Clear();
            PrintCenterRow(string, 0, false);
            return;
        }

        for (int i = string.length() - 1; i >= 0; i--)
        {
            if (string.charAt(i) == ' ')
            {
                String first = string.substring(0, i);
                String second = string.substring(i + 1);

                first.trim();
                second.trim();

                if (first.length() <= LCD_COLS && second.length() <= LCD_COLS)
                {
                    if(clear) Clear();
                    PrintCenterRow(first, 0, false);
                    PrintCenterRow(second, 1, false);
                    return;
                }
            }
        }

        PrintCenterRow(string, 0, clear);
    }

    void PrintCenter(char *str, bool clear = true)
    {
        String string(str);

        PrintCenter(string, clear);
    }

    void PrintCenter(const char *str, bool clear = true)
    {
        PrintCenter((char *)str, clear);
    }

}