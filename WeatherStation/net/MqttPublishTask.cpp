/*
 * MqttPublishTask.cpp
 *
 *  Created on: 7. 1. 2017
 *      Author: jindra
 */

#include "MqttPublishTask.h"

#include <avr/pgmspace.h>
#include <Arduino.h>
#include <defines.h>
#include <HttpClient.h>
#include <IPAddress.h>
#include <Logger.h>
#include <PubSubClient.h>
#include <sensors/SensorFlags.h>
#include <sensors/SensorReading.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <SensorIds.h>
#include <WiFiEspClient.h>
#include <WString.h>
#include <TaskIds.h>

#include "../ProgramState.h"
#include "Network.h"
#include "PublishUtils.h"

#define DEVICE_TOPIC "dev/"
#define WS_TOPIC "weatherSt/"
#define BASE_TOPIC "base/"
#define SENSOR_TOPIC "sensor/"
#define TH1_TOPIC "th1/"
#define PT1_TOPIC "pt1/"
#define L1_TOPIC "l1/"
#ifdef ENABLE_W433_SENSORS
#define REMOTE_TOPIC "remote/"
#define SENCOR_TOPIC "sencor/"
#define SENCOR_CH1_TOPIC "ch1/"
#define SENCOR_CH2_TOPIC "ch2/"
#define SENCOR_CH3_TOPIC "ch3/"
#endif
#define TEMPERATURE_TOPIC "temperature"
#define TEMPERATURE_REAL_FEEL_TOPIC "tempRealFeel"
#define PRESSURE_ABSOLUTE_TOPIC "pressureAbs"
#define PRESSURE_SEA_LEVEL_TOPIC "pressureSea"
#define HUMIDITY_TOPIC "humidity"
#define HUMIDITY_ABSOLUTE_TOPIC "humidityAbs"
#ifdef ENABLE_LIGHT_SENSOR
#define LIGHT_TOPIC "light"
#endif
#define UP_TOPIC "up"

#define WS_DEVICE DEVICE_TOPIC WS_TOPIC
#define BASE_SENSOR WS_DEVICE BASE_TOPIC SENSOR_TOPIC
#define REMOTE_DEV WS_DEVICE REMOTE_TOPIC
#define REMOTE_SENCOR REMOTE_DEV SENCOR_TOPIC
#define REMOTE_WS REMOTE_DEV WS_TOPIC SENSOR_TOPIC

//static const char TIMESTAMP_TOPIC[] PROGMEM = "/timestamp";
//static const char UNIT_TOPIC[] PROGMEM = "/unit";

