/*
 * SmartLivingPublishTask.h
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#ifndef LOGREADINGSTASK_H_
#define LOGREADINGSTASK_H_

#include <Print.h>
#include <stdint.h>
#include <Task.h>

class LogReadingsTask  : public Task {
public:
    LogReadingsTask(unsigned long periodMs);

    LogReadingsTask(const LogReadingsTask& that) = delete;
    void operator=(const LogReadingsTask& that) = delete;

    virtual void run();
};


#endif /* LOGREADINGSTASK_H_ */
