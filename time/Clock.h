/*
 * TimeTask.h
 *
 *  Created on: 25. 1. 2016
 *      Author: jindra
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdbool.h>
#include <WireRtcLib.h>

#include "TimeReading.h"


#define READ_AT_MOST_EVERY_N_MS 500

class Clock {
private:
    TimeReading actualTime;
    unsigned long timeAge;
    WireRtcLib rtc;

public:
    Clock();

    Clock(const Clock& that) = delete;
    void operator=(const Clock& that) = delete;

    TimeReading& getTime(bool updateFirst = false);

    WireRtcLib & getRtc() {
        return rtc;
    }

private:
    void readTimeFromRtc();
};

#endif /* CLOCK_H_ */
