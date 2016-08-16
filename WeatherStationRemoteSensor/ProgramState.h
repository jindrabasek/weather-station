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
#include <sensors/Dht22TempMeasureTask.h>
#include <sensors/LightIntensityMeasureTask.h>
#include <sensors/SensorReading.h>
#include <stddef.h>
#include <SensorIds.h>
#include <SoftTimer.h>

#include "LogReadingsTask.h"
#include "WirelessSend433MhzTask.h"

class ToDraw;

class ProgramState {
public:
    static const int DHT_PIN = 4;
    static const int DHT_POWER_PIN = 5;
    static const unsigned long DHT_MEASURE_FREQ = 10000000;
    static const unsigned long LIGHT_MEASURE_FREQ = 10000000;
    static const unsigned long PRINT_VALUES_FREQ = 30000000;
    static const unsigned long SEND_VALUES_FREQ = 30000000;

//-----------------------------------------------------------------------------

private:
    Dht22TempMeasureTask measureTempTask;
    LightIntensityMeasureTask measureLightIntensityTask;
    LogReadingsTask logReadingsTask;
    WirelessSend433MhzTask wirelessSend433MhzTask;

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

    LightIntensityMeasureTask& getMeasureLightIntensityTask() {
        return measureLightIntensityTask;
    }

    Dht22TempMeasureTask& getDht22MeasureTempTask() {
        return measureTempTask;
    }

private:
    ProgramState() :
            measureTempTask(DHT_PIN, DHT_MEASURE_FREQ, DHT_POWER_PIN),
            measureLightIntensityTask(LIGHT_MEASURE_FREQ),
            logReadingsTask(PRINT_VALUES_FREQ),
            wirelessSend433MhzTask(SEND_VALUES_FREQ)
    {

        pinMode(LED_BUILTIN, OUTPUT);

        measureTempTask.startAtEarliestOportunity();
        measureLightIntensityTask.startAtEarliestOportunity();
        logReadingsTask.startAtEarliestOportunity();
        wirelessSend433MhzTask.startAtEarliestOportunity();

        SoftTimer.add(&measureTempTask);
        SoftTimer.add(&measureLightIntensityTask);
        SoftTimer.add(&logReadingsTask);
        SoftTimer.add(&wirelessSend433MhzTask);

        measureTempTask.getLatestReading().registerSensorValues(sensorValues);
        measureLightIntensityTask.getLatestReading().registerSensorValues(
                sensorValues);

        setStateRef();
    }
};

#endif /* PROGRAMSTATE_H_ */
