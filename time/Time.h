/*
 * TimeTask.h
 *
 *  Created on: 25. 1. 2016
 *      Author: jindra
 */

#ifndef TIME_H_
#define TIME_H_

#define READ_AT_MOST_EVERY_N_MS 500

#include <WireRtcLib.h>

#include "TimeReading.h"

class Time {
private:
	TimeReading actualTime;
	unsigned long timeAge;
	WireRtcLib rtc;

public:
	Time();

	Time(const Time& that) = delete;
	void operator=(const Time& that) = delete;

	TimeReading& getTime(bool updateFirst = false);

private:
	void readTimeFromRtc();
};

#endif /* TIME_H_ */
