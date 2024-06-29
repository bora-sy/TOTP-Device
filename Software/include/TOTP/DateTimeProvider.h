#pragma once
#include <Arduino.h>
#include <Ds1302.h>
#include "Pins.h"
#include "uUnixDate.h"

namespace DateTimeProvider
{    
    bool Initialize();

    int64_t GetUnixTime();

    void Set(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
    
    void Set(int64_t unix);
}