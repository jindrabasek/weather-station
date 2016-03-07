/*
 * SetTaskFrequencyAction.cpp
 *
 *  Created on: 21. 2. 2016
 *      Author: jindra
 */

#include "SetTaskFrequencyAction.h"
#include "../ProgramSettings.h"

SetTaskFrequencyAction::SetTaskFrequencyAction(Task& target,
		unsigned long & periodSec) :
		target(target),
		periodSec(periodSec){
}

void SetTaskFrequencyAction::doAction() {
	target.setPeriodMs(periodSec * ProgramSettings::ONE_SEC_IN_MS);
}
