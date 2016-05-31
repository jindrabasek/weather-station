/*
 * NetworkTestTask.h
 *
 *  Created on: 19. 4. 2016
 *      Author: jindra
 */

#ifndef NETWORKTESTTASK_H_
#define NETWORKTESTTASK_H_

#include <Task.h>

class NetworkTestTask : public Task {
public:
    NetworkTestTask();

    NetworkTestTask(const NetworkTestTask& that) = delete;
    void operator=(const NetworkTestTask& that) = delete;

    virtual void run();
};

#endif /* NETWORKTESTTASK_H_ */
