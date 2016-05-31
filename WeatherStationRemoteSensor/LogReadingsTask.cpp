/*
 * SmartLivingPublishTask.cpp
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#include <Logger.h>
#include <sensors/SensorReading.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <SensorIds.h>

#include "LogReadingsTask.h"
#include "ProgramState.h"

extern ProgramState *state;

LogReadingsTask::LogReadingsTask(unsigned long periodMs) :
        Task(periodMs) {
}

using namespace WeatherStation;

void LogReadingsTask::run() {

    for (uint8_t i = 0; i < WeatherStation::SensorValueId::SensorsEnumSize;
            i++) {
        SensorReading * sensorValue = state->getSensorValues()[i];
        if (sensorValue != NULL) {

            if (sensorValue->getReadState() == ReadState::READ_OK) {
                if (LOG_LEVEL >= LOGGER_LEVEL_DEBUG) {
                    LOGGER_DEBUG.printTime();
                    LOGGER_DEBUG.print(' ');
                    LOGGER_DEBUG.print(sensorValue->getTimeStamp());
                    LOGGER_DEBUG.print(' ');
                    uint8_t nameLength = sensorValue->printValueName(i, false, LOGGER_DEBUG);
                    WeatherStation::SensorValueUnit valueUnit = sensorValue->valueUnit(i,
                            false);
                    sensorValue->printValue(i, false, LOGGER_DEBUG, 30 - nameLength - 2
                            - WeatherStation::SensorValueUnits::sensorUnitNameLength(
                                    valueUnit));
                    LOGGER_DEBUG.print(' ');

                    WeatherStation::SensorValueUnits::printSensorUnit(valueUnit, LOGGER_DEBUG);
                    LOGGER_DEBUG.println();
                }
            } else {
                LOG_WARN2(
                        F("Sensor data error or not read "),
                        i, (unsigned int)sensorValue->getReadState());
            }
        }
    }
}

