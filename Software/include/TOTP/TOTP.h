#pragma once
#include <Arduino.h>


struct TOTPInfo
{
    uint8_t Title[15];
    uint8_t Secret[64];

    TOTPInfo();
    TOTPInfo(uint8_t* data);

    TOTPInfo(String _title, uint8_t* _secret);
};


struct TOTP
{
    String Title;
    String Code;
    ulong Expire;

    TOTPInfo Info;

    void Regenerate();

    TOTP(TOTPInfo info);

};

