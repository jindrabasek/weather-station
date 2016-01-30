/*
 * PressMeasureTask.cpp
 *
 *  Created on: 17. 1. 2016
 *      Author: jindra
 */

#include "AirPressureMeasureTask.h"

#include "../ProgramState.h"

AirPressureMeasureTask::AirPressureMeasureTask(unsigned long periodMs) :
		Task(periodMs) {
}

void AirPressureMeasureTask::run() {
	bool err = false;
	if (latestReading.getReadState() == NOT_YET_READ
			|| latestReading.getReadState() == READ_ERROR) {
		err = !bmp.begin();
	}

	if (err) {
		AirPressureReading errReading(true);
		latestReading = AirPressureReading(true, state.getTimeStamp(true));
	} else {

		digitalWrite(13, HIGH);

		int32_t UT = bmp.readRawTemperature();
		int32_t UP = bmp.readRawPressure();
		float temperature = bmp.correctTemperature(UT);
		float pressurePa = bmp.correctPressure(UT, UP);
		float pressure = pressurePa / 100.0;
		float pressureSea = bmp.seaLevelForAltitude(
				state.getSettings().getAltitude(), pressurePa) / 100.0;

		digitalWrite(13, LOW);

		latestReading = AirPressureReading(pressure, pressureSea, temperature,
				state.getTimeStamp(true));

	}
}

