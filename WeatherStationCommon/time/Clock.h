/*
 * TimeTask.h
 *
 *  Created on: 25. 1. 2016
 *      Author: jindra
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <defines.h>

#ifdef USE_RTC

#include <stdbool.h>
#include <WireRtcLib.h>

#define READ_AT_MOST_EVERY_N_MS 500

class Clock {
private:
    static WireRtcLib::tm actualTime;
    static unsigned long timeAge;

public:
    static WireRtcLib::tm& getTime(bool updateFirst = false);
    static void timeToStr(const WireRtcLib::tm & time, char * buffer);

private:
    static void readTimeFromRtc();
};

#endif

#endif /* CLOCK_H_ */
