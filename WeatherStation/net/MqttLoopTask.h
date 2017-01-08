/*
 * MqttLoopTask.h
 *
 *  Created on: 7. 1. 2017
 *      Author: jindra
 */

#ifndef MQTTLOOPTASK_H_
#define MQTTLOOPTASK_H_

#include <PubSubClient.h>
#include <stdbool.h>
#include <Task.h>
#include <WiFiEspClient.h>

class MqttLoopTask : public Task {

public:
    MqttLoopTask();

    MqttLoopTask(const MqttLoopTask& that) = delete;
    void operator=(const MqttLoopTask& that) = delete;

    virtual void run();

    bool tryConnectLoop();

    static void publishWsPing(PubSubClient& client);

    PubSubClient& getClient() {
        return client;
    }

private:


    WifiEspTimeouts timeouts;
    WiFiEspClient wifiClient;
    PubSubClient client;
    long lastReconnectAttempt = 0;
    bool reconnect();

};

#endif /* MQTTLOOPTASK_H_ */