static const char PRESSURE_ID[] PROGMEM = BASE_SENSOR PT1_TOPIC PRESSURE_ABSOLUTE_TOPIC;
static const char PRESSURE_SEA_LEVEL_ID[] PROGMEM = BASE_SENSOR PT1_TOPIC PRESSURE_SEA_LEVEL_TOPIC;
static const char BMP_TEMPERATURE_ID[] PROGMEM = BASE_SENSOR PT1_TOPIC TEMPERATURE_TOPIC;
#ifdef ENABLE_LIGHT_SENSOR
static const char LIGHT_INTENSITY_ID[] PROGMEM = BASE_SENSOR L1_TOPIC LIGHT_TOPIC;
#endif
static const char DHT_TEMPERTAURE_ID[] PROGMEM = BASE_SENSOR TH1_TOPIC TEMPERATURE_TOPIC;
static const char DHT_TEMPERTAURE_REAL_FEEL_ID[] PROGMEM = BASE_SENSOR TH1_TOPIC TEMPERATURE_REAL_FEEL_TOPIC;
static const char DHT_HUMIDITY_ID[] PROGMEM = BASE_SENSOR TH1_TOPIC HUMIDITY_TOPIC;
static const char ABSOLUTE_HUMIDITY_ID[] PROGMEM = BASE_SENSOR TH1_TOPIC HUMIDITY_ABSOLUTE_TOPIC;
#ifdef ENABLE_W433_SENSORS
static const char TEMPERATURE_SENCOR_CH1_ID[] PROGMEM = REMOTE_SENCOR SENCOR_CH1_TOPIC SENSOR_TOPIC TEMPERATURE_TOPIC;
static const char TEMPERATURE_SENCOR_CH2_ID[] PROGMEM = REMOTE_SENCOR SENCOR_CH2_TOPIC SENSOR_TOPIC TEMPERATURE_TOPIC;
static const char TEMPERATURE_SENCOR_CH3_ID[] PROGMEM = REMOTE_SENCOR SENCOR_CH3_TOPIC SENSOR_TOPIC TEMPERATURE_TOPIC;
static const char LIGHT_INTENSITY_OUTDOOR_ID[] PROGMEM = REMOTE_WS L1_TOPIC LIGHT_TOPIC;
static const char DHT_HUMIDITY_OUTDOOR_ID[] PROGMEM = REMOTE_WS TH1_TOPIC HUMIDITY_TOPIC;
static const char DHT_TEMPERTAURE_REAL_FEEL_OUTDOOR_ID[] PROGMEM = REMOTE_WS TH1_TOPIC TEMPERATURE_REAL_FEEL_TOPIC;
static const char DHT_TEMPERTAURE_OUTDOOR_ID[] PROGMEM = REMOTE_WS TH1_TOPIC TEMPERATURE_TOPIC;
static const char ABSOLUTE_HUMIDITY_OUTDOOR_ID[] PROGMEM = REMOTE_WS TH1_TOPIC HUMIDITY_ABSOLUTE_TOPIC;
#endif

static const char WEATHER_STATION_STATUS_ID[] PROGMEM = WS_DEVICE UP_TOPIC;

static const char* const assetIds[] PROGMEM = { PRESSURE_ID,
        PRESSURE_SEA_LEVEL_ID, BMP_TEMPERATURE_ID
#ifdef ENABLE_LIGHT_SENSOR
		, LIGHT_INTENSITY_ID
#endif
		, DHT_HUMIDITY_ID, DHT_TEMPERTAURE_REAL_FEEL_ID, DHT_TEMPERTAURE_ID,
        ABSOLUTE_HUMIDITY_ID
#ifdef ENABLE_W433_SENSORS
		, TEMPERATURE_SENCOR_CH1_ID, TEMPERATURE_SENCOR_CH2_ID,
        TEMPERATURE_SENCOR_CH3_ID, LIGHT_INTENSITY_OUTDOOR_ID, DHT_HUMIDITY_OUTDOOR_ID,
        DHT_TEMPERTAURE_REAL_FEEL_OUTDOOR_ID, DHT_TEMPERTAURE_OUTDOOR_ID,
        ABSOLUTE_HUMIDITY_OUTDOOR_ID
#endif
};

//#define DATA_UPLOAD_TIME_MEASURE
#ifdef DATA_UPLOAD_TIME_MEASURE
#define perfMeasure() LOG_DEBUG2(F("T"), __LINE__, millis()-t); t = millis();
#else
#define  perfMeasure() ;
#endif

extern ProgramState *state;
using namespace WeatherStation;

MqttPublishTask::MqttPublishTask(unsigned long periodMs) :
        Task(periodMs, true, MqttPublish_Task){
    startAtEarliestOportunity();
}

