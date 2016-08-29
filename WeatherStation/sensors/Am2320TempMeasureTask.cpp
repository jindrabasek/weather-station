/*
 * Am2320TempMeasureTask.cpp
 *
 *  Created on: 23. 8. 2016
 *      Author: jindra
 */

#include "Am2320TempMeasureTask.h"

#include <AM2320.h>
#include <defines.h>
#include <sensors/SensorFlags.h>
#include <stdint.h>
#include <SensorIds.h>
#include <Logger.h>

#ifndef DO_NOT_USE_RTC
#include <time/Clock.h>
#else
#include <Arduino.h>
#endif

using namespace WeatherStation;

Am2320TempMeasureTask::Am2320TempMeasureTask(unsigned long periodMs) :
        Task(periodMs),
        latestReading(SensorValueId::DHT_HUMIDITY) {
}

#ifdef USE_RTC
#define timeStamp() Clock::getTime(true).timeStamp
#else
#define timeStamp() millis()
#endif


void Am2320TempMeasureTask::run() {
    AM2320 th;

    switch (th.Read()) {
        case 2:
            LOG_ERROR(F("Error reading thermometer: CRC failed"));
            latestReading = TempReading(SensorValueId::DHT_HUMIDITY, true,
                    timeStamp());
            break;
        case 1:
            LOG_ERROR(F("Error reading thermometer: Sensor offline"));
            latestReading = TempReading(SensorValueId::DHT_HUMIDITY, true,
                    timeStamp());
            break;
        case 0:
            latestReading = TempReading(SensorValueId::DHT_HUMIDITY, th.h, th.t,
                    timeStamp());
            break;
    }

#ifdef USE_SENSOR_FLAGS
    // indicate sensor reading was refreshed
    SensorFlags::writeFlag(SensorValueId::DHT_HUMIDITY, false);
    SensorFlags::writeFlag(SensorValueId::DHT_TEMPERTAURE_REAL_FEEL, false);
    SensorFlags::writeFlag(SensorValueId::DHT_TEMPERTAURE, false);
    SensorFlags::writeFlag(SensorValueId::ABSOLUTE_HUMIDITY, false);
#endif
}
