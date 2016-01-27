/*
 * TimeTask.cpp
 *
 *  Created on: 25. 1. 2016
 *      Author: jindra
 */

#include "TimeTask.h"

TimeTask::TimeTask(unsigned long periodMs) :
		Task(periodMs), timeAge(0) {
}

void TimeTask::run() {
	readTimeFromRtc();
}

TimeReading& TimeTask::getTime(bool updateFirst) {
	if (updateFirst){
		readTimeFromRtc();
	}
	return actualTime;
}

void TimeTask::readTimeFromRtc() {
	if (timeAge - millis() > READ_AT_MOST_EVERY_N_MS || timeAge - millis() < 0
			|| actualTime.getReadState() == NOT_YET_READ
			|| actualTime.getReadState() == READ_ERROR) {

		if (actualTime.getReadState() == NOT_YET_READ
				|| actualTime.getReadState() == READ_ERROR) {
			rtc.begin();
		}

		timeAge = millis();
		WireRtcLib::tm* t = rtc.getTime();
		if (t->error) {
			actualTime = TimeReading(true);
		} else {
			actualTime = TimeReading(t);
		}
	}
}

