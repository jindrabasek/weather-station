/*
 * SmartLivingPublishTask.h
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#ifndef SMARTLIVINGPUBLISHSCHEDULABLE_H_
#define SMARTLIVINGPUBLISHSCHEDULABLE_H_

#include <Print.h>
#include <stdint.h>
#include <Schedulable.h>
#include <Task.h>

class SmartLivingPublishSchedulable  : public Schedulable {
public:
    SmartLivingPublishSchedulable() {

    }

    SmartLivingPublishSchedulable(const SmartLivingPublishSchedulable& that) = delete;
    void operator=(const SmartLivingPublishSchedulable& that) = delete;

    virtual void run(Task * task);

private:
    static const int ASSET_ID_LENGTH = 24;
    static const int FORMAT_TIME_LENGTH = 25;

    static void getAssetId(char* buffer, uint8_t valueId);
    static void formatTime(Print & out, unsigned long timeStamp);
};


#endif /* SMARTLIVINGPUBLISHSCHEDULABLE_H_ */
