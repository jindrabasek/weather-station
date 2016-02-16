/*
 * LightIntensityMeasureTask.cpp
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#include "LightIntensityMeasureTask.h"

#include "../ProgramState.h"

LightIntensityMeasureTask::LightIntensityMeasureTask(
		unsigned long periodMs) :
		Task(periodMs){
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

	ProgramState & state = ProgramState::instance();
	if (err){
		latestReading = LightIntensityReading(true, state.getTimeStamp(true));
	}else {
		int16_t intensity = bh.GetLightIntensity();

		if (intensity < 0) {
			latestReading = LightIntensityReading(true, state.getTimeStamp(true));
		} else {
		    latestReading = LightIntensityReading(intensity, state.getTimeStamp(true));
		}
	}
}

