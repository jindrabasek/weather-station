/*
 * LightIntensityMeasureTask.h
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#ifndef LIGHTINTENSITYMEASURETASK_H_
#define LIGHTINTENSITYMEASURETASK_H_

#include <Task.h>
#include <BH1750FVI.h>

#include "LightIntensityReading.h"

class ProgramState;

class LightIntensityMeasureTask: public Task {
private:
	LightIntensityReading latestReading;
	BH1750FVI bh;
	ProgramState & state;

//-----------------------------------------------------------------------------

public:
	LightIntensityMeasureTask(unsigned long periodMs, ProgramState & state);
	virtual void run();

	LightIntensityReading& getLatestReading() {
		return latestReading;
	}

};


#endif /* LIGHTINTENSITYMEASURETASK_H_ */
