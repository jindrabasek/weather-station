/*
 * MeasureTempTask.cpp
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#include "TempMeasureTask.h"

#include "ProgramState.h"
#include "defines.h"

TempMeasureTask::TempMeasureTask(uint8_t pin, unsigned long periodMs,
		ProgramState & state) :
		Task(periodMs), dht(pin), pin(pin), state(state) {
}

void TempMeasureTask::run() {
	DhtReadState dhtState = dht.read();

	if (dhtState == DHT_GOOD) {
		float h = dht.readHumidity();
		// Read temperature as Celsius (the default)
		float t = dht.readTemperature();

		float hic = NAN;
		// Check if any reads failed and exit early (to try again).
		if (!isnan(h) && !isnan(t)) {
			hic = dht.computeHeatIndex(t, h);
		}

		latestReading = TempReading(h, t, hic, state.getTimeStamp());
	} else {
		latestReading = TempReading(dhtState == DHT_ERROR, state.getTimeStamp());
	}

#ifdef PRINT_TO_STREAM_SUPPORT
#ifdef DEBUG_PRINT_SENSOR_VALUES
	latestReading.printToStream(&Serial);
#endif
#endif
}

