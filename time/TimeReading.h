/*
 * TimeReading.h
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#ifndef TIMEREADING_H_
#define TIMEREADING_H_

#include <WireRtcLib.h>

#include "../PeripheryReading.h"

class TimeReading : public PeripheryReading {
private:
    WireRtcLib::tm time;
    unsigned long timeStamp;

public:
    TimeReading(WireRtcLib::tm time);
    TimeReading();

    WireRtcLib::tm getTime() const {
        return time;
    }

    unsigned long getTimeStamp() const {
        return timeStamp;
    }

    void timeToStr(char * buffer) const;
};

#endif /* TIMEREADING_H_ */
