/*
 * MeasureTempTask.cpp
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#include "TempMeasureTask.h"

#include <DHT.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "../time/Clock.h"

TempMeasureTask::TempMeasureTask(uint8_t pin, unsigned long periodMs) :
        Task(periodMs),
        dht(pin) {
}

void TempMeasureTask::run() {
    DhtReadState dhtState = dht.read();
    if (dhtState == DHT_GOOD) {
        float h = dht.getHumidity();
        // Read temperature as Celsius (the default)
        float t = dht.getTemperature();

        float hic = NAN;
        float absoluteHumidity = NAN;
        if (!isnan(h) && !isnan(t)) {
            hic = DHT::computeHeatIndex(t, h);
            absoluteHumidity = DHT::computeAbsoluteHumidity(t, h);
        }

        latestReading = TempReading(h, absoluteHumidity, t, hic,
                Clock::getTime(true).timeStamp);
    } else {
        latestReading = TempReading(true, Clock::getTime(true).timeStamp);
    }
}

