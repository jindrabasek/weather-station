/*
 * LightIntensityMeasureTask.cpp
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#include "LightIntensityMeasureTask.h"

#include "ProgramState.h"
#include "defines.h"

LightIntensityMeasureTask::LightIntensityMeasureTask(
		unsigned long periodMs, ProgramState & state) :
		Task(periodMs), state(state){
}

void LightIntensityMeasureTask::run() {
	bool err = false;
	if (latestReading.getReadState() == NOT_YET_READ || latestReading.getReadState() == READ_ERROR){
		if (bh.begin() > 0){
			err = true;
		} else {
			bh.SetMode(Continuous_H_resolution_Mode);
		}
	}

	if (err){
		latestReading = LightIntensityReading(true, state.getTimeStamp());
	}else {
		digitalWrite(13, HIGH);
		int16_t intensity = bh.GetLightIntensity();
		digitalWrite(13, LOW);

		if (intensity < 0) {
			latestReading = LightIntensityReading(true, state.getTimeStamp());
		} else {
		    latestReading = LightIntensityReading(intensity, state.getTimeStamp());
		}
	}
#ifdef PRINT_TO_STREAM_SUPPORT
#ifdef DEBUG_PRINT_SENSOR_VALUES
	latestReading.printToStream(&Serial);
#endif
#endif
}

