/*
 * LightIntensityMeasureTask.h
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#ifndef LIGHTINTENSITYMEASURETASK_H_
#define LIGHTINTENSITYMEASURETASK_H_

#include <Task.h>
#include <BH1750FVI.h>

#include "LightIntensityReading.h"

class LightIntensityMeasureTask : public Task {
private:
    LightIntensityReading latestReading;
    BH1750FVI bh;

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
