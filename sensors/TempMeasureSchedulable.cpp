/*
 * MeasureTempTask.cpp
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#include "TempMeasureSchedulable.h"

#include <DHT.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "../ProgramState.h"

TempMeasureSchedulable::TempMeasureSchedulable(uint8_t pin) :
        dht(pin){
}

void TempMeasureSchedulable::run(Task * task) {
    DhtReadState dhtState = dht.read();
    ProgramState & state = ProgramState::instance();
    if (dhtState == DHT_GOOD) {
        float h = dht.getHumidity();
        // Read temperature as Celsius (the default)
        float t = dht.getTemperature();

        float hic = NAN;
        float absoluteHumidity = NAN;
        if (!isnan(h) && !isnan(t)) {
            hic = dht.computeHeatIndex(t, h);
            absoluteHumidity = dht.computeAbsoluteHumidity(t, h);
        }

        latestReading = TempReading(h, absoluteHumidity, t, hic, state.getTimeStamp(true));
    } else {
        latestReading = TempReading(true, state.getTimeStamp(true));
    }
}

