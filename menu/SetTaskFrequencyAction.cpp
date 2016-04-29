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

SetTaskFrequencyAction::SetTaskFrequencyAction(
        Task & target, unsigned int (ProgramSettings::*period)() const,
        unsigned long multiplier) :
        target(target),
        period(period),
        multiplier(multiplier) {
}

void SetTaskFrequencyAction::doAction() {
    target.setPeriodUs(
            (ProgramState::instance().getSettings().*period)() * multiplier);
}
