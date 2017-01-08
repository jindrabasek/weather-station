/*
 * PublishUtils.cpp
 *
 *  Created on: 7. 1. 2017
 *      Author: jindra
 */

#include "PublishUtils.h"

#include <avr/pgmspace.h>
#include <math.h>
#include <Print.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <WireRtcLib.h>
#include <WString.h>

#include "../ProgramSettings.h"
#include "../ProgramState.h"

extern ProgramState *state;
using namespace WeatherStation;

bool PublishUtils::getAssetId(char* buffer, uint8_t valueId, const char * const * const assetIds, size_t maxSize) {
    char* assetIdAddr = (char*) pgm_read_word(&(assetIds[valueId]));
    if (assetIdAddr == NULL) {
        return false;
    }
    strncpy_P(buffer, assetIdAddr, maxSize);
    return true;
}

#define printTimePart(timePart, separator) if(timePart < 10) out.print('0'); itoa(timePart, buffer, 10); out.print(buffer); out.print(separator)
void PublishUtils::formatTime(Print & out, unsigned long timeStamp) {
    ProgramSettings & settings = state->getSettings();

    WireRtcLib::tm time = WireRtcLib::breakTime(timeStamp);
    char buffer[5];

    printTimePart(time.year, '-');
    printTimePart(time.mon, '-');
    printTimePart(time.mday, 'T');
    printTimePart(time.hour, ':');
    printTimePart(time.min, ':');
    printTimePart(time.sec, settings.getTimeZone() < 0 ? '-' : '+');
    printTimePart(settings.getTimeZone(), F(":00"));
}

size_t PublishUtils::numberOfDigits(double number, uint16_t floatDigits) {
    size_t n = 0;

    if (isnan(number) || isinf(number) || number > 4294967040.0
            || number < -4294967040.0) {
        return 3;
    }

    // Handle negative numbers
    if (number < 0.0) {
        n++;
    }

    unsigned long int_part = (unsigned long) number;

    do {
        n++;
        int_part /= 10;
    } while (int_part);

    if (floatDigits > 0) {
        n += 1 + floatDigits;
    }

    return n;
}

size_t PublishUtils::numberOfDigits(long number) {
    size_t n = 0;

    // Handle negative numbers
    if (number < 0) {
        n++;
    }

    do {
        n++;
        number /= 10;
    } while (number);

    return n;
}
