/*
 * PressMeasureTask.h
 *
 *  Created on: 17. 1. 2016
 *      Author: jindra
 */

#ifndef AIRPRESSUREMEASURESCHEDULABLE_H_
#define AIRPRESSUREMEASURESCHEDULABLE_H_

#include <Adafruit_BMP085.h>
#include <Schedulable.h>

#include "AirPressureReading.h"

class AirPressureMeasureSchedulable : public Schedulable {
private:
    AirPressureReading latestReading;
    Adafruit_BMP085 bmp;

//-----------------------------------------------------------------------------

public:
    AirPressureMeasureSchedulable(){

    }

    AirPressureMeasureSchedulable(const AirPressureMeasureSchedulable& that) = delete;
    void operator=(const AirPressureMeasureSchedulable& that) = delete;

    virtual void run(Task * task);

    AirPressureReading& getLatestReading() {
        return latestReading;
    }
};

#endif /* AIRPRESSUREMEASURESCHEDULABLE_H_ */
