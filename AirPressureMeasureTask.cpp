/*
 * PressMeasureTask.cpp
 *
 *  Created on: 17. 1. 2016
 *      Author: jindra
 */

#include "AirPressureMeasureTask.h"

#include "ProgramState.h"
#include "defines.h"

AirPressureMeasureTask::AirPressureMeasureTask(unsigned long periodMs,
		ProgramState & state) :
		Task(periodMs), state(state) {
}

void AirPressureMeasureTask::run() {
	bool err = false;
	if (latestReading.getReadState() == NOT_YET_READ
			|| latestReading.getReadState() == READ_ERROR) {
		err = !bmp.begin();
	}

	if (err) {
		AirPressureReading errReading(true);
		latestReading = AirPressureReading(true, state.getTimeStamp());
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
				state.getTimeStamp());

	}
#ifdef PRINT_TO_STREAM_SUPPORT
#ifdef DEBUG_PRINT_SENSOR_VALUES
	latestReading.printToStream(&Serial);
#endif
#endif
}

