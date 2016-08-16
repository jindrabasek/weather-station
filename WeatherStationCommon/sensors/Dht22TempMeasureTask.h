/*
 * MeasureTempTask.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef TEMPMEASURETASK_H_
#define TEMPMEASURETASK_H_

#include <sensors/TempReading.h>
#include <stdint.h>
#include <Task.h>

class Dht22TempMeasureTask : public Task {
private:
    TempReading latestReading;
    uint8_t dataPin;
    uint8_t powerPin;

//-----------------------------------------------------------------------------

public:
    Dht22TempMeasureTask(uint8_t pin, unsigned long periodMs, uint8_t powerPin = 0);

    Dht22TempMeasureTask(const Dht22TempMeasureTask& that) = delete;
    void operator=(const Dht22TempMeasureTask& that) = delete;

    virtual void run();

    TempReading& getLatestReading() {
        return latestReading;
    }
};

#endif /* TEMPMEASURETASK_H_ */
