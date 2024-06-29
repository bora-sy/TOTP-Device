#pragma once
#include <Arduino.h>
#include "TOTP/DateTimeProvider.h"


struct TOTPInfo
{
    uint8_t Title[15];
    uint8_t Secret[64];
    uint16_t SecretLength;

    TOTPInfo();
    TOTPInfo(uint8_t* data);

    TOTPInfo(String _title, uint8_t* _secret, uint16_t _secretLength);
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

