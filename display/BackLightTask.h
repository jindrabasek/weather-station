/*
 * BackLightTask.h
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#ifndef BACKLIGHTTASK_H_
#define BACKLIGHTTASK_H_

#include <Task.h>
#include <LCD.h>

class BackLightTask: public Task {
private:
	LCD & display;

//-----------------------------------------------------------------------------

public:
	BackLightTask(LCD & display);

	BackLightTask(const BackLightTask& that) = delete;
	void operator=(const BackLightTask& that) = delete;

	virtual void run();

};

#endif /* BACKLIGHTTASK_H_ */
