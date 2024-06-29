#include "TOTP/TOTP.h"

void TOTP::Regenerate()
{
}

TOTP::TOTP(TOTPInfo info)
{

}

TOTPInfo::TOTPInfo()
{
    
}

TOTPInfo::TOTPInfo(uint8_t *data)
{
    memset(Title, 0, 15);
    memset(Secret, 0, 64);

    memcpy(Title, data, 15);
    memcpy(Secret, data + 15, 64);
}

TOTPInfo::TOTPInfo(String _title, uint8_t *_secret)
{
    memset(Title, 0, 15);
    memset(Secret, 0, 64);

    if (_title.length() > 14)
    {
        _title = _title.substring(0, 13);
    }

    strcpy((char *)Title, _title.c_str());
    memcpy(Secret, _secret, 64);
}