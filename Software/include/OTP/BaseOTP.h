#include <Arduino.h>

struct OTPCode
{
    String Code;
    ulong ExpireMS;
};


struct BaseOTP
{
    virtual String GetTitle() = 0;
    virtual OTPCode GetCode() = 0;
};
