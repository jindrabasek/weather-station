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
#include <Logger.h>
#include <TaskIds.h>

#include "../ProgramSettings.h"
#include "../ProgramState.h"

extern ProgramState *state;

AirPressureMeasureTask::AirPressureMeasureTask(unsigned long periodMs) :
        Task(periodMs, true, AirPressureMeasure_Task) {
}

using namespace WeatherStation;

void AirPressureMeasureTask::run() {
    uint8_t err = 0;
    if (latestReading.getReadState() == ReadState::NOT_YET_READ
            || latestReading.getReadState() == ReadState::READ_ERROR) {
        err = bmp.begin();
    }

    int32_t UT = 0;
    int32_t UP = 0;
    if (!err) {
        UT = bmp.readRawTemperature(err);
        UP = bmp.readRawPressure(err);
    }

    if (err) {
        LOG_ERROR1(F("Error reading barometer: "), err);
        latestReading = AirPressureReading(true,
                Clock::getTime(true).timeStamp);
    } else {
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

