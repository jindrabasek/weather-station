/*
 * ScreenToDraw.h
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#ifndef SENSORREADINGSCREEN_H_
#define SENSORREADINGSCREEN_H_

#include <LCD.h>

#include "../display/ToDraw.h"
#include "SensorReading.h"

class SensorReadingScreen : public ToDraw {
private:
    SensorReading & toDraw;

public:
    SensorReadingScreen(SensorReading & toDraw);
    virtual void draw(LCD & display);
};

#endif /* SENSORREADINGSCREEN_H_ */
