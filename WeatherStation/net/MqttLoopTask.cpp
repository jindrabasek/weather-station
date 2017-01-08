/*
 * MqttLoopTask.cpp
 *
 *  Created on: 7. 1. 2017
 *      Author: jindra
 */

#include "MqttLoopTask.h"

#include <avr/pgmspace.h>
#include <Arduino.h>
#include <Logger.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time/Clock.h>

#include "../config.h"
#include "Network.h"
#include "WifiWatchdogTask.h"

#define RECONNECT_INTERVAL 30000

static const char WS_NAME[] PROGMEM = "WeatherStation";
static const char WS_TIMESTAMP[] PROGMEM = "dev/weatherSt/timestamp";
static const char MQTT_ADDRESS[] PROGMEM = MQTT_LOCAL_ADDRESS;

MqttLoopTask::MqttLoopTask() :
        Task(2000000),
        wifiClient(&timeouts),
        client(wifiClient) {
    startAtEarliestOportunity();
    timeouts.setConnectionTimeoutTcp(5000)->setReadTimeout(5000);
}

bool MqttLoopTask::tryConnectLoop() {
    bool connected = false;
    if (Network::networkConnected()) {
        if (!client.connected()) {
            long now = millis();
            if (now - lastReconnectAttempt > RECONNECT_INTERVAL) {
                lastReconnectAttempt = now;
                // Attempt to reconnect
                connected = reconnect();
                if (connected) {
                    lastReconnectAttempt = 0;
                    LOG_INFO(F("Connecting to MQTT complete"));
                } else {
                    LOG_WARN(F("Connecting to MQTT failed"));
                }
                WifiWatchdogTask::aliveOrNot(connected);
            }
        } else {
            // Client connected
            connected = true; //client.loop();
            WifiWatchdogTask::aliveOrNot(true);
        }
    } else {
        LOG_WARN(F("Cannot connect to MQTT, network not connected."));
    }
    return connected;
}

void MqttLoopTask::run() {
    tryConnectLoop();
}

void MqttLoopTask::publishWsPing(PubSubClient& client) {
    // publish current timestamp to device/weatherStation/timestamp

    char wsTimestamp[sizeof(WS_TIMESTAMP)];
    strcpy_P(wsTimestamp, WS_TIMESTAMP);
    char timestamp[11];
    ultoa(Clock::getTime(true).timeStamp, timestamp, 10);
    client.publish(wsTimestamp, timestamp, true);
    LOG_INFO(F("Client subscribed to MQTT"));
}

bool MqttLoopTask::reconnect() {
    LOG_INFO(F("Attempting to connect to MQTT"));

    char address[sizeof(MQTT_ADDRESS)];
    strcpy_P(address, MQTT_ADDRESS);

    char wsName[sizeof(WS_NAME)];
    strcpy_P(wsName, WS_NAME);
    if (client.connect(address, MQTT_LOCAL_PORT, wsName)) {
        LOG_INFO(F("Connected to MQTT"));
        publishWsPing(client);
    }
    return client.connected();
}

