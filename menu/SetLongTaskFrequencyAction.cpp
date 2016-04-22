/*
 * SetLongTaskFrequencyAction.cpp
 *
 *  Created on: 22. 4. 2016
 *      Author: jindra
 */

#include "SetLongTaskFrequencyAction.h"

#include <LongTask.h>


SetLongTaskFrequencyAction::SetLongTaskFrequencyAction(LongTask& target,
                                               unsigned long & periodHours) :
        target(target),
        periodHours(periodHours) {
}

void SetLongTaskFrequencyAction::doAction() {
    target.setPeriod(periodHours, 0);
}
