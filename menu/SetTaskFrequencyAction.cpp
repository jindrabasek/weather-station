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

	Serial.println("SetTaskFrequencyAction"); delay(100);

}

void SetTaskFrequencyAction::doAction() {
	target.setPeriodMs(periodSec * ProgramSettings::ONE_SEC_IN_MS);
}
