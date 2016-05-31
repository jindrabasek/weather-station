/*
 * TimeTask.cpp
 *
 *  Created on: 25. 1. 2016
 *      Author: jindra
 */

#include <time/Clock.h>

#ifdef USE_RTC

#include <Arduino.h>
#include <stdbool.h>
#include <stdio.h>
#include <WireRtcLib.h>
#include <WString.h>


WireRtcLib::tm Clock::actualTime;
unsigned long Clock::timeAge = 0;

WireRtcLib::tm& Clock::getTime(bool updateFirst) {
    if (updateFirst) {
        readTimeFromRtc();
    }
    return actualTime;
}

void Clock::readTimeFromRtc() {
    if (timeAge - millis() > READ_AT_MOST_EVERY_N_MS || timeAge - millis() < 0
            || actualTime.error) {

        WireRtcLib rtc;

        if (actualTime.error) {
            rtc.begin();
        }

        timeAge = millis();
        actualTime = rtc.getTime();
    }
}

void Clock::timeToStr(const WireRtcLib::tm & time, char * buffer) {
    if (!time.error) {
        snprintf_P(buffer, 9, (const char *) F("%02d:%02d:%02d"), time.hour,
                time.min, time.sec);
    } else {
        snprintf_P(buffer, 9, (const char *) F("??:??:??"));
    }
}

#endif
