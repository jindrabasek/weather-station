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
#include <Logger.h>

#ifndef DO_NOT_USE_RTC
#include <time/Clock.h>
#else
#include <Arduino.h>
#endif

using namespace WeatherStation;

TempMeasureTask::TempMeasureTask(uint8_t pin, unsigned long periodMs) :
        Task(periodMs),
        latestReading(SensorValueId::DHT_HUMIDITY),
        dht(pin) {
}

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

        latestReading = TempReading(SensorValueId::DHT_HUMIDITY, h, t,
                timeStamp());
    } else {
        LOG_ERROR1(F("Error reading thermometer: "), dhtState);
        latestReading = TempReading(SensorValueId::DHT_HUMIDITY, true, timeStamp());
    }

#ifdef USE_SENSOR_FLAGS
    // indicate sensor reading was refreshed
    SensorFlags::writeFlag(SensorValueId::DHT_HUMIDITY, false);
    SensorFlags::writeFlag(SensorValueId::DHT_TEMPERTAURE_REAL_FEEL, false);
    SensorFlags::writeFlag(SensorValueId::DHT_TEMPERTAURE, false);
    SensorFlags::writeFlag(SensorValueId::ABSOLUTE_HUMIDITY, false);
#endif
}

