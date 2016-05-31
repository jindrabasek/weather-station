/*
 * SetTaskFrequencyAction.cpp
 *
 *  Created on: 21. 2. 2016
 *      Author: jindra
 */

#include "SetTaskFrequencyAction.h"

#include <Task.h>

#include "../ProgramSettings.h"
#include "../ProgramState.h"

extern ProgramState *state;

SetTaskFrequencyAction::SetTaskFrequencyAction(
        Task & target, unsigned int (ProgramSettings::*period)() const,
        uint8_t multiplierSec) :
        target(target),
        period(period),
        multiplierSec(multiplierSec) {
}

void SetTaskFrequencyAction::doAction() {
    target.setPeriodUs(
            (long)((state->getSettings().*period)()) * multiplierSec * ProgramSettings::ONE_SEC_IN_US);
}
