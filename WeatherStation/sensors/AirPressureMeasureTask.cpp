/*
 * PressMeasureTask.cpp
 *
 *  Created on: 17. 1. 2016
 *      Author: jindra
 */

#include "AirPressureMeasureTask.h"

#include <sensors/SensorFlags.h>
#include <sensors/SensorReading.h>
#include <stdbool.h>
#include <stdint.h>
#include <SensorIds.h>
#include <time/Clock.h>

#include "../ProgramSettings.h"
#include "../ProgramState.h"

extern ProgramState *state;

AirPressureMeasureTask::AirPressureMeasureTask(unsigned long periodMs) :
        Task(periodMs) {
}

using namespace WeatherStation;

void AirPressureMeasureTask::run() {
    bool err = false;
    if (latestReading.getReadState() == ReadState::NOT_YET_READ
            || latestReading.getReadState() == ReadState::READ_ERROR) {
        err = !bmp.begin();
    }

    if (err) {
        AirPressureReading errReading(true);
        latestReading = AirPressureReading(true,
                Clock::getTime(true).timeStamp);
    } else {
        int32_t UT = bmp.readRawTemperature();
        int32_t UP = bmp.readRawPressure();
        float temperature = bmp.correctTemperature(UT);
        float pressurePa = bmp.correctPressure(UT, UP);
        float pressure = pressurePa / 100.0;
        float pressureSea = Adafruit_BMP085::seaLevelForAltitude(
                state->getSettings().getAltitude(),
                pressurePa) / 100.0;

        latestReading = AirPressureReading(pressure, pressureSea, temperature,
                Clock::getTime(true).timeStamp);
    }

    // indicate sensor reading was refreshed
    SensorFlags::writeFlag(SensorValueId::BMP_TEMPERATURE, false);
    SensorFlags::writeFlag(SensorValueId::PRESSURE, false);
    SensorFlags::writeFlag(SensorValueId::PRESSURE_SEAL_LEVEL, false);
}
