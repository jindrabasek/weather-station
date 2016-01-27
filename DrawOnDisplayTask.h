/*
 * TempPrintToDisplayTask.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef DRAWONDISPLAYTASK_H_
#define DRAWONDISPLAYTASK_H_

#include <Task.h>

#include <LCD.h>
#include "ToDraw.h"

class DrawOnDisplayTask: public Task {
private:
	LCD & display;
	ToDraw * toDraw;
	bool clear;

//-----------------------------------------------------------------------------

public:
	DrawOnDisplayTask(unsigned long periodMs, LCD & display, ToDraw * toDraw);
	virtual void run();

	void setToDraw(ToDraw * toDraw, bool clearFirst = false) {
		this->toDraw = toDraw;
		this->clear = clearFirst;
	}
};

#endif /* DRAWONDISPLAYTASK_H_ */
