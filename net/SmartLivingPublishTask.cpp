/*
 * SmartLivingPublishTask.cpp
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#include "SmartLivingPublishTask.h"

#include <avr/pgmspace.h>
#include <Arduino.h>
#include <HttpClient.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <WiFiEspClient.h>
#include <WireRtcLib.h>
#include <WString.h>

#include "../Logger.h"
#include "../PeripheryReading.h"
#include "../ProgramSettings.h"
#include "../ProgramState.h"
#include "../sensors/SensorReading.h"
#include "../sensors/Sensors.h"
#include "Network.h"

const char PRESSURE_ID[] PROGMEM = "***REMOVED***";
const char PRESSURE_SEAL_LEVEL_ID[] PROGMEM = "***REMOVED***";
const char BMP_TEMPERATURE_ID[] PROGMEM = "***REMOVED***";
const char LIGHT_INTENSITY_ID[] PROGMEM = "***REMOVED***";
const char DHT_TEMPERTAURE_ID[] PROGMEM = "***REMOVED***";
const char DHT_TEMPERTAURE_REAL_FEEL_ID[] PROGMEM = "***REMOVED***";
const char DHT_HUMIDITY_ID[] PROGMEM = "***REMOVED***";

const char PATH_FORMAT[] PROGMEM = "/asset/%s/state";

const char* const assetIds[] PROGMEM = { PRESSURE_ID, PRESSURE_SEAL_LEVEL_ID,
        BMP_TEMPERATURE_ID, LIGHT_INTENSITY_ID, DHT_TEMPERTAURE_ID,
        DHT_TEMPERTAURE_REAL_FEEL_ID, DHT_HUMIDITY_ID, PATH_FORMAT };

SmartLivingPublishTask::SmartLivingPublishTask(unsigned long periodMs) :
        Task(periodMs) {
    startAtEarliestOportunity();
}

void SmartLivingPublishTask::run() {
    if (Network::networkConnected()) {
        LOG_DEBUG(F("Uploading data...\n"));

        ProgramState & state = ProgramState::instance();
        for (uint8_t i = 0; i < WeatherStation::Sensors::sensorsEnumSize; i++) {
            SensorReading * sensorValue = state.getSensorValues()[i];
            char assetId[ASSET_ID_LENGTH + 1] = { 0 };
            getAssetId(assetId, i);
            if (sensorValue->getReadState() == ReadState::READ_OK) {
                LOG_INFO1(F("Sensor data uploading "), assetId);

                WiFiEspClient client;
                client.setUseSsl(true);
                HttpClient http(client);

                http.beginRequest();
                char path[ASSET_ID_LENGTH + PATH_FORMAT_LENGTH + 1] = { 0 };
                char pathFormat[PATH_FORMAT_LENGTH + 1] = { 0 };
                strcpy_P(pathFormat, (char*) pgm_read_word(&(assetIds[WeatherStation::Sensors::sensorsEnumSize])));
                sprintf(path, pathFormat, assetId);
                client.beginPacket();
                int err = http.put("65.52.140.212", 443, path);
                if (err == 0) {
                    // to improve UI response
                    yield();
                    client.println(F("Auth-ClientId: jindra"));
                    client.println(F("Auth-ClientKey: ***REMOVED***"));
                    client.print(F("Content-Length: "));
                    // to improve UI response
                    yield();
                    client.println(
                            WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH
                                    + FORMAT_TIME_LENGTH + 30);
                    client.println(F("Content-Type: application/json; charset=utf-8"));
                    http.endRequest();

                    // to improve UI response
                    yield();
                    client.println('{');
                    client.print(F("\"value\": "));
                    sensorValue->printValue(i, client);
                    client.println(',');
                    // to improve UI response
                    yield();
                    client.print(F("\"at\": \""));
                    formatTime(client, sensorValue->getTimeStamp());
                    client.println('\"');
                    client.println('}');
                    client.println();

                    // to improve UI response
                    yield();
                }
                client.endPacket();
                // to improve UI response
                yield();
                http.receiveAndPrintResponse(err, LOGGER_DEBUG, LOGGER_DEBUG);
                Logger.flush();
                http.stop();

            } else {
                LOG_WARN1(F("Sensor data not uploaded. Error or not read "), assetId);
            }
            yield();
        }
        LOG_INFO(F("Sensor data uploaded"));
    } else {
        LOG_WARN(F("Cannot upload data, network not connected."));
    }
}

void SmartLivingPublishTask::getAssetId(char* buffer, uint8_t valueId) {
    strcpy_P(buffer, (char*) pgm_read_word(&(assetIds[valueId])));
}

#define printTimePart(timePart, separator) if(timePart < 10) out.print('0'); itoa(timePart, buffer, 10); out.print(buffer); out.print(separator)
void SmartLivingPublishTask::formatTime(Print & out, unsigned long timeStamp) {
    ProgramSettings & settings = ProgramState::instance().getSettings();

    WireRtcLib::tm time = WireRtcLib::breakTime(timeStamp);
    char buffer[5];

    printTimePart(time.year, '-');
    printTimePart(time.mon, '-');
    printTimePart(time.mday, 'T');
    printTimePart(time.hour, ':');
    printTimePart(time.min, ':');
    printTimePart(time.sec, settings.getTimeZone() < 0 ? '-' : '+');
    printTimePart(settings.getTimeZone(), F(":00"));
}

