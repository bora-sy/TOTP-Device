#include "TOTP/TOTP.h"
#include <Hash.h>


void TOTP::Regenerate()
{
    long unix = DateTimeProvider::GetUnixTime();
    int64_t counter = unix / 30;

    
    this->Expire = (counter + 1) * 30;
    this->Title = String((char*)this->Info.Title);
    
    uint8_t* counterBytes = (uint8_t*)&counter;
    uint8_t* secret = this->Info.Secret;

    std::reverse(counterBytes, counterBytes + 8);

    // SHA1 HMAC

    uint8_t oKeyPad[64];
    uint8_t iKeyPad[64];

    for (int i = 0; i < 64; i++)
    {
        oKeyPad[i] = (byte)(0x5C ^ secret[i]);
        iKeyPad[i] = (byte)(0x36 ^ secret[i]);
    }
    
    uint8_t innerBytes[72];

    memcpy(innerBytes, iKeyPad, 64);
    memcpy(innerBytes + 64, counterBytes, 8);

    uint8_t innerHash[20];
    
    sha1(innerBytes, 72, innerHash);

    uint8_t hmacBytes[84];
    memcpy(hmacBytes, oKeyPad, 64);
    memcpy(hmacBytes + 64, innerHash, 20);

    uint8_t hmacHash[20];

    sha1(hmacBytes, 84, hmacHash);

    int offset = hmacHash[19] & 0xf;
    int bin_code = (hmacHash[offset] & 0x7f) << 24 |
                   (hmacHash[offset + 1] & 0xff) << 16 |
                   (hmacHash[offset + 2] & 0xff) << 8 |
                   (hmacHash[offset + 3] & 0xff);
    
    int code = bin_code % 1000000;
    
    String codeStr = String(code);

    while (codeStr.length() < 6)
    {
        codeStr = "0" + codeStr;
    }

    this->Code = codeStr.substring(0, 3) + " " + codeStr.substring(3, 6);
}

TOTP::TOTP(TOTPInfo info)
{
    this->Info = info;
    this->Regenerate();
}


//----------------------------------------------

TOTPInfo::TOTPInfo(){}

TOTPInfo::TOTPInfo(uint8_t *data)
{
    memset(Title, 0, 15);
    memset(Secret, 0, 64);

    memcpy(Title, data, 15);
    memcpy(Secret, data + 15, 64);
}

TOTPInfo::TOTPInfo(String _title, uint8_t *_secret, uint16_t _secretLength)
{
    _secretLength = _secretLength > 64 ? 64 : _secretLength;

    memset(Title, 0, 15);
    memset(Secret, 0, 64);

    if (_title.length() > 14)
    {
        _title = _title.substring(0, 13);
    }

    strcpy((char *)Title, _title.c_str());

    memcpy(Secret, _secret, _secretLength);
    this->SecretLength = _secretLength;
}