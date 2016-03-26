/*
 * TimeSyncTask.h
 *
 *  Created on: 17. 3. 2016
 *      Author: jindra
 */

#ifndef TIMESYNCTASK_H_
#define TIMESYNCTASK_H_

#include <LongTask.h>

class TimeSyncTask: public LongTask {
public:
	TimeSyncTask(unsigned long periodHours, bool enabled = true);

protected:
	virtual void run();
};

#endif /* TIMESYNCTASK_H_ */
