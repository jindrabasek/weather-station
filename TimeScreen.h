/*
 * TimeScreen.h
 *
 *  Created on: 26. 1. 2016
 *      Author: jindra
 */

#ifndef TIMESCREEN_H_
#define TIMESCREEN_H_

#include "ToDraw.h"
#include "TimeReading.h"

class TimeScreen: public ToDraw {
private:
	TimeReading & actualTime;
public:
	TimeScreen(TimeReading & actualTime);

	virtual void draw(LCD & display);
};

#endif /* TIMESCREEN_H_ */
