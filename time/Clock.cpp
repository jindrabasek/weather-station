/*
 * TimeTask.cpp
 *
 *  Created on: 25. 1. 2016
 *      Author: jindra
 */

#include "Clock.h"

#include <Arduino.h>
#include <stdbool.h>
#include <WireRtcLib.h>

#include "../PeripheryReading.h"

TimeReading& Clock::getTime(bool updateFirst) {
    if (updateFirst) {
        readTimeFromRtc();
    }
    return actualTime;
}

void Clock::readTimeFromRtc() {
    if (timeAge - millis() > READ_AT_MOST_EVERY_N_MS || timeAge - millis() < 0
            || actualTime.getReadState() == ReadState::NOT_YET_READ
            || actualTime.getReadState() == ReadState::READ_ERROR) {

        WireRtcLib rtc;

        if (actualTime.getReadState() == ReadState::NOT_YET_READ
                || actualTime.getReadState() == ReadState::READ_ERROR) {
            rtc.begin();
        }

        timeAge = millis();
        actualTime = TimeReading(rtc.getTime());
    }
}

Clock::Clock() :
        timeAge(0) {
}
