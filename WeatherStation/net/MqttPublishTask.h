/*
 * MqttPublishTask.h
 *
 *  Created on: 7. 1. 2017
 *      Author: jindra
 */

#ifndef MQTTPUBLISHTASK_H_
#define MQTTPUBLISHTASK_H_

#include <Task.h>

class MqttPublishTask : public Task {
public:
    MqttPublishTask(unsigned long periodMs);

    MqttPublishTask(const MqttPublishTask& that) = delete;
    void operator=(const MqttPublishTask& that) = delete;

    virtual void run();

private:
    static const int ASSET_ID_MAX_LENGTH = 64;
    static const int FORMAT_TIME_LENGTH = 10;
    static const int VALUE_MAX_LENGTH = 20;
    static const int FLOAT_DIGITS = 1;

};

#endif /* MQTTPUBLISHTASK_H_ */
