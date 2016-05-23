/*
 * TimeScreen.cpp
 *
 *  Created on: 26. 1. 2016
 *      Author: jindra
 */

#include "TimeScreen.h"

#include <LCD.h>
#include <stdbool.h>
#include <stdio.h>
#include <WireRtcLib.h>
#include <WString.h>

#include "Clock.h"

void TimeScreen::draw(LCD & display) {
    char buffer[11];

    WireRtcLib::tm & actualTime = Clock::getTime(true);

    if (!actualTime.error) {
        snprintf_P(buffer, 9, (const char *) F("%02d:%02d:%02d"),
                actualTime.hour, actualTime.min,
                actualTime.sec);
        display.setCursor(6, 1);
        display.print(buffer);
        snprintf_P(buffer, 11, (const char *) F("%02d.%02d.%04d"),
                actualTime.mday, actualTime.mon,
                actualTime.year);
        display.setCursor(5, 2);
        display.print(buffer);
    } else {
        snprintf_P(buffer, 9, (const char *) F("??:??:??"));
        display.setCursor(6, 1);
        display.print(buffer);
        snprintf_P(buffer, 11, (const char *) F("??.??.????"));
        display.setCursor(5, 2);
        display.print(buffer);
    }
}
