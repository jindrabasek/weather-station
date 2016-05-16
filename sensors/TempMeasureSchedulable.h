/*
 * MeasureTempTask.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef TEMPMEASURESCHEDULABLE_H_
#define TEMPMEASURESCHEDULABLE_H_

#include <DHT.h>
#include <stdint.h>
#include <Schedulable.h>

#include "TempReading.h"

class TempMeasureSchedulable : public Schedulable {
private:
    TempReading latestReading;
    DHT dht;

//-----------------------------------------------------------------------------

public:
    TempMeasureSchedulable(uint8_t pin);

    TempMeasureSchedulable(const TempMeasureSchedulable& that) = delete;
    void operator=(const TempMeasureSchedulable& that) = delete;

    virtual void run(Task * task);

    TempReading& getLatestReading() {
        return latestReading;
    }
};

#endif /* TEMPMEASURESCHEDULABLE_H_ */
