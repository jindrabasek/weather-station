/*
 * TimeTask.h
 *
 *  Created on: 25. 1. 2016
 *      Author: jindra
 */

#ifndef TIMETASK_H_
#define TIMETASK_H_

#define READ_AT_MOST_EVERY_N_MS 500

#include <Task.h>
#include <WireRtcLib.h>

#include "TimeReading.h"

class TimeTask : public Task {
private:
	TimeReading actualTime;
	unsigned long timeAge;
	WireRtcLib rtc;

public:
	TimeTask(unsigned long periodMs);

	virtual void run();

	TimeReading& getTime(bool updateFirst = false);

private:
	void readTimeFromRtc();
};

#endif /* TIMETASK_H_ */
