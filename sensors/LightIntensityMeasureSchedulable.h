/*
 * LightIntensityMeasureTask.h
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#ifndef LIGHTINTENSITYMEASURESCHEDULABLE_H_
#define LIGHTINTENSITYMEASURESCHEDULABLE_H_

#include <Schedulable.h>

#include "LightIntensityReading.h"

class LightIntensityMeasureSchedulable : public Schedulable {
private:
    LightIntensityReading latestReading;

//-----------------------------------------------------------------------------

public:
    LightIntensityMeasureSchedulable(){

    }

    LightIntensityMeasureSchedulable(const LightIntensityMeasureSchedulable& that) = delete;
    void operator=(const LightIntensityMeasureSchedulable& that) = delete;

    virtual void run(Task * task);

    LightIntensityReading& getLatestReading() {
        return latestReading;
    }
};

#endif /* LIGHTINTENSITYMEASURESCHEDULABLE_H_ */
