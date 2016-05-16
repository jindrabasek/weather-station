/*
 * NetworkTestTask.h
 *
 *  Created on: 19. 4. 2016
 *      Author: jindra
 */

#ifndef NETWORKTESTSCHEDULABLE_H_
#define NETWORKTESTSCHEDULABLE_H_

#include <Schedulable.h>

class NetworkTestSchedulable : public Schedulable {
public:
    NetworkTestSchedulable() {
    }

    NetworkTestSchedulable(const NetworkTestSchedulable& that) = delete;
    void operator=(const NetworkTestSchedulable& that) = delete;

    virtual void run(Task * task);
};

#endif /* NETWORKTESTSCHEDULABLE_H_ */
