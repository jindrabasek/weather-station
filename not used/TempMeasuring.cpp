/*
 * temperature.cpp
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#include "TempMeasuring.h"

#include <DHT.h>

#include "TempReading.h"

TempMeasuring::TempMeasuring(uint8_t pin, uint8_t type) :
		dht(pin, type), pin(pin) {
}

void TempMeasuring::doSetup() {
	dht.begin();
	pinMode(pin, INPUT);
}

TempReading TempMeasuring::measureTemp() {
	float h = dht.readHumidity();
	// Read temperature as Celsius (the default)
	float t = dht.readTemperature();

	float hic = NAN;
	// Check if any reads failed and exit early (to try again).
	if (!isnan(h) && !isnan(t)) {
		hic = dht.computeHeatIndex(t, h, false);
	}

	return TempReading(h, t, hic);
}

