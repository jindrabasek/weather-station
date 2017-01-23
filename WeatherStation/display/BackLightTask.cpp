/*
 * BackLightTask.cpp
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#include "BackLightTask.h"

#include <LCD.h>
#include <stdbool.h>
#include <Task.h>
#include <TaskIds.h>

#include "../ProgramState.h"

extern ProgramState *state;

BackLightTask::BackLightTask(LCD & display) :
        Task(0, false, BackLight_Task),
        display(display) {
}

void BackLightTask::run() {
    if (state->isBackLight()) {
        display.backlight();
    } else {
        display.noBacklight();
    }
    setEnabled(false);
}
