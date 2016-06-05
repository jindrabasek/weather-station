/*
 * SmartLivingPublishTask.cpp
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#include "WirelessSend433MhzTask.h"

#include <Arduino.h>
#include <Logger.h>
#include <sensors/LightIntensityMeasureTask.h>
#include <sensors/LightIntensityReading.h>
#include <sensors/SensorReading.h>
#include <sensors/TempMeasureTask.h>
#include <sensors/TempReading.h>
#include <stdint.h>

#include "ProgramState.h"

extern ProgramState *state;

WirelessSend433MhzTask::WirelessSend433MhzTask(unsigned long periodMs) :
        Task(periodMs) {
    pinMode(SENDER_PORT, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

using namespace WeatherStation;

void WirelessSend433MhzTask::run() {

    if (state->getMeasureLightIntensityTask().getLatestReading().getReadState() == ReadState::READ_OK &&
            state->getMeasureTempTask().getLatestReading().getReadState() == ReadState::READ_OK) {

        int16_t intensity = state->getMeasureLightIntensityTask().getLatestReading().getIntensity();
        int16_t temperature = int16_t(state->getMeasureTempTask().getLatestReading().getTemperatureCelsius() * 10);
        int16_t humidity = int16_t(state->getMeasureTempTask().getLatestReading().getHumidity() * 10);

        LOG_DEBUG1(F("intensity"), intensity);
        LOG_DEBUG1(F("temperature"), temperature);
        LOG_DEBUG1(F("humidity"), humidity);
        LOGGER_DEBUG.println(intensity, 2);
        LOGGER_DEBUG.println(temperature, 2);
        LOGGER_DEBUG.println(humidity, 2);

        for (uint8_t i = 0; i < REPEAT_SENDS; i++) {
            sync();

            // MSB goes first

            // sensor type - 2 for WeatherStation outdoor sensor
            bit0();
            bit0();
            bit1();
            bit0();

            // intensity - 12 bit
            send12bit(intensity);
            // temperature - 12 bit
            send12bit(temperature);
            // humidity - 12 bit
            send12bit(humidity);
        }

        // closing sync
        sync();
        lineUp();

        LOG_DEBUG(F("Sensor data sent."));

    } else {
        LOG_WARN(F("Sensor data not sent. Error or not read."));
    }

}
