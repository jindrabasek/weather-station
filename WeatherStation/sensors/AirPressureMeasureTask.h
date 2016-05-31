/*
 * PressMeasureTask.h
 *
 *  Created on: 17. 1. 2016
 *      Author: jindra
 */

#ifndef AIRPRESSUREMEASURETASK_H_
#define AIRPRESSUREMEASURETASK_H_

#include <Adafruit_BMP085.h>
#include <Task.h>

#include "AirPressureReading.h"

class AirPressureMeasureTask : public Task {
private:
    AirPressureReading latestReading;
    Adafruit_BMP085 bmp;

//-----------------------------------------------------------------------------

public:
    AirPressureMeasureTask(unsigned long periodMs);

    AirPressureMeasureTask(const AirPressureMeasureTask& that) = delete;
    void operator=(const AirPressureMeasureTask& that) = delete;

    virtual void run();

    AirPressureReading& getLatestReading() {
        return latestReading;
    }
};

#endif /* AIRPRESSUREMEASURETASK_H_ */
