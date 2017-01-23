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
#include <stdbool.h>
#include <stdint.h>
#include <SensorIds.h>
#include <Logger.h>
#include <sensors/Dht22TempMeasureTask.h>
#include <TaskIds.h>

#ifndef DO_NOT_USE_RTC
#include <time/Clock.h>
#else
#include <Arduino.h>
#endif

using namespace WeatherStation;

Dht22TempMeasureTask::Dht22TempMeasureTask(uint8_t pin, unsigned long periodMs, uint8_t powerPin) :
        Task(periodMs, true, Dht22TempMeasure_Task),
        latestReading(SensorValueId::DHT_HUMIDITY),
        dataPin(pin),
        powerPin(powerPin){
}

#ifdef USE_RTC
#define timeStamp() Clock::getTime(true).timeStamp
#else
#define timeStamp() millis()
#endif

void Dht22TempMeasureTask::run() {

    DHT dht(dataPin);

    if (powerPin > 0) {
        if (latestReading.getReadState() == ReadState::NOT_YET_READ) {
            pinMode(powerPin, OUTPUT);
            digitalWrite(powerPin, HIGH);
            delay(2000); // stabilize sensor
        } else if (latestReading.getReadState() == ReadState::READ_ERROR) {
            // restart DHT
            pinMode(dataPin, INPUT);
            digitalWrite(powerPin, LOW);
            delay(20000); // let it off for a while
            digitalWrite(powerPin, HIGH);
            delay(3000); // stabilize sensor
            latestReading = TempReading(SensorValueId::DHT_HUMIDITY);
            return;
        }
    }

    uint8_t data[5];
    DhtReadState dhtState = dht.read(data);
    if (dhtState == DHT_GOOD) {
        float h = dht.getHumidity(data);
        // Read temperature as Celsius (the default)
        float t = dht.getTemperature(data);

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