void MqttPublishTask::run() {
    if (Network::networkConnected() && state->getMqttLoopTask().tryConnectLoop()) {
        LOG_DEBUG(F("Uploading data to MQTT...\n"));

        if (AppStartUploadFlags::isFlag(ReadingUploader::MQTT_LOCAL)) {

            LOG_INFO(F("UP status uploading to MQTT"));

            bool err = false;
            char upTopic[sizeof(WEATHER_STATION_STATUS_ID) + 1];
            strcpy_P(upTopic, WEATHER_STATION_STATUS_ID);

            perfMeasure();

            char value[2] = "1";
            err |= !state->getMqttLoopTask().getClient().publish(upTopic, value, true);

            perfMeasure();

		    if (!err) {
		    	AppStartUploadFlags::statusUploaded(ReadingUploader::MQTT_LOCAL);
		    	LOG_DEBUG(F("UP status uploaded to MQTT"));
		    } else {
		    	LOG_WARN(F("Error uploading UP status to MQTT"));
		    }

		    yield();
		}

        uint8_t sensorIdIdx = 0;

        for (uint8_t i = 0; i < WeatherStation::SensorValueId::SensorsEnumSize;
                i++) {
#ifdef DATA_UPLOAD_TIME_MEASURE
            unsigned long t = millis();
#endif
            SensorReading * sensorValue = state->getSensorValues()[i];
            if (sensorValue != NULL) {
                // upload only if not already uploaded
                if (!SensorFlags::isFlag((SensorValueId) i,
                        ReadingUploader::MQTT_LOCAL)) {
                    char assetId[ASSET_ID_MAX_LENGTH + 1] = { 0 };
                    // if false, value is not registered to be uploaded to cloud
                    bool shouldUpload = PublishUtils::getAssetId(assetId, sensorIdIdx++, assetIds, ASSET_ID_MAX_LENGTH);
                    if (shouldUpload){
                        if (sensorValue->getReadState() == ReadState::READ_OK) {
                            LOG_INFO2(F("Sensor data uploading to MQTT"), i, assetId);

                            double doubleValue = sensorValue->getDoubleValue(i, false);
                            uint8_t valueLenght = PublishUtils::numberOfDigits(doubleValue, FLOAT_DIGITS);

                            perfMeasure();

                            bool err = false;

                            char value[valueLenght + 1];
                            dtostrf(doubleValue, valueLenght, 1, value);
                            state->getMqttLoopTask().getWifiClient().beginPacket();
                            err |= !state->getMqttLoopTask().getClient().publish(assetId, value, true);
                            state->getMqttLoopTask().getWifiClient().endPacket();

                            // not working or too slow - will have to fix pubsubclient to open/close packets explicitly
                            /*perfMeasure();

                            char assetIdBuffer[ASSET_ID_MAX_LENGTH + 1] = { 0 };
                            strncpy(assetIdBuffer, assetId, ASSET_ID_MAX_LENGTH);
                            strcat_P(assetIdBuffer, TIMESTAMP_TOPIC);
                            char timestamp[FORMAT_TIME_LENGTH + 1];
                            ultoa(sensorValue->getTimeStamp(), timestamp, 10);
                            err |= !state->getMqttLoopTask().getClient().publish(assetIdBuffer, timestamp, true);

                            perfMeasure();

                            strncpy(assetIdBuffer, assetId, ASSET_ID_MAX_LENGTH);
                            strcat_P(assetIdBuffer, UNIT_TOPIC);
                            WeatherStation::SensorValueUnit valueUnit = sensorValue->valueUnit(i, false);
                            uint8_t unitLength = WeatherStation::SensorValueUnits::sensorUnitNameLength(valueUnit);
                            char unit[unitLength + 1];
                            WeatherStation::SensorValueUnits::getSensorUnit(unit, valueUnit);
                            err |= !state->getMqttLoopTask().getClient().publish(assetIdBuffer, unit, true);*/

                            perfMeasure();

                            if (!err) {
                                SensorFlags::writeFlag((SensorValueId) i, true,
                                        ReadingUploader::MQTT_LOCAL);
                                LOG_DEBUG2(F("Sensor data uploaded to MQTT"), i, assetId);
                            } else {
                                LOG_WARN1(F("Error uploading sensor data to MQTT"), assetId);
                            }

                            yield();
                        } else {
                            LOG_WARN2(
                                    F("Sensor data not uploaded to MQTT. Error or not read "),
                                    i, assetId);
                        }
                    }
                } else {
                    LOG_INFO1(F("Sensor data already uploaded to MQTT"), i);
                }
            }
            yield();
        }

        LOG_INFO(F("Sensor data uploaded to MQTT"));
    } else {
        LOG_WARN(F("Cannot upload data, network not connected or MQTT."));
    }
}
