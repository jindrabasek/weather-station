/*
 * SetLongTaskFrequencyAction.cpp
 *
 *  Created on: 22. 4. 2016
 *      Author: jindra
 */

#include "SetLongTaskFrequencyAction.h"

#include <LongTask.h>

#include "../ProgramSettings.h"
#include "../ProgramState.h"

extern ProgramState *state;

SetLongTaskFrequencyAction::SetLongTaskFrequencyAction(
        LongTask & target, unsigned int (ProgramSettings::*periodHours)() const) :
        target(target),
        periodHours(periodHours) {
}

void SetLongTaskFrequencyAction::doAction() {
    target.setPeriod(
                (state->getSettings().*periodHours)(), 0);
}
