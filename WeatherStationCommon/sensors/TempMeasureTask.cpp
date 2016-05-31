/*
 * MeasureTempTask.cpp
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#include <defines.h>
#include <DHT.h>
#include <math.h>
#include <sensors/SensorFlags.h>
#include <sensors/TempMeasureTask.h>
#include <stdbool.h>
#include <stdint.h>
#include <SensorIds.h>

#ifndef DO_NOT_USE_RTC
#include <time/Clock.h>
#else
#include <Arduino.h>
#endif

TempMeasureTask::TempMeasureTask(uint8_t pin, unsigned long periodMs) :
        Task(periodMs),
        dht(pin) {
}

using namespace WeatherStation;

#ifdef USE_RTC
#define timeStamp() Clock::getTime(true).timeStamp
#else
#define timeStamp() millis()
#endif

void TempMeasureTask::run() {
    DhtReadState dhtState = dht.read();
    if (dhtState == DHT_GOOD) {
        float h = dht.getHumidity();
        // Read temperature as Celsius (the default)
        float t = dht.getTemperature();

        float hic = NAN;
        float absoluteHumidity = NAN;
        if (!isnan(h) && !isnan(t)) {
            hic = DHT::computeHeatIndex(t, h);
            absoluteHumidity = DHT::computeAbsoluteHumidity(t, h);
        }

        latestReading = TempReading(h, absoluteHumidity, t, hic,
                timeStamp());
    } else {
        latestReading = TempReading(true, timeStamp());
    }

#ifdef USE_SENSOR_FLAGS
    // indicate sensor reading was refreshed
    SensorFlags::writeFlag(SensorValueId::ABSOLUTE_HUMIDITY, false);
    SensorFlags::writeFlag(SensorValueId::DHT_HUMIDITY, false);
    SensorFlags::writeFlag(SensorValueId::DHT_TEMPERTAURE, false);
    SensorFlags::writeFlag(SensorValueId::DHT_TEMPERTAURE_REAL_FEEL, false);
#endif
}

