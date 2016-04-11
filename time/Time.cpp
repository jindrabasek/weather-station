/*
 * TimeTask.cpp
 *
 *  Created on: 25. 1. 2016
 *      Author: jindra
 */

#include "Time.h"

#include <Arduino.h>
#include <stdbool.h>
#include <WireRtcLib.h>

#include "../PeripheryReading.h"

TimeReading& Time::getTime(bool updateFirst) {
    if (updateFirst) {
        readTimeFromRtc();
    }
    return actualTime;
}

void Time::readTimeFromRtc() {
    if (timeAge - millis() > READ_AT_MOST_EVERY_N_MS || timeAge - millis() < 0
            || actualTime.getReadState() == NOT_YET_READ
            || actualTime.getReadState() == READ_ERROR) {

        if (actualTime.getReadState() == NOT_YET_READ
                || actualTime.getReadState() == READ_ERROR) {
            rtc.begin();
        }

        timeAge = millis();
        actualTime = TimeReading(rtc.getTime());
    }
}

Time::Time() :
        timeAge(0) {
}
