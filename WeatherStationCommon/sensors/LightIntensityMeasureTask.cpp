/*
 * LightIntensityMeasureTask.cpp
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#include "LightIntensityMeasureTask.h"

#include <BH1750FVI.h>
#include <defines.h>
#include <sensors/SensorFlags.h>
#include <sensors/SensorReading.h>
#include <stdbool.h>
#include <stdint.h>
#include <SensorIds.h>

#ifndef DO_NOT_USE_RTC
#include <time/Clock.h>
#else
#include <Arduino.h>
#endif

LightIntensityMeasureTask::LightIntensityMeasureTask(unsigned long periodMs) :
        Task(periodMs) {
}

using namespace WeatherStation;

#ifdef USE_RTC
#define timeStamp() Clock::getTime(true).timeStamp
#else
#define timeStamp() millis()
#endif

void LightIntensityMeasureTask::run() {
    bool err = false;
    BH1750FVI bh;
    if (latestReading.getReadState() == ReadState::NOT_YET_READ
            || latestReading.getReadState() == ReadState::READ_ERROR) {
        if (bh.begin() > 0) {
            err = true;
        } else {
            bh.SetMode(Continuous_H_resolution_Mode);
        }
    }

    if (err) {
        latestReading = LightIntensityReading(true,
                timeStamp());
    } else {
        int16_t intensity = bh.GetLightIntensity();

        if (intensity < 0) {
            latestReading = LightIntensityReading(true,
                    timeStamp());
        } else {
            latestReading = LightIntensityReading(intensity,
                    timeStamp());
        }
    }

#ifdef USE_SENSOR_FLAGS
    // indicate sensor reading was refreshed
    SensorFlags::writeFlag(SensorValueId::LIGHT_INTENSITY, false);
#endif
}

