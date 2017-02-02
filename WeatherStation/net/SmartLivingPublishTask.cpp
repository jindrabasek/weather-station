/*
 * SmartLivingPublishTask.cpp
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#include "SmartLivingPublishTask.h"

#include <avr/pgmspace.h>
#include <Arduino.h>
#include <defines.h>
#include <HttpClient.h>
#include <Logger.h>
#include <sensors/SensorFlags.h>
#include <sensors/SensorReading.h>
#include <stdio.h>
#include <SensorIds.h>
#include <time/Clock.h>
#include <TaskIds.h>
#include <WiFiEspClient.h>
#include <WString.h>

#include "../config.h"
#include "../ProgramState.h"
#include "AppStartUploadFlags.h"
#include "Network.h"
#include "PublishUtils.h"
#include "WifiWatchdogTask.h"

static const char PRESSURE_ID[] PROGMEM = SMART_LIVING_SENSOR_ID_PRESSURE;
static const char PRESSURE_SEA_LEVEL_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_PRESSURE_SEA_LEVEL;
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

static const char WEATHER_STATION_STATUS_ID[] PROGMEM
= SMART_LIVING_SENSOR_ID_WEATHER_STATION_STATUS;

static const char* const assetIds[] PROGMEM = { PRESSURE_ID,
        PRESSURE_SEA_LEVEL_ID, BMP_TEMPERATURE_ID, LIGHT_INTENSITY_ID,
        DHT_TEMPERTAURE_ID, DHT_TEMPERTAURE_REAL_FEEL_ID, DHT_HUMIDITY_ID,
        ABSOLUTE_HUMIDITY_ID, TEMPERATURE_SENCOR_CH1_ID, TEMPERATURE_SENCOR_CH2_ID,
        TEMPERATURE_SENCOR_CH3_ID, LIGHT_INTENSITY_OUTDOOR_ID, DHT_HUMIDITY_OUTDOOR_ID,
        DHT_TEMPERTAURE_REAL_FEEL_OUTDOOR_ID, DHT_TEMPERTAURE_OUTDOOR_ID,
        ABSOLUTE_HUMIDITY_OUTDOOR_ID };

static const char PATH_FORMAT[] PROGMEM = "/asset/%s/state";
static const char SMART_LIVING_IP[] PROGMEM = "api.allthingstalk.io";

//#define DATA_UPLOAD_TIME_MEASURE
#ifdef DATA_UPLOAD_TIME_MEASURE
#define perfMeasure() LOG_DEBUG2(F("T"), __LINE__, millis()-t); t = millis();
#else
#define  perfMeasure() ;
#endif

extern ProgramState *state;

SmartLivingPublishTask::SmartLivingPublishTask(unsigned long periodMs) :
        Task(periodMs, true, SmartLivingPublish_Task) {
    startAtEarliestOportunity();
}

using namespace WeatherStation;

void SmartLivingPublishTask::run() {
    if (Network::networkConnected()) {
        LOG_DEBUG(F("Uploading data to AllThings...\n"));

        uint8_t sensorIdIdx = 0;
        uint8_t toUpload = 0;
        uint8_t uploadSucceded = 0;


		char pathFormat[sizeof(PATH_FORMAT)];
		strcpy_P(pathFormat, PATH_FORMAT);

        char smartLivingIp[sizeof(SMART_LIVING_IP)];
        strcpy_P(smartLivingIp, SMART_LIVING_IP);

		if (AppStartUploadFlags::isFlag(ReadingUploader::SMART_LIVING)) {
			LOG_INFO(F("UP status uploading to AllThings"));
			WiFiEspClient client;
			client.setUseSsl(true);
			HttpClient http(client);
			perfMeasure();
			http.beginRequest();
			char statusId[sizeof(WEATHER_STATION_STATUS_ID)];
			strcpy_P(statusId, WEATHER_STATION_STATUS_ID);
			char path[ASSET_ID_LENGTH + sizeof(PATH_FORMAT) + 1] = { 0 };
			sprintf(path, pathFormat, statusId);
			client.beginPacket();
			perfMeasure();
			int err = http.put(smartLivingIp, 443, path);
			perfMeasure();
			if (err == 0) {
				client.println(F("Auth-ClientId: " SMART_LIVING_CLIENT_ID));
				client.println(F("Auth-ClientKey: " SMART_LIVING_CLIENT_KEY));
				client.print(F("Content-Length: "));
				perfMeasure();

				client.println(1 + FORMAT_TIME_LENGTH + 30);
				perfMeasure();

				client.println(
						F("Content-Type: application/json; charset=utf-8"));
				http.endRequest();

				perfMeasure();

				client.println('{');
				client.print(F("\"value\": "));

				client.print(1);

				client.println(',');
				perfMeasure();
				client.print(F("\"at\": \""));
				PublishUtils::formatTime(client, Clock::getTime(false).timeStamp);
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
				http.receiveAndPrintResponse(err, LOGGER_DEBUG, LOGGER_DEBUG);

				if (err == 0) {
					// mark reading was uploaded
					AppStartUploadFlags::statusUploaded(ReadingUploader::SMART_LIVING);
					LOG_DEBUG(F("UP status uploaded to AllThings"));
				} else {
					LOG_WARN(F("Error receiving UP status upload confirmation"));
				}
			} else {
				LOG_WARN1(F("Error uploading UP status to AllThings"), err);
			}

			perfMeasure();
			Logger.flush();
			http.stop();
			perfMeasure();
		}

        for (uint8_t i = 0; i < SensorValueId::SensorsEnumSize;
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
                    bool shouldUpload = PublishUtils::getAssetId(assetId, sensorIdIdx++, assetIds, ASSET_ID_LENGTH);
                    if (shouldUpload){
                        if (sensorValue->getReadState() == ReadState::READ_OK) {
                            toUpload++;
                            LOG_INFO2(F("Sensor data uploading to AllThings"), i, assetId);

                            WiFiEspClient client;
                            client.setUseSsl(true);
                            HttpClient http(client);
                            perfMeasure();
                            http.beginRequest();
                            char path[ASSET_ID_LENGTH + sizeof(PATH_FORMAT)] = { 0 };
                            sprintf(path, pathFormat, assetId);
                            client.beginPacket();

                            ValueType valueType = sensorValue->getValueType(i, false);

                            double doubleValue = 0;
                            long longValue = 0;
                            uint8_t valueLenght = 0;

                            switch (valueType) {
                                case ValueType::NA:
                                    LOG_ERROR1(F("NA Value type - you asked for non existing sensor"), i);
                                    valueLenght = 3; // for "err" string
                                    break;
                                case ValueType::DOUBLE:
                                    doubleValue = sensorValue->getDoubleValue(i, false);
                                    valueLenght = PublishUtils::numberOfDigits(doubleValue, FLOAT_DIGITS);
                                    break;
                                case ValueType::LONG:
                                    longValue = sensorValue->getDoubleValue(i, false);
                                    valueLenght = PublishUtils::numberOfDigits(longValue);
                                    break;
                            }

                            if (LOG_LEVEL >= LOGGER_LEVEL_DEBUG) {
                                LOGGER_DEBUG.printTimeAndLevel(LOGGER_LEVEL_DEBUG);
                                LOGGER_DEBUG.print(path);
                                LOGGER_DEBUG.print(' ');

                                switch (valueType) {
                                    case ValueType::NA:
                                        LOGGER_DEBUG.print(F("err"));
                                        break;
                                    case ValueType::DOUBLE:
                                        LOGGER_DEBUG.print(doubleValue, FLOAT_DIGITS);
                                        break;
                                    case ValueType::LONG:
                                        LOGGER_DEBUG.print(longValue);
                                        break;
                                }

                                LOGGER_DEBUG.print(' ');
                                PublishUtils::formatTime(LOGGER_DEBUG, sensorValue->getTimeStamp());
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

                                switch (valueType) {
                                    case ValueType::NA:
                                        client.print(F("err"));
                                        break;
                                    case ValueType::DOUBLE:
                                        client.print(doubleValue, FLOAT_DIGITS);
                                        break;
                                    case ValueType::LONG:
                                        client.print(longValue);
                                        break;
                                }

                                client.println(',');
                                perfMeasure();
                                client.print(F("\"at\": \""));
                                PublishUtils::formatTime(client, sensorValue->getTimeStamp());
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
                                http.receiveAndPrintResponse(err, LOGGER_DEBUG, LOGGER_DEBUG);

                                if (err == 0) {
                                    uploadSucceded++;
                                    // mark reading was uploaded
                                    SensorFlags::writeFlag((SensorValueId) i, true,
                                            ReadingUploader::SMART_LIVING);
                                    LOG_DEBUG2(F("Sensor data uploaded to AllThings"), i, assetId);
                                } else {
                                    LOG_WARN2(F("Error receiving upload confirmation"), assetId,
                                                                            err);
                                }
                            } else {
                                LOG_WARN2(F("Error uploading sensor data to AllThings"), assetId,
                                        err);
                            }

                            perfMeasure();
                            Logger.flush();
                            http.stop();
                            perfMeasure();
                        } else {
                            LOG_WARN2(
                                    F("Sensor data not uploaded to AllThings. Error or not read "),
                                    i, assetId);
                        }
                    }
                } else {
                    LOG_INFO1(F("Sensor data already uploaded to AllThings"), i);
                }
            }
            yield();
        }

        WifiWatchdogTask::aliveOrNot(toUpload == uploadSucceded);

        LOG_INFO(F("Sensor data uploaded to AllThings"));
    } else {
        LOG_WARN(F("Cannot upload data to AllThings, network not connected."));
    }
}
