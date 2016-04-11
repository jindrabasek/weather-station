/*
 * TimeSyncTask.cpp
 *
 *  Created on: 17. 3. 2016
 *      Author: jindra
 */

#include "TimeSyncTask.h"

TimeSyncTask::TimeSyncTask(unsigned long periodHours, bool enabled) :
        LongTask(periodHours, 0, enabled) {
}

void TimeSyncTask::run() {
}
