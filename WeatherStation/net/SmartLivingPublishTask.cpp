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
#include <Logger.h>
#include <sensors/SensorFlags.h>
#include <sensors/SensorReading.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <SensorIds.h>
#include <WiFiEspClient.h>
#include <WireRtcLib.h>
#include <WString.h>

#include "../config.h"
#include "../ProgramSettings.h"
#include "../ProgramState.h"
#include "Network.h"

static const char PRESSURE_ID[] PROGMEM = SMART_LIVING_SENSOR_ID_PRESSURE;
static const char PRESSURE_SEAL_LEVEL_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_PRESSURE_SEAL_LEVEL;
static const char BMP_TEMPERATURE_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_BMP_TEMPERATURE;
static const char LIGHT_INTENSITY_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_LIGHT_INTENSITY;
static const char DHT_TEMPERTAURE_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_DHT_TEMPERTAURE;
static const char DHT_TEMPERTAURE_REAL_FEEL_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_DHT_TEMPERTAURE_REAL_FEEL;
static const char DHT_HUMIDITY_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_DHT_HUMIDITY;
static const char ABSOLUTE_HUMIDITY_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_ABSOLUTE_HUMIDITY;
static const char * TEMPERATURE_SENCOR_CH1_ID
= NULL;
static const char TEMPERATURE_SENCOR_CH2_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_TEMPERATURE_SENCOR_CH2;
static const char * TEMPERATURE_SENCOR_CH3_ID
= NULL;
static const char LIGHT_INTENSITY_OUTDOOR_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_LIGHT_INTENSITY_OUTDOOR;
static const char DHT_HUMIDITY_OUTDOOR_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_DHT_HUMIDITY_OUTDOOR;
static const char DHT_TEMPERTAURE_REAL_FEEL_OUTDOOR_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_DHT_TEMPERTAURE_REAL_FEEL_OUTDOOR;
static const char DHT_TEMPERTAURE_OUTDOOR_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_DHT_TEMPERTAURE_OUTDOOR;
static const char ABSOLUTE_HUMIDITY_OUTDOOR_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_ABSOLUTE_HUMIDITY_OUTDOOR;

static const char* const assetIds[] PROGMEM = { PRESSURE_ID,
        PRESSURE_SEAL_LEVEL_ID, BMP_TEMPERATURE_ID, LIGHT_INTENSITY_ID,
        DHT_TEMPERTAURE_ID, DHT_TEMPERTAURE_REAL_FEEL_ID, DHT_HUMIDITY_ID,
        ABSOLUTE_HUMIDITY_ID, TEMPERATURE_SENCOR_CH1_ID, TEMPERATURE_SENCOR_CH2_ID,
        TEMPERATURE_SENCOR_CH3_ID, LIGHT_INTENSITY_OUTDOOR_ID, DHT_HUMIDITY_OUTDOOR_ID,
        DHT_TEMPERTAURE_REAL_FEEL_OUTDOOR_ID, DHT_TEMPERTAURE_OUTDOOR_ID,
        ABSOLUTE_HUMIDITY_OUTDOOR_ID };

static const char PATH_FORMAT[] PROGMEM = "/asset/%s/state";
static const char SMART_LIVING_IP[] PROGMEM = "65.52.140.212";

//#define DATA_UPLOAD_TIME_MEASURE
#ifdef DATA_UPLOAD_TIME_MEASURE
#define perfMeasure() LOG_DEBUG2(F("T"), __LINE__, millis()-t); t = millis();
#else
#define  perfMeasure() ;
#endif

extern ProgramState *state;

SmartLivingPublishTask::SmartLivingPublishTask(unsigned long periodMs) :
        Task(periodMs) {
    startAtEarliestOportunity();
}

using namespace WeatherStation;

