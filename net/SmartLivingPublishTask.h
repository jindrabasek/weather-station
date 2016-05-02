/*
 * SmartLivingPublishTask.h
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#ifndef SMARTLIVINGPUBLISHTASK_H_
#define SMARTLIVINGPUBLISHTASK_H_

#include <Print.h>
#include <stdint.h>
#include <Task.h>

class SmartLivingPublishTask  : public Task {
public:
    SmartLivingPublishTask(unsigned long periodMs);

    SmartLivingPublishTask(const SmartLivingPublishTask& that) = delete;
    void operator=(const SmartLivingPublishTask& that) = delete;

    virtual void run();

private:
    static const int ASSET_ID_LENGTH = 24;
    static const int PATH_FORMAT_LENGTH = 15;
    static const int FORMAT_TIME_LENGTH = 25;

    void getAssetId(char* buffer, uint8_t valueId);
    void formatTime(Print & out, unsigned long timeStamp);
};


#endif /* SMARTLIVINGPUBLISHTASK_H_ */
