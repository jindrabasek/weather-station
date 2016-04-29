/*
 * MeasureTempTask.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef TEMPMEASURETASK_H_
#define TEMPMEASURETASK_H_

#include <DHT.h>
#include <stdint.h>

#include "TempReading.h"

class TempMeasureTask : public Task {
private:
    TempReading latestReading;
    DHT dht;

//-----------------------------------------------------------------------------

public:
    TempMeasureTask(uint8_t pin, unsigned long periodMs);

    TempMeasureTask(const TempMeasureTask& that) = delete;
    void operator=(const TempMeasureTask& that) = delete;

    virtual void run();

    TempReading& getLatestReading() {
        return latestReading;
    }
};

#endif /* TEMPMEASURETASK_H_ */
