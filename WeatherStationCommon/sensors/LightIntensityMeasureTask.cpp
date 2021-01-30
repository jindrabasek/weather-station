/*
 * LightIntensityMeasureTask.cpp
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#ifdef ENABLE_LIGHT_SENSOR

#include "LightIntensityMeasureTask.h"

#include <BH1750FVI.h>
#include <defines.h>
#include <sensors/SensorFlags.h>
#include <sensors/SensorReading.h>
#include <stdbool.h>
#include <stdint.h>
#include <SensorIds.h>
#include <Logger.h>
#include <TaskIds.h>

#ifndef DO_NOT_USE_RTC
#include <time/Clock.h>
#else
#include <Arduino.h>
#endif

using namespace WeatherStation;

LightIntensityMeasureTask::LightIntensityMeasureTask(unsigned long periodMs) :
        Task(periodMs, true, LightIntensityMeasure_Task),
        latestReading(SensorValueId::LIGHT_INTENSITY) {
}

#ifdef USE_RTC
#define timeStamp() Clock::getTime(true).timeStamp
#else
#define timeStamp() millis()
#endif

void LightIntensityMeasureTask::run() {
    uint8_t err = 0;
    BH1750FVI bh;
    if (latestReading.getReadState() == ReadState::NOT_YET_READ
            || latestReading.getReadState() == ReadState::READ_ERROR) {
        err = bh.begin();
        if (!err) {
            bh.SetMode(Continuous_H_resolution_Mode);
        }
    }

    int16_t intensity = 0;
    if (!err) {
        intensity = bh.GetLightIntensity();
        if (intensity < 0) {
            err = intensity * -1;
        }
    }

    if (err) {
        LOG_ERROR1(F("Error reading intensity: "), err);
        latestReading = LightIntensityReading(SensorValueId::LIGHT_INTENSITY, true, timeStamp());
    } else {
        latestReading = LightIntensityReading(SensorValueId::LIGHT_INTENSITY, intensity,
                timeStamp());
    }

#ifdef USE_SENSOR_FLAGS
    // indicate sensor reading was refreshed
    SensorFlags::writeFlag(SensorValueId::LIGHT_INTENSITY, false);
#endif
}

#endif
