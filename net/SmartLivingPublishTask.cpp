/*
 * SmartLivingPublishTask.cpp
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#include "SmartLivingPublishTask.h"

#include <avr/pgmspace.h>
#include <HardwareSerial.h>
#include <HttpClient.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <WiFiEspClient.h>
#include <WireRtcLib.h>
#include <WString.h>

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
    ProgramState & state = ProgramState::instance();

    if (state.getNetwork().networkConnected()) {
        Serial.println(F("Uploading data...\n"));

        for (int i = 0; i < WeatherStation::Sensors::sensorsEnumSize; i++) {
            SensorReading * sensorValue = state.getSensorValues()[i];
            char assetId[ASSET_ID_LENGTH + 1] = { 0 };
            getAssetId(assetId, i);
            if (sensorValue->getReadState() == ReadState::READ_OK) {
                Serial.print(F("Sensor data uploading "));
                Serial.println(assetId);

                WiFiEspClient client;
                client.setUseSsl(true);
                HttpClient http(client);

                http.beginRequest();
                char path[ASSET_ID_LENGTH + PATH_FORMAT_LENGTH + 1] = { 0 };
                char pathFormat[PATH_FORMAT_LENGTH + 1] = { 0 };
                strcpy_P(pathFormat, (char*) pgm_read_word(&(assetIds[WeatherStation::Sensors::sensorsEnumSize])));
                sprintf(path, pathFormat, assetId);
                int err = http.put("65.52.140.212", 443, path);
                if (err == 0) {
                    client.println(F("Auth-ClientId: jindra"));
                    client.println(F("Auth-ClientKey: ***REMOVED***"));
                    client.print(F("Content-Length: "));
                    client.println(
                            WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH
                                    + FORMAT_TIME_LENGTH + 30);
                    client.println(F("Content-Type: application/json; charset=utf-8"));
                    http.endRequest();

                    client.println('{');
                    client.print(F("\"value\": "));
                    sensorValue->printValue(i, client);
                    client.println(',');
                    client.print(F("\"at\": \""));
                    formatTime(client, sensorValue->getTimeStamp());
                    client.println('\"');
                    client.println('}');
                    client.println();
                }
                http.receiveAndPrintResponse(err);
                http.stop();

            } else {
                Serial.print(F("Sensor data not uploaded, error or not read "));
                Serial.println(assetId);
            }
            yield();
        }
        Serial.println(F("Sensor data uploaded"));
    } else {
        Serial.println(F("Cannot upload data, network not connected."));
    }
}

void SmartLivingPublishTask::getAssetId(char* buffer, int valueId) {
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

