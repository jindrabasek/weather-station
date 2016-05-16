/*
 * TimeSyncTask.h
 *
 *  Created on: 17. 3. 2016
 *      Author: jindra
 */

#ifndef TIMESYNCSCHEDULABLE_H_
#define TIMESYNCSCHEDULABLE_H_

#include <Schedulable.h>
#include <Task.h>

class TimeSyncSchedulable : public Schedulable {
public:
    virtual void run(Task * task);
};

#endif /* TIMESYNCSCHEDULABLE_H_ */
