/*
 * TimeReading.cpp
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#include "TimeReading.h"

#include <stdio.h>
#include <WireRtcLib.h>
#include <WString.h>

#include "../PeripheryReading.h"

TimeReading::TimeReading(WireRtcLib::tm time) :
        PeripheryReading(time.error ? ReadState::READ_ERROR : ReadState::READ_OK),
        time(time) {
    if (!time.error) {
        timeStamp = WireRtcLib::makeTime(time);
    } else {
        timeStamp = 0;
    }
}

TimeReading::TimeReading() :
        PeripheryReading(ReadState::NOT_YET_READ),
        timeStamp(0) {
}

void TimeReading::timeToStr(char * buffer) const {
    if (getReadState() == ReadState::READ_OK) {
        snprintf_P(buffer, 9, (const char *) F("%02d:%02d:%02d"), time.hour,
                time.min, time.sec);
    } else {
        snprintf_P(buffer, 9, (const char *) F("??:??:??"));
    }
}

