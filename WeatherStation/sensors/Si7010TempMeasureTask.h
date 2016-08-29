/*
 * Si7010TempMeasureTask.h
 *
 *  Created on: 29. 8. 2016
 *      Author: jindra
 */

#ifndef SI7010TEMPMEASURETASK_H_
#define SI7010TEMPMEASURETASK_H_

#include <sensors/TempReading.h>
#include <SparkFun_Si7021_Breakout_Library.h>
#include <Task.h>

class Si7010TempMeasureTask : public Task {
private:
    TempReading latestReading;
    Si7010Weather sensor;

public:
    Si7010TempMeasureTask(unsigned long periodMs);

    Si7010TempMeasureTask(const Si7010TempMeasureTask& that) = delete;
    void operator=(const Si7010TempMeasureTask& that) = delete;

    virtual void run();

    TempReading& getLatestReading() {
        return latestReading;
    }
};

#endif /* SI7010TEMPMEASURETASK_H_ */
