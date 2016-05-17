/*
 * LightIntensityMeasureTask.cpp
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#include "LightIntensityMeasureTask.h"

#include <BH1750FVI.h>
#include <stdbool.h>
#include <stdint.h>

#include "../PeripheryReading.h"
#include "../time/Clock.h"
#include "../time/TimeReading.h"

LightIntensityMeasureTask::LightIntensityMeasureTask(unsigned long periodMs) :
        Task(periodMs) {
}

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
                Clock::getTime(true).getTimeStamp());
    } else {
        int16_t intensity = bh.GetLightIntensity();

        if (intensity < 0) {
            latestReading = LightIntensityReading(true,
                    Clock::getTime(true).getTimeStamp());
        } else {
            latestReading = LightIntensityReading(intensity,
                    Clock::getTime(true).getTimeStamp());
        }
    }
}

