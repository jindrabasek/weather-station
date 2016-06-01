/*
 * PrgState.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef PROGRAMSTATE_H_
#define PROGRAMSTATE_H_

#include "ProgramState.h"

#include <Arduino.h>
#include <sensors/LightIntensityMeasureTask.h>
#include <sensors/SensorReading.h>
#include <sensors/TempMeasureTask.h>
#include <stddef.h>
#include <SensorIds.h>
#include <SoftTimer.h>

#include "../../../eclipse/eclipseArduino3/eclipseArduino/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/variants/standard/pins_arduino.h"
#include "LogReadingsTask.h"

class ToDraw;

class ProgramState {
public:
    static const int DHT_PIN = 4;
    static const unsigned long DHT_MEASURE_FREQ = 10000000;
    static const unsigned long LIGHT_MEASURE_FREQ = 10000000;
    static const unsigned long PRINT_VALUES_FREQ = 30000000;

//-----------------------------------------------------------------------------

private:
    TempMeasureTask measureTempTask;
    LightIntensityMeasureTask measureLightIntensityTask;
    LogReadingsTask logReadingsTask;

    SensorReading * sensorValues[WeatherStation::SensorValueId::SensorsEnumSize] =
            { NULL };

    void setStateRef();

//-----------------------------------------------------------------------------

public:
    ProgramState(const ProgramState& that) = delete;
    void operator=(const ProgramState& that) = delete;
    static ProgramState& instance();

    SensorReading** getSensorValues() {
        return sensorValues;
    }

private:
    ProgramState() :
            measureTempTask(DHT_PIN, DHT_MEASURE_FREQ),
            measureLightIntensityTask(LIGHT_MEASURE_FREQ),
            logReadingsTask(PRINT_VALUES_FREQ)
    {

        pinMode(LED_BUILTIN, OUTPUT);

        SoftTimer.add(&measureTempTask);
        SoftTimer.add(&measureLightIntensityTask);
        SoftTimer.add(&logReadingsTask);

        measureTempTask.getLatestReading().registerSensorValues(sensorValues);
        measureLightIntensityTask.getLatestReading().registerSensorValues(
                sensorValues);

        setStateRef();
    }
};

#endif /* PROGRAMSTATE_H_ */
