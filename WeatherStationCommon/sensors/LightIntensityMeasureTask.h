/*
 * LightIntensityMeasureTask.h
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#ifndef LIGHTINTENSITYMEASURETASK_H_
#define LIGHTINTENSITYMEASURETASK_H_

#include <Task.h>

#include "LightIntensityReading.h"

class LightIntensityMeasureTask : public Task {
private:
    LightIntensityReading latestReading;

//-----------------------------------------------------------------------------

public:
    LightIntensityMeasureTask(unsigned long periodMs);

    LightIntensityMeasureTask(const LightIntensityMeasureTask& that) = delete;
    void operator=(const LightIntensityMeasureTask& that) = delete;

    virtual void run();

    LightIntensityReading& getLatestReading() {
        return latestReading;
    }
};

#endif /* LIGHTINTENSITYMEASURETASK_H_ */
