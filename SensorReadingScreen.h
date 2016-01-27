/*
 * ScreenToDraw.h
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#ifndef SENSORREADINGSCREEN_H_
#define SENSORREADINGSCREEN_H_

#include "ToDraw.h"
#include "TimeTask.h"
#include "SensorReading.h"

class SensorReadingScreen: public ToDraw {
private:
	SensorReading & toDraw;
	TimeTask & time;

public:
	SensorReadingScreen(SensorReading & toDraw, TimeTask & time);
	virtual void draw(LCD & display);
};

#endif /* SENSORREADINGSCREEN_H_ */
