#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

namespace LCD
{
    const int LCD_COLS = 16;
    const int LCD_ROWS = 2;

    LiquidCrystal_I2C display(0x27, LCD_COLS, LCD_ROWS);


    void CreateCustomChars()
    {
        uint8_t arr1[] = {
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b10000
        };

        uint8_t arr2[] ={
            0b11000,
            0b11000,
            0b11000,
            0b11000,
            0b11000,
            0b11000,
            0b11000
        };

        uint8_t arr3[] ={
            0b11100,
            0b11100,
            0b11100,
            0b11100,
            0b11100,
            0b11100,
            0b11100
        };

        uint8_t arr4[] = {
            0b11110,
            0b11110,
            0b11110,
            0b11110,
            0b11110,
            0b11110,
            0b11110
        };

        uint8_t arr5[] = {
            0b00000,
            0b00000,
            0b00001,
            0b00010,
            0b10100,
            0b01000,
            0b00000
        };

        uint8_t arr6[] = {
            0b00000,
            0b10001,
            0b01010,
            0b00100,
            0b01010,
            0b10001,
            0b00000
        };
        
        display.createChar(1, arr1);
        display.createChar(2, arr2);
        display.createChar(3, arr3);
        display.createChar(4, arr4);
        display.createChar(5, arr5);
        display.createChar(6, arr6);


    }

    bool Initialize()
    {
        Wire.setClock(400000);
        bool suc = display.init();

        CreateCustomChars();

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

    void Print(const char* str, uint8_t col = 0, uint8_t row = 0, bool clear = true)
    {
        if (clear) ClearRow(row);

        display.setCursor(col, row);
        display.print(str);
    }

    void Print(String str, uint8_t col = 0, uint8_t row = 0, bool clear = true)
    {
        Print(str.c_str(), col, row, clear);
    }



    void PrintCenterRow(String str, uint8_t row = 0, bool clear = true, uint8_t offset = 0)
    {
        offset = offset < 0 ? 0 : offset;

        String string(str);
        string.trim();
        if(string.length() > LCD_COLS - offset)
        {
            Print(string, offset, row, clear);
        }

        uint8_t pos = (LCD_COLS - offset - string.length()) / 2;
        if(pos < offset) pos = offset;

        if(string.length() > LCD_COLS - offset) string = string.substring(0, LCD_COLS + 1 - offset);

        Print(string, pos, row, clear);
    }

    void PrintCenterRow(char *str, uint8_t row = 0, bool clear = true, uint8_t offset = 0)
    {
        String string(str);

        PrintCenterRow(string, row, clear);
    }

    void PrintCenterRow(const char *str, uint8_t row = 0, bool clear = true, uint8_t offset = 0)
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


    void LCDCharTest(uint8_t triggerButtonPin)
    {
        pinMode(triggerButtonPin, INPUT_PULLUP);

        int c = 0;

        while (true)
        {
            char str[17];
            memset(str, 0, 17);
            String ser = "";

            for(int i = 0; i < 16; i++)
            {
                uint8_t num = (c * 16) + i + 1;
                str[i] = num;
                ser += String(num) + " / ";
            }

            PrintCenterRow(str, 0, true);
            Serial.println(ser);


            while (digitalRead(triggerButtonPin)) delay(10);
            delay(200);

            c++;
            
        }
        
    }

}