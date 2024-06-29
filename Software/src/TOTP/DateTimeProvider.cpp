#include "TOTP/DateTimeProvider.h"

namespace DateTimeProvider
{
    Ds1302 RTC(PIN_ENA, PIN_CLK, PIN_DAT);

    bool Initialize()
    {
        RTC.init();
        
        return !RTC.isHalted();
    }

    int64_t GetUnixTime()
    {
        Ds1302::DateTime rtcdt;
        RTC.getDateTime(&rtcdt);
        Serial.printf("%d.%d.%d %d:%d:%d\n", rtcdt.year + 2000, rtcdt.month, rtcdt.day, rtcdt.hour, rtcdt.minute, rtcdt.second);
        uUnixDate unixdt = uUnixDate(rtcdt.year + 2000, rtcdt.month, rtcdt.day, rtcdt.hour, rtcdt.minute, rtcdt.second);
        
        return (int64_t)unixdt.timestamp();
    }

    void Set(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
    {
        Ds1302::DateTime rtcdt;
        rtcdt.year = year - 2000;
        rtcdt.month = month;
        rtcdt.day = day;
        rtcdt.hour = hour;
        rtcdt.minute = minute;
        rtcdt.second = second;
        RTC.setDateTime(&rtcdt);
    }
    
    void Set(int64_t unix)
    {
        uUnixDate unixdt = uUnixDate(unix);

        Ds1302::DateTime rtcdt;
        rtcdt.year = unixdt.year() - 2000;
        rtcdt.month = unixdt.month();
        rtcdt.day = unixdt.day();
        rtcdt.hour = unixdt.hour();
        rtcdt.minute = unixdt.minute();
        rtcdt.second = unixdt.second();

        RTC.setDateTime(&rtcdt);
    }


}