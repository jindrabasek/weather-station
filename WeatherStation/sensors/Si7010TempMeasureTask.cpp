/*
 * Si7010TempMeasureTask.cpp
 *
 *  Created on: 29. 8. 2016
 *      Author: jindra
 */

#include "Si7010TempMeasureTask.h"

#include <defines.h>
#include <sensors/SensorFlags.h>
#include <stdint.h>
#include <SensorIds.h>
#include <SparkFun_Si7021_Breakout_Library.h>
#include <Logger.h>
#include <TaskIds.h>

#ifndef DO_NOT_USE_RTC
#include <time/Clock.h>
#else
#include <Arduino.h>
#endif

using namespace WeatherStation;

Si7010TempMeasureTask::Si7010TempMeasureTask(unsigned long periodMs) :
        Task(periodMs, true, Si7010TempMeasure_Task),
        latestReading(SensorValueId::DHT_HUMIDITY) {
}

#ifdef USE_RTC
#define timeStamp() Clock::getTime(true).timeStamp
#else
#define timeStamp() millis()
#endif


void Si7010TempMeasureTask::run() {
    uint8_t err = 0;
    if (latestReading.getReadState() == ReadState::NOT_YET_READ
            || latestReading.getReadState() == ReadState::READ_ERROR) {
        err = !sensor.begin();
    }

    if (err) {
        latestReading = TempReading(SensorValueId::DHT_HUMIDITY, true,
                            timeStamp());
    } else {
        latestReading = TempReading(SensorValueId::DHT_HUMIDITY, sensor.getRH(), sensor.getTemp(),
                            timeStamp());
    }

#ifdef USE_SENSOR_FLAGS
    // indicate sensor reading was refreshed
    SensorFlags::writeFlag(SensorValueId::DHT_HUMIDITY, false);
    SensorFlags::writeFlag(SensorValueId::DHT_TEMPERTAURE_REAL_FEEL, false);
    SensorFlags::writeFlag(SensorValueId::DHT_TEMPERTAURE, false);
    SensorFlags::writeFlag(SensorValueId::ABSOLUTE_HUMIDITY, false);
#endif
}
