/*
 * TimeTask.h
 *
 *  Created on: 25. 1. 2016
 *      Author: jindra
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdbool.h>
#include "TimeReading.h"


#define READ_AT_MOST_EVERY_N_MS 500

class Clock {
private:
    static TimeReading actualTime;
    static unsigned long timeAge;

public:
    static TimeReading& getTime(bool updateFirst = false);

private:
    static void readTimeFromRtc();
};

#endif /* CLOCK_H_ */