void SmartLivingPublishTask::run() {
    if (Network::networkConnected()) {
        LOG_DEBUG(F("Uploading data...\n"));

        uint8_t sensorIdIdx = 0;
        uint8_t toUpload = 0;
        uint8_t uploadSucceded = 0;

        char smartLivingIp[sizeof(SMART_LIVING_IP)];
        strcpy_P(smartLivingIp, SMART_LIVING_IP);

        for (uint8_t i = 0; i < WeatherStation::SensorValueId::SensorsEnumSize;
                i++) {
#ifdef DATA_UPLOAD_TIME_MEASURE
            unsigned long t = millis();
#endif
            SensorReading * sensorValue = state->getSensorValues()[i];
            if (sensorValue != NULL) {
                // upload only if not already uploaded
                if (!SensorFlags::isFlag((SensorValueId) i,
                        ReadingUploader::SMART_LIVING)) {
                    char assetId[ASSET_ID_LENGTH + 1] = { 0 };
                    // if false, value is not registered to be uploaded to cloud
                    bool shouldUpload = getAssetId(assetId, sensorIdIdx++);
                    if (shouldUpload){
                        if (sensorValue->getReadState() == ReadState::READ_OK) {
                            toUpload++;
                            LOG_INFO2(F("Sensor data uploading"), i, assetId);

                            WiFiEspClient client;
                            client.setUseSsl(true);
                            HttpClient http(client);
                            perfMeasure();
                            http.beginRequest();
                            char path[ASSET_ID_LENGTH + sizeof(PATH_FORMAT)] = { 0 };
                            char pathFormat[sizeof(PATH_FORMAT)];
                            strcpy_P(pathFormat, PATH_FORMAT);
                            sprintf(path, pathFormat, assetId);
                            client.beginPacket();

                            double value = sensorValue->getValue(i, false);
                            uint8_t valueLenght = numberOfDigits(value);

                            if (LOG_LEVEL >= LOGGER_LEVEL_DEBUG) {
                                LOGGER_DEBUG.printTime();
                                LOGGER_DEBUG.print(path);
                                LOGGER_DEBUG.print(' ');
                                LOGGER_DEBUG.print(value, FLOAT_DIGITS);
                                LOGGER_DEBUG.print(' ');
                                formatTime(LOGGER_DEBUG, sensorValue->getTimeStamp());
                                LOGGER_DEBUG.println();
                            }

                            perfMeasure();
                            int err = http.put(smartLivingIp, 443, path);
                            perfMeasure();
                            if (err == 0) {
                                client.println(
                                        F("Auth-ClientId: " SMART_LIVING_CLIENT_ID));
                                client.println(
                                        F("Auth-ClientKey: " SMART_LIVING_CLIENT_KEY));
                                client.print(F("Content-Length: "));
                                perfMeasure();

                                client.println(
                                        valueLenght + FORMAT_TIME_LENGTH + 30);
                                perfMeasure();

                                client.println(
                                        F("Content-Type: application/json; charset=utf-8"));
                                http.endRequest();

                                perfMeasure();

                                client.println('{');
                                client.print(F("\"value\": "));
                                client.print(value, FLOAT_DIGITS);
                                client.println(',');
                                perfMeasure();
                                client.print(F("\"at\": \""));
                                formatTime(client, sensorValue->getTimeStamp());
                                client.println('\"');
                                client.println('}');
                                client.println();
                                perfMeasure();
                            }
                            client.endPacket();
                            perfMeasure();
                            // to improve UI response
                            yield();
                            perfMeasure();
                            if (err == 0) {
                                uploadSucceded++;
                                // mark reading was uploaded
                                SensorFlags::writeFlag((SensorValueId) i, true,
                                        ReadingUploader::SMART_LIVING);
                                LOG_DEBUG2(F("Sensor data uploaded"), i, assetId);
                            } else {
                                LOG_WARN2(F("Error uploading sensor data"), assetId,
                                        err);
                            }

                            http.receiveAndPrintResponse(err, LOGGER_DEBUG, LOGGER_DEBUG);

                            perfMeasure();
                            Logger.flush();
                            http.stop();
                            perfMeasure();
                        } else {
                            LOG_WARN2(
                                    F("Sensor data not uploaded. Error or not read "),
                                    i, assetId);
                        }
                    }
                } else {
                    LOG_INFO1(F("Sensor data already uploaded"), i);
                }
            }
            yield();
        }

        WifiWatchdogTask::aliveOrNot(toUpload == uploadSucceded);

        LOG_INFO(F("Sensor data uploaded"));
    } else {
        LOG_WARN(F("Cannot upload data, network not connected."));
    }
}

bool SmartLivingPublishTask::getAssetId(char* buffer, uint8_t valueId) {
    char* assetIdAddr = (char*) pgm_read_word(&(assetIds[valueId]));
    if (assetIdAddr == NULL) {
        return false;
    }
    strcpy_P(buffer, assetIdAddr);
    return true;
}

#define printTimePart(timePart, separator) if(timePart < 10) out.print('0'); itoa(timePart, buffer, 10); out.print(buffer); out.print(separator)
void SmartLivingPublishTask::formatTime(Print & out, unsigned long timeStamp) {
    ProgramSettings & settings = state->getSettings();

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

size_t SmartLivingPublishTask::numberOfDigits(double number) {
    size_t n = 0;

    if (isnan(number) || isinf(number) || number > 4294967040.0
            || number < -4294967040.0) {
        return 3;
    }

    // Handle negative numbers
    if (number < 0.0) {
        n++;
    }

    unsigned long int_part = (unsigned long) number;

    do {
        n++;
        int_part /= 10;
    } while (int_part);

    n +=2;

    return n;
}
