/*
 * MeasureTempTask.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef TEMPMEASURETASK_H_
#define TEMPMEASURETASK_H_

#include <Task.h>
#include <DHT.h>

#include "TempReading.h"

class ProgramState;

class TempMeasureTask: public Task {
private:
	TempReading latestReading;
	DHT dht;
	uint8_t pin;
	ProgramState & state;

//-----------------------------------------------------------------------------

public:
	TempMeasureTask(uint8_t pin, unsigned long periodMs, ProgramState & state);

	virtual void run();

	TempReading& getLatestReading() {
		return latestReading;
	}
};

#endif /* TEMPMEASURETASK_H_ */
