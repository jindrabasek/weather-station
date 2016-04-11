/*
 * MeasureTempTask.cpp
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#include "TempMeasureTask.h"

#include "../ProgramState.h"

TempMeasureTask::TempMeasureTask(uint8_t pin, unsigned long periodMs) :
        Task(periodMs),
        dht(pin),
        pin(pin) {
}

void TempMeasureTask::run() {
    DhtReadState dhtState = dht.read();

    ProgramState & state = ProgramState::instance();
    if (dhtState == DHT_GOOD) {
        float h = dht.readHumidity();
        // Read temperature as Celsius (the default)
        float t = dht.readTemperature();

        float hic = NAN;
        // Check if any reads failed and exit early (to try again).
        if (!isnan(h) && !isnan(t)) {
            hic = dht.computeHeatIndex(t, h);
        }

        latestReading = TempReading(h, t, hic, state.getTimeStamp(true));
    } else {
        latestReading = TempReading(dhtState == DHT_ERROR,
                state.getTimeStamp(true));
    }

}

