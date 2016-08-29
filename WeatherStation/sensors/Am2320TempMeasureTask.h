/*
 * Am2320TempMeasureTask.h
 *
 *  Created on: 23. 8. 2016
 *      Author: jindra
 */

#ifndef AM2320TEMPMEASURETASK_H_
#define AM2320TEMPMEASURETASK_H_

#include <sensors/TempReading.h>
#include <Task.h>

class Am2320TempMeasureTask : public Task {
private:
    TempReading latestReading;

public:
    Am2320TempMeasureTask(unsigned long periodMs);

    Am2320TempMeasureTask(const Am2320TempMeasureTask& that) = delete;
    void operator=(const Am2320TempMeasureTask& that) = delete;

    virtual void run();

    TempReading& getLatestReading() {
        return latestReading;
    }
};

#endif /* AM2320TEMPMEASURETASK_H_ */
