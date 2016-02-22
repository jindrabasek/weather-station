/*
 * SetTaskFrequencyAction.h
 *
 *  Created on: 21. 2. 2016
 *      Author: jindra
 */

#ifndef SETTASKFREQUENCYACTION_H_
#define SETTASKFREQUENCYACTION_H_

#include <MenuAction.h>
#include <Task.h>

class SetTaskFrequencyAction: public MenuAction {
private:
	Task & target;
	unsigned long & periodSec;
public:
	SetTaskFrequencyAction(Task & target, unsigned long & periodSec);
	virtual void doAction();
};

#endif /* SETTASKFREQUENCYACTION_H_ */
